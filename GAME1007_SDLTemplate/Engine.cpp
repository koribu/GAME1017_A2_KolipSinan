#include "Engine.h"



#include "EventManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "States.h"
#include "TextureManager.h"


int Engine::Init(const char* title, int xPos, int yPos, int width, int height, int flags)
{
	cout << "Initializing engine..." << endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)//If initialization okay...
	{
		// Create the SDL window...
		m_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (m_pWindow != nullptr)
		{
			//Create the SDL renderer... (back buffer)
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, NULL);
			if (m_pRenderer != nullptr)
			{
				TEMA::Init();
				EVMA::Init();
				SOMA::Init();
			}
			else return false; // Renderer creation failed.
		}
		else return false; // Window creation failed.
	}
	else return false; // Initialization failed.
	m_fps = (Uint32)round((1.0 / (double)FPS) * 1000); // Converts FPS into milliseconds, e.g 16.67
	m_keystates = SDL_GetKeyboardState(nullptr);
	m_startLast = SDL_GetTicks();
	/*g_dest.x = 512;
	g_dest.y = 384;
	g_dest.w = 100;
	g_dest.h = 200;*/
	//m_player.SetReks({ 0,0,512,512 }, { 200,200,512 / 4,512 / 4 }); // First {} is source rectangle, and second {} destination rect 
	//m_bg1.SetReks({ 0,0,1024,768 }, { 0,0,1024,768 });
	//m_bg2.SetReks({ 0,0,1024,768 }, { 1024 ,0,1024,768 });
	//


	STMA::PushState(new TitleState());
	
	m_running = true;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
	m_deltaTime = (m_start - m_startLast) / 1000.0;
	m_startLast = m_start;
}

void Engine::HandleEvent()
{
	EVMA::HandleEvents();
}

