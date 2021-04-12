#pragma once
#include <vector>
#include "Obstacle.h"

class ObstacleManager :public GameObject
{
private:
	vector<Obstacle*> m_obstacles;
	int m_spawnCounter;
public:
	ObstacleManager();
	~ObstacleManager();

	void Update();
	void Render();

	vector<Obstacle*>* getObstacles();
};

