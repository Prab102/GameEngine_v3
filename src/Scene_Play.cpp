
#include "Scene_Menu.h"
#include "Scene_Play.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Components.h"
#include "Action.h"
#include "Physics.h"
#include <algorithm>
#include <SFML/Audio.hpp>

Scene_Play::Scene_Play(GameEngine* gameEngine, const std::string& levelPath)
	: Scene(gameEngine), m_levelPath(levelPath)
{
	init(m_levelPath);
}

void Scene_Play::init(const std::string& path)
{
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");

	registerAction(sf::Keyboard::D, "RIGHT");
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::Space, "SHOOT");


    // auto sound.setBuffer(m_soundMap.at(soundName)); // Use the buffer from the map

	// sf::SoundBuffer buffer;
    // if (!buffer.loadFromFile("/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/Mega Man 2 - Dr. Wilys Castle.wav")){
	// 	std::cout << "no sound found";
	// }
	// std::cout << "ther is sound" <<std::endl;
	// sf::Sound sound;
	// sound.setBuffer(buffer);
	// sound.play();
	// sf::Music music;
	// // if (!music.openFromFile("/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/Mega Man 2 - Dr. Wilys Castle.wav")){
	// // 		std::cout << "BAD SOUND";
	// // }
	// 	// sf::SoundBuffer buffer;
	// 	// // load something into the sound buffer...
	// 	// buffer.loadFromFile("/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/scream.wav");
    

	// 	// sf::Sound sound;
	// 	// sound.setBuffer(buffer);
	// 	// sound.play();

    // if (music.getStatus() == sf::Music::Status::Stopped) {
   	// 	music.openFromFile("/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/Mega Man 2 - Dr. Wilys Castle.wav");
   	// 	music.play();
	// }
    // auto sound.setBuffer(m_soundMap.at(soundName)); // Use the buffer from the map
        
	// auto sound = m_game->soundmanager().getSound("scream");
	// m_game->soundmanager().playSound("scream"); // Play sound


	m_gridText.setCharacterSize(12);
	m_gridText.setFont(m_game->assets().getFont("Arial"));

	loadlevel(path);
}

