#pragma once
#include "Scene.h"
#include "Assets.h"
#include "SoundManager.h"


#include <memory>
//cpp
// typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{
    protected:

        sf::RenderWindow       m_window;
        Assets                 m_assets;
        SoundManager           m_soundmanager;
        std::string            m_currentScene;
        std::map<std::string, std::shared_ptr<Scene>>               m_sceneMap;
        size_t                 m_simulationSpeed = 1;
        bool                   m_running = true;
        // std::vector<std::string>   m_levelPaths;

        void init(const std::string & path);
        void update();

        void sUserInput();

        std::shared_ptr<Scene> currentScene();
    
    public:

        GameEngine(const std::string & path);
        ~GameEngine();

        void changeScene(const std::string & sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);

        void quit();
        void run();

        sf::RenderWindow & window();
        // const Assets & assets() const;
        const Assets & assets() const;

        SoundManager & soundmanager();
        //based off current scene set the music

        bool isRunning();

};