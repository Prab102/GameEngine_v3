#include <SFML/Audio.hpp>
// #pragma once
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include "SoundManager.h"

SoundManager::SoundManager()
{

}
void SoundManager::loadSounds(const std::string & path)
{   

    //this should read in from a file and add sounds if everything is correct
    addSound("scream",path);
    addSound("burp","/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/burp.wav");
    // "/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/burp.wav"

}
void SoundManager::addSound(const std::string & soundName, const std::string & path)
{
    // sf::SoundBuffer buffer;
	// // load something into the sound buffer...
	// buffer.loadFromFile(path);
		sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(path)) {
            std::cout << "NO FILE FOUND FOR SOUND"; 
            return;
        }
        m_soundMap[soundName] = buffer; // Store it in the map

    std::cout << "Loaded " << soundName << path;
}
void SoundManager::playSound(const std::string& soundName){
   
    auto it = m_soundMap.find(soundName);
    if (it != m_soundMap.end()) {
        m_sounds.emplace_back(); // Create a new sound object
        m_sounds.back().setBuffer(it->second); // Set the buffer
        m_sounds.back().play(); // Play the sound

        return;
    } else {
        std::cout << "Sound not found: " << soundName << std::endl;
    }
}

// const sf::Sound & SoundManager::getSound(const std::string& soundName) const {

//         // std::cout << "LALALALALALALA" <<std::endl;
//         // auto sound = sf::Sound();
//         // sound->setBuffer(m_soundMap[soundName]); // Use the buffer from the map
//         // sound.setBuffer(m_soundMap.at(soundName)); // Use the buffer from the map
//         // if (m_soundMap.find(soundName) != m_soundMap.end())
//         // {
//         //     // std::cout << "There is texture with name: " << name << "\n";
//         //     // sound.setBuffer(m_soundMap.at(soundName)); // Use the buffer from the map
            
//         // }
//         // else{
//         //     // std::cerr << "There is no texture with name: " << name << "\n";
//         //     exit(-1);
//         // }
//         // std::cout << soundName <<std::endl;

//         // return m_textureMap.at(name);
//         // return sound; // Return shared_ptr to manage the sound's lifetime
// }
