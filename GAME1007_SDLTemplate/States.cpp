#include "States.h"

#include <fstream>

#include "StateManager.h"
#include "TextureManager.h"
#include "Engine.h"
#include "SoundManager.h"
#include "Button3.h"

#include "CollisionManager.h"
#include "EventManager.h"
#include "Primitives.h"

#include <iostream>

#include "Background.h"
#include "FontManager.h"
#include "ObstacleManager.h"
#include "Player.h"


using namespace std;

string bestTime;
string lastTime;

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::Resume(){}

GameObject* State::GetGo(const std::string& s)
{ // Using 'std' just to show origin.
	auto it = std::find_if(m_objects.begin(), m_objects.end(), 
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == s;
		});
	if (it != m_objects.end())
		return it->second;
	else return nullptr;
}

auto State::GetIt(const std::string& s)
{ 
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == s;
		});
	return it;
}

// Begin TitleState
TitleState::TitleState(){}

void TitleState::Enter()
{
	TEMA::Load("Img/button.png", "play");
	TEMA::Load("Img/TitleBack.jpg", "bg");

	
	m_objects.push_back(pair<string, GameObject*>("bg",
		new Image({ 0, 0, 1920, 1200 }, { 0, 0, 1024, 768 }, "bg")));
	m_objects.push_back(pair<string, GameObject*>("play",
		new PlayButton({ 0, 0, 400, 100 }, { 412, 200, 200, 50 }, "play")));
	
	SOMA::AllocateChannels(16);
	SOMA::SetMusicVolume(32);
	SOMA::PlayMusic("title", -1, 2000);
}

void TitleState::Update()
{
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	State::Render();
}

void TitleState::Exit()
{
	TEMA::Unload("play");
	TEMA::Unload("bg");
	
	SOMA::StopMusic();
	SOMA::Unload("title", SOUND_MUSIC);
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr; // ;)
	}
}
// End TitleState

// Begin GameState
GameState::GameState(){}

void GameState::Enter() // Used for initialization.
{
	m_dyingCounter = 0;

	SOMA::Load("Aud/jump.wav", "jump", SOUND_SFX);
	SOMA::Load("Aud/dying.wav", "dying", SOUND_SFX);
	SOMA::Load("Aud/spearSound.wav", "spear", SOUND_SFX);
	SOMA::Load("Aud/Machadeiro.mp3", "song", SOUND_MUSIC);

	SOMA::SetSoundVolume(16);
	SOMA::SetMusicVolume(5);
	SOMA::PlayMusic("song", -1, 2000);
	
	TEMA::Load("Img/background.png", "background");
	TEMA::Load("Img/player.png", "player");
	TEMA::Load("Img/obstacles.png", "obstacles");

	FOMA::Load("Img/ltype.TTF", "Label", 24);
	
	m_objects.push_back(pair<string, GameObject*>("background",
			new Background({ 0, 0, 1024, 768 }, { 0, 0, 1024, 768 }, 1)));
	m_objects.push_back(pair<string, GameObject*>("background",
		new Background({ 0, 0, 1024, 768 }, { 1024, 0, 1024, 768 }, 1)));
	m_objects.push_back(pair<string, GameObject*>("background",
		new Background({ 1024, 0, 1024, 768 }, { 0, 0, 1024, 768 }, 2)));
	m_objects.push_back(pair<string, GameObject*>("background",
		new Background({ 1024, 0, 1024, 768 }, { 1024, 0, 1024, 768 }, 2)));
	m_objects.push_back(pair<string, GameObject*>("background",
		new Background({ 2048, 0, 1024, 768 }, { 0, 0, 1024, 768 }, 3)));
	m_objects.push_back(pair<string, GameObject*>("background",
		new Background({ 2048, 0, 1024, 768 }, { 1024, 0, 1024, 768 }, 3)));

	m_objects.push_back(pair<string, GameObject*>("OBMA",
		new ObstacleManager()));
	
	m_objects.push_back(pair<string, GameObject*>("background",
		new Background({ 3072, 0, 1024, 768 }, { 0, 0, 1024, 768 }, 5)));
	m_objects.push_back(pair<string, GameObject*>("background",
		new Background({ 3072, 0, 1024, 768 }, { 1024, 0, 1024, 768 }, 5)));

	

	m_objects.push_back(pair<string, GameObject*>("Player",
		new Player({ 0,0,50,37 }, { 200,300,100,74 })));
	

	bestTime = m_timer.GetTime();
	m_dyingCounter++;

	ifstream file;
	file.open("time.txt");
	file >> bestTime;
	file.close();
	string temp;
	temp = "Timer: 0     Best Time: " + bestTime;
	
	m_label = new Label("Label", 400, 50, temp.c_str());
	m_timer.Start();
	SOMA::PlayMusic("song");
}

