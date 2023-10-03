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
        using entity_type = std::uint32_t;
        static constexpr auto null = entt::null;

        constexpr explicit SceneObject(entity_type value = null, Scene* scene = nullptr) noexcept
        : m_Entt{value}, m_Scene{scene} {
            m_Uuid = uuidGenerator.getUUID();
        }

        constexpr SceneObject(const SceneObject &other) noexcept
                : m_Entt{other.m_Entt}, m_Scene{other.m_Scene} {
            m_Uuid = other.m_Uuid;
        }

        constexpr explicit operator entity_type() const noexcept {
            return m_Entt;
        }

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args){
            return m_Scene->objectRegistry.emplace<T>(m_Entt, std::forward<Args>(args)...);
        }

        template<typename T>
        bool HasComponent() {
            return m_Scene->objectRegistry.any_of<T>(m_Entt);
        }

        template<typename T>
        void RemoveComponent() {
            m_Scene->objectRegistry.remove<T>(m_Entt);
        }

        void OnUpdate(float dt);

        UUIDv4::UUID GetUUID(){
            return m_Uuid;
        }

    private:
        entity_type m_Entt;
        Scene* m_Scene = nullptr;
        UUIDv4::UUID m_Uuid;
    };

} // DuckEngine

#endif //DUCKENGINE_SCENEOBJECT_H
