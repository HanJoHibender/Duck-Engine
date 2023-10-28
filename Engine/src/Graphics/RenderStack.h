//
// Created by VrikkaDev on 16/10/2023.
//

#ifndef DUCKENGINE_RENDERSTACK_H
#define DUCKENGINE_RENDERSTACK_H

namespace DuckEngine {

    class Renderable3D;
    class Camera;

    class RenderStack {
    public:
        RenderStack();

        void AddRenderable3D(Renderable3D* renderable);
        void RemoveRenderable3d(Renderable3D* renderable);

        void Render(Camera* camera);
    private:
        std::vector<Renderable3D*> m_3dQueue;
    };

} // DuckEngine

#endif //DUCKENGINE_RENDERSTACK_H
