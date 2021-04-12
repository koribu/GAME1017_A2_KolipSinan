#pragma once
#include <vector>
#include "Obstacle.h"

class ObstacleManager :public GameObject
{
private:
	vector<Obstacle*> m_obstacles;
	int m_spawnCounter;

	bool m_gameOver;
public:
	ObstacleManager();
	~ObstacleManager();

	void Update();
	void Render();

	void gameOver();

	vector<Obstacle*>* getObstacles();
};

