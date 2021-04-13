#include "Obstacle.h"

#include "SoundManager.h"

Obstacle::Obstacle(SDL_Rect s, SDL_FRect d,ObstacleTypes type): SpriteObject(s,d)
{
	m_aniMods = type;
	m_flip = SDL_FLIP_NONE;
	
	switch (m_aniMods)
	{
	case SAW:
		m_src.w = 120;
		m_src.h = 45;
		m_dst.w = 120;
		m_dst.h = 45;
		m_dst.y = 521;
		m_iSpriteMax = 3;
		m_iSpriteYaxis = 130;

		m_iFrameMax = 5;
		
		break;
	case SPEARNONFLIP:


		m_dst.h = 130;
		m_dst.y = 436;

		m_rangeMax = m_dst.h;
		m_collisionRect.y += m_dst.h;
		m_collisionRect.h -= m_dst.h;


		m_src.w = 80;
		m_src.h = 130;
		m_dst.w = 80;

		m_iSpriteMax = 7;
		m_iSpriteYaxis = 0;

		m_iFrameMax = 10;

		
		break;

	case SPEARFLIP:
		m_dst.h = 130;
		m_dst.y = 400;

		m_rangeMax = m_dst.h;
		m_collisionRect.h = 0;

		m_src.w = 80;
		m_src.h = 130;
		m_dst.w = 80;

		m_iSpriteMax = 7;
		m_iSpriteYaxis = 0;

		m_iFrameMax = 10;

		m_flip = SDL_FLIP_VERTICAL;
		break;
	case ROLLWALL:
		m_src.w = 200;
		m_src.h = 350;
		m_dst.w = 200;
		m_dst.h = 350;
		m_dst.y = 200;
		m_iSpriteMax = 1;
		m_iSpriteYaxis = 175;

		m_iFrameMax = 5;
		break;
	}

	
	m_iSprite = m_iFrame = 0;

	m_speed = 3;
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update()
{
	m_iFrame++;

	m_dst.x -= 3;
	
	if (m_iFrame == m_iFrameMax)
	{
		m_iFrame = 0;
		m_iSprite++;
		
		if (m_iSprite == m_iSpriteMax)
		{
			m_iSprite = 0;
		}

		if (m_aniMods == SPEARNONFLIP)
		{
			if (m_iSprite == 4)
			{
				m_collisionRect.h = m_rangeMax;
				m_collisionRect.y = m_dst.y;
				SOMA::PlaySound("spear");
			}

			else if (m_iSprite == 3 || m_iSprite == 5)
			{
				m_collisionRect.h = m_rangeMax * 2 / 3;
				m_collisionRect.y = m_dst.y + m_rangeMax / 3;
			}
			else
			{
				m_collisionRect.h = 0;
				m_collisionRect.y = m_dst.y + m_rangeMax;
			}
			//m_collisionRect.h -= m_moveRange;
			//m_collisionRect.y += m_moveRange;
			//if (m_collisionRect.h > m_rangeMax-1)
			//	m_moveRange = -m_moveRange;
			//else if (m_collisionRect.h < 1)
			//	m_moveRange = -m_moveRange;
		}
		else if (m_aniMods == SPEARFLIP)
		{
			m_collisionRect.y = m_dst.y;
			if (m_iSprite == 4)
			{
				m_collisionRect.h = m_rangeMax;
				SOMA::PlaySound("spear");
			}

			else if (m_iSprite == 3 || m_iSprite == 5)
				m_collisionRect.h = m_rangeMax * 2 / 3;
			else
				m_collisionRect.h = m_rangeMax / 3;
			//m_collisionRect.h += m_moveRange;
			//
			//if (m_collisionRect.h >= m_rangeMax)
			//	m_moveRange = -m_moveRange;
			//else if (m_collisionRect.h <= 0)
			//	m_moveRange = -m_moveRange;
		}		
	}

	m_src.x = m_src.w * m_iSprite;
	m_src.y =  m_iSpriteYaxis;

	if(m_aniMods == ROLLWALL)
	{
		m_collisionRect = m_dst;
		m_collisionRect.h = 320;
	}
	else if (m_aniMods == SAW)
	{
		m_collisionRect = m_dst;
		m_collisionRect.x += 30;
		m_collisionRect.w -= 60;
	}
	if (m_aniMods == SPEARNONFLIP || m_aniMods == SPEARFLIP)
	{
		m_collisionRect.x = m_dst.x + 30;
		m_collisionRect.w = m_dst.w-60;
	}

}

void Obstacle::Render()
{
	if(m_aniMods == SPEARFLIP)
	{
		SDL_Rect tempSrc = { 0,525,200,250 };
		SDL_FRect tempDst = {m_dst.x-10,m_dst.y-209,200,250};	
		//tempDst.y -= 300;
		
		SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("obstacles"),
			&tempSrc, &tempDst, 0, nullptr, SDL_FLIP_NONE);
	}

	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("obstacles"),
		&m_src, &m_dst, 0, nullptr, m_flip);
//	SDL_RenderDrawRectF(Engine::Instance().GetRenderer(), &m_collisionRect);

}


