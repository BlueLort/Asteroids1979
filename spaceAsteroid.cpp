#include "spaceAsteroid.h"

unsigned int spaceAsteroid::VAO_LARGE;
unsigned int spaceAsteroid::VAO_MED;
unsigned int spaceAsteroid::VAO_SMALL;
float* spaceAsteroid::largeAsteroid;
float* spaceAsteroid::mediumAsteroid;
float* spaceAsteroid::smallAsteroid;
int spaceAsteroid::LARGE_VERTS;
int spaceAsteroid::MED_VERTS;
int spaceAsteroid::SMALL_VERTS;
int spaceAsteroid::currentAsteroids=0;
spaceAsteroid::spaceAsteroid(lort::Shader *shader) 
{

}

spaceAsteroid::spaceAsteroid()
{
}

void spaceAsteroid::loadBuffer(lort::Shader *shader)
{
	//////////////////////////////////
	largeAsteroid = new float[11 * 3];
	spaceAsteroid::LARGE_VERTS = 11;

	largeAsteroid[0] = 5 * -2.5f;
	largeAsteroid[1] = 5 * 0.0f;
	largeAsteroid[2] = 5 * 0.0f;

	largeAsteroid[3] = 5 * -4.5f;
	largeAsteroid[4] = 5 * 1.0f;
	largeAsteroid[5] = 5 * 0.0f;

	largeAsteroid[6] = 5 * -1.5f;
	largeAsteroid[7] = 5 * 4.0f;
	largeAsteroid[8] = 5 * 0.0f;

	largeAsteroid[9] = 5 * 2.5f;
	largeAsteroid[10] = 5 * 4.0f;
	largeAsteroid[11] = 5 * 0.0f;

	largeAsteroid[12] = 5 * 4.5f;
	largeAsteroid[13] = 5 * 1.0f;
	largeAsteroid[14] = 5 * 0.0f;

	largeAsteroid[15] = 5 * 4.5f;
	largeAsteroid[16] = 5 * -2.0f;
	largeAsteroid[17] = 5 * 0.0f;

	largeAsteroid[18] = 5 * 2.5f;
	largeAsteroid[19] = 5 * -4.0f;
	largeAsteroid[20] = 5 * 0.0f;

	largeAsteroid[21] = 5 * 0.5f;
	largeAsteroid[22] = 5 * -4.0f;
	largeAsteroid[23] = 5 * 0.0f;

	largeAsteroid[24] = 5 * 0.5f;
	largeAsteroid[25] = 5 * -1.0f;
	largeAsteroid[26] = 5 * 0.0f;

	largeAsteroid[27] = 5 * -1.5f;
	largeAsteroid[28] = 5 * -4.0f;
	largeAsteroid[29] = 5 * 0.0f;

	largeAsteroid[30] = 5 * -4.5f;
	largeAsteroid[31] = 5 * -1.0f;
	largeAsteroid[32] = 5 * 0.0f;
	///////////////////////////////////////////////
	mediumAsteroid = new float[10 * 3];
	spaceAsteroid::MED_VERTS = 10;

	mediumAsteroid[0] = 3 * -4.0f;
	mediumAsteroid[1] = 3 * 3.0f;
	mediumAsteroid[2] = 3 * 0.0f;

	mediumAsteroid[3] = 3 * -2.0f;
	mediumAsteroid[4] = 3 * 5.0f;
	mediumAsteroid[5] = 3 * 0.0f;

	mediumAsteroid[6] = 3 * 0.0f;
	mediumAsteroid[7] = 3 * 3.0f;
	mediumAsteroid[8] = 3 * 0.0f;

	mediumAsteroid[9] = 3 * 2.0f;
	mediumAsteroid[10] = 3 * 5.0f;
	mediumAsteroid[11] = 3 * 0.0f;

	mediumAsteroid[12] = 3 * 4.0f;
	mediumAsteroid[13] = 3 * 3.0f;
	mediumAsteroid[14] = 3 * 0.0f;

	mediumAsteroid[15] = 3 * 3.0f;
	mediumAsteroid[16] = 3 * 2.0f;
	mediumAsteroid[17] = 3 * 0.0f;

	mediumAsteroid[18] = 3 * 4.0f;
	mediumAsteroid[19] = 3 * -1.0f;
	mediumAsteroid[20] = 3 * 0.0f;

	mediumAsteroid[21] = 3 * 1.0f;
	mediumAsteroid[22] = 3 * -2.0f;
	mediumAsteroid[23] = 3 * 0.0f;

	mediumAsteroid[24] = 3 * -2.0f;
	mediumAsteroid[25] = 3 * -2.0f;
	mediumAsteroid[26] = 3 * 0.0f;

	mediumAsteroid[27] = 3 * -4.0f;
	mediumAsteroid[28] = 3 * 0.0f;
	mediumAsteroid[29] = 3 * 0.0f;
	/////////////////////////////
	smallAsteroid = new float[12 * 3];
	spaceAsteroid::SMALL_VERTS = 12;

	smallAsteroid[0] = -3.5f;
	smallAsteroid[1] = 0.5f;
	smallAsteroid[2] = 0.0f;

	smallAsteroid[3] = -3.5f;
	smallAsteroid[4] = 2.5f;
	smallAsteroid[5] = 0.0f;

	smallAsteroid[6] = -0.5f;
	smallAsteroid[7] = 3.5f;
	smallAsteroid[8] = 0.0f;

	smallAsteroid[9] = 0.5f;
	smallAsteroid[10] = 2.5f;
	smallAsteroid[11] = 0.0f;

	smallAsteroid[12] = 2.5f;
	smallAsteroid[13] = 3.5f;
	smallAsteroid[14] = 0.0f;

	smallAsteroid[15] = 4.5f;
	smallAsteroid[16] = 2.5f;
	smallAsteroid[17] = 0.0f;

	smallAsteroid[18] = 2.5f;
	smallAsteroid[19] = 0.5f;
	smallAsteroid[20] = 0.0f;

	smallAsteroid[21] = 4.5f;
	smallAsteroid[22] = -1.5f;
	smallAsteroid[23] = 0.0f;

	smallAsteroid[24] = 2.5f;
	smallAsteroid[25] = -3.5f;
	smallAsteroid[26] = 0.0f;

	smallAsteroid[27] = -0.5f;
	smallAsteroid[28] = -2.5f;
	smallAsteroid[29] = 0.0f;

	smallAsteroid[30] = -2.5f;
	smallAsteroid[31] = -3.5f;
	smallAsteroid[32] = 0.0f;

	smallAsteroid[33] = -4.5f;
	smallAsteroid[34] = -0.5f;
	smallAsteroid[35] = 0.0f;
	////////////////////////
	unsigned int _VBO_LARGE;
	unsigned int _VAO_LARGE;

	unsigned int _VBO_MED;
	unsigned int _VAO_MED;

	unsigned int _VBO_SMALL;
	unsigned int _VAO_SMALL;
	glGenVertexArrays(1, &_VAO_LARGE);
	glBindVertexArray(_VAO_LARGE);
	glGenBuffers(1, &_VBO_LARGE);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO_LARGE);
	glBufferData(GL_ARRAY_BUFFER, 11*3 * sizeof(float), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 11*3 * sizeof(float),largeAsteroid);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);//to enable the vertex attribute of index 0 (LOCATION 0 in VERTEX SHADER)
	glBindBuffer(GL_ARRAY_BUFFER, 0);//we can unbind VBO but we cant unbind EBO AS its not auto uploaded on VAO
	glBindVertexArray(0);

	glGenVertexArrays(1, &_VAO_MED);
	glBindVertexArray(_VAO_MED);
	glGenBuffers(1, &_VBO_MED);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO_MED);
	glBufferData(GL_ARRAY_BUFFER,10*3* sizeof(float), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0,10*3 * sizeof(float), mediumAsteroid);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glGenVertexArrays(1, &_VAO_SMALL);
	glBindVertexArray(_VAO_SMALL);
	glGenBuffers(1, &_VBO_SMALL);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO_SMALL);
	glBufferData(GL_ARRAY_BUFFER, 12*3* sizeof(float), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0,12*3* sizeof(float), smallAsteroid);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	

	VAO_LARGE = _VAO_LARGE;
	VAO_MED = _VAO_MED;
	spaceAsteroid::VAO_SMALL = _VAO_SMALL;
	shader->setUniformMat4("transform", 1, GL_FALSE, glm::value_ptr(MODEL_MATRIX));
}
void spaceAsteroid::update(float deltatime)
{
	switch (this->_CURRENT_STATE_MASK) {
	case 4:
		this->_posY += LARGE_VELOCITY * glm::cos(glm::radians(this->_rotateAngle))*deltatime;
		this->_posX += LARGE_VELOCITY * -glm::sin(glm::radians(this->_rotateAngle))*deltatime;
		break;
	case 2:
		this->_posY += MED_VELOCITY * glm::cos(glm::radians(this->_rotateAngle))*deltatime;
		this->_posX += MED_VELOCITY * -glm::sin(glm::radians(this->_rotateAngle))*deltatime;
		break;
	case 1:
		this->_posY += SMALL_VELOCITY * glm::cos(glm::radians(this->_rotateAngle))*deltatime;
		this->_posX += SMALL_VELOCITY * -glm::sin(glm::radians(this->_rotateAngle))*deltatime;
		break;
	default:
		break;
	}
	this->_posY += glm::cos(glm::radians(this->_rotateAngle))*deltatime;

	spaceObject::wrapPOS(this->_posY, this->_posX);
}
spaceAsteroid::~spaceAsteroid()
{
}

