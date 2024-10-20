#pragma once
#include "Scene.h"
#include <map>
#include <memory>

#include "EntityManager.h"

class Scene_Play : public Scene
{
    struct PlayerConfig
    {
        float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
        std::string WEAPON;
    };

    protected:
        std::shared_ptr<Entity> m_player;
        std::string             m_levelPath;
        PlayerConfig            m_playerConfig;
        bool                    m_drawTextures = true;
        bool                    m_drawCollision = false;
        bool                    m_drawGrid = false;
        const Vec2              m_gridSize = { 64, 64};
        sf::Text                m_gridText;

        void init(const std::string & levelPath);
        
        void loadlevel(const std::string & filename);
        Vec2 gridToPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);

        void spawnPlayer();

	    void spawnBullet(std::shared_ptr<Entity> entity);

    public:
        Scene_Play(GameEngine* gameEngine, const std::string& levelPath);
        // ~ScenePlay() override = default;
        void update();
        void sDoAction(const Action& action);
        void sRender();
        void onEnd();

        //Systems
        void sAnimation();
        void drawLine(const Vec2& p1, const Vec2& p2);
        void sMovement();
        void sLifeSpan();
        //void sEnemySpawner();
        void sCollision();

        //void sDebug();
};