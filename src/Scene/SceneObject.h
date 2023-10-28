//
// Created by VrikkaDev on 02/10/2023.
//

#ifndef DUCKENGINE_SCENEOBJECT_H
#define DUCKENGINE_SCENEOBJECT_H

#include "Core/Constants.h"
#include "Scene.h"

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
            m_Components = other.m_Components;
            ObjectName = other.ObjectName;
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
        Component& AddComponent(Args&&... args) {

            // Checks if object already has the component and return that if so.
            if(HasComponent<T>()){
                Component& co = GetComponent<T>();
                std::cout<< "Object already has component " << co.ToString() << std::endl;
                return co;
            }


            // Adds the component with args
            auto& r = m_Scene->objectRegistry.emplace<T>(m_Entt, std::forward<Args>(args)...);
            Component& co = r;

            m_Components.push_back(&co);

            // Call OnComponentAttached event to this object, and OnAttached to the component
            this->OnComponentAttached(co);
            co.OnAttached(this);
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

            m_Components.erase(std::find(m_Components.begin(), m_Components.end(), (Component&)(this->GetComponent<T>())));

            // Call OnRemove on the component before removing it
            (Component&)(this->GetComponent<T>()).OnRemove();

            m_Scene->objectRegistry.remove<T>(m_Entt);
        }

        template<typename T>
        Component& GetComponent(){

            if(!this->HasComponent<T>()){
                std::cout<<"Trying to get component that doesnt exist.." << std::endl;
                // TODO handle
            }

            return m_Scene->objectRegistry.get<T>(m_Entt);
        }

        std::vector<Component*> GetComponents(){
            return m_Components;
        }

        // Updates object components
        virtual void OnUpdate(float dt);

        // Gets called when is object added to a scene
        virtual void OnStart(){}

        // Gets called right when this object gets destroyed
        virtual void OnDestroy();

        // Gets called when component gets added to this object
        virtual void OnComponentAttached(const Component& component) {
        };

        UUIDv4::UUID GetUUID(){
            return m_Uuid;
        }

        Scene* GetScene(){
            return m_Scene;
        }

        bool isEnabled = true;

        virtual const std::string ToString();
        // TODO better naming system, maybe name as init variable? number suffix?
        std::string ObjectName = "SceneObject";

    private:
        entt::entity m_Entt;
        Scene* m_Scene = nullptr;
        UUIDv4::UUID m_Uuid; // Might be unnecessary, could use the entity_type above?

        std::vector<Component*> m_Components{};
    };

} // DuckEngine

#endif //DUCKENGINE_SCENEOBJECT_H
