#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include "GameObject.h"
#include "Primitives.h"
#include "Timer.h"

class State // This is the abstract base class for all states
{
public:
	virtual void Enter() = 0; // = 0 means pure virtual - must be defined in subclass
	virtual void Update() = 0; 
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume(); 
	virtual ~State() {} // or = default;
	GameObject* GetGo(const std::string& s);
	auto GetIt(const std::string& s);
protected: // Private but inherited
	State() {} // What does this prevent?
	vector<std::pair<std::string, GameObject*>> m_objects;
	
};

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class GameState : public State
{
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
	int score;
	int m_dyingCounter;

	Label* m_label ;
	Timer m_timer;
};

class PauseState : public State
{
public:
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();

};

class LoseState : public State
{
public:
	LoseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
};

class WinState : public State
{
public:
	WinState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
};

#endif

