#include "Player.h"

#include "EventManager.h"
#include "SoundManager.h"

Player::Player(SDL_Rect s, SDL_FRect d):SpriteObject(s,d) 
{
	
	m_iSprite = m_iSpriteMin = m_iSpriteMax = m_iSpriteYaxis = m_iFrame = 0;
	m_iFrameMax = 8;

	m_velocity = 0;
	m_jumpForce = 15;
	m_gravity = 1;
	m_aniMod = RUN;

	
}

Player::~Player()
= default;

void Player::Update()
{
	if(m_aniMod ==DEAD && GetDst()->y == 490)
	{
		Animate();
		return;
	}
	m_aniMod = RUN;

	m_collisionRect = m_dst;
	m_collisionRect.x += 40;
	m_collisionRect.w -= 60;
	m_collisionRect.y += 15;
	m_collisionRect.h -= 5;

	
	if (EVMA::KeyHeld(SDL_SCANCODE_S))
	{
		m_aniMod = ROLL;
		m_collisionRect.x -= 10;
		m_collisionRect.y += 25;
		m_collisionRect.h -= 20;
		
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_D))
	{
		if (GetDst()->x < 900)
			GetDst()->x += 5;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_A))
	{
		if (GetDst()->x > 10)
			GetDst()->x -= 5;
	}
	
	if (EVMA::KeyPressed(SDL_SCANCODE_SPACE))
	{
		cout << "hello";
		m_velocity += m_jumpForce;
		GetDst()->y -= m_velocity;

		SOMA::PlaySound("jump");
	}

	
	if (GetDst()->y < 490)
	{
		m_velocity -= m_gravity;
		GetDst()->y -= m_velocity;
		m_aniMod = JUMP;
	}
	else
	{
		GetDst()->y = 490;
		m_velocity = 0;
	}
	


	
	
	Animate();
}

void Player::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("player"),
		&m_src, &m_dst, 0, nullptr,SDL_FLIP_NONE);
	SDL_RenderDrawRectF(Engine::Instance().GetRenderer(),&m_collisionRect);
}

void Player::setDead()
{
	m_aniMod = DEAD;
	SOMA::PlaySound("dying");
}

bool Player::isDead()
{
	if (m_aniMod == DEAD)
		return true;
	return false;
}


void Player::Animate()
{
	switch(m_aniMod)
	{
	case RUN:
		m_iSpriteMin = 1;
		m_iSpriteYaxis = 1;
		m_iSpriteMax = 6;
		break;
	case JUMP:
		m_iSpriteMin = 3;
		m_iSpriteYaxis = 2;
		m_iSpriteMax = 6;
		break;
	case ROLL:
		m_iSpriteMin = 3;
		m_iSpriteYaxis = 3;
		m_iSpriteMax = 6;
		break;
	case DEAD:
		m_iSpriteMin = 3;
		m_iSpriteYaxis = 9;
		m_iSpriteMax = 6;
	default:
			break;
	}
	m_iFrame++;
	if (m_iFrame == m_iFrameMax)
	{
		m_iFrame = 0;
		if (m_aniMod != DEAD && m_iSprite != m_iSpriteMax)
		{
			m_iSprite++;

			if (m_iSprite == m_iSpriteMax)
			{
				m_iSprite = m_iSpriteMin;
			}
		}
	}

	m_src.x = m_src.w * m_iSprite;
	m_src.y = m_src.h * m_iSpriteYaxis;
}
