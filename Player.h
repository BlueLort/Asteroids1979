#pragma once
#include "spaceObject.h"
#include "UFO.h"
enum player_movement {
	FORWARD,
	LEFT,
	RIGHT,
	FIRE
};


class Player : public spaceObject
{
	
public:

	Player(lort::Shader *shader);
	~Player();
	void ProcessKeyboard(player_movement direction, float deltaTime,lort::Shader* shader, std::vector<Bullet>& bullets);
	void draw(lort::Shader *shader, float deltatime);
	void static loadBuffer(lort::Shader *shader);
	Collider collider;
	float POSITIONX = 0.0f;
	float POSITIONY = 0.0f;
	bool hit_Able;
	bool alive=true;
	//Destroyed Objects Count
	int destroy_count = 0;
	bool Death();
	void reset();
	// setters
	void setScore(float x) {
		_score=x;
	}
	//getters
	float getScore() {
		return _score;
	}
	int getLives() {
		return _lives;
	}
	float _vunerable_time;
	
protected:
	
	float _score;
	std::vector<Bullet> _bullets;

	float velocity = 0.0f;
	float rotateAngle = 0.0f;
	float currentAngle = 0.0f;
	int _lives;

private:
	static int verticies_count;
	static float* verticies;
	static float *thrust;
	static float *miniThrust;
	static unsigned int _VBO_PLAYER;
	static unsigned int _VAO_PLAYER;
	static unsigned int _VBO_THRUST;
	static unsigned int _VAO_THRUST;

	
};

