#pragma once
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_
#include "GameObject.h"
#include "ObstacleTypes.h"


class Obstacle : public SpriteObject
{
private:
	ObstacleTypes m_aniMods;

	int m_iSprite,
		m_iSpriteMax,
		m_iSpriteYaxis,
		m_iFrame,
		m_iFrameMax;
	float m_rangeMax,m_speed;

	SDL_RendererFlip m_flip;


public:
	Obstacle(SDL_Rect s, SDL_FRect d,ObstacleTypes type);
	~Obstacle();
	
	void Update() override;
	void Render() override;

};

#endif