void spaceAsteroid::draw(lort::Shader * shader, float deltatime)
{
	update(deltatime);

	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(this->_posX, this->_posY, 0.0f));
	trans = glm::rotate(trans, glm::radians(this->_rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	shader->setUniformMat4("transform", 1, GL_FALSE, glm::value_ptr(trans));
	switch (this->_CURRENT_STATE_MASK) {
	case 4:
		glBindVertexArray(spaceAsteroid::VAO_LARGE);
		glDrawArrays(GL_LINE_LOOP, 0, spaceAsteroid::LARGE_VERTS);
		break;
	case 2:
		glBindVertexArray(spaceAsteroid::VAO_MED);
		glDrawArrays(GL_LINE_LOOP, 0, spaceAsteroid::MED_VERTS);
		break;
	case 1:
		glBindVertexArray(spaceAsteroid::VAO_SMALL);
		glDrawArrays(GL_LINE_LOOP, 0, spaceAsteroid::SMALL_VERTS);
		break;
	default:
		break;
	}


	glBindVertexArray(0);
}

void spaceAsteroid::destroy(std::vector<spaceAsteroid>& _Asteroids, int pX, int pY)
{
	spaceAsteroid x, y;//NEW ASTEROIDS -> LOCALS
	int z = this->_CURRENT_STATE_MASK / 2;
	if (x.initAsteroid(z, pX, pY))_Asteroids.push_back(x);
	if (y.initAsteroid(z, pX, pY))_Asteroids.push_back(y);
}

bool spaceAsteroid::initAsteroid(int STATE, int pX, int pY)
{
	if (!STATE) {
		return false;
	}
	this->_posX = pX;
	this->_posY = pY;
	this->_rotateAngle = rand() % 360;//TOTALLY RANDOM NUMBERR
	this->_CURRENT_STATE_MASK = STATE;
	switch (this->_CURRENT_STATE_MASK) {
	case 4:
		//SETTING APPROX COLLISION
		_collider.init(20.0f, 15.0f);
		break;
	case 2:
		_collider.init(10.5f, 13.0f);
		break;
	case 1:
		_collider.init(4.0f, 6.0f);
		break;
	default:
		break;
	}
	currentAsteroids++;
	return true;
}

bool spaceAsteroid::initAsteroid(int STATE)
{
	if (!STATE) {
		return false;
	}
	switch (rand() % 4) {
	case 0:
		this->_posX = CAMERA_CONSTRAINT;
		this->_posY = rand() % 150;// anyplace between 0 and 150 on y
		break;
	case 1:
		this->_posX = -CAMERA_CONSTRAINT;
		this->_posY = rand() % 150;// anyplace between 0 and 150 on y
		break;
	case 2:
		this->_posX = rand() % 150;
		this->_posY = CAMERA_CONSTRAINT;// anyplace between 0 and 150 on y
		break;
	case 3:
		this->_posX = rand() % 150;
		this->_posY = -CAMERA_CONSTRAINT;// anyplace between 0 and 150 on y
		break;
	default:
		break;


	}
	this->_rotateAngle = rand() % 360;//TOTALLY RANDOM NUMBERR
	this->_CURRENT_STATE_MASK = STATE;
	switch (this->_CURRENT_STATE_MASK) {
	case 4:
		//SETTING APPROX COLLISION
		_collider.init(20.0f, 15.0f);
		break;
	case 2:
		_collider.init(10.5f, 13.0f);
		break;
	case 1:
		_collider.init(4.0f, 6.0f);
		break;
	default:
		break;
	}
	currentAsteroids++;
	return true;
}
//GETTERS
float spaceAsteroid::getPosX()
{
	return this->_posX;
}

float spaceAsteroid::getPosY()
{
	return this->_posY;
}

Collider spaceAsteroid::getCollider()
{
	return this->_collider;
}

float spaceAsteroid::getRotateAngle()
{
	return this->_rotateAngle;
}

int spaceAsteroid::getCurrentStateMask()
{
	return this->_CURRENT_STATE_MASK;
}

