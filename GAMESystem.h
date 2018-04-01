#pragma once

#include "EngineSYSTEM.h"
#include "spaceObject.h"
#include "Player.h"
#include "spaceAsteroid.h"
#include "UFO.h"
#include <ft2build.h>
#include <map>
#include <string>
#include FT_FREETYPE_H
const int WIDTH = 800;
const int HEIGHT = 600;
const std::string TITLE="Asteroids 1979";
class GAMESystem
{
public:
	static int currentLevel;
	static GAMESystem *TheGameSystem;
	static GAMESystem* getInstance();

	GAMESystem();
	~GAMESystem();
	void Game_Loop();
	//Create like destruction animation whenever anything destroyed
	void CrateDestruction(int x, int POSISIONX, int POSITIONY);
private:
	bool escape = false;
	bool random = false;
	//THIS LINE TO Make Window with (HEIGHT WIDTH )size and a name (TITLE)
	lort::EngineSYSTEM *_LORT = new lort::EngineSYSTEM(HEIGHT, WIDTH, TITLE.c_str());
	GLuint TEXT_VAO, TEXT_VBO;
	//Shader Class (Not Included in Files)
	//it just load and compile Shaders in that filepath
	lort::Shader *_shader = new lort::Shader("Shaders/vertexShader.txt", "Shaders/fragmentShader.txt");
	lort::Shader*_text_shader= new lort::Shader("Shaders/textVertexShader.txt", "Shaders/textFragmentShader.txt");
	
	//Camera Class (Not Included in Files) its just an ortho Camera with const position 
	//i had to make it with camera for scaling and stuff xD
	lort::Camera _camera;
	//OBJECTS IN THE GAME
	Player *_p = new Player(_shader);
	std::vector<Bullet> _P_BULLETS;
	std::vector<spaceAsteroid> _Asteroids;
	std::vector<UFO>	_UFOs;
	std::vector<Bullet> _UFO_BULLETS;
	std::vector<Point>  _Destroyed_Points;
	/* FUNCTIONS */
	//COLLISION DETECTORS 
	//PA -> Player Asteroid
	bool checkCollisionPA(Player p, spaceAsteroid a);
	//BA -> Bullet Asteroid (Player Bullet)
	bool checkCollisionBA(Bullet b, spaceAsteroid a);
	//BU -> Bullet UFO (Player Bullet)
	bool checkCollisionBU(Bullet b, UFO u);
	//BP -> Bullet Player (UFO Bullet)
	bool checkCollisionBP(Player p, Bullet b);
	//PU -> Player UFO
	bool checkCollisionPU(Player p, UFO u);
	//Check Collisions using above functions for all objects in scene
	bool checkCollisionsForPA();
	void checkCollisionsForPlayerBullets();
	bool checkCollisionsForBP();
	bool checkCollisionsForPU();

	//Collision for all stuff
	bool collisionDETECTION();

	//time out functions (for example if a bullet lived for certain time without collision i destroy it )
	void timeOutBP();
	void timeOutBU();
	void timeOutPoints();
	void timeOutAll();

	//ESCAPE Functionality for the user (Escort to safe area with certain Cooldown)
	void playerEscape();

	//Draw All Objects and Text in the Scene
	void draw();

	//Render Certain Text on Certain location on screen
	void RenderText(lort::Shader & s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	//Draw Text On The Screen
	//Score, Lives, Escape_CoolDown
	void drawTextOverScreen();


	void processInput(GLFWwindow *window,float deltaTime);
	//INIT LEVELS (AUTO GENERATED EVERYTIME PLAYER finish a level ) -> Harder Every Time
	void initLevel(int levelN);
	
	
};

