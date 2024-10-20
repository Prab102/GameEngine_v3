#pragma once

#include "Scene.h"
#include <map>
#include <memory>
#include <deque>

#include "EntityManager.h"
#include "GameEngine.h"

class Scene_Menu : public Scene
{
    protected:

        std::string                m_title;
        std::vector<std::string>   m_menuStrings;
        std::vector<std::string>   m_levelPaths;
        sf::Text                   m_menuText;
        size_t                     m_selectedMenuIndex = 0;

        void init();
        void update() override;
        void onEnd();
        void sDoAction(const Action & action) override;
    
    public:

        Scene_Menu(GameEngine * gameEngine = nullptr);
        void sRender() override;


};
