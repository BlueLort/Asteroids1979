#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vertex.h"
#include <vector>
#include "Shader.h"
#include <ctime>
#define PI 3.1415926535897f
const float CAMERA_CONSTRAINT = 150.0f;
const float BULLET_VELOCITY = 70.0f;
const float POINT_VELOCITY = 8.0f;
const float UFO_VELOCITY = 45.0f;
struct Collider {
	float sizeX;
	float sizeY;
	bool rect;//RECTANGLE COLLIDER
		void init(float x, float y) {
		sizeX = x;
		sizeY = y;
	}

};
struct Point {
	static unsigned int VAO;
	static int POINT_COUNT;
	float lifeTime = 2.0f;//2.0 secs;
	float posX;
	float posY;
	float rotateAngle;
	void initPoint(int x, int y) {
		posX = x + (rand() % 2) - 0.4f;
		posY = y + (rand() % 2) - 0.4f;
		rotateAngle = rand() % 360;
		POINT_COUNT++;
	}
	void draw(lort::Shader *shader, float deltatime) {
		update(deltatime);

		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(posX, posY, 0.0f));
		trans = glm::rotate(trans, glm::radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
		shader->setUniformMat4("transform", 1, GL_FALSE, glm::value_ptr(trans));
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);

	}
	void update(float deltatime) {
		lifeTime -= deltatime;
		posY += POINT_VELOCITY*glm::cos(glm::radians(rotateAngle))*deltatime;
		posX += -POINT_VELOCITY*glm::sin(glm::radians(rotateAngle))*deltatime;
		if (posY > CAMERA_CONSTRAINT)posY = -CAMERA_CONSTRAINT;
		if (posY< -CAMERA_CONSTRAINT)posY = CAMERA_CONSTRAINT;
		if (posX> CAMERA_CONSTRAINT)posX= -CAMERA_CONSTRAINT; 
		if (posX< -CAMERA_CONSTRAINT)posX = CAMERA_CONSTRAINT;


	}

};

class spaceObject
{
public:
	
	spaceObject();
	spaceObject(lort::Shader *shader);
	~spaceObject();
	virtual void draw(lort::Shader *shader, float deltatime);
	 static void load_buffers();
	static void wrapPOS(float &y, float &x);
	void destruction(float posX, float posY, std::vector<Point>& _Point);
	
protected:
	static void loadBulletBuffer();
	static void loadCrashBuffer();
	int _count;
	static float *bullet;

	static float *crashPoint;

	


	static glm::mat4 MODEL_MATRIX;
	float speed;
	float acceleration;
	/*FUNCTIONS*/
	
};



struct Bullet {
	static unsigned int VAO;
	static int PLAYER_COUNT;
	static int UFO_COUNT;
	float lifeTime = 3.0f;//3.0 secs;
	float posX = 0.0f;
	float posY = 0.0f;//a little shift
	glm::vec2 dir;
	bool enemy = false;

	float rotateAngle = 0.0f;
	Collider collider;
	void initCollider() {
		collider.init(0.4f, 1.0f);
	}
	void draw(lort::Shader *shader, float deltatime) {
		update(deltatime);

		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(posX, posY, 0.0f));
		trans = glm::rotate(trans, glm::radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
		shader->setUniformMat4("transform", 1, GL_FALSE, glm::value_ptr(trans));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

	}
	void update(float deltatime) {
		lifeTime -= deltatime;
		if (!enemy) {
			posY += BULLET_VELOCITY*glm::cos(glm::radians(rotateAngle))*deltatime;
			posX += -BULLET_VELOCITY*glm::sin(glm::radians(rotateAngle))*deltatime;
		}
		else {
			posY += BULLET_VELOCITY*dir.y*deltatime;
			posX += -BULLET_VELOCITY*dir.x*deltatime;
		}
		spaceObject::wrapPOS(posY, posX);

	}
};

