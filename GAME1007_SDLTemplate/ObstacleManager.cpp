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
	if (!m_gameOver)
	{
		m_spawnCounter++;
		for (Obstacle* obstacle : m_obstacles)
		{
			obstacle->Update();
		}

		if (m_spawnCounter > 100 + rand() % 40)
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
