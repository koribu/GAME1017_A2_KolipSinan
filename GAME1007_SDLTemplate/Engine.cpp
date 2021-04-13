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


//	STMA::PushState(new GameState());
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
}

void Engine::Render()
{
	STMA::Render();
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

