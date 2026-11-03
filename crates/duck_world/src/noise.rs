//! Deterministic Perlin gradient noise and fractal Brownian motion (fBm) generator.

pub struct PerlinNoise {
    perm: [u8; 512],
}

impl Default for PerlinNoise {
    fn default() -> Self {
        Self::new(1337)
    }
}

impl PerlinNoise {
    pub fn new(seed: u32) -> Self {
        let mut p: [u8; 256] = [0; 256];
        for i in 0..256 {
            p[i] = i as u8;
        }

        // Simple LCG shuffle based on seed
        let mut state = seed as u64;
        for i in (1..256).rev() {
            state = state.wrapping_mul(6364136223846793005).wrapping_add(1);
            let j = (state >> 33) as usize % (i + 1);
            p.swap(i, j);
        }

        let mut perm = [0u8; 512];
        for i in 0..512 {
            perm[i] = p[i & 255];
        }

        Self { perm }
    }

    #[inline]
    fn fade(t: f64) -> f64 {
        t * t * t * (t * (t * 6.0 - 15.0) + 10.0)
    }

    #[inline]
    fn lerp(t: f64, a: f64, b: f64) -> f64 {
        a + t * (b - a)
    }

    #[inline]
    fn grad2(hash: u8, x: f64, y: f64) -> f64 {
        let h = hash & 7;
        let u = if h < 4 { x } else { y };
        let v = if h < 4 { y } else { x };
        (if (h & 1) == 0 { u } else { -u }) + (if (h & 2) == 0 { v } else { -v })
    }

    #[inline]
    fn grad3(hash: u8, x: f64, y: f64, z: f64) -> f64 {
        let h = hash & 15;
        let u = if h < 8 { x } else { y };
        let v = if h < 4 {
            y
        } else if h == 12 || h == 14 {
            x
        } else {
            z
        };
        (if (h & 1) == 0 { u } else { -u }) + (if (h & 2) == 0 { v } else { -v })
    }

    pub fn noise2d(&self, x: f64, y: f64) -> f64 {
        let xi = x.floor() as i64;
        let yi = y.floor() as i64;

        let xf = x - x.floor();
        let yf = y - y.floor();

        let u = Self::fade(xf);
        let v = Self::fade(yf);

        let aa = self.perm[(self.perm[(xi & 255) as usize] as usize + (yi & 255) as usize) & 511];
        let ab = self.perm[(self.perm[(xi & 255) as usize] as usize + ((yi + 1) & 255) as usize) & 511];
        let ba = self.perm[(self.perm[((xi + 1) & 255) as usize] as usize + (yi & 255) as usize) & 511];
        let bb = self.perm[(self.perm[((xi + 1) & 255) as usize] as usize + ((yi + 1) & 255) as usize) & 511];

        let x1 = Self::lerp(u, Self::grad2(aa, xf, yf), Self::grad2(ba, xf - 1.0, yf));
        let x2 = Self::lerp(u, Self::grad2(ab, xf, yf - 1.0), Self::grad2(bb, xf - 1.0, yf - 1.0));

        Self::lerp(v, x1, x2)
    }

    pub fn noise3d(&self, x: f64, y: f64, z: f64) -> f64 {
        let xi = x.floor() as i64;
        let yi = y.floor() as i64;
        let zi = z.floor() as i64;

        let xf = x - x.floor();
        let yf = y - y.floor();
        let zf = z - z.floor();

        let u = Self::fade(xf);
        let v = Self::fade(yf);
        let w = Self::fade(zf);

        let a = self.perm[(xi & 255) as usize] as usize + (yi & 255) as usize;
        let aa = self.perm[a & 511] as usize + (zi & 255) as usize;
        let ab = self.perm[(a + 1) & 511] as usize + (zi & 255) as usize;

        let b = self.perm[((xi + 1) & 255) as usize] as usize + (yi & 255) as usize;
        let ba = self.perm[b & 511] as usize + (zi & 255) as usize;
        let bb = self.perm[(b + 1) & 511] as usize + (zi & 255) as usize;

        let c1 = Self::grad3(self.perm[aa & 511], xf, yf, zf);
        let c2 = Self::grad3(self.perm[ba & 511], xf - 1.0, yf, zf);
        let c3 = Self::grad3(self.perm[ab & 511], xf, yf - 1.0, zf);
        let c4 = Self::grad3(self.perm[bb & 511], xf - 1.0, yf - 1.0, zf);

        let c5 = Self::grad3(self.perm[(aa + 1) & 511], xf, yf, zf - 1.0);
        let c6 = Self::grad3(self.perm[(ba + 1) & 511], xf - 1.0, yf, zf - 1.0);
        let c7 = Self::grad3(self.perm[(ab + 1) & 511], xf, yf - 1.0, zf - 1.0);
        let c8 = Self::grad3(self.perm[(bb + 1) & 511], xf - 1.0, yf - 1.0, zf - 1.0);

        let x1 = Self::lerp(u, c1, c2);
        let x2 = Self::lerp(u, c3, c4);
        let y1 = Self::lerp(v, x1, x2);

        let x3 = Self::lerp(u, c5, c6);
        let x4 = Self::lerp(u, c7, c8);
        let y2 = Self::lerp(v, x3, x4);

        Self::lerp(w, y1, y2)
    }

    /// Fractal Brownian Motion (octaves) for realistic procedural hills and terrain.
    pub fn fbm2d(&self, x: f64, y: f64, octaves: usize, persistence: f64, lacunarity: f64) -> f64 {
        let mut total = 0.0;
        let mut frequency = 1.0;
        let mut amplitude = 1.0;
        let mut max_value = 0.0;

        for _ in 0..octaves {
            total += self.noise2d(x * frequency, y * frequency) * amplitude;
            max_value += amplitude;
            amplitude *= persistence;
            frequency *= lacunarity;
        }

        total / max_value
    }
}

