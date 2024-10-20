#include "Scene_Menu.h"
#include "Scene_Play.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Components.h"
#include "Action.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Vec2.h"

Scene_Menu::Scene_Menu(GameEngine* gameEngine)
    : Scene(gameEngine)
{
    // std::cout << "makes it to init";

    init();
}

void Scene_Menu::init()
{
    // std::cout << "makes it to init";
   
    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::D, "SELECT");
    registerAction(sf::Keyboard::Escape, "QUIT");

    m_title = "Mega Mario";
    m_menuStrings.push_back("Level  1");
    // m_menuStrings.push_back("Level  2");
    // m_menuStrings.push_back("Level  3");

    m_levelPaths.push_back("/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/level1.txt");
    // std::cout << "makes it here";
    
    m_menuText.setFont(m_game->assets().getFont("Megaman"));

    // std::cout << "makes it after setFont";
    m_menuText.setCharacterSize(64);
}
void Scene_Menu::update()
{
    m_entityManager.update();

    // std::cout << "comes to this update";

    sRender();

}

void Scene_Menu::sRender()
{
    // clear the window to a blue
    // std::cout << "before render";

    m_game->window().setView(m_game->window().getDefaultView());
    m_game->window().clear(sf::Color(100, 100, 255));

    // draw the game title in the top-left of the screen
    m_menuText.setCharacterSize(48);
    m_menuText.setString(m_title);
    m_menuText.setFillColor(sf::Color::Black);
    m_menuText.setPosition(sf::Vector2f(10, 10));
    m_game->window().draw(m_menuText);

    // draw all of the menu options
    for (size_t i = 0; i < m_menuStrings.size(); i++)
    {
        m_menuText.setString(m_menuStrings[i]);
        m_menuText.setFillColor(i == m_selectedMenuIndex ? sf::Color::White : sf::Color(0, 0, 0));
        m_menuText.setPosition(sf::Vector2f(10, 110 + i * 72));
        m_game->window().draw(m_menuText);
    }

    // draw the controls in the bottom-left
    m_menuText.setCharacterSize(20);
    m_menuText.setFillColor(sf::Color::Black);
    m_menuText.setString("up: w     down: s    play: d      back: esc");
    m_menuText.setPosition(sf::Vector2f(10, 690));

    m_game->window().draw(m_menuText);

    m_game->window().display();
}

void Scene_Menu::sDoAction(const Action& action)
{
    if (action.type() == "START")
    {
        if (action.name() == "QUIT")
        { 
            onEnd(); 
        }
        else if (action.name() == "SELECT") 
        { 
            m_game->changeScene("PLAY", std::make_shared<Scene_Play>(m_game, m_levelPaths[m_selectedMenuIndex]));
        }
        else if (action.name() == "UP") 
        { 
            if (m_selectedMenuIndex > 0) { m_selectedMenuIndex -= 1; }
            else { m_selectedMenuIndex = m_menuStrings.size() - 1; } 
        }
        else if (action.name() == "DOWN")
        {
            m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_menuStrings.size();
        }

    }

}

void Scene_Menu::onEnd()
{
    m_game->quit();
}

