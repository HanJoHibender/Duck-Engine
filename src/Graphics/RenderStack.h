//
// Created by VrikkaDev on 16/10/2023.
//

#ifndef DUCKENGINE_RENDERSTACK_H
#define DUCKENGINE_RENDERSTACK_H

namespace DuckEngine {

    class Renderable3D;

    class RenderStack {
    public:
        RenderStack();

        void AddRenderable3D(std::unique_ptr<Renderable3D> renderable);
        void RemoveRenderable3d(std::unique_ptr<Renderable3D> renderable);

        void Render();
    private:
        std::vector<std::unique_ptr<Renderable3D>> m_3dQueue;
    };

} // DuckEngine

#endif //DUCKENGINE_RENDERSTACK_H
