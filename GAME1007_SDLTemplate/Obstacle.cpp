#include "Obstacle.h"

Obstacle::Obstacle(SDL_Rect s, SDL_FRect d,ObstacleTypes type): SpriteObject(s,d)
{
	m_aniMods = type;
	m_flip = SDL_FLIP_NONE;
	m_collisionRect = m_dst;
	
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

		break;
	case SPEAR:
		m_flip = static_cast<SDL_RendererFlip>((rand() % 2)*2);
		if(m_flip == SDL_FLIP_NONE)
		{
			m_dst.h = 130;
			m_dst.y = 436;

			m_rangeMax = m_dst.h;
			m_moveRange = m_dst.h / 4;
			m_collisionRect.y -= m_collisionRect.h;
		}
		else if(m_flip == SDL_FLIP_VERTICAL)
		{
			m_dst.h = 130;
			m_dst.y = 380;

			m_rangeMax = m_dst.h;
			m_moveRange = m_dst.h / 4;
			m_collisionRect.h = 0;
		}
		
		m_src.w = 80;
		m_src.h = 130;
		m_dst.w = 80;

		m_iSpriteMax = 1;
		m_iSpriteYaxis = 0;


		 
		
		break;
	case ROLLWALL:
		m_src.w = 200;
		m_src.h = 350;
		m_dst.w = 200;
		m_dst.h = 350;
		m_dst.y = 200;
		m_iSpriteMax = 1;
		m_iSpriteYaxis = 175;
		break;
	}

	
	m_iSprite = m_iFrame = 0;
	m_iFrameMax = 5;

	m_speed = 3;
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update()
{
	m_iFrame++;
	if (m_iFrame == m_iFrameMax)
	{
		m_iFrame = 0;
		m_iSprite++;
		
		if (m_iSprite == m_iSpriteMax)
		{
			m_iSprite = 0;
		}

		if (m_aniMods == SPEAR)
		{
			if (m_flip == SDL_FLIP_NONE)
			{
				if (m_collisionRect.y > m_rangeMax)
					m_moveRange = -m_moveRange;
				else if (m_collisionRect.y < 0)
					m_moveRange = -m_moveRange;
				m_collisionRect.y += m_moveRange;
			}
			else if (m_flip == SDL_FLIP_VERTICAL)
			{
				if (m_collisionRect.h > m_rangeMax)
					m_moveRange = -m_moveRange;
				else if (m_collisionRect.h < 0)
					m_moveRange = -m_moveRange;
				m_collisionRect.h += m_moveRange;
			}

		}
	}

	m_src.x = m_src.w * m_iSprite;
	m_src.y =  m_iSpriteYaxis;


	m_dst.x -= 3;
}

void Obstacle::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("obstacles"),
		&m_src, &m_dst, 0, nullptr,m_flip);
	//if(m_flip == 2)
	//{
	//	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("obstacles"),
	//		&m_src, &(m_dst+{0,0,0,0}), 0, nullptr, SDL_FLIP_NONE);
	//}
}

SDL_FRect Obstacle::getCollisionRect()
{
	return m_collisionRect;
}

