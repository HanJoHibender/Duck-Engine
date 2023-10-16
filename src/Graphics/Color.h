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
            this->a = 100;
        }
        Color(int r, int g, int b, int a){
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

        int GetR() const{
            return this->r;
        }
        int GetG() const{
            return this->g;
        }
        int GetB() const{
            return this->b;
        }
        int GetA() const{
            return this->a;
        }

    private:
        int r, g, b, a;
    };

} // DuckEngine
#endif //DUCKENGINE_COLOR_H