void Engine::Update()
{
	STMA::Update();




	//// Parse player movement.
	//if (KeyDown(SDL_SCANCODE_W) && m_player.GetDst()->y > 0)
	//{
	//	m_player.GetDst()->y -= m_speed;
	//}
	//else if (KeyDown(SDL_SCANCODE_S) && m_player.GetDst()->y < HEIGHT - m_player.GetDst()->h)
	//{
	//	m_player.GetDst()->y += m_speed;
	//}
	//if (KeyDown(SDL_SCANCODE_A) && m_player.GetDst()->x > 0)
	//{
	//	m_player.GetDst()->x -= m_speed;
	//}
	//else if (KeyDown(SDL_SCANCODE_D) && m_player.GetDst()->x < WIDTH - m_player.GetDst()->w)
	//{
	//	m_player.GetDst()->x += m_speed;
	//}
	///*if (KeyDown(SDL_SCANCODE_EQUALS)) // +
	//	m_speed++;
	//if (KeyDown(SDL_SCANCODE_MINUS)) //-
	//	m_speed--;// Note: if you go under 0, you go opposite speed*/
	//for (unsigned i = 0; i < m_bullets.size(); i++)//size() is actual filled number of elements.
	//	m_bullets[i]->Update();// -> combines dereference and member access. long way:(*banana).Update()


	//for (unsigned i = 0; i < m_bullets.size(); i++)
	//{
	//	if (m_bullets[i]->GetRekt()->x >= 1024)//off-screen.
	//	{
	//		delete m_bullets[i]; //Flag for reallocation.
	//		m_bullets[i] = nullptr;//Wrangle your dangle
	//		m_bullets.erase(m_bullets.begin() + i);
	//		m_bullets.shrink_to_fit();//reduces capacity to size
	//		break;
	//	}
	//}
	//for (unsigned i = 0; i < m_eBullets.size(); i++)
	//{
	//	if (m_eBullets[i]->GetRekt()->x <= -100)
	//	{
	//		delete m_eBullets[i]; 
	//		m_eBullets[i] = nullptr;
	//		m_eBullets.erase(m_eBullets.begin() + i);
	//		m_eBullets.shrink_to_fit();
	//		break;
	//	}
	//}


	//if (timerSpawn > FPS*3)
	//{
	//	m_enemys.push_back(new Enemy());
	//	timerSpawn = 0;
	//}
	//timerSpawn++;
	//if (timerShoot > FPS)
	//{
	//	for (unsigned j = 0; j < m_enemys.size(); j++)
	//	{
	//		m_eBullets.push_back(new Bullet({ m_enemys[j]->GetRekt()->x,m_enemys[j]->GetRekt()->y +50}));
	//		Mix_PlayChannel(-1, m_eShot, 0);
	//	}
	//	timerShoot = 0;
	//}
	//timerShoot++;
	//if (timerAsteroid > FPS * 5)
	//{
	//	int num = 3 + rand()%6;
	//	
	//	
	//	for (int j = 0; j < num; j++)
	//	{
	//		int total = m_asteroids.size();
	//		m_asteroids.push_back(new Asteroid());
	//		
	//		if (total > 1&&(m_asteroids[total - 1]->GetRekt()->y) == (m_asteroids[total]->GetRekt()->y))
	//			m_asteroids.pop_back();
	//	}
	//	timerAsteroid = 0;
	//}
	//timerAsteroid++;

	//for (unsigned i = 0; i < m_asteroids.size(); i++)
	//{
	//	m_asteroids[i]->GetRekt()->x-= m_speed/2;
	//	m_asteroids[i]->Update();
	//	if (SDL_HasIntersection(m_asteroids[i]->GetRekt(), m_player.GetDst()) && m_pTexture != nullptr)
	//	{
	//		Mix_PlayChannel(-1, m_astrExplosion, 0);
	//		m_player.~Sprite();
	//		m_pTexture = nullptr;
	//	}
	//	if (m_asteroids[i]->GetRekt()->y < -50)
	//	{
	//		delete m_asteroids[i];
	//		m_asteroids[i] = nullptr;
	//		m_asteroids.erase(m_asteroids.begin() + i);
	//		m_asteroids.shrink_to_fit();
	//		break;
	//	}
	//}
	//for (unsigned q = 0; q < m_asteroids.size(); q++)
	//{
	//	for(unsigned i = 0;i<m_bullets.size();i++)
	//	if (SDL_HasIntersection(m_bullets[i]->GetRekt(), m_asteroids[q]->GetRekt()))
	//	{
	//		Mix_PlayChannel(-1, m_astrExplosion, 0);;
	//		delete m_bullets[i];
	//		m_bullets[i] = nullptr;
	//		m_bullets.erase(m_bullets.begin() + i);
	//		m_bullets.shrink_to_fit();
	//		delete m_asteroids[q];
	//		m_asteroids[q] = nullptr;
	//		m_asteroids.erase(m_asteroids.begin() + q);
	//		m_asteroids.shrink_to_fit();
	//		break;
	//	}
	//}
	//for (unsigned i = 0; i < m_eBullets.size(); i++)
	//{
	//	m_eBullets[i]->UpdateE();
	//	if (SDL_HasIntersection(m_eBullets[i]->GetRekt(), m_player.GetDst())&& m_pTexture != nullptr)
	//	{
	//		Mix_PlayChannel(-1, m_explosion, 0);
	//		delete m_eBullets[i];
	//		m_eBullets[i] = nullptr;
	//		m_eBullets.erase(m_eBullets.begin() + i);
	//		m_eBullets.shrink_to_fit();
	//		m_player.~Sprite();
	//		m_pTexture = nullptr;	
	//		break;
	//	}
	//
	//}
	//for (unsigned j = 0; j < m_enemys.size(); j++)
	//{
	//	m_enemys[j]->GetRekt()->x -= m_speed;
	//	if (SDL_HasIntersection(m_enemys[j]->GetRekt(), m_player.GetDst()) && m_pTexture != nullptr)
	//	{
	//		Mix_PlayChannel(-1, m_explosion, 0);
	//		m_player.~Sprite();
	//		m_pTexture = nullptr;
	//	}
	//}

	//for (unsigned i = 0; i < m_bullets.size(); i++)
	//{
	//	for (unsigned j = 0; j < m_enemys.size(); j++)
	//	{
	//		if (SDL_HasIntersection(m_bullets[i]->GetRekt(), m_enemys[j]->GetRekt()))
	//		{
	//			Mix_PlayChannel(-1, m_explosion, 0);
	//			delete m_bullets[i];
	//			m_bullets[i] = nullptr;
	//			m_bullets.erase(m_bullets.begin() + i);
	//			m_bullets.shrink_to_fit();
	//			delete m_enemys[j];
	//			m_enemys[j] = nullptr;
	//			m_enemys.erase(m_enemys.begin() + j);
	//			m_enemys.shrink_to_fit();
	//			break;
	//		}
	//	}

	//}
	//for (unsigned j = 0; j < m_enemys.size(); j++)
	//{
	//	if (m_enemys[j]->GetRekt()->x <= -100)
	//	{
	//		
	//		delete m_enemys[j];
	//		m_enemys[j] = nullptr;
	//		m_enemys.erase(m_enemys.begin() + j);
	//		m_enemys.shrink_to_fit();

	//		break;

	//	}
	//}

}

