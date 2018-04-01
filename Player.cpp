#include "Player.h"

// CONSTANTS FOR PLAYER MOVEMENT
const float ROTATE_SPEED = 5.0f;
const float ROTATE_ANGLE = 20.0f;
 const float MAX_SPEED = 55.0f;
 const float MAX_ACCELERATION = 2.0f;

 //BOOLEAN TO CHECK IF TO DRAW THE THRUST OR NOT
 bool drawThrust = false;
 //MAX LIVE BULLETS FOR PLAYER
 const int MAX_BULLETS =16;

 float* Player::verticies;
 float* Player::thrust;
 float* Player::miniThrust;
 unsigned int Player::_VBO_PLAYER;
 unsigned int Player::_VAO_PLAYER;
 unsigned int Player::_VBO_THRUST;
 unsigned int Player::_VAO_THRUST;
 int Player::verticies_count;

Player::Player(lort::Shader *shader) :spaceObject(shader)
{
	_score = 0.0f;
	_vunerable_time = 3.0f;
	_lives = 3;
	hit_Able = false;

	MODEL_MATRIX = glm::mat4();//IDENTITY MATRIX
	speed = 0.0f;
	acceleration = 0.0f;
	collider.init(3.0f, 8.0f);
}


Player::~Player()
{
	/*delete[] verticies;
	delete[] thrust;
	delete[] miniThrust;
	delete[] bullet;*/
}
void Player::ProcessKeyboard(player_movement direction, float deltaTime, lort::Shader* shader,std::vector<Bullet>& bullets)
{
	


	if (direction == FORWARD) {
		if (currentAngle != rotateAngle) {
			float tmp = glm::cos(glm::radians(glm::abs(currentAngle - rotateAngle)));
			currentAngle = rotateAngle;
			acceleration *=tmp ;
			speed = acceleration*20.0f*tmp;
		}
			acceleration += 0.20f;
			if (acceleration > MAX_ACCELERATION)acceleration = MAX_ACCELERATION;
			speed += acceleration;
			if (speed > MAX_SPEED) speed = MAX_SPEED;
		velocity = speed * deltaTime;
		drawThrust = true;
		
	}
	
		
	if (direction == LEFT) {
		rotateAngle += ROTATE_ANGLE*ROTATE_SPEED*deltaTime;
		if (rotateAngle > 360.0f)rotateAngle -= 360.0f;
		
	}
		
	if (direction == RIGHT) {
		rotateAngle += -ROTATE_ANGLE*ROTATE_SPEED*deltaTime;
		if (rotateAngle < 0.0f)rotateAngle += 360.0f;
	}
	if (direction == FIRE) {
		static float delay = 0.0f;
		delay -= deltaTime;
		if (delay <= 0.0f) {
			delay = 0.2f;//0.2Seconds
			if (Bullet::PLAYER_COUNT<= MAX_BULLETS) {

				Bullet *newBullet= new Bullet;
				newBullet->rotateAngle = rotateAngle;
				//POSITION AT THE TOP OF THE PLAYER SHIP
				newBullet->posX += POSITIONX - 9.0f*glm::sin(glm::radians(rotateAngle));
				newBullet->posY += POSITIONY+9.0f*glm::cos(glm::radians(rotateAngle));
				newBullet->initCollider();
				bullets.push_back(*newBullet);
				Bullet::PLAYER_COUNT++;	
			}
		}
	}
	
}
bool Player::Death()
{
	_lives--;
	_vunerable_time = 3.0f;
	hit_Able = false;
	if (_lives <= 0) {
		alive = false;
		return true;
	}
	return false;
}
void Player::reset()
{
	POSITIONX = 0.0f;
	POSITIONY = 0.0f;
	rotateAngle = 0.0f;
	velocity = 0.0f;
	
	acceleration = 0.0f;
	speed = 0.0f;
}
void   Player::loadBuffer(lort::Shader *shader) {
	/////////////////////////////////////
	verticies = new float[5 * 3];
	verticies[0] = 0.0f;
	verticies[1] = 8.0f;
	verticies[2] = 0.0f;

	verticies[3] = 4.0f;
	verticies[4] = -8.0f;
	verticies[5] = 0.0f;


	verticies[6] = 2.0f;
	verticies[7] = -6.0f;
	verticies[8] = 0.0f;

	verticies[9] = -2.0f;
	verticies[10] = -6.0f;
	verticies[11] = 0.0f;

	verticies[12] = -4.0f;
	verticies[13] = -8.0f;
	verticies[14] = 0.0f;

	verticies_count = 5 * 3;
	////////////////////////////////////
	thrust = new float[3 * 3];
	thrust[0] = 1.5f;
	thrust[1] = -6.0f;
	thrust[2] = 0.0f;

	thrust[3] = 0.0f;
	thrust[4] = -10.0f;
	thrust[5] = 0.0f;

	thrust[6] = -1.5f;
	thrust[7] = -6.0f;
	thrust[8] = 0.0f;
	////////////////////////////////
	miniThrust = new float[3 * 3];
	miniThrust[0] = 1.35f;
	miniThrust[1] = -6.0f;
	miniThrust[2] = 0.0f;

	miniThrust[3] = 0.0f;
	miniThrust[4] = -9.2f;
	miniThrust[5] = 0.0f;

	miniThrust[6] = -1.35f;
	miniThrust[7] = -6.0f;
	miniThrust[8] = 0.0f;
	////////////////////////////
	glGenVertexArrays(1, &_VAO_PLAYER);
	glBindVertexArray(_VAO_PLAYER);
	glGenBuffers(1, &_VBO_PLAYER);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO_PLAYER);
	glBufferData(GL_ARRAY_BUFFER, verticies_count*sizeof(float), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, verticies_count * sizeof(float), verticies);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);//to enable the vertex attribute of index 0 (LOCATION 0 in VERTEX SHADER)
	glBindBuffer(GL_ARRAY_BUFFER, 0);//we can unbind VBO but we cant unbind EBO AS its not auto uploaded on VAO
	glBindVertexArray(0);
	
	glGenVertexArrays(1, &_VAO_THRUST);
	glBindVertexArray(_VAO_THRUST);
	glGenBuffers(1, &_VBO_THRUST);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO_THRUST);
	glBufferData(GL_ARRAY_BUFFER, 2* 3 * 3 * sizeof(float), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3* 3 * sizeof(float), thrust);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(float), 3 * 3 * sizeof(float), miniThrust);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	shader->setUniformMat4("transform", 1, GL_FALSE, glm::value_ptr(MODEL_MATRIX));
	
}

