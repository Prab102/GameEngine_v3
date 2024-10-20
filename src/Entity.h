#pragma once
#include "Components.h"
#include <memory>
#include <string>
#include <tuple>
//cpp


class EnitytManager;

typedef std::tuple<
    CTransform,
    CLifespan,
    CInput,
    CBoundingBox,
    CAnimation,
    CGravity,
    CState
> ComponentTuple;

class Entity{

    friend class EntityManager;

    size_t         m_id     = 0;
    std::string    m_tag    = "default";
    bool           m_active = true;
    ComponentTuple m_components;
 
    //std::get<CState>(m_components);   example use

    //constructor and destructor 
    Entity(const size_t id, const std::string& tag);

    public:

        //component pointers
        // std::shared_ptr<CTransform> cTransform;
        // std::shared_ptr<CShape> cShape;
        // std::shared_ptr<CCollision> cCollision;
        // std::shared_ptr<CInput> cInput;
        // std::shared_ptr<CScore> cScore;
        // std::shared_ptr<CLifespan> cLifespan;

        //private member access functions
        bool isActive() const;
        const std::string & tag() const;
        const size_t id()const;
        void destroy();

        // templated functions
        template <typename T>
        T& getComponent() {
            return std::get<T>(m_components);
        }

        template <typename T>
        const T& getComponent() const {
            return std::get<T>(m_components);
        }

        template <typename T>
        bool hasComponent() const {
            return getComponent<T>().has;
        }

        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&... m_args) {
            // std::cout<< "testing";
            auto& component = getComponent<T>();
            component = T(std::forward<TArgs>(m_args)...);
            component.has = true;
            return component;
        }

        template <typename T>
        void removeComponent() {
            getComponent<T>() = T();
        }


};