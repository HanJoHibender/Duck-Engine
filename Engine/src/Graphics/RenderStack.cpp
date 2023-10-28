//
// Created by VrikkaDev on 16/10/2023.
//

#include "RenderStack.h"
#include "Scene/Components/Renderable3D.h"
#include "Scene/Objects/Camera.h"

namespace DuckEngine {
    RenderStack::RenderStack() {

    }

    void RenderStack::Render(Camera* camera) {
        for(const auto& r3 : m_3dQueue){

            // If doesnt have transform component dont draw.
            if(!r3->GetObject()->HasComponent<Transform>()){
                continue;
            }
            auto& trans = r3->GetObject()->GetComponent<Transform>();
            r3->model->Draw(camera, dynamic_cast<const Transform&>(trans));
        }
    }

    void RenderStack::AddRenderable3D(Renderable3D* renderable) {
        m_3dQueue.push_back(renderable);
    }

    void RenderStack::RemoveRenderable3d(Renderable3D* renderable) {
        m_3dQueue.erase(std::find(m_3dQueue.begin(), m_3dQueue.end(), renderable));
    }
} // DuckEngine