Vec2 Scene_Play::gridToPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{

	//TODO: This function takes in a grid (x,y) position and an Entity
	//		Return a Vec2 indicating where the CENTER position of the Entity should be
	//		You must use the Entity's Animation size to position it correctly
	//		The size of the grid width and height is stored in m_gridSize.x and m_gridSize.y
	//		The bottom-left corner of the Animation should align with the bottom left of the grid cell
	// m_game->assets().getTexture(entity->tag()).getSize().x;
	float Cx,Cy = 0;
	// std::cout << m_game->assets().getAnimation(entity->tag()).getSize().x <<" this is width of texture" <<std::endl;
	// std::cout << m_game->assets().getAnimation(entity->tag()).getSize().y <<" this is height of texture" <<std::endl;

	// std::cout << width() <<" this is the width of scene " <<std::endl;
	// std::cout << height() <<" this is the hieght of scene " << std::endl;

	//test gridX 1, gridY,3  should be 96 224   gridX * 64 + sizeX/2
	Cx = (gridX*64) + (m_game->assets().getAnimation(entity->tag()).getSize().x /2);
	Cy = height() - ((gridY*64) + (m_game->assets().getAnimation(entity->tag()).getSize().y /2));


	// std::cout << width() <<std::endl;




	return Vec2(Cx,Cy);
}
void Scene_Play::spawnPlayer()
{
	//here is a sample player entity which you can use to  construct other entities
	m_player = m_entityManager.addEntity("player");
	// std::cout <<"makes it before animation component"; 
	// m_game->assets().getAnimation("Stand");
	// std::cout << m_player->hasComponent<CAnimation>() << " this is number " <<std::endl;
	m_player->addComponent<CAnimation>(m_game->assets().getAnimation("Air"), true);

	// std::cout << m_player->hasComponent<CAnimation>() << " has component animation" <<std::endl ; 

	m_player->addComponent<CTransform>(Vec2(224, 352));
	m_player->addComponent<CBoundingBox>(Vec2(48, 58));
	m_player->addComponent<CGravity>(1);

	PlayerConfig().WEAPON = "buster";

	// TODO: be sure to add the remaining componnets to the player
	//load player config aswell

}
void Scene_Play::loadlevel(const std::string& filename)
{
	//reset the entity manager every time we load a level
	m_entityManager = EntityManager();

	//TODO: read in the level file and add the appropriate entities
	//		use the PlayerConfig struct m_playerConfig to store player properties
	//		ths struct is defined at the top of Scene_Play.h

	//NOTE: all of the code below is sample code which shows you how to
	//		set up and use entities with the new syntax, it should be removed

	// spawnPlayer();

	std::ifstream file(filename);
    std::string str;
    std::cout << std::filesystem::current_path() << std::endl;

    std::cout << file.good() << " this is file good";// need to fix opening assets.txt file

    while (file.good())
    {
		file >> str;
		if(str == "Tile"){
			std::string name, xpos, ypos;
			float gridX, gridY;

			file >> name >> gridX >> gridY;

			auto tile = m_entityManager.addEntity(name);
			tile->addComponent<CAnimation>(m_game->assets().getAnimation(name),true);
			// std::cout <<std::endl << x << " " <<y << "this is x y ";
			tile->addComponent<CTransform>(gridToPixel(gridX, gridY, tile));
			tile->addComponent<CBoundingBox>(m_game->assets().getAnimation(name).getSize());

			// tile->addComponent<CTransform>(Vec2(x,y)); //this needs to have correct scale;
 
		}
		else if(str == "Dec"){
			std::string name, xpos, ypos;
			float gridX, gridY;

			file >> name >> gridX >> gridY;

			auto dec = m_entityManager.addEntity(name);
			dec->addComponent<CAnimation>(m_game->assets().getAnimation(name),true);
			// std::cout <<std::endl << x << " " <<y << "this is x y ";
			dec->addComponent<CTransform>(gridToPixel(gridX, gridY, dec));
		}
	}

	spawnPlayer();

	
	//some sample entities COMMENTED BELLOW
	// auto brick = m_entityManager.addEntity("tile");
	// // //IMPORTANT: always add the CAnimation component first so that gridToMidPixel can compute correctly
	// brick->addComponent<CAnimation>(m_game->assets().getAnimation("Brick"), true);
	// brick->addComponent<CTransform>(Vec2(96, 480));
	// //NOTE: You final code shold position the entity with the grid x,y position read from the file:
	// brick->addComponent<CTransform>(gridToMidPixel(gridX, gridY, brick);

	// if (brick->getComponent<CAnimation>().animation.getName() == "Brick")
	// {
	// 	std::cout << "This could be a good way of identifiying if a tile is a brick!\n";
	// }

	// auto block = m_entityManager.addEntity("tile");
	// block->addComponent<CAnimation>(m_game->assets().getAnimation("Block"), true);
	// block->addComponent<CTransform>(Vec2(96, height() - 224));
	// // //add a bounding box, this will now show up if we press the 'C' key
	// block->addComponent<CBoundingBox>(m_game->assets().getAnimation("Block").getSize());
	

	// auto question = m_entityManager.addEntity("tile");
	// question->addComponent<CAnimation>(m_game->assets().getAnimation("Question"), true);
	// question->addComponent<CTransform>(Vec2(352, 480));
	// std::cout <<"makes it here"; COMMENTED ABOVE

	//NOTE: THIS INCREDIBLY IMPORTANT PLEASE READ THIS EXAMPLE
	//		Components are now returned as references rather than pointers
	//		If you do not specify a reference variable type, it will COPY the component
	//		Here is an example:
	//		
	//		This will COPY the transform into the variable 'transform1' - it is INCORRECT
	//		Any changes you make to transform1 will not be changed inside the enitity
	//		auto transform1 = entity->get<CTransform>()
	//
	//		This will REFERENCE the transform with the variable 'transform2' - it is CORRECT
	//		Now any changes you make to transform2 will be changed inside the entity
	//		auot & transform2 = entity->get<CTransform>()
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity)
{
	//TODO: this should spwan a bullet at the given entity, going in the direction the entity is facing
	//this is not where input should be handled
	auto bullet = m_entityManager.addEntity("bullet");
	bullet->addComponent<CAnimation>(m_game->assets().getAnimation("Buster"),false);
	bullet->addComponent<CTransform>(Vec2(entity->getComponent<CTransform>().pos.x,entity->getComponent<CTransform>().pos.y));
	if(entity->getComponent<CTransform>().scale.x > 0){
		bullet->getComponent<CTransform>().velocity.x = 10;
	}
	else{
		bullet->getComponent<CTransform>().velocity.x = -10;
	}
	bullet->addComponent<CBoundingBox>(Vec2(24,18));

	// m_player->getComponent<CInput>().canShoot = true;

}

