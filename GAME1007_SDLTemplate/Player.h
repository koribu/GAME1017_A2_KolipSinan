#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"

class Player : public SpriteObject
{
public:
	Player(SDL_Rect s, SDL_FRect d);
	~Player();
	
	void Update();
	void Render();

private:
	enum AnimationMod {RUN,JUMP,ROLL};
	AnimationMod m_aniMod;

	void Animate();
	
	int m_iSprite,
		m_iSpriteMin,
		m_iSpriteMax,
		m_iSpriteYaxis,
		m_iFrame,
		m_iFrameMax;

	float m_jumpForce,
		m_velocity,
		m_gravity;
	;
};

#endif

