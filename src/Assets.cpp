// #pragma once
#include "Assets.h"
// #include <cassert>
#include <map>
#include <filesystem>
#include <string>


Assets::Assets()
{

}

void Assets::loadFromFile(const std::string & path)
{
    // std::filesystem:: filePath = "myfile.txt"; 
    std::ifstream file(path);
    std::string str;
    std::cout << std::filesystem::current_path() << std::endl;

    std::cout << file.good();// need to fix opening assets.txt file

    while (file.good())
    {
        
        file >> str;

        if (str == "Texture")
        {
            // std::cout <<"makes it here";
            std::string name, path;
            file >> name >> path;
            addTexture(name, "/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/" + path);
        }
        else if (str == "Animation")
        {
            // std::cout <<"makes it here";

            std::string name, texture;
            size_t frames, speed;
            file >> name >> texture >> frames >> speed;
            addAnimation(name, texture, frames, speed);
        }
        else if (str == "Font")
        {
            // std::cout <<" this is the fonts fonts" <<std::endl; 
            std::string name, path;
            file >> name >> path;
            addFont(name, "/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/"+path);
        }
        // else if (str == "Sound"){
        //     std::string name, path;
        //     file >> name >>path;
        //     addSound(name,"/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/"+path);
        // }
        else
        {
            std::cerr << "Unknown Asset Type: " << str << std::endl;
        }
    }
    // SoundManager soundManager;
    // if (!soundManager.addSound("scream", "/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/scream.wav")) {
    //     std::cout << "BAD APPLE "; // Handle error if sound fails to load
    // }

    // auto sound = soundManager.getSound("scream");
    // sound->play();


    // addSound("scream", "/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/scream.wav");
    // if (!addSound("scream", "/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/scream.wav")) {
    //     std::cout << "there was huge error"; // Handle error if sound fails to load
    // }

    std::cout <<"NO PROBLEMS OCCURD" <<std::endl <<std::endl;
}

void Assets::addTexture(const std::string & textureName, const std::string & path, bool smooth)
{
    m_textureMap[textureName] = sf::Texture();
    std::cout << textureName  <<std::endl;
    if (!m_textureMap[textureName].loadFromFile(path))
    {
        std::cerr << "Could not load texture file: " << path << std::endl;
        m_textureMap.erase(textureName);
    }
    else
    {
        m_textureMap[textureName].setSmooth(smooth);
        std::cout << "Loaded Texture: " << path << std::endl;
    }
}

// const sf::Texture & Assets::getTexture(const std::string & textureName) const
// {
//     assert(m_textureMap.find(textureName) != m_textureMap.end());
//     return m_textureMap.at(textureName);

// }
const sf::Texture& Assets::getTexture(const std::string& name) const
{
    // if (!m_textureMap.contains(name))
    // {
    //     std::cerr << "There's no texture with name: " << name << "\n";
    //     exit(-1);
    // }
    if (m_textureMap.find(name) != m_textureMap.end())
    {
        // std::cout << "There is texture with name: " << name << "\n";
        
    }
    else{
        // std::cerr << "There is no texture with name: " << name << "\n";
        exit(-1);
    }

    return m_textureMap.at(name);
}

void Assets::addAnimation(const std::string & animationName, const std::string & textureName, size_t frameCount, size_t speed)
{

    m_animationMap[animationName] = Animation(animationName, getTexture(textureName), frameCount, speed);
    // std::cout << "succesfull animation load";
}

// const Animation & Assets::getAnimation(const std::string & animationName) const
// {
//     assert(m_animationMap.find(animationName) != m_animationMap.end());
//     return m_animationMap.at(animationName);
// }
const Animation& Assets::getAnimation(const std::string& name) const
{
    
    // if (!m_animationMap.contains(name)) { std::cerr << "There's no animation with name: " << name << "\n"; }
    if (m_animationMap.find(name) != m_animationMap.end())
    {
        // std::cout << "There is animation with name: " << name << "\n";   
    }
    else{
        // std::cerr << "There is no texture with name: " << name << "\n";
    }

    // std::cout << "makes it to getAnimation";    
    return m_animationMap.at(name);
}

void Assets::addFont(const std::string & fontName, const std::string & path)
{
    m_fontMap[fontName] = sf::Font();
    if (!m_fontMap[fontName].loadFromFile(path))
    {
        std::cerr << "Could not load font file: " << path << std::endl;
        m_fontMap.erase(fontName);
    }
    else
    {
        std::cout << "Loaded Font:    " << path << std::endl;
    }
}

// const sf::Font & Assets::getFont(const std::string & fontName) const
// {
//     assert(m_fontMap.find(fontName) != m_fontMap.end());
//     return m_fontMap.at(fontName);
// }
const sf::Font& Assets::getFont(const std::string& fontName) const
{
    // m_fontMap.contains("hello");
    // sf::Font defaultFont;
    // std::cout << m_fontMap;
    
    if (m_fontMap.find(fontName) != m_fontMap.end())
    {
        // std::cout << "There is font with name: " << fontName << "\n";
       
    }
    else{
        // std::cerr << "There is no font with name: " << fontName << "\n";
        exit(-1);
    }
    // std::cout <<"makes it here pls";
    return m_fontMap.at(fontName);
}
// bool Assets::addSound(const std::string & soundName, const std::string & path)
// {
//     // sf::SoundBuffer buffer;
// 	// // load something into the sound buffer...
// 	// buffer.loadFromFile(path);
// 		sf::SoundBuffer buffer;
//         if (!buffer.loadFromFile(path)) {
//             std::cout << "NO FILE FOUND FOR SOUND"; 
//             return false;
//         }
//         m_soundMap[soundName] = std::move(buffer); // Store it in the map
//         return true;

//     std::cout << "made it to addSound ";

// }
// std::shared_ptr<sf::Sound>  Assets::getSound(const std::string& soundName) {
//         auto sound = std::make_shared<sf::Sound>();
//         // sound->setBuffer(m_soundMap[soundName]); // Use the buffer from the map
//         sound->setBuffer(m_soundMap.at(soundName)); // Use the buffer from the map
//         return sound; // Return shared_ptr to manage the sound's lifetime
// }
// void Assets::loadSounds(const std::string & path)
// {   

//     //this should read in from a file and add sounds if everything is correct
//     addSound("scream",path);
//     addSound("burp","/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/burp.wav");
//     // "/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/burp.wav"

// }
