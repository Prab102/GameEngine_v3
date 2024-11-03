//to run ./sfmlgametest
//to compile g++ main.cpp -I /opt/homebrew/Cellar/sfml/2.6.1/include -o sfmlgametest -std=c++17 -L /opt/homebrew/Cellar/sfml/2.6.1/lib  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
// #pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include "GameEngine.h"
#include <iostream>
// #include "Vec2.h"
// #include "Vec2.cpp"
//for testing

int main(){

    // Vec2 v1(1,2);
    // Vec2 v2(5,7);

    // Vec2 v3 = v1 + v2;

    // std::cout << v3.x <<" "<<v3.y;
    ///////////////////////////////////////////
    //find a better place to play this when scene is chosen
    sf::Music music;
	if (!music.openFromFile("/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/oceanman.wav")){
			std::cout << "BAD SOUND";
	}
    music.setVolume(20);
	music.play();
    //////////////////////////////////////////
    // SoundManager soundManager;
    // if (!soundManager.addSound("scream", "/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/scream.wav")) {
    //     std::cout << "BAD APPLE "; // Handle error if sound fails to load
    // }

    // auto sound = soundManager.getSound("scream");
    // sound->play();
    // SoundManager soundManager;
	// if (!soundManager.addSound("scream", "/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/scream.wav")) {
	//     std::cout << "BAD APPLE "; // Handle error if sound fails to load
	// }


    GameEngine g("/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/assets.txt");
    g.run();
   
    return 0;
    

}