void Scene_Play::update()
{
	m_entityManager.update();

	//TODO: implement pause functionality
	sMovement();
	sLifeSpan();
	sCollision();
	sAnimation();
	sRender();

}


void Scene_Play::sMovement()
{

	Vec2 playerVelocity(0,m_player->getComponent<CTransform>().velocity.y);
	// Vec2 playerVelocity(0,0);

	// size_t jumpstart = 0 ;

	auto& pPos = m_player->getComponent<CTransform>().pos; 
	m_player->getComponent<CTransform>().prevPos = m_player->getComponent<CTransform>().pos;

	// TODO: Implement player movement / jumping based on its CInput component
	if(m_player->getComponent<CInput>().right)
	{
            // m_player->cTransform->pos.y -= m_player->cTransform->velocity.y;
			playerVelocity.x = 6;
			// m_player->getComponent<CState>().state = "run";

			m_player->getComponent<CTransform>().scale.x = 1; 
			if(m_player->getComponent<CInput>().canJump == true && m_player->getComponent<CState>().state != "run"){
				m_player->getComponent<CState>().state = "run";
			}

    }
	else if(m_player->getComponent<CInput>().right == false && m_player->getComponent<CInput>().left == false){

		// std::cout <<"makes it here";
			if(m_player->getComponent<CInput>().canJump == true && m_player->getComponent<CState>().state != "stand"){
				m_player->getComponent<CState>().state = "stand";
			}

	}
	else if(m_player->getComponent<CInput>().left )
	{
            // m_player->cTransform->pos.y -= m_player->cTransform->velocity.y;
			playerVelocity.x = -6;
			// m_player->getComponent<CState>().state = "run";

			m_player->getComponent<CTransform>().scale.x = -1; 
			if(m_player->getComponent<CInput>().canJump == true && m_player->getComponent<CState>().state != "run"){
				m_player->getComponent<CState>().state = "run";
			}

    }
	if(m_player->getComponent<CInput>().up && m_player->getComponent<CInput>().canJump) //removed ground CState check
	{
            // m_player->cTransform->pos.y -= m_player->cTransform->velocity.y;
			playerVelocity.y = -21;
			
			// m_player->getComponent<CState>().state = "air";
			if(m_player->getComponent<CInput>().canJump == false && m_player->getComponent<CState>().state != "air"){
				m_player->getComponent<CState>().state = "air";
			}
			m_player->getComponent<CInput>().canJump = false;
			// jumpstart = m_currentFrame;
			
    }
	if(m_player->getComponent<CTransform>().velocity.y - 15 != 0){

		// std::cout << "Should come here if jumping";
		// m_player->getComponent<CState>().state ="air";
		if(m_player->getComponent<CInput>().canJump == false && m_player->getComponent<CState>().state != "air"){
				m_player->getComponent<CState>().state = "air";
		}
		m_player->getComponent<CInput>().canJump = false;
		
	}
	// std::cout << m_player->getComponent<CTransform>().velocity.y <<std::endl;

	//ADDING SHOOT BUTTON PRESS
	if(m_player->getComponent<CInput>().canShoot == true && m_player->getComponent<CInput>().shoot == true){
		spawnBullet(m_player);
		m_player->getComponent<CInput>().canShoot = false;
	}
	if(m_player->getComponent<CInput>().canShoot == false && m_player->getComponent<CInput>().shoot == false){
		// spawnBullet(m_player);
		m_player->getComponent<CInput>().canShoot = true;
	}

	
	m_player->getComponent<CTransform>().velocity = playerVelocity;


	// TODO: Implement gravity's effect on the player
	// TODO: Implement the maximum player speed in bothg X and Y directions
	// NOTE: Setting an entity's scale.x to -1/1 will make it face to the left/right

	//MOVEMENT LOOP
	for(auto e: m_entityManager.getEntities()){
		//if entity has gravity and has a y velocity less that 10 add gravity to it
		if(e->hasComponent<CGravity>() && e->getComponent<CTransform>().velocity.y < 15){
			e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().gravity;
			// e->getComponent<CTransform>().pos.y += e->getComponent<CTransform>().velocity.y; 
		}
		if(e->getComponent<CTransform>().velocity.y == 15 && m_player->getComponent<CInput>().canJump && e->hasComponent<CBoundingBox>()){ //removed ground Cstate
			e->getComponent<CTransform>().velocity.y = 0;
		}
		//this gets previous position
		e->getComponent<CTransform>().prevPos = e->getComponent<CTransform>().pos;

		//left and right running
		e->getComponent<CTransform>().pos.x += e->getComponent<CTransform>().velocity.x; 
		//falling and jumping
		e->getComponent<CTransform>().pos.y += e->getComponent<CTransform>().velocity.y; 

	}


}

