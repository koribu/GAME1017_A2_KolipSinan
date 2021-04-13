#include "ObstacleManager.h"

ObstacleManager::ObstacleManager()
{
	m_spawnCounter = 0;
	srand(time(NULL));

	m_gameOver = false;
}

ObstacleManager::~ObstacleManager()
{
	for (int i = 0; i < m_obstacles.size(); ++i)
	{
		delete m_obstacles[i];
		m_obstacles[i] = nullptr;
	}
}

void ObstacleManager::Update()
{
	for (int i=0;i< m_obstacles.size();i++)
	{
		if(m_obstacles[i]->GetDst()->x<-200)
		{
			delete m_obstacles[i];
			m_obstacles[i] = nullptr;
			m_obstacles.erase(m_obstacles.begin() + i);
			m_obstacles.shrink_to_fit();
			cout << "obstacle dead now";
		}
	}
	
	if (!m_gameOver)
	{
		m_spawnCounter++;
		for (Obstacle* obstacle : m_obstacles)
		{
			obstacle->Update();
		}

		if (m_spawnCounter > 150 + rand() % 75)
		{
			m_obstacles.push_back(new Obstacle({ 0,0,0,0 }, { 1100,400,0,0 }, static_cast<ObstacleTypes>(rand() % 3)));
			m_spawnCounter = 0;
		}
	}
}

void ObstacleManager::Render()
{
	for (Obstacle* obstacle : m_obstacles)
	{
		obstacle->Render();
	}
}

void ObstacleManager::gameOver()
{
	m_gameOver = true;
}

vector<Obstacle*>* ObstacleManager::getObstacles()
{
	return &m_obstacles;
}
