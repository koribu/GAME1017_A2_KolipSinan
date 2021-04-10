#pragma once
#ifndef _ASTEROIDSPRITES_H_
#define _ASTEROIDSPRITES_H_

#include "GameObject.h"
#include "SDL.h"
#include <vector>

class Bullet;

class Asteroid : public SpriteObject
{
public:
	Asteroid(SDL_Rect s, SDL_FRect d);
	void Update();
	void Render();
	const SDL_FPoint& GetCenter() { return m_center; }
	const double& GetRadius() { return m_radius; }
	void SetColMods(Uint8 r, Uint8 g, Uint8 b);
private:
	SDL_FPoint m_center;
	double m_angle,
		m_dx, m_dy,
		m_radius,
		m_rotSpeed;
	Uint8 m_rMod, m_gMod, m_bMod;
};

class Enemy : public SpriteObject
{
public:
	Enemy(SDL_Rect s, SDL_FRect d);
	void Update();
	void Render();
	const SDL_FPoint& GetCenter() { return m_center; }
	const double& GetRadius() { return m_radius; }
	void SetColMods(Uint8 r, Uint8 g, Uint8 b);
	vector<Bullet*>& GetBullets() { return m_bullets; }
private:
	SDL_FPoint m_center;
	double m_angle,
		m_dx, m_dy,
		m_radius;
	int m_timerShot, m_timerMax;
	
	vector<Bullet*> m_bullets;

};


class AsteroidField : public GameObject
{ // Manager class for the individual asteroids.
public:
	AsteroidField(unsigned int sz,int timer);
	~AsteroidField();
	void Update();
	void Render();
	vector<Asteroid*>& GetAsteroids() { return m_asteroids; }
	const unsigned int GetSize() { return m_size; }
private:
	vector<Asteroid*> m_asteroids;
	int m_size,m_timerAsteroid,m_timerMax;
};

class Bullet : public SpriteObject
{
public:
	Bullet(SDL_Rect s, SDL_FRect d, const char* key);
	void Update();
	void Render();
	const SDL_FPoint& GetCenter() { return m_center; }
	const double& GetRadius() { return m_radius; }
	void setDirect(int a) { m_direct = a; }
private:
	SDL_FPoint m_center;
	int m_ctr, m_ctrMax,m_direct;
	double m_angle,
		m_dx, m_dy,
		m_radius;
	std::string m_key;
};
class EnemyManager : public GameObject
{ // Manager class for the individual asteroids.
public:
	EnemyManager(unsigned int sz, int timer);
	~EnemyManager();
	void Update();
	void Render();
	vector<Enemy*>& GetEnemies() { return m_enemies; }
	const unsigned int GetSize() { return m_size; }
	
private:
	vector<Enemy*> m_enemies;
	int m_size, m_timerEnemy, m_timerMax;
	
};

class SpaceShip : public AnimatedSpriteObject
{
public: // Methods.
	SpaceShip(SDL_Rect s, SDL_FRect d);
	~SpaceShip();
	void Update();
	void Render();
	const SDL_FPoint& GetCenter() { return m_center; }
	const double& GetRadius() { return m_radius; }
	vector<Bullet*>& GetBullets() { return m_bullets; }
private: // Properties.
	SDL_FPoint m_center;
	double
		m_velX, m_velY,
		m_velMax,
		m_radius;

	enum PlayerState { STATE_IDLING, STATE_MOVING } m_state;
	vector<Bullet*> m_bullets;
};



#endif