void Scene_Play::sLifeSpan()
{
	//TODO: Check lifespan of entities that have them, and destroy them if they go over
	for(auto b: m_entityManager.getEntities()){
            // std::cout << b->cLifespan->total << "this is total";
            if(b->hasComponent<CLifespan>()){
				// std::cout << "m_currentFrame: " << m_currentFrame << std::endl;

				if(b->getComponent<CLifespan>().total <= m_currentFrame){
                	b->destroy();
				}
            }
        }
}

void Scene_Play::sCollision()
{
	//REMEBER: SFML's (0,0) position is on the TOP-LEFT corner
	//			This means jumping will have a negatice y-component
	//			and gravity will have a positive y-component
	//			Also, something BELOW something else will have a y value GREATER than it
	//			Also, something ABOVE something else will have a y value LESS than it

	//TODO: Implement Physics::GetOverlap() function, use it inside this function
	Physics apple;
	// Vec2 overlap = apple.GetOverlap(m_player, m_player);
	for(auto b:m_entityManager.getEntities("bullet")){
		for(auto e:m_entityManager.getEntities()){
			if(e->hasComponent<CBoundingBox>() && e->tag() != "player" && e->tag() != "bullet"){
				Vec2 bulletoverlap = apple.GetOverlap(b, e);

				if(bulletoverlap.x > 0 && bulletoverlap.y > 0){
					// std::cout << "bullet collided" <<std::endl;
					b->destroy();
					if(e->tag() == "Brick"){
						// std::cout << "hit da brick" <<std::endl;
						e->addComponent<CAnimation>(m_game->assets().getAnimation("Brick2"),false);
								e->addComponent<CLifespan>(m_currentFrame + .5);
								m_game->soundmanager().playSound("burp"); // Play sound

								// e->destroy();
								auto piece = m_entityManager.addEntity("piece");
								piece->addComponent<CAnimation>(m_game->assets().getAnimation("Piece"),true);
								piece->addComponent<CTransform>(Vec2(e->getComponent<CTransform>().pos.x,e->getComponent<CTransform>().pos.y));
								piece->addComponent<CGravity>(.5);
								piece->getComponent<CTransform>().velocity = Vec2(-3,-15);
								piece->getComponent<CTransform>().scale.x = .7; 
								piece->getComponent<CTransform>().scale.y = .7; 



								auto piece1 = m_entityManager.addEntity("piece");
								piece1->addComponent<CAnimation>(m_game->assets().getAnimation("Piece"),true);
								piece1->addComponent<CTransform>(Vec2(e->getComponent<CTransform>().pos.x,e->getComponent<CTransform>().pos.y));
								piece1->addComponent<CGravity>(.5);
								piece1->getComponent<CTransform>().velocity = Vec2(3,-15);
								piece1->getComponent<CTransform>().scale.x = -.7; 
								piece1->getComponent<CTransform>().scale.y = .7; 



								auto piece2 = m_entityManager.addEntity("piece");
								piece2->addComponent<CAnimation>(m_game->assets().getAnimation("Piece"),true);
								piece2->addComponent<CTransform>(Vec2(e->getComponent<CTransform>().pos.x,e->getComponent<CTransform>().pos.y));
								piece2->addComponent<CGravity>(.5);
								piece2->getComponent<CTransform>().velocity = Vec2(-3,-10);
								piece2->getComponent<CTransform>().scale.x = .7; 
								piece2->getComponent<CTransform>().scale.y = -.7; 



								auto piece3 = m_entityManager.addEntity("piece");
								piece3->addComponent<CAnimation>(m_game->assets().getAnimation("Piece"),true);
								piece3->addComponent<CTransform>(Vec2(e->getComponent<CTransform>().pos.x,e->getComponent<CTransform>().pos.y));
								piece3->addComponent<CGravity>(.5);
								piece3->getComponent<CTransform>().velocity = Vec2(3,-10);
								piece3->getComponent<CTransform>().scale.x = -.7; 
								piece3->getComponent<CTransform>().scale.y = -.7; 

					}
				}



			}
		}
	}
	for(auto e:m_entityManager.getEntities()){
		//player/tile collision
		//i think overlap is not getting proper overlap based on midpoint
		if(e->hasComponent<CBoundingBox>() && e->tag() != "player" && e->tag() != "bullet"){
			Vec2 overlap = apple.GetOverlap(m_player, e);
			//there is collision with player
			if(overlap.x > 0 && overlap.y > 0){      	
				Vec2 prevOverlap = apple.GetPreviousOverlap(m_player,e);
				//verticle 
				if(prevOverlap.x > 0){
					//movement came from top
					if(e->getComponent<CAnimation>().animation.getName() != "Coin"){

						if(m_player->getComponent<CTransform>().prevPos.y < e->getComponent<CTransform>().pos.y){
							//top
							m_player->getComponent<CTransform>().pos.y -= overlap.y;
							// m_player->getComponent<CState>().state = "stand";
							m_player->getComponent<CInput>().canJump = true;
						}
						else{
							//bottom
							m_player->getComponent<CTransform>().pos.y += overlap.y;
							//10 is the max speed
							m_player->getComponent<CTransform>().velocity.y = 0;
							// m_player->getComponent<CState>().state = "air";
							m_player->getComponent<CInput>().canJump = false;
							//if hit a question block spawn a coin for some time and change the question to a empty block
							if(e->getComponent<CAnimation>().animation.getName() == "Question"){
								std::cout <<"hit the question box" <<std::endl;
								auto coin = m_entityManager.addEntity("coin");
								coin->addComponent<CAnimation>(m_game->assets().getAnimation("Coin"),true);
								coin->addComponent<CTransform>(Vec2(e->getComponent<CTransform>().pos.x,e->getComponent<CTransform>().pos.y-64));
								coin->addComponent<CBoundingBox>(Vec2(32,64));
								e->addComponent<CAnimation>(m_game->assets().getAnimation("Question2"),true);

							}
							//if player hits a brick block from under
							if(e->getComponent<CAnimation>().animation.getName() == "Brick"){
								// std::cout <<"hit the brick" <<std::endl;

								//change brick animation
								e->addComponent<CAnimation>(m_game->assets().getAnimation("Brick2"),false);
								e->addComponent<CLifespan>(m_currentFrame + .5);
								m_game->soundmanager().playSound("burp"); // Play sound

								// e->destroy();
								auto piece = m_entityManager.addEntity("piece");
								piece->addComponent<CAnimation>(m_game->assets().getAnimation("Piece"),true);
								piece->addComponent<CTransform>(Vec2(e->getComponent<CTransform>().pos.x,e->getComponent<CTransform>().pos.y));
								piece->addComponent<CGravity>(.5);
								piece->getComponent<CTransform>().velocity = Vec2(-3,-15);
								piece->getComponent<CTransform>().scale.x = .7; 
								piece->getComponent<CTransform>().scale.y = .7; 



								auto piece1 = m_entityManager.addEntity("piece");
								piece1->addComponent<CAnimation>(m_game->assets().getAnimation("Piece"),true);
								piece1->addComponent<CTransform>(Vec2(e->getComponent<CTransform>().pos.x,e->getComponent<CTransform>().pos.y));
								piece1->addComponent<CGravity>(.5);
								piece1->getComponent<CTransform>().velocity = Vec2(3,-15);
								piece1->getComponent<CTransform>().scale.x = -.7; 
								piece1->getComponent<CTransform>().scale.y = .7; 



								auto piece2 = m_entityManager.addEntity("piece");
								piece2->addComponent<CAnimation>(m_game->assets().getAnimation("Piece"),true);
								piece2->addComponent<CTransform>(Vec2(e->getComponent<CTransform>().pos.x,e->getComponent<CTransform>().pos.y));
								piece2->addComponent<CGravity>(.5);
								piece2->getComponent<CTransform>().velocity = Vec2(-3,-10);
								piece2->getComponent<CTransform>().scale.x = .7; 
								piece2->getComponent<CTransform>().scale.y = -.7; 



								auto piece3 = m_entityManager.addEntity("piece");
								piece3->addComponent<CAnimation>(m_game->assets().getAnimation("Piece"),true);
								piece3->addComponent<CTransform>(Vec2(e->getComponent<CTransform>().pos.x,e->getComponent<CTransform>().pos.y));
								piece3->addComponent<CGravity>(.5);
								piece3->getComponent<CTransform>().velocity = Vec2(3,-10);
								piece3->getComponent<CTransform>().scale.x = -.7; 
								piece3->getComponent<CTransform>().scale.y = -.7; 






								//spawn in small pieces and give them gravity 
							}

						}
					}

				}
				//horizontal
				else if(prevOverlap.y > 0 ){
					if(m_player->getComponent<CTransform>().prevPos.x < e->getComponent<CTransform>().pos.x ){
						//left
						m_player->getComponent<CTransform>().pos.x -= overlap.x;
					}
					else{
						//right
						m_player->getComponent<CTransform>().pos.x += overlap.x;
					}
				}

				if(e->getComponent<CAnimation>().animation.getName() == "Coin"){
					// std::cout <<"Deystroy this cig" <<std::endl;
					e->destroy();
				}
    		}

			
			
			//player /left world colision
			if(m_player->getComponent<CTransform>().pos.x < 0){
				// m_game->soundmanager().playSound("scream"); // Play sound
				m_player->getComponent<CTransform>().pos.x += 1;
			}
			//player/falling into pit collision
			if(m_player->getComponent<CTransform>().pos.y > height()+32){
				// SoundManager soundManager;
				// if (!m_game->soundmanager().addSound("scream", "/Users/prabsingh/Documents/Visual Studio Code/GameDev-SFML/GameEngine_V3/sounds/scream.wav")) {
				// 	std::cout << "BAD APPLE "; // Handle error if sound fails to load
				// }
				// auto sound = m_game->soundmanager().getSound("scream");
				// auto sound = m_game->getSound("scream");
				// sound->play();
				m_game->soundmanager().playSound("scream"); // Play sound
				// m_game->assets().playSound("scream");
				
				m_player->getComponent<CTransform>().pos.x =224;
				m_player->getComponent<CTransform>().pos.y =352;
			}
			
			//no collision
			// m_player->getComponent<CState>().state = "air";


		}
	}
	//TODO: Implement bullet / tile collisions
	//		Destroy the tile if it has a Brick animation
	//TODO: Implement player / tile collisionis and resolutions
	//		Update the CState component of the player to store whether
	//		it is currently on the ground or in the air. This will be
	//		used by the Animation system - done
	//TODO: Check to see if the player has fallen down a hole (y > height()) - done
	//TODO: Dont' let player walk off the left side of the map - done
}
void Scene_Play::sDoAction(const Action& action)
{
	// std::cout << " actions ";
	if (action.type() == "START")
	{
		if (action.name() == "TOGGLE_TEXTURE") { m_drawTextures = !m_drawTextures; }
		else if (action.name() == "TOGGLE_COLLISION") { m_drawCollision = !m_drawCollision; }
		else if (action.name() == "TOGGLE_GRID") { m_drawGrid = !m_drawGrid; }
		else if (action.name() == "PAUSE") { setPaused(!m_paused); }
		else if (action.name() == "QUIT") { onEnd(); }
		else if (action.name() == "RIGHT") {m_player->getComponent<CInput>().right = true;}
		else if (action.name() == "LEFT") {m_player->getComponent<CInput>().left = true;}
		else if (action.name() == "UP") {m_player->getComponent<CInput>().up = true;}
		else if (action.name() == "DOWN") {m_player->getComponent<CInput>().down = true;}
		else if (action.name() == "SHOOT") {m_player->getComponent<CInput>().shoot = true;}

	}
	else if (action.type() == "END")
	{
		if(action.name() == "RIGHT") {m_player->getComponent<CInput>().right = false;}
		if(action.name() == "LEFT") {m_player->getComponent<CInput>().left = false;}
		if(action.name() == "UP") {m_player->getComponent<CInput>().up = false;}
		if(action.name() == "DOWN") {m_player->getComponent<CInput>().down = false;}
		if(action.name() == "SHOOT") {m_player->getComponent<CInput>().shoot = false;}

	}
}

