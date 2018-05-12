#pragma once
#include <iostream>
#include <Potts/Potts.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/Window.h>
#include <GameEngine/Shader.h>
#include <GameEngine/Timer.h>
#include <GameEngine/Quad.h>
#include <GameEngine/Button.h>
#include <GameEngine/Graph.h>

class Game
{
public:
	Game(int width, int height, std::string title, int fps = 60);
	~Game();
	void cleanUp();
	void start();
	void gameLogic();
	void waitAndShoutFPS();

private:
	glm::mat4 m_projection;
	GameEngine::Shader* m_shader;
	GameEngine::Quad* m_quad;
	int m_fps = 60;
	
	void processInput();
	int m_width;
	int m_height;

	std::string m_title;
 
	GameEngine::Window* m_window;

	GameEngine::Timer* m_timer;
	float lastX;
	float lastY;
	void loop();
};