void Engine::Render()
{
	STMA::Render();


	//
	//SDL_SetRenderDrawColor(m_pRenderer, 100, 128, 128, 255);
	//SDL_RenderClear(m_pRenderer);
	//// Any drawing here...
	///*SDL_SetRenderDrawColor(m_pRenderer, 0, 128, 128, 255);
	//SDL_RenderDrawRect(m_pRenderer, &m_dest);
	//SDL_RenderFillRect(m_pRenderer, &m_dest);*/

	//
	//SDL_RenderCopy(m_pRenderer, m_pBGTexture, m_bg1.GetSrc(), m_bg1.GetDst());
	//SDL_RenderCopy(m_pRenderer, m_pBGTexture, m_bg2.GetSrc(), m_bg2.GetDst());
	//for (int i = 0; i < m_bullets.size(); i++)
	//	m_bullets[i]->Render(m_pRenderer);
	//for (int i = 0; i < m_enemys.size(); i++)
	//	m_enemys[i]->Render(m_pRenderer, m_eTexture);
	//for (int i = 0; i < m_asteroids.size(); i++)
	//	m_asteroids[i]->Render(m_pRenderer, m_astTexture);
	//for (int i = 0; i < m_eBullets.size(); i++)
	//	m_eBullets[i]->RenderE(m_pRenderer);





	//SDL_RenderCopyEx(m_pRenderer, m_pTexture, m_player.GetSrc(), m_player.GetDst(), 90.0, NULL, SDL_FLIP_NONE);


	//SDL_RenderPresent(m_pRenderer); // flip buffers - send data to window.

}


void Engine::Sleep()
{
	m_end = SDL_GetTicks(); // GetTicks return time in ms since initialization

	m_delta = m_end - m_start;
	if (m_delta < m_fps)
		SDL_Delay(m_fps - m_delta);
}


int Engine::Run()
{
	
	if (m_running)
	{
		return 1;
	}
	//Start and run the "engine"
	if (Init("GAME1007 M1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL) == false) //may NULL => SDL_WINDOW_RESIZABLE
	{
		return 2;
	}
	// We passed pur initial checks, start the loop!
	while (m_running == true)
	{
		Wake();
		HandleEvent();  // Input
		Update();		// Processing	
		Render();		// Output
		if (m_running == true)
			Sleep();
	}
	Clean();
	return 0;

}

Engine& Engine::Instance()
{
	static Engine instance;// Magic Statics. Creating the object.
	return instance;
}


void Engine::Clean()
{
	//cout << "Cleaning engine..." << endl;
	//for (unsigned i = 0; i < m_bullets.size(); i++)
	//{
	//	delete m_bullets[i]; //Flag for reallocation.
	//	m_bullets[i] = nullptr;//Wrangle your dangle
	//}
	//for (unsigned i = 0; i < m_eBullets.size(); i++)
	//{
	//	delete m_eBullets[i]; 
	//	m_eBullets[i] = nullptr;
	//}
	//for (unsigned i = 0; i < m_enemys.size(); i++)
	//{
	//	delete m_enemys[i]; 
	//	m_enemys[i] = nullptr;
	//}
	//for (unsigned i = 0; i < m_asteroids.size(); i++)
	//{
	//	delete m_asteroids[i];
	//	m_asteroids[i] = nullptr;
	//}

	//m_asteroids.clear();
	//m_asteroids.shrink_to_fit();
	//m_bullets.clear();//wipe out all elements.
	//m_bullets.shrink_to_fit();//reduces capacity to size
	//m_eBullets.clear();
	//m_eBullets.shrink_to_fit();
	//m_enemys.clear();
	//m_enemys.shrink_to_fit();
	//
	
	STMA::Quit();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	TEMA::Quit();
	EVMA::Quit();
	SOMA::Quit();
	IMG_Quit();
	SDL_Quit();
}

bool& Engine::Running() { return m_running; } // Getter.
void Engine::SetRunning(const bool b) { m_running = b; }