void Scene_Play::sAnimation()
{

	//TODO: Complete the Animation class code first

	//TODO: set the animation of the player based on its CState component
	//TODO: for each entity with an animation, call entity->getComponent<CAnimation>().animation.update()
	//		if the animation is not repeated, and it has ended, destroy the entity

	if(m_player->getComponent<CState>().state == "stand"){

		m_player->addComponent<CAnimation>(m_game->assets().getAnimation("Stand"),true);
	}
	else if(m_player->getComponent<CState>().state == "air"){

		m_player->addComponent<CAnimation>(m_game->assets().getAnimation("Air"),true);

	}
	else if(m_player->getComponent<CState>().state == "run" && m_player->getComponent<CAnimation>().animation.getName() != "Run"){

		m_player->addComponent<CAnimation>(m_game->assets().getAnimation("Run"),true);
		// std::cout <<"makes it here animation system: ";
		// m_player->getComponent<CAnimation>().animation.update();

	}
	for (auto& e : m_entityManager.getEntities())
		{

			if (e->hasComponent<CAnimation>())
			{
				e->getComponent<CAnimation>().animation.update();
			}
		}

	// set the animation of the player based on its CState component

}

void Scene_Play::onEnd()
{
	//TODO: When scene ends, change back to the MENU scene
	// m_game->changeScene("Menu", nullptr, true); //this causes a seg fault
	m_game->quit();
}
void Scene_Play::drawLine(const Vec2& p1, const Vec2& p2)
{
	sf::Vertex line[] = { sf::Vector2f(p1.x, p1.y), sf::Vector2f(p2.x, p2.y) };
	m_game->window().draw(line, 2, sf::Lines);
}

