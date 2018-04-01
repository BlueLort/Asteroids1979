#pragma once
#include "spaceObject.h"
class UFO : public spaceObject
{
public:
	UFO();
	~UFO();
	void initUFO();
	void draw(lort::Shader *shader, float deltatime, std::vector<Bullet>& bullet);
	//GETTERS
	Collider getCollider();
	float getPosX();
	float getPosY();
	////////////////
	//STATIC MEMBERS
	static int UFO_COUNT;
	static unsigned int _VAO;
	static float _PLAYER1X, _PLAYER1Y;
	static void loadBuffer();
private:
	/**
	*	CALLED EACH TIME WE DRAW TO UPDATE UFO STATS
	*/
	void update(float deltatime, std::vector<Bullet>& bullet);
	
	Collider _collider;
	//initial position should be y place on edges of screen so 
	// x = camera constraint and the other random
	float _posX;//UFO POSITION ON X
	float _posY;//UFO POSITION ON Y
	bool _directionIsRight;//i had to check which direction the UFO MOVES 
	float _cooldown = 0.5f;//0.5sec cooldown between each shot
	static float *_ufo;

};




	
	
	
