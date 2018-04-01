#include "spaceObject.h"
glm::mat4 spaceObject::MODEL_MATRIX;
float* spaceObject::bullet;
float* spaceObject::crashPoint;
unsigned int	Bullet::VAO;
int Bullet::PLAYER_COUNT=0.0f;
int Bullet::UFO_COUNT=0.0f;

unsigned int	Point::VAO;
int	Point::POINT_COUNT = 0;
spaceObject::spaceObject()
{
}
spaceObject::spaceObject(lort::Shader *shader)
{
	/////////////////////////////////
	bullet = new float[3 * 3];

	bullet[0] = 0.5f;
	bullet[1] = -1.0f;
	bullet[2] = 0.0f;

	bullet[3] = -0.5f;
	bullet[4] = -1.0f;
	bullet[5] = 0.0f;

	bullet[6] = 0.0f;
	bullet[7] =	1.0f;
	bullet[8] = 0.0f;
	////////////////////////
	crashPoint = new float[1 * 3];
	crashPoint[0] = 0.0f;
	crashPoint[1] = 0.0f;
	crashPoint[2] = 0.0f;
	//////////////////////////
	srand(time(NULL));
}


spaceObject::~spaceObject()
{
}

void spaceObject::draw(lort::Shader *shader, float deltatime)
{
}

void spaceObject::load_buffers()
{
	loadBulletBuffer();
	loadCrashBuffer();

}

void spaceObject::wrapPOS(float &y, float &x)
{
	if (y > CAMERA_CONSTRAINT)y = -CAMERA_CONSTRAINT;
	if (y < -CAMERA_CONSTRAINT)y = CAMERA_CONSTRAINT;
	if (x > CAMERA_CONSTRAINT)x = -CAMERA_CONSTRAINT;
	if (x< -CAMERA_CONSTRAINT)x = CAMERA_CONSTRAINT;
}

void spaceObject::destruction(float posX, float posY,std::vector<Point>& _Point)
{
	//12 points are enough
	for (int i = 0; i < 12; i++) {
		Point x;
		x.initPoint(posX, posY);
		_Point.push_back(x);
	}
}

void spaceObject::loadBulletBuffer()
{
	unsigned int _VBO_BULLET;
	unsigned int _VAO_BULLET;
	glGenVertexArrays(1, &_VAO_BULLET);
	glBindVertexArray(_VAO_BULLET);
	glGenBuffers(1, &_VBO_BULLET);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO_BULLET);
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(float), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * 3 * sizeof(float), bullet);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	Bullet::VAO = _VAO_BULLET;
}

void spaceObject::loadCrashBuffer()
{

	unsigned int _VAO_CRASH;
	unsigned int _VBO_CRASH;
	glGenVertexArrays(1, &_VAO_CRASH);
	glBindVertexArray(_VAO_CRASH);
	glGenBuffers(1, &_VBO_CRASH);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO_CRASH);
	glBufferData(GL_ARRAY_BUFFER, 1 * 3 * sizeof(float), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 1 * 3 * sizeof(float), crashPoint);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	Point::VAO = _VAO_CRASH;
}


