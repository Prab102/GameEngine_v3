#include "Animation.h"
#include <iostream>

Animation::Animation()
{
}

Animation::Animation(const std::string& name, const sf::Texture& t)
	: Animation(name, t, 1, 0)
{
}

Animation::Animation(const std::string& name, const sf::Texture& t, size_t cellCount, size_t speed)
	: m_name(name), m_sprite(t), m_frameCount(cellCount), m_currentFrame(0), m_speed(speed)
{
	m_size = Vec2((float)t.getSize().x / m_frameCount, (float)t.getSize().y);
	m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
	m_sprite.setTextureRect(sf::IntRect(std::floor(m_currentFrame) * m_size.x, 0, m_size.x, m_size.y));
}

//updates the current animation to show the next frame, depending on its speed
//animation loops whien it reaches the end
void Animation::update()
{
	
	m_currentFrame++;

	int animFrame = (m_currentFrame/m_speed) % m_frameCount;
	
	m_sprite.setTextureRect(sf::IntRect(std::floor(animFrame) * m_size.x, 0, m_size.x, m_size.y));

	// std::cout <<"makes it here animation system: " <<  animFrame <<std::endl;



	//add the speed variable to the current frame
	//TODO: 1) calculate the correct frame of animation to play based on the currentFrame and speed
	//		2) set the texture rectangle properly (see constructor for sample)
	// m_sprite.setTextureRect(sf::IntRect(std::floor(m_currentFrame) * m_size.x, 0, m_size.x, m_size.y));

	//i need to show the correct part of the texture given the framecount and speed

}

const Vec2& Animation::getSize() const
{
	return m_size;
}

const std::string& Animation::getName() const
{
	return m_name;
}

sf::Sprite& Animation::getSprite()
{
	return m_sprite;
}

bool Animation::hasEnded() const
{
	return false;
}