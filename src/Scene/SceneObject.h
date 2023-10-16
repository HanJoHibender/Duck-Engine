//
// Created by VrikkaDev on 02/10/2023.
//

#ifndef DUCKENGINE_SCENEOBJECT_H
#define DUCKENGINE_SCENEOBJECT_H

#include "Scene.h"
#include "Core/Constants.h"

namespace DuckEngine {

    class SceneObject {
    public:
        static constexpr auto null = entt::null;

        explicit SceneObject(entt::entity value = null, Scene* scene = nullptr) noexcept
        : m_Entt{value}, m_Scene{scene} {
            m_Uuid = uuidGenerator.getUUID();
        }

        SceneObject(const SceneObject &other) noexcept
                : m_Entt{other.m_Entt}, m_Scene{other.m_Scene} {
            m_Uuid = other.m_Uuid;
        }

        // Initializes scene variables if didnt create object using Scene::CreateObject
        // Gets called from Scene::AddObject
        void setupWithScene(Scene* scene, entt::entity entity){
            m_Scene = scene;
            m_Entt = entity;
        }

        explicit operator entt::entity() const noexcept {
            return m_Entt;
        }

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args) {
            // Adds the component with args
            auto& r = m_Scene->objectRegistry.emplace<T>(m_Entt, std::forward<Args>(args)...);
            auto& c = static_cast<Component&>(r);
            // Call OnComponentAttached event to this object, and OnAttached to the component
            this->OnComponentAttached(c);
            c.OnAttached(this);
            return r;
        }

        template<typename T>
        bool HasComponent() {
            return m_Scene->objectRegistry.any_of<T>(m_Entt);
        }

        template<typename T>
        void RemoveComponent() {

            // Return if this object doesn't have the component
            if(!this->HasComponent<T>()){
                return;
            }

            // Call OnRemove on the component before removing it
            static_cast<Component>(this->GetComponent<T>()).OnRemove();

            m_Scene->objectRegistry.remove<T>(m_Entt);
        }

        template<typename T>
        T& GetComponent(){
            return m_Scene->objectRegistry.get<T>(m_Entt);
        }

        // Updates object components
        virtual void OnUpdate(float dt);

        // Gets called right when this object gets destroyed
        virtual void OnDestroy();

        // Gets called when component gets added to this object
        virtual void OnComponentAttached(const Component& component) {};

        UUIDv4::UUID GetUUID(){
            return m_Uuid;
        }

        Scene* GetScene(){
            return m_Scene;
        }

    private:
        entt::entity m_Entt;
        Scene* m_Scene = nullptr;
        UUIDv4::UUID m_Uuid; // Might be unnecessary, could use the entity_type above?
    };

} // DuckEngine

#endif //DUCKENGINE_SCENEOBJECT_H