void Player::draw(lort::Shader *shader,float deltatime)
{
	//SHOUlD HAVE DONE IT IN 2 seperate functions instead :(
	if (_vunerable_time > 0) {
		_vunerable_time -= deltatime;
	}
	else {
		hit_Able = true;
	}
	POSITIONY += velocity*glm::cos(glm::radians(currentAngle));
	POSITIONX += -velocity*glm::sin(glm::radians(currentAngle));
	wrapPOS(POSITIONY, POSITIONX);
	UFO::_PLAYER1X = POSITIONX;
	UFO::_PLAYER1Y = POSITIONY;
	MODEL_MATRIX = glm::mat4();
	MODEL_MATRIX = glm::translate(MODEL_MATRIX, glm::vec3(POSITIONX, POSITIONY, 0.0f));
	MODEL_MATRIX = glm::rotate(MODEL_MATRIX, glm::radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));

	shader->setUniformMat4("transform", 1, GL_FALSE, glm::value_ptr(MODEL_MATRIX));
	if (hit_Able) {
		glBindVertexArray(_VAO_PLAYER);
		glDrawArrays(GL_LINE_LOOP, 0, 5);
		glBindVertexArray(0);

		if (drawThrust) {
			if (speed == MAX_SPEED) {
				drawThrust = false;
				return;// WARNING BE NOTED !!!! LAST FUNCTION !!
			}
			static int x = 0;
			shader->setUniformMat4("transform", 1, GL_FALSE, glm::value_ptr(MODEL_MATRIX));
			glBindVertexArray(_VAO_THRUST);
			glDrawArrays(GL_LINE_LOOP, 0, 6);
			glBindVertexArray(0);
			x++;
			if (x == 8) {//8frames
				drawThrust = false;
				x = 0;
			}

		}
	}
	else {
	static float y = 0.0025f;
	y -= deltatime;
	if (y<=0.0f) {
		y = 0.025f;
		
		glBindVertexArray(_VAO_PLAYER);
		glDrawArrays(GL_LINE_LOOP, 0, 5);
		glBindVertexArray(0);

		if (drawThrust) {
			if (speed == MAX_SPEED) {
				drawThrust = false;
				return;// WARNING BE NOTED !!!! LAST FUNCTION !!
			}
			static int x = 0;
			shader->setUniformMat4("transform", 1, GL_FALSE, glm::value_ptr(MODEL_MATRIX));
			glBindVertexArray(_VAO_THRUST);
			glDrawArrays(GL_LINE_LOOP, 0, 6);
			glBindVertexArray(0);
			x++;
			if (x == 8) {//8frames
				drawThrust = false;
				x = 0;
			}
		}
		
	}
	}
}