void Scene_Play::sRender()
{
	// // color the background darker so you know that the game is paused
	if (!m_paused) { m_game->window().clear(sf::Color(100, 100, 255)); } //100 100 255
	else { m_game->window().clear(sf::Color(50, 50, 150)); }

	//add a background renderer

	// //set the view port of the window to be centered on the player if it's far enough right
	// std::cout << m_player->hasComponent<CTransform>() <<std::endl;
	auto& pPos = m_player->getComponent<CTransform>().pos;
	// std::cout << pPos.x;

	float windowCenterX = std::max(width() / 2.0f, pPos.x);
	// float windowCenterX = std::max(width() / 2.0f, 2.0f);

	sf::View view = m_game->window().getView();
	// std::cout << windowCenterX <<std::endl;
	//this is causing a seg fault
	view.setCenter(windowCenterX, height() - view.getCenter().y);
	


	m_game->window().setView(view);

	// //draw all Entity textures / animations
	if (m_drawTextures)
	{
		for (auto& e : m_entityManager.getEntities())
		{
			auto& transform = e->getComponent<CTransform>();
			// std::cout << "testing";
			if (e->hasComponent<CAnimation>())
			{
				auto& animation = e->getComponent<CAnimation>().animation;
				animation.getSprite().setRotation(transform.angle);
				animation.getSprite().setPosition(transform.pos.x, transform.pos.y);
				animation.getSprite().setScale(transform.scale.x, transform.scale.y);
				m_game->window().draw(animation.getSprite());
			}
		}
	}
	

	// //draw all Entity collision bounding boxes with a rectangleshape
	if (m_drawCollision)
	{
		for (auto& e : m_entityManager.getEntities())
		{
			if (e->hasComponent<CBoundingBox>())
			{
				auto& box = e->getComponent<CBoundingBox>();
				auto& transform = e->getComponent<CTransform>();
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
				rect.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
				rect.setPosition(transform.pos.x, transform.pos.y);
				rect.setFillColor(sf::Color(0, 0, 0, 0));
				rect.setOutlineColor(sf::Color(255, 255, 255, 255));
				rect.setOutlineThickness(1);
				m_game->window().draw(rect);
			}
		}
	}

	// //draw the grid 
	if (m_drawGrid)
	{
		float leftX = m_game->window().getView().getCenter().x - width() / 2.0f;
		float rightX = leftX + width() + m_gridSize.x;
		float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);

		for (float x = nextGridX ; x < rightX; x += m_gridSize.x)
		{
			drawLine(Vec2(x, 0), Vec2(x, height()));
		}

		for (float y = 0; y < height(); y += m_gridSize.y)
		{
			drawLine(Vec2(leftX, height() - y), Vec2(rightX, height() - y));
			for (float x = nextGridX; x < rightX; x += m_gridSize.x)
			{
				std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
				std::string yCell = std::to_string((int)y / (int)m_gridSize.y);
				m_gridText.setString("(" + xCell + "," + yCell + ")");
				m_gridText.setPosition(x + 3, height() - y - m_gridSize.y + 2);
				m_game->window().draw(m_gridText);
			}
			
		}

	}


}
// Vec2 Scene_Play::gridToPixel(float gridx, float gridy, std::shared_ptr<Entity> entity)
// {
//     // TODO: This function takes in grid (x,y)position and an Entity
//     // 

//     return Vec2(0,0);
// }

// void Scene_Play::loadeLevel(const std::string & filename)
// {
//     //reset entity manager every time we load a level
//     m_entityManager = EntityManager();
// }