#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include <time.h>
#include "SDL_mixer.h"


#define FPS 60
#define WIDTH 1024
#define HEIGHT 768
//#define SPEED 5;

using namespace std;


class Engine
{
private: // private properties 
	bool m_running = false;
	Uint32 m_start,m_startLast, m_end, m_delta, m_fps;
	double m_deltaTime;
	const Uint8* m_keystates;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	

	//SDL_Rect m_dest; // Rectangle struct  with four integers: x y w(width) h(height).
	int m_speed = 5;
	//vector<Bullet*> m_bullets,m_eBullets;
	//vector<Enemy*> m_enemys;
	//vector<Asteroid*> m_asteroids;
	//int timerSpawn=0, timerShoot = 0,timerAsteroid = 0;



private: // private method prototypes.
	int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
	void Clean();
	void Wake();
	void HandleEvent();
	
	void Update();
	void Render();
	void Sleep();


public: // public method prototypes.
	int Run();

	static Engine& Instance();
	SDL_Renderer* GetRenderer() { return m_pRenderer; }
	double GetDeltaTime() const { return m_deltaTime; }
	bool& Running();
	void SetRunning(const bool b);
};

#endif // !_ENGINE_H_

//Reminder: you can ONLY have declarations in headers, not logical code.