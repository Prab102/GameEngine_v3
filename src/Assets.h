#pragma once
#include "Animation.h"
#include <map>
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
#include "SoundManager.h"

// #include <ifstream>
//cpp
class SoundManager;

class Assets
{
    std::map<std::string, sf::Texture>     m_textureMap;
    std::map<std::string,  Animation>      m_animationMap;
    std::map<std::string,  sf::Font>       m_fontMap;

    // SoundManager                           m_soundManager;

    //SOUND STUFF
    // std::map<std::string, sf::SoundBuffer> m_soundMap; // Declare the sound map
    // std::vector<sf::Sound> m_sounds; // Store active sound objects
    // std::map<std::string,  sf::SoundBuffer>      m_soundMap;

    void addTexture(const std::string & textureName, const std::string & path, bool smooth = true);
    void addAnimation(const std::string & animationName, const std::string & textureName, size_t frameCount, size_t speed);
    void addFont(const std::string & fontName, const std::string & path);
    // bool addSound(const std::string & soundName,const std::string & path);

    public:

    Assets();

    void loadFromFile(const std::string & path);

    const sf::Texture & getTexture(const std::string & textureName) const;
    const Animation &   getAnimation(const std::string & animationName) const;
    const sf::Font &    getFont(const std::string & fontName) const;
    // std::shared_ptr<sf::Sound> getSound(const std::string & soundName);
    
    //SOUND STUFF
    // void addSound(const std::string & soundName,const std::string & path);
    // const void playSound(const std::string& soundName) ;
    // const sf::Sound & getSound(const std::string & soundName) const;

   

    // void loadSounds(const std::string & path); //THIS SHOULD BE IN LOAD FROMFILE
};