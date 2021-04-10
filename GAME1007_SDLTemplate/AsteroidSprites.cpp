#include "AsteroidSprites.h"

#include "EventManager.h"
#include "SoundManager.h"
#include "MathManager.h"
#include "StateManager.h"
#include "States.h"

Asteroid::Asteroid(SDL_Rect s, SDL_FRect d) : SpriteObject(s, d),
                                              m_angle(0.0), m_radius(33.0)
{
	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
	m_rotSpeed = (1.0 + rand() % 5) * (rand() % 2 * 2.0 - 1.0); // -1 or 1
	MAMA::SetDeltas(MAMA::Deg2Rad((rand() % 360) - 90.0), m_dx, m_dy, 2.0f, 2.0f);
}

void Asteroid::Update()
{
	// Rotate and move object.
	m_angle += m_rotSpeed;
	m_center.x -= 5;

	// Update dest rectangle.
	m_dst.x = m_center.x - m_dst.w / 2;
	m_dst.y = m_center.y - m_dst.h / 2;

	
}

void Asteroid::Render()
{
	SDL_SetTextureColorMod(TEMA::GetTexture("sprites"), 255-m_rMod, 255-m_gMod, 255-m_bMod);
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("sprites"),
		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
	SDL_SetTextureColorMod(TEMA::GetTexture("sprites"), 255, 255, 255); // Resetting it so not all sprites are tinted this way.
}

void Asteroid::SetColMods(Uint8 r, Uint8 g, Uint8 b)
{
	m_rMod = r; m_gMod = g; m_bMod = b;
}

Enemy::Enemy(SDL_Rect s, SDL_FRect d) : SpriteObject(s, d),
m_angle(270.0), m_radius(33.0),m_timerShot(0),m_timerMax(30)
{
	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
}

void Enemy::Update()
{
	m_center.x -= 5;

	// Update dest rectangle.
	m_dst.x = m_center.x - m_dst.w / 2;
	m_dst.y = m_center.y - m_dst.h / 2;

	if (m_timerShot <= 0)
	{
		m_bullets.push_back(new Bullet({ 500, 0, 18, 24 },
			{ m_center.x, m_center.y, 18, 24 },
			"sprites"));
		m_bullets.back()->setDirect(-1);
		m_bullets.shrink_to_fit();
		m_timerShot = m_timerMax;
	}

	m_timerShot--;

	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->Update();
		if (!m_bullets[i]->GetEnabled())
		{
			delete m_bullets[i];
			m_bullets[i] = nullptr;
			m_bullets.erase(m_bullets.begin() + i);
			m_bullets.shrink_to_fit();
		}
	}

	for (unsigned i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->GetDst()->x >= 1024)//off-screen.
		{
			delete m_bullets[i]; //Flag for reallocation.
			m_bullets[i] = nullptr;//Wrangle your dangle
			m_bullets.erase(m_bullets.begin() + i);
			m_bullets.shrink_to_fit();//reduces capacity to size
			break;
		}
	}
}

void Enemy::Render()
{
	SDL_SetTextureColorMod(TEMA::GetTexture("bullet"), 255, 255, 255);
	for (const auto b : m_bullets)
	{
		SDL_SetTextureColorMod(TEMA::GetTexture("sprites"), 255, 0, 0);
		b->Render();
		SDL_SetTextureColorMod(TEMA::GetTexture("sprites"), 255, 255, 255);
	}
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("enemy"),
		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
}

void Enemy::SetColMods(Uint8 r, Uint8 g, Uint8 b)
{
}

AsteroidField::AsteroidField(unsigned int sz, int timer) :GameObject({ 0,0,0,0 }), m_size(sz)
{
	m_timerMax = timer;


}

AsteroidField::~AsteroidField()
{
	for (auto a : m_asteroids)
	{
		delete a;
		a = nullptr; // ;)
	}
	m_asteroids.clear();
}

void AsteroidField::Update()
{
	if (m_timerAsteroid <= 0)
	{
		for (int i = 0; i < m_size; i++)
		{
			m_asteroids.push_back(new Asteroid({ 539, 0, 61, 66 },
				{ 1050.0f, 25.0f+25.0f * (rand() % 30),
				61.0f, 66.0f }));
			m_asteroids.back()->SetColMods((rand() % 129), (rand() % 129), (rand() % 129));
		}
		m_timerAsteroid = m_timerMax;
	}
	
	m_timerAsteroid--;
	

	for ( auto a : m_asteroids)
	{
		a->Update();
	}
	
}

void AsteroidField::Render()
{
	for (const auto a : m_asteroids)
		a->Render();
}

Bullet::Bullet(SDL_Rect s, SDL_FRect d, const char* key):
	SpriteObject(s, d), m_key(key), m_angle(90), m_radius(10),m_direct(1),
	m_ctr(0), m_ctrMax(75)
{
	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
	MAMA::SetDeltas(MAMA::Deg2Rad(m_angle - 90.0), m_dx, m_dy, 10.0f, 10.0f);
}

