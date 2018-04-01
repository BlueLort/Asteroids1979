#include "UFO.h"
int UFO::UFO_COUNT = 0.0f;
float UFO::_PLAYER1X = 0.0f, UFO::_PLAYER1Y = 0.0f;
unsigned int	UFO::_VAO;
float* UFO::_ufo;



UFO::UFO()
{

}


UFO::~UFO()
{
	//delete[] _ufo;
}

void UFO::initUFO(){
	switch (rand() % 2) {
	case 0:
		this->_posX = CAMERA_CONSTRAINT;
		this->_posY = rand() % 140;// anyplace between 0 and 140 on y
		this->_directionIsRight = false;
		break;
	case 1:
		this->_posX = -CAMERA_CONSTRAINT;
		this->_posY = rand() % 140;// anyplace between 0 and 140 on y
		this->_directionIsRight = true;
		break;
	default:
		break;
	}
this->_collider.init(7.0f, 1.5f);
this->UFO_COUNT++;
}

void UFO::draw(lort::Shader *shader, float deltatime, std::vector<Bullet>& bullet) {
	update(deltatime, bullet);

	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(this->_posX, this->_posY, 0.0f));
	shader->setUniformMat4("transform", 1, GL_FALSE, glm::value_ptr(trans));
	glBindVertexArray(this->_VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 8);//BODY
	glDrawArrays(GL_LINES, 8, 10);//MID LINE
	glDrawArrays(GL_LINES, 10, 12);//UPPER LINE
	glBindVertexArray(0);
}
//GETTERS
Collider UFO::getCollider()
{
	return this->_collider;
}
float UFO::getPosX()
{
	return this->_posX;
}
float UFO::getPosY()
{
	return this->_posY;
}
void UFO::loadBuffer()
{
	/////////////////////////////////
	_ufo = new float[12 * 3];
	_ufo[0] = 0.5f * -15.0f;
	_ufo[1] = 0.5f * -2.0f;
	_ufo[2] = 0.5f *  0.0f;

	_ufo[3] = 0.5f * -6.0f;
	_ufo[4] = 0.5f * 3.0f;
	_ufo[5] = 0.5f * 0.0f;

	_ufo[6] = 0.5f * -3.0f;
	_ufo[7] = 0.5f * 7.0f;
	_ufo[8] = 0.5f * 0.0f;

	_ufo[9] = 0.5f * 3.0f;
	_ufo[10] = 0.5f * 7.0f;
	_ufo[11] = 0.5f * 0.0f;

	_ufo[12] = 0.5f * 6.0f;
	_ufo[13] = 0.5f * 3.0f;
	_ufo[14] = 0.5f * 0.0f;

	_ufo[15] = 0.5f * 15.0f;
	_ufo[16] = 0.5f * -2.0f;
	_ufo[17] = 0.5f * 0.0f;

	_ufo[18] = 0.5f * 7.0f;
	_ufo[19] = 0.5f * -7.0f;
	_ufo[20] = 0.5f * 0.0f;

	_ufo[21] = 0.5f * -7.0f;
	_ufo[22] = 0.5f * -7.0f;
	_ufo[23] = 0.5f * 0.0f;
	// MID LINE
	_ufo[24] = 0.5f * -15.0f;
	_ufo[25] = 0.5f * -2.0f;
	_ufo[26] = 0.5f * 0.0f;

	_ufo[27] = 0.5f * 15.0f;
	_ufo[28] = 0.5f * -2.0f;
	_ufo[29] = 0.5f * 0.0f;
	//UPPER LINE
	_ufo[30] = 0.5f * -6.0f;
	_ufo[31] = 0.5f * 3.0f;
	_ufo[32] = 0.5f * 0.0f;

	_ufo[33] = 0.5f * 6.0f;
	_ufo[34] = 0.5f * 3.0f;
	_ufo[35] = 0.5f * 0.0f;
	////////////////////////
	unsigned int _VBO_UFO;
	unsigned int _VAO_UFO;
	glGenVertexArrays(1, &_VAO_UFO);
	glBindVertexArray(_VAO_UFO);
	glGenBuffers(1, &_VBO_UFO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO_UFO);
	glBufferData(GL_ARRAY_BUFFER, 12 * 3 * sizeof(float), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 12 * 3 * sizeof(float),_ufo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	_VAO = _VAO_UFO;
}
///////////////////
void UFO::update(float deltatime, std::vector<Bullet>& bullet) {
	if (this->_directionIsRight) {
		this->_posX += UFO_VELOCITY * deltatime;
	}
	else {

		this->_posX -= UFO_VELOCITY * deltatime;
	}
	spaceObject::wrapPOS(this->_posY, this->_posX);
	static float delay = 0.0f;
	delay -= deltatime;
	if (delay <= 0.0f) {
		delay = 0.5f;//0.5Seconds
		glm::vec2 bulletDirection;
		bulletDirection = glm::normalize(glm::vec2(this->_PLAYER1X, this->_PLAYER1Y) - glm::vec2(this->_posX, this->_posY));
		float dotProduct = glm::dot(bulletDirection, glm::vec2(0.0f, 1.0f));
		float angleDiff;
		if (this->_PLAYER1X < this->_posX) {
			angleDiff = glm::acos(dotProduct)*(180.0f / PI);//rads to degrees
		}
		else {
			angleDiff = -glm::acos(dotProduct)*(180.0f / PI);//rads to degrees
		}
		Bullet *x = new Bullet;
		x->rotateAngle = angleDiff;


		//POSITION AT THE TOP OF THE PLAYER SHIP
		x->posX += this->_posX;
		x->posY += this->_posY - 7.0f;
		x->initCollider();
		bullet.push_back(*x);
		Bullet::UFO_COUNT++;
	}
}
