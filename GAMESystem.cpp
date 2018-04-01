#include "GAMESystem.h"
//Text Rendering THINGS FROM HERE : "https://learnopengl.com/In-Practice/Text-Rendering"
//That Site is Epic to learn OpenGL if you are new :D
GAMESystem* GAMESystem::TheGameSystem = nullptr;
struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

std::map<GLchar, Character> Characters;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
bool levelSuccess = false;
float LEVEL_SCORE = 0.0f;
int GAMESystem::currentLevel=1;
float escapeCD = 0.0f;
#define MAX_ESCAPE_CD 8.0f
GAMESystem::GAMESystem()
{

	 initLevel(currentLevel);
	// initOpenAl();
	 glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));
	_text_shader->use();
	 glUniformMatrix4fv(glGetUniformLocation(_text_shader->getProgID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	 FT_Library ft;
	 if (FT_Init_FreeType(&ft))
		 std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	 FT_Face face;
	 if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
		 std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	 FT_Set_Pixel_Sizes(face, 0, 48);
	 if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
		 std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
	 glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	 for (GLubyte c = 0; c < 128; c++)
	 {
		 // Load character glyph 
		 if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		 {
			 std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			 continue;
		 }
		 // Generate texture
		 GLuint texture;
		 glGenTextures(1, &texture);
		 glBindTexture(GL_TEXTURE_2D, texture);
		 glTexImage2D(
			 GL_TEXTURE_2D,
			 0,
			 GL_RED,
			 face->glyph->bitmap.width,
			 face->glyph->bitmap.rows,
			 0,
			 GL_RED,
			 GL_UNSIGNED_BYTE,
			 face->glyph->bitmap.buffer
		 );
		 // Set texture options
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		 // Now store character for later use
		 Character character = {
			 texture,
			 glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			 glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			 face->glyph->advance.x
		 };
		Characters.insert(std::pair<GLchar, Character>(c, character));
	 }
	 FT_Done_Face(face);
	 FT_Done_FreeType(ft);
	
	 glGenVertexArrays(1, &TEXT_VAO);
	 glGenBuffers(1, &TEXT_VBO);
	 glBindVertexArray(TEXT_VAO);
	 glBindBuffer(GL_ARRAY_BUFFER, TEXT_VBO);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	 glEnableVertexAttribArray(0);
	 glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glBindVertexArray(0);
	 _text_shader->unuse();

	 UFO::loadBuffer();
	 Player::loadBuffer(this->_shader);
	 spaceObject::load_buffers();
	 spaceAsteroid::loadBuffer(this->_shader);
	 
}

GAMESystem * GAMESystem::getInstance()
{
	if (TheGameSystem == nullptr) {
		TheGameSystem = new GAMESystem();
		return TheGameSystem;
	}
	else {
		return TheGameSystem;
	}
}

void GAMESystem::RenderText(lort::Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	// Activate corresponding render state	
	s.use();
	glUniform3f(glGetUniformLocation(s.getProgID(), "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(TEXT_VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, TEXT_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
GAMESystem::~GAMESystem()
{
	_LORT->SYSTEM_TERMINATE();
	_p->~Player();
}

void GAMESystem::Game_Loop()
{//TEXT DRAWING
	RenderText(*_text_shader, "Score: " + std::to_string((int)_p->getScore()), 10.0f, 575.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(*_text_shader, "Lives: " + std::to_string(_p->getLives()), 10.0f, 550.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	if (escapeCD > 0.0f)RenderText(*_text_shader, "Escape : " + std::to_string((int)escapeCD), 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	else RenderText(*_text_shader, "Escape : Available", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	if (!_p->alive) {
		RenderText(*_text_shader, "Game Over", 230.0f, HEIGHT / 2.0f + 30.0f, 1.4f, glm::vec3(1.0f, 1.0f, 1.0f));
		RenderText(*_text_shader, "Objects Desteroyed: " + std::to_string(_p->destroy_count), 240.0f, HEIGHT / 2.0f, 0.65f, glm::vec3(1.0f, 1.0f, 1.0f));
		RenderText(*_text_shader, "Score: " + std::to_string((int)_p->getScore()), 240.0f, HEIGHT / 2.0f - 30.0f, 0.65f, glm::vec3(1.0f, 1.0f, 1.0f));
		RenderText(*_text_shader, "Level: " + std::to_string(currentLevel), 240.0f, HEIGHT / 2.0f - 60.0f, 0.65f, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);// you enable blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glfwSwapInterval(1);
	//glfwSetInputMode(_LORT->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	_shader->use();
	glm::mat4 view = glm::lookAt(_camera.Position, _camera.Position + _camera.Front, _camera.Up);
	_shader->setUniformMat4("view", 1, GL_FALSE, glm::value_ptr(view));
	glm::mat4 projection;
	projection = glm::ortho(-CAMERA_CONSTRAINT, CAMERA_CONSTRAINT, -CAMERA_CONSTRAINT, CAMERA_CONSTRAINT, 0.1f, 30.0f);
	_shader->setUniformMat4("projection", 1, GL_FALSE, glm::value_ptr(projection));
	_shader->unuse();
	while (!glfwWindowShouldClose(_LORT->getWindow()))//if its instructed to close it will be true and loop ends
	{
		if (_p->getScore() == LEVEL_SCORE ) {
			levelSuccess = true;
		}
		if (levelSuccess) {
			initLevel(++currentLevel);
			_p->reset();
			escapeCD = -1.0f;
			levelSuccess = false;
		}
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//PROCCESSING INPUTS
		processInput(_LORT->getWindow(),deltaTime);
		if (_p->alive) {
			if (collisionDETECTION()) {

				_p->reset();
			}
		}
		
		draw();
	
		glfwPollEvents();//CHECK FOR ANY POLLING EVENTS
		//if (!_p->alive)break;
	}
}
void GAMESystem::CrateDestruction(int n,int POSISIONX,int POSITIONY) {
	for (int i = 0; i <n; i++) {
		Point p;
		p.initPoint(POSISIONX, POSITIONY);
		_Destroyed_Points.push_back(p);

	}
}

bool GAMESystem::checkCollisionPA(Player p, spaceAsteroid a)
{
	return !(p.POSITIONX + p.collider.sizeX <= a.getPosX() -a.getCollider().sizeX  ||
			 p.POSITIONX - p.collider.sizeX >= a.getPosX() +a.getCollider().sizeX  ||
			 p.POSITIONY + p.collider.sizeY <= a.getPosY() -a.getCollider().sizeY  ||
			 p.POSITIONY - p.collider.sizeY >= a.getPosY() +a.getCollider().sizeY  
		);

}

bool GAMESystem::checkCollisionBA(Bullet b, spaceAsteroid a)
{
	return !(b.posX + b.collider.sizeX <= a.getPosX() - a.getCollider().sizeX ||
		     b.posX - b.collider.sizeX >= a.getPosX() + a.getCollider().sizeX ||
		     b.posY + b.collider.sizeY <= a.getPosY() - a.getCollider().sizeY ||
		     b.posY - b.collider.sizeY >= a.getPosY() + a.getCollider().sizeY 
		);
}
bool GAMESystem::checkCollisionBU(Bullet b, UFO u) {
	return !(b.posX + b.collider.sizeX <= u.getPosX() - u.getCollider().sizeX ||
		b.posX - b.collider.sizeX >= u.getPosX() + u.getCollider().sizeX ||
		b.posY + b.collider.sizeY <= u.getPosY() - u.getCollider().sizeY ||
		b.posY - b.collider.sizeY >= u.getPosY() + u.getCollider().sizeY
		);

}

bool GAMESystem::checkCollisionBP(Player p, Bullet b)
{
	return !(p.POSITIONX + p.collider.sizeX <= b.posX - b.collider.sizeX ||
		p.POSITIONX - p.collider.sizeX >= b.posX + b.collider.sizeX ||
		p.POSITIONY + p.collider.sizeY <= b.posY - b.collider.sizeY ||
		p.POSITIONY - p.collider.sizeY >= b.posY + b.collider.sizeY
		);
}

bool GAMESystem::checkCollisionPU(Player p, UFO u)
{
	return !(p.POSITIONX + p.collider.sizeX <= u.getPosX() - u.getCollider().sizeX ||
		p.POSITIONX - p.collider.sizeX >= u.getPosX() + u.getCollider().sizeX ||
		p.POSITIONY + p.collider.sizeY <= u.getPosY() - u.getCollider().sizeY ||
		p.POSITIONY - p.collider.sizeY >= u.getPosY() + u.getCollider().sizeY
		);
	return false;
}

bool GAMESystem::checkCollisionsForPA()
{
	/* PLAYER COLLISION LOSING */
	for (int i = 0; i < spaceAsteroid::currentAsteroids; i++) {
		if (checkCollisionPA(*_p, _Asteroids[i])) {
			CrateDestruction(25, _p->POSITIONX, _p->POSITIONY);
			_p->Death();
			return true;
		}
	}
	return false;
}

void GAMESystem::checkCollisionsForPlayerBullets()
{
	for (int i = 0; i < Bullet::PLAYER_COUNT; i++) {
		for (int j = 0; j < spaceAsteroid::currentAsteroids; j++) {
			if (checkCollisionBA(_P_BULLETS[i], _Asteroids[j])) {
				////////////
				_p->setScore(_p->getScore() + (1.0f / _Asteroids[j].getCurrentStateMask())*20.0f);
				//////////////
				CrateDestruction(12, _Asteroids[j].getPosX(), _Asteroids[j].getPosY());
				///////////////////
				_Asteroids[j].destroy(_Asteroids, _Asteroids[j].getPosX(), _Asteroids[j].getPosY());//BAD WAY BUT WORKS
				_Asteroids[j] = _Asteroids.back();
				_Asteroids.pop_back();
				spaceAsteroid::currentAsteroids--;
				//////////////////
				_P_BULLETS[i].lifeTime = 0.0f;
				_p->destroy_count++;
				break;
			}
		}
		for (int j = 0; j < UFO::UFO_COUNT; j++) {
			if (checkCollisionBU(_P_BULLETS[i], _UFOs[j])) {
				////////////
				_p->setScore(_p->getScore() + 40.0f);
				//////////////
				CrateDestruction(15, _UFOs[j].getPosX(), _UFOs[j].getPosY());
				///////////////////
				_UFOs[j] = _UFOs.back();
				_UFOs.pop_back();
				UFO::UFO_COUNT--;
				//////////////////
				_P_BULLETS[i].lifeTime = 0.0f;
				_p->destroy_count++;
				break;

			}
		}
	}
}

bool GAMESystem::checkCollisionsForBP()
{
	for (int i = 0; i < Bullet::UFO_COUNT; i++) {
		if (checkCollisionBP(*_p, _UFO_BULLETS[i])) {
			CrateDestruction(25, _p->POSITIONX, _p->POSITIONY);
			_p->Death();
			return true;
		}
	}
	return false;
}

bool GAMESystem::checkCollisionsForPU()
{
	for (int i = 0; i < UFO::UFO_COUNT; i++) {
		if (checkCollisionPU(*_p, _UFOs[i])) {
			_p->Death();
			CrateDestruction(25, _p->POSITIONX, _p->POSITIONY);
			return true;
		}
	}
	return false;

}

void GAMESystem::timeOutBP()
{
	for (int i = 0; i < Bullet::PLAYER_COUNT; i++) {
		_P_BULLETS[i].draw(_shader, deltaTime);
		if (_P_BULLETS[i].lifeTime <= 0.0f) {
			_P_BULLETS[i] = _P_BULLETS.back();
			_P_BULLETS.pop_back();
			Bullet::PLAYER_COUNT--;
		}
	}
}

void GAMESystem::timeOutBU()
{
	for (int i = 0; i < Bullet::UFO_COUNT; i++) {
		_UFO_BULLETS[i].draw(_shader, deltaTime);
		if (_UFO_BULLETS[i].lifeTime <= 0.0f) {
			_UFO_BULLETS[i] = _UFO_BULLETS.back();
			_UFO_BULLETS.pop_back();
			Bullet::UFO_COUNT--;
		}
	}
}

void GAMESystem::timeOutPoints()
{
	for (int i = 0; i <Point::POINT_COUNT; i++) {
		_Destroyed_Points[i].draw(_shader, deltaTime);
		if (_Destroyed_Points[i].lifeTime <= 0.0f) {
			_Destroyed_Points[i] = _Destroyed_Points.back();
			_Destroyed_Points.pop_back();
			Point::POINT_COUNT--;
		}
	}

}

void GAMESystem::timeOutAll()
{
	timeOutBP();
	timeOutBU();
	timeOutPoints();
}

void GAMESystem::playerEscape()
{
	if (escape) {

		if (random) {
			bool rerun;
			do {
				rerun = false;
				float x = (rand() % 300) - 150.0f, y = (rand() % 300) - 150.0f;
				_p->POSITIONX = x;
				_p->POSITIONY = y;
				for (int i = 0; i < spaceAsteroid::currentAsteroids; i++) {
					if (checkCollisionPA(*_p, _Asteroids[i])) {
						rerun = true;
					}
				}

				for (int i = 0; i < UFO::UFO_COUNT; i++) {
					if (checkCollisionPU(*_p, _UFOs[i])) {
						rerun = true;
					}
				}

				for (int i = 0; i < Bullet::UFO_COUNT; i++) {
					if (checkCollisionBP(*_p, _UFO_BULLETS[i])) {
						rerun = true;
					}
				}
			} while (rerun);
		}
		static	float time = 1.0f;
		time -= deltaTime;
		if (time <= 0.0f) {
			escape = false;
			time = 1.0f;
		}
	}
}

bool GAMESystem::collisionDETECTION()
{
	if (_p->hit_Able) {
		if (checkCollisionsForPA())return true;
		if (checkCollisionsForPU())return true;
		if (checkCollisionsForBP())return true;
	}
	checkCollisionsForPlayerBullets();
	return false;
}

void GAMESystem::draw()
{
	//RENDERING STUFF HERE
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//TOTALLY BLACK
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	escapeCD -= deltaTime;
	
	drawTextOverScreen();
	_shader->use();
	//DRAWING HERE
	if(_p->alive&&!escape)_p->draw(_shader, deltaTime);
	playerEscape();
	for (int i = 0; i <spaceAsteroid::currentAsteroids; i++) {
		_Asteroids[i].draw(_shader, deltaTime);
	}
	//DRAW 1 UFO ONLY
	if(UFO::UFO_COUNT)_UFOs[ 0].draw(_shader, deltaTime,_UFO_BULLETS);
	timeOutAll();
   //SWAP FOR DOUBLE BUFFER
	glfwSwapBuffers(_LORT->getWindow());
	_shader->unuse();
}

void GAMESystem::processInput(GLFWwindow * window,float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		
	}
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		_p->ProcessKeyboard(FORWARD, deltaTime, _shader, _P_BULLETS);
	
	

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (escapeCD <= 0) {
			escape = true;
			_p->hit_Able = false;
			random = true;
			_p->_vunerable_time = 1.5f;
			escapeCD = MAX_ESCAPE_CD;
		}
	}
	
	
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		_p->ProcessKeyboard(LEFT, deltaTime, _shader, _P_BULLETS);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		_p->ProcessKeyboard(RIGHT, deltaTime, _shader, _P_BULLETS);
	if (_p->alive) {
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			_p->ProcessKeyboard(FIRE, deltaTime, _shader, _P_BULLETS);
		}
	}
}

void GAMESystem::initLevel(int levelN)
{
	for (int i = 0; i < levelN * 2; i++) {
		spaceAsteroid x;
		x.initAsteroid(0b100);
		_Asteroids.push_back(x);
		LEVEL_SCORE += 105.0f;
		if (i%2==0) {
			UFO y;
			y.initUFO();
			_UFOs.push_back(y);
			LEVEL_SCORE += 40.0f;
		}
	}
}

void GAMESystem::drawTextOverScreen()
{
	//TEXT DRAWING
	RenderText(*_text_shader, "Score: " + std::to_string((int)_p->getScore()), 10.0f, 575.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText(*_text_shader, "Lives: " + std::to_string(_p->getLives()), 10.0f, 550.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	if (escapeCD > 0.0f)RenderText(*_text_shader, "Escape : " + std::to_string((int)escapeCD), 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	else RenderText(*_text_shader, "Escape : Available", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	if (!_p->alive) {
		RenderText(*_text_shader, "Game Over", 230.0f, HEIGHT / 2.0f + 30.0f, 1.4f, glm::vec3(1.0f, 1.0f, 1.0f));
		RenderText(*_text_shader, "Objects Desteroyed: " + std::to_string(_p->destroy_count), 240.0f, HEIGHT / 2.0f, 0.65f, glm::vec3(1.0f, 1.0f, 1.0f));
		RenderText(*_text_shader, "Score: " + std::to_string((int)_p->getScore()), 240.0f, HEIGHT / 2.0f - 30.0f, 0.65f, glm::vec3(1.0f, 1.0f, 1.0f));
		RenderText(*_text_shader, "Level: " + std::to_string(currentLevel), 240.0f, HEIGHT / 2.0f - 60.0f, 0.65f, glm::vec3(1.0f, 1.0f, 1.0f));
	}
}
