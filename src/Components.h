#pragma once
#include "Vec2.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Assets.h"
// #include "Entity.h"

class Component
{
public:
    bool has = false;
};
// class Entity;

//no logic except constructor logic to set data
class CTransform : public Component
{
public:
	Vec2 pos		= { 0.0, 0.0 };
	Vec2 prevPos	= { 0.0, 0.0 };
	Vec2 scale		= { 1.0, 1.0 };
	Vec2 velocity	= { 0.0, 0.0 };
	float angle		= 0;

	CTransform() {};
	CTransform(const Vec2& p)
		:pos(p) {}
	CTransform(const Vec2& p, const Vec2& sp, const Vec2& sc, float a)
		: pos(p), prevPos(p), velocity(sp), scale(sc), angle(a) {}
};

class CLifespan : public Component{
    public:
        int remaining =0;
        int total = 0;
        CLifespan(){}
        CLifespan(int total)
            :remaining(total), total(total) {}
};

//component that stores whether or not a specific key is pressed
class CInput : public Component{
    public:
        bool up     = false;
        bool left   = false;
        bool right  = false;
        bool down   = false;
        bool shoot  = false;
        bool canShoot = true;
	    bool canJump = true;

        CInput(){}
};

class CBoundingBox : public Component{
    public:
        
        Vec2 size;
        Vec2 halfSize;
        CBoundingBox() {}
        CBoundingBox(const Vec2 & s)
            : size (s), halfSize(s.x / 2, s.y / 2) {}


};

class CAnimation : public Component
{
public:
	Animation animation;
	bool repeat = false;
	CAnimation() {}
	CAnimation(const Animation& a, bool r)
		: animation(a), repeat(r) {}
};

class CGravity : public Component
{
public:
	float gravity = 0;
	CGravity() {}
	CGravity(float g) : gravity(g) {}
};


class CState : public Component
{
public:
	std::string state = "jumping";
	CState() {}
	CState(const std::string& s) : state(s) {}
};
// #pragma once

// #include <array>
// #include "Animation.h"
// #include "Assets.h"

// class Component;
// class Entity;

// const size_t MaxComponents = 32;

// class Component
// {
// public:
//     virtual ~Component() {}
// };

// class CTransform : public Component
// {
// public:
//     Vec2 pos        = { 0.0, 0.0 };
//     Vec2 prevPos    = { 0.0, 0.0 };
//     Vec2 scale      = { 1.0, 1.0 };
//     Vec2 speed      = { 0.0, 0.0 };
//     float angle = 0;

//     CTransform(const Vec2 & p = { 0, 0 })
//         : pos(p), angle(0) {}
//     CTransform(const Vec2 & p, const Vec2 & sp, const Vec2 & sc, float a)
//         : pos(p), prevPos(p), speed(sp), scale(sc), angle(a) {}

// };

// class CLifespan : public Component
// {
// public:
//     sf::Clock clock;
//     int lifespan = 0;
    
//     CLifespan(int l) : lifespan(l) {}
// };

// class CInput : public Component
// {
// public:
//     bool up         = false;
//     bool down       = false;
//     bool left       = false;
//     bool right      = false;
//     bool shoot      = false;
//     bool canShoot   = true;

//     CInput() {}
// };

// class CBoundingBox : public Component
// {
// public:
//     Vec2 size;
//     Vec2 halfSize;
//     CBoundingBox(const Vec2 & s)
//         : size(s), halfSize(s.x / 2, s.y / 2) {}
// };

// class CAnimation : public Component
// {
// public:
//     Animation animation;
//     bool repeat;

//     CAnimation(const Animation & animation, bool r)
//         : animation(animation), repeat(r) {}
// };

// class CGravity : public Component
// {
// public:
//     float gravity;
//     CGravity(float g) : gravity(g) {}
// };

// class CState : public Component
// {
// public:
//     std::string state = "jumping";
//     CState(const std::string & s) : state(s) {}
// };