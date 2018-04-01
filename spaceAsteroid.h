#pragma once
#include "spaceObject.h"
const float LARGE_VELOCITY = 25.0f;
const float MED_VELOCITY = 45.0f;
const float SMALL_VELOCITY = 70.0f;


class spaceAsteroid :public spaceObject
{
public:
	static void loadBuffer(lort::Shader * shader);
	spaceAsteroid(lort::Shader *shader);
	spaceAsteroid();
	static unsigned int VAO_LARGE;
	static unsigned int VAO_MED;
	static unsigned int VAO_SMALL;
	static int LARGE_VERTS;
	static int MED_VERTS;
	static int SMALL_VERTS;
	static  int currentAsteroids;
	~spaceAsteroid();
	void draw(lort::Shader *shader, float deltatime);
	void destroy(std::vector<spaceAsteroid>& _Asteroids, int pX, int pY);
	bool initAsteroid(int STATE/*4 2 1 LARGE MED SMALL*/, int pX, int pY);
	bool initAsteroid(int STATE/*4 2 1 LARGE MED SMALL*/);
	//GETTERS
	
	float getPosX();
	float getPosY();
	Collider getCollider();
	float getRotateAngle();
	int getCurrentStateMask();



	
	
	
private :
	static float *largeAsteroid;
	static float *mediumAsteroid;
	static float *smallAsteroid;
	void update(float deltatime);
	int _CURRENT_STATE_MASK; //starts with 4 (Big Asteroid) divided by 2 each time it destroyed 
							//and Created 2 of its smaller size until it vanish 
	//initial position should be any place on edges of screen so 
	// either y or x = camera constraint and the other random
	float _posX;
	float _posY;
	float _rotateAngle;//RANDOM NUMBER 
	Collider _collider;


	
};

