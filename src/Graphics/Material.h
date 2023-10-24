//
// Created by VrikkaDev on 24/10/2023.
//

#ifndef DUCKENGINE_MATERIAL_H
#define DUCKENGINE_MATERIAL_H


namespace DuckEngine {

    struct Material {

        std::unique_ptr<Shader> shader;

        virtual void Bind();
        virtual void UnBind();
    };

} // DuckEngine

#endif //DUCKENGINE_MATERIAL_H