void GameState::Update()
{

	auto obs = static_cast<ObstacleManager*>(GetGo("OBMA"));
	auto p = static_cast<Player*>(GetGo("Player"));


	
	if (EVMA::KeyPressed(SDL_SCANCODE_X))
	{
		STMA::ChangeState(new TitleState());
		return;
	}
	else if(EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		m_timer.Pause();
		STMA::PushState(new PauseState());
		return;

	}
	else if (EVMA::KeyPressed(SDL_SCANCODE_U))
	{
		STMA::ChangeState(new LoseState());
		return;
	}

	if (p->isDead())
	{
		lastTime = m_timer.GetTime();
		int a = atoi(bestTime.c_str());
		int b = atoi(m_timer.GetTime().c_str());
		if(b>a)
		{
			bestTime = m_timer.GetTime();
			ofstream file;
			file.open("time.txt");
			file << bestTime;
			file.close();
		}

		m_dyingCounter++;
		if (m_dyingCounter > 100)
		{
			STMA::ChangeState(new LoseState());
			return;
		}
		p->Update();		
	}
	else
	{
		m_timer.Update();
		for (auto const& i : m_objects)
		{

			
			i.second->Update();
			if (STMA::StateChanging()) return;
		}
	}


	


	for (int i = 0; i < obs->getObstacles()->size(); ++i)
	{
		if(COMA::AABBCheck(p->getCollisionRect(),obs->getObstacles()->operator[](i)->getCollisionRect()))
		{
			p->setDead();
			obs->gameOver();
		}
	}
	
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	if(m_timer.HasChanged())
	{
		string temp = "Timer: " + m_timer.GetTime() + "     Best Time: "+ bestTime;
		m_label->SetText(temp.c_str());
	}
	m_label->Render();
	if ( dynamic_cast<GameState*>(STMA::GetStates().back()) ) // Check to see if current state is of type GameState
		State::Render();
	
}


void GameState::Exit()
{
	TEMA::Unload("background");
	TEMA::Unload("player");
	TEMA::Unload("obstacles");
	FOMA::Unload("Label");
	SOMA::StopSound();
	SOMA::StopMusic();
	SOMA::Unload("jump", SOUND_SFX);
	SOMA::Unload("dying", SOUND_SFX);
	SOMA::Unload("spear", SOUND_SFX);
	SOMA::Unload("song", SOUND_MUSIC);
	for (auto& i : m_objects)
	{
		delete i.second; // De-allocating GameObject*s
		i.second = nullptr; // ;)
	}
}

void GameState::Resume() { m_timer.Resume(); }

PauseState::PauseState(){}

void PauseState::Enter()
{
	TEMA::Load("Img/resumebutton.png", "resume");
	m_objects.push_back(pair<string, GameObject*>("resume",
		new ResumeButton({ 0, 0, 400, 100 }, { 412, 384, 200, 50 }, "resume")));

}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
		STMA::PopState();

	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
}

void PauseState::Render()
{
	STMA::GetStates().front()->Render();

	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 128);
	SDL_Rect rect = {156,128,712,512};
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);

	for (auto const& i : m_objects)
		i.second->Render();
	State::Render();


}

void PauseState::Exit()
{

	TEMA::Unload(( "resume"));

	for (auto& i : m_objects)
	{
		delete i.second; // De-allocating GameObject*s
		i.second = nullptr; // ;)
	}
}

void PauseState::Resume()
{
}

// End GameState

// Begin of Lose State

LoseState::LoseState(){}

void LoseState::Enter()
{
	TEMA::Load("Img/menubutton.png", "menu");
	TEMA::Load("Img/LoseBack.jpg", "losebg");

	FOMA::Load("Img/ltype.TTF", "Label", 24);
	
	m_objects.push_back(pair<string, GameObject*>("LoseBg",
		new Image({ 0, 0, 1920, 1200 }, { 0, 0, 1024, 768 }, "losebg")));
	m_objects.push_back(pair<string, GameObject*>("MainMenu",
		new MainMenuButton({ 0, 0, 400, 100 }, { 412, 384, 200, 50 }, "menu")));

	string temp = "     Last Time: " +lastTime+   "     Best Time: " + bestTime;
	m_label = new Label("Label", 250, 550, temp.c_str());

}

void LoseState::Update()
{
	for (auto const& i : m_objects)
		i.second->Update();
	if (STMA::StateChanging()) return;
}

void LoseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 100, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	//for (auto const& i : m_objects)
	//	i.second->Render();
	for (auto const& i : m_objects)
		i.second->Render();

	m_label->Render();
	
	State::Render();
}

void LoseState::Exit()
{
	TEMA::Unload("menu");
	TEMA::Unload("losebg");
	FOMA::Unload("Label");
	for (auto& i : m_objects)
	{
		delete i.second; // De-allocating GameObject*s
		i.second = nullptr; // ;)
	}
}

void LoseState::Resume(){}

// End of Lose State

