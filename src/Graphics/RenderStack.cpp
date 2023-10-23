//
// Created by VrikkaDev on 16/10/2023.
//

#include "RenderStack.h"
#include "Scene/Components/Renderable3D.h"

namespace DuckEngine {
    RenderStack::RenderStack() {

    }

    void RenderStack::Render() {
        for(const auto& r3 : m_3dQueue){

        }
    }

    void RenderStack::AddRenderable3D(std::unique_ptr<Renderable3D> renderable) {
        m_3dQueue.push_back(std::move(renderable));
    }

    void RenderStack::RemoveRenderable3d(std::unique_ptr<Renderable3D> renderable) {
        m_3dQueue.erase(std::find(m_3dQueue.begin(), m_3dQueue.end(), renderable));
    }
} // DuckEngine