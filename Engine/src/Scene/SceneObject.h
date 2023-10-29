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
        explicit SceneObject(Scene* scene = nullptr, const UUID uuid = UUID()) noexcept
        : m_Scene{scene} {
        }

        SceneObject(const SceneObject &other) noexcept
                : m_Uuid{other.m_Uuid}, m_Scene{other.m_Scene} {
            m_Uuid = other.m_Uuid;
            m_Components = other.m_Components;
            ObjectName = other.ObjectName;
        }

        // Initializes scene variables if didnt create object using Scene::CreateObject
        // Gets called from Scene::AddObject
        void SetScene(Scene* scene){
            m_Scene = scene;
        }

        template<typename T, typename... Args>
        Component* AddComponent(Args&&... args) {

            // Checks if object already has the component and return that if so.
            if(HasComponent<T>()){
                Component* co = GetComponent<T>();
                std::cout<< this->ToString() << " already has component " << co->ToString() << std::endl;
                return co;
            }


            // Adds the component with args
            Component* r = m_Components[std::type_index(typeid(T))] = new T(std::forward<Args>(args)...);

            // Call OnComponentAttached event to this object, and OnAttached to the component
            this->OnComponentAttached(*r);
            r->OnAttached(this);
            return r;
        }

        template<typename T>
        bool HasComponent() {
            return m_Components.find(std::type_index(typeid(T))) != m_Components.end();
        }

        template<typename T>
        void RemoveComponent() {

            auto it = m_Components.find(std::type_index(typeid(T)));
            if (it != m_Components.end()) {
                // Call OnRemove on the component before removing it
                (Component&)(this->GetComponent<T>()).OnRemove();
                m_Components.erase(it);
            }

        }

        template<typename T>
        Component* GetComponent(){

            // Check if has component and if doesnt return nullptr
            if(!this->HasComponent<T>()){
                std::cout<<"Trying to get component that doesnt exist.." << std::endl;
                return nullptr;
            }

            auto it = m_Components.find(std::type_index(typeid(T)));
            if (it != m_Components.end()) {
                return dynamic_cast<T*>(it->second);
            }

            return nullptr;
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

        UUID GetUUID(){
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
        Scene* m_Scene = nullptr;
        UUID m_Uuid;

        std::unordered_map<std::type_index, Component*> m_Components{};
    };

} // DuckEngine

#endif //DUCKENGINE_SCENEOBJECT_H
