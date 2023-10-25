//
// Created by VrikkaDev on 24/10/2023.
//

#ifndef DUCKENGINE_MODEL_H
#define DUCKENGINE_MODEL_H

#include "Mesh.h"
#include "Material.h"

namespace DuckEngine {

    class Model {
    public:
        Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

        void Draw();

        Mesh* GetMesh(){
            return m_Mesh.get();
        }

        Material* GetMaterial(){
            return m_Material.get();
        }

    private:
        std::shared_ptr<Mesh> m_Mesh;
        std::shared_ptr<Material> m_Material;
    };

} // DuckEngine

#endif //DUCKENGINE_MODEL_H
