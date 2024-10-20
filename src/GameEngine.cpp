#include "GameEngine.h"

#include "Assets.h"
// #include "Scene.h"
#include "Scene_Play.h"
#include "Scene_Menu.h"
#include <SFML/Audio.hpp>


GameEngine::GameEngine(const std::string & path)
{
    init(path);  //path is assets file
}

void GameEngine::init(const std::string & path)
{
    // std::cout << "makes it here first";
    m_assets.loadFromFile(path);     
    // std::cout << "makes it here second";

    m_window.create(sf::VideoMode(1280,768), "Definitley Not Mario");
    m_window.setFramerateLimit(60);
    
    // std::cout << "makes it here second";
    // m_levelPaths.push_back("level1.txt");
    // std::cout << m_running && m_window.isOpen();

    changeScene("Menu", std::make_shared<Scene_Menu>(this), false);   

    // changeScene("PLAY", std::make_shared<Scene_Play>(this, m_levelPaths[0]));
    // std::cout << "makes it here last";

}

std::shared_ptr<Scene> GameEngine::currentScene() 
{
    return m_sceneMap[m_currentScene];
}

bool GameEngine::isRunning()
{
    // std::cout << m_running && m_window.isOpen();
    return m_running && m_window.isOpen();
}

sf::RenderWindow & GameEngine::window()
{
    return m_window;
}

void GameEngine::update()
{
    // where everything updates;
    // m_window.clear();
    if (!isRunning()) { 
        // std::cout << "not running ";
        return; }
	
	if (m_sceneMap.empty()) { return; }
    // std::cout << "running";
	sUserInput();
    // std::cout << m_currentScene;
	currentScene()->simulate(m_simulationSpeed);
	currentScene()->sRender(); //this is what will show everything up on screen might be causing the problem
	m_window.display();
}
void GameEngine::run()
{
    // main gaim loop
    // std::cout << "makes it here lalalala";
    sf::Music music;
        if (!music.openFromFile("/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/Mega Man 2 - Dr. Wilys Castle.wav")){
                std::cout << "BAD SOUND";
        }
        music.setVolume(20);
        // music.play();

        if (music.getStatus() == sf::SoundSource::Status::Stopped) {
            music.openFromFile("/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/oceanman.wav");
            music.play();
	    }
        

    while(isRunning())
    {
        // std::cout << "makes it here";
        update();

    }
}

//User input is handled in the GameEngine and an action is created, then the action is sent to the the specific scene that 
void GameEngine::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            quit();
        }
        
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::X)
            {
                std::cout << "screenshot saved to " << "test.png" <<std::endl;
                sf::Texture texture;
                texture.create(m_window.getSize().x, m_window.getSize().y);
                texture.update(m_window);
                if(texture.copyToImage().saveToFile("test.png"))
                {
                    std::cout << "screenshot saved to " << "test.png" << std::endl;
                }
            }
        }

        if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            if(currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end())
            {
                // std::cout << "no action";
                continue;
            }
            //sets action type based on key 
            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

            currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));

        }


    }
}


void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
    //to change scene currentscene needs to be set
    //change current scene string 
    // and lookup that new current scene  in scene map and store
    // std::cout << "makes it here changescene ";

    // if (endCurrentScene){
    //     m_sceneMap.erase(m_currentScene);
    // }
    // m_currentScene = sceneName;
    // m_sceneMap[m_currentScene] = scene;
    if (endCurrentScene)
	{
		m_sceneMap.erase(m_sceneMap.find(m_currentScene));
	}
    if (scene) 
	{ 
		m_sceneMap[sceneName] = scene;

	}
	else
	{
		if (m_sceneMap.find(sceneName) == m_sceneMap.end())
		{
			std::cerr << "Warning: Scene does not exist: " << sceneName << std::endl;
			return;
		}
	}

	m_currentScene = sceneName;

    // std::cout<< m_currentScene;
    

}

void GameEngine::quit()
{
    m_running = false;
}

const Assets & GameEngine::assets() const
{
    return m_assets;
}

