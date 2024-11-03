#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <vector>

class Assets;

class SoundManager {
public:
    
    void addSound(const std::string & soundName,const std::string & path);
    void playSound(const std::string& soundName);
    const sf::Sound & getSound(const std::string & soundName) const;

    SoundManager();

    void loadSounds(const std::string & path);

   
private:

    std::map<std::string, sf::SoundBuffer> m_soundMap; // Declare the sound map
    std::vector<sf::Sound> m_sounds; // Store active sound objects
};