void Bullet::Update()
{
	// Move object.
	m_center.x += (float)m_dx*m_direct;
	m_center.y += (float)m_dy;
	// Wrap on screen.
	if (m_center.x < -m_dst.w) m_center.x = WIDTH + m_dst.w / 2;
	else if (m_center.x > WIDTH + m_dst.w) m_center.x = 0 - m_dst.w / 2;
	else if (m_center.y < -m_dst.h) m_center.y = HEIGHT + m_dst.h / 2;
	else if (m_center.y > HEIGHT + m_dst.h) m_center.y = 0 - m_dst.h / 2;
	// Update dest rectangle.
	m_dst.x = m_center.x - m_dst.w / 2;
	m_dst.y = m_center.y - m_dst.h / 2;

}

void Bullet::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture(m_key),
		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
}

EnemyManager::EnemyManager(unsigned sz, int timer):m_timerEnemy(50)
{
	m_timerMax = timer;
	m_size = sz;
}

EnemyManager::~EnemyManager()
{
	for (auto a : m_enemies)
	{
		delete a;
		a = nullptr; // ;)
	}
	m_enemies.clear();
}

void EnemyManager::Update()
{
	if (m_timerEnemy <= 0)
	{
		for (int i = 0; i < m_size; i++)
		{
			m_enemies.push_back(new Enemy({ 0, 0, 600, 665 },
				{ 1050.0f, 25.0f + 25.0f * (rand() % 30),
				120.0f, 133.0f }));
		}
		m_timerEnemy = m_timerMax;
	}

	m_timerEnemy--;


	for (auto a : m_enemies)
	{
		a->Update();
	}
}

void EnemyManager::Render()
{
	for (const auto a : m_enemies)
	{
		a->Render();
	}
}

SpaceShip::SpaceShip(SDL_Rect s, SDL_FRect d) :
	AnimatedSpriteObject(s, d), m_state(STATE_IDLING), m_velMax(6.0), m_radius(38)
{
	m_velX = m_velY = 0.0;
	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
	SetAnimation(1, 0, 1);
}

SpaceShip::~SpaceShip()
{
	SOMA::StopSound(15);
	for (auto a : m_bullets)
	{
		delete a;
		a = nullptr; // ;)
	}
	m_bullets.clear();
}


void SpaceShip::Update()
{
	// Rotate player. State-independent.
	if (EVMA::KeyHeld(SDL_SCANCODE_W))
		m_dst.y -= 5;
	else if (EVMA::KeyHeld(SDL_SCANCODE_S))
		m_dst.y += 5;
	else if (EVMA::KeyHeld(SDL_SCANCODE_D))
		m_dst.x += 5;
	else if (EVMA::KeyHeld(SDL_SCANCODE_A))
		m_dst.x -= 5;
	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
	// Spawn bullet.
	if (EVMA::KeyPressed(SDL_SCANCODE_SPACE))
	{
		m_bullets.push_back(new Bullet({ 500, 0, 18, 24 },
			{ m_dst.x +25, m_dst.y + 36, 18, 24 },
			"sprites"));
		m_bullets.shrink_to_fit();
		SOMA::PlaySound("pLaser");
	}
	// Checking animation states.
	switch (m_state)
	{
	case STATE_IDLING:
		if (EVMA::KeyPressed(SDL_SCANCODE_S) || EVMA::KeyPressed(SDL_SCANCODE_W)|| EVMA::KeyPressed(SDL_SCANCODE_A)|| EVMA::KeyPressed(SDL_SCANCODE_D))
		{
			m_state = STATE_MOVING;
			SetAnimation(2, 0, 4);
		}
		break;
	case STATE_MOVING:

		// Check for idle transition.
		if (!EVMA::KeyHeld(SDL_SCANCODE_S) && !EVMA::KeyHeld(SDL_SCANCODE_W)&& !EVMA::KeyHeld(SDL_SCANCODE_A) && !EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			m_state = STATE_IDLING;
			SetAnimation(1, 0, 1);
		}
		break;
	}

	// Invoke the animation.
	Animate();
	// Update bullets.
	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->Update();
		if (!m_bullets[i]->GetEnabled())
		{
			delete m_bullets[i];
			m_bullets[i] = nullptr; 
			m_bullets.erase(m_bullets.begin() + i);
			m_bullets.shrink_to_fit();
		}
	}

	for (unsigned i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->GetDst()->x >= 1024)//off-screen.
		{
			delete m_bullets[i]; //Flag for reallocation.
			m_bullets[i] = nullptr;//Wrangle your dangle
			m_bullets.erase(m_bullets.begin() + i);
			m_bullets.shrink_to_fit();//reduces capacity to size
			break;
		}
	}
}

void SpaceShip::Render()
{
	for (const auto b : m_bullets)
		b->Render();
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("sprites"),
		&m_src, &m_dst, 90, nullptr, SDL_FLIP_NONE);
}