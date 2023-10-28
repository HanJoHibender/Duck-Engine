//
// Created by VrikkaDev on 16/10/2023.
//

#ifndef DUCKENGINE_COLOR_H
#define DUCKENGINE_COLOR_H
namespace DuckEngine {

    class Color{
    public:
        Color(){
            this->r = 0;
            this->g = 0;
            this->b = 0;
            this->a = 1.f;
        }
        Color(float r, float g, float b, float a){
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

        float GetR() const{
            return this->r;
        }
        float GetG() const{
            return this->g;
        }
        float GetB() const{
            return this->b;
        }
        float GetA() const{
            return this->a;
        }

        float r, g, b, a;
    };

} // DuckEngine
#endif //DUCKENGINE_COLOR_H
