#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "Game.h"

#include <vector>
#include <cstdlib>
#include <fstream>
#include <thread>

#include <iostream>
#include <unistd.h>



Game::Game(int width, int height, std::string title, int fps): m_width{width}, m_height(height), m_title(title)
{	
	for(int i=0;i<4;i++)
		m_selectedFields[i] = 0;
	srand(time(NULL));
	//m_server = new Network::ListenerServer();
	m_client = new Network::Client();
	m_window = new GameEngine::Window(m_width, m_height, m_title);
	
	m_timer = new GameEngine::Timer(fps);

	lastX = m_width / 2.0f;
	lastY = m_height / 2.0f;

	m_instanceShader = new GameEngine::Shader("instance.vs", "instance.fs");
	m_shader = new GameEngine::Shader("2dshader.vs", "2dshader.fs");
	m_projection = glm::ortho(0.0f, (GLfloat)m_width, (GLfloat)m_height, 0.0f, -10.0f, 10.0f);

	m_shader->use();
	m_shader->setMat4("orthoMatrix", m_projection);

	m_instanceShader->use();
	m_instanceShader->setMat4("orthoMatrix", m_projection);

	// Simple quad
	float vertices[] = {
       1.0f,  1.0f, 0.0f,  1.0f,  1.0f, // top right
       1.0f, -1.0f, 0.0f,  1.0f,  0.0f,// bottom right
      -1.0f, -1.0f, 0.0f,  0.0f,  0.0f,// bottom left
      -1.0f,  1.0f, 0.0f,  0.0f,  1.0f // top left
  };
  unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,  // first Triangle
      1, 2, 3   // second Triangle
  };



	float offset = (float)m_width/8.0f;
	std::vector<glm::vec3> col;
	std::vector<glm::vec3> pos;
	
	for(int i =0;i<8;i++){
		for(int j =0;j<8;j++){
			 pos.push_back(glm::vec3(offset*i,offset*j,0));
			 col.push_back(glm::vec3((i+j)%2));
		}
	}

	m_board = new GameEngine::QuadField(vertices, indices, sizeof(vertices), sizeof(indices), pos, col, offset);
	for(int i =0;i<3;i++){
		for(int j =0;j<4;j++){
			m_draughtsOpposite.push_back(new GameEngine::TexturedQuad(vertices, indices, sizeof(vertices), sizeof(indices), glm::vec2(200*j + (i == 1 ? 100: 0),100*i), glm::vec3(0.13, 0.7, 0.12), offset, "red.png"));
		}
	}

for(int i =5;i<8;i++){
		for(int j =0;j<4;j++){
			m_draughts.push_back(new GameEngine::TexturedQuad(vertices, indices, sizeof(vertices), sizeof(indices), glm::vec2(200*j + (i == 5 || i == 7 ? 100: 0),100*i), glm::vec3(0.13, 0.7, 0.12), offset, "white.png"));
		}
	}

	
	m_texturedQuad = new GameEngine::TexturedQuad(vertices, indices, sizeof(vertices), sizeof(indices), glm::vec2(100,0), glm::vec3(0.3, 0.7, 0.1), offset, "white.png");
   
	


}

std::ostream& operator<<(std::ostream& stream, glm::vec2& vec){

	stream << "[" << vec.x << ", " << vec.y << "]";
	return stream;
}

std::ostream& operator<<(std::ostream& stream, glm::vec3& vec){

	stream << "[" <<vec.x << ", " << vec.y << ", " << vec.z << "]";
	return stream;

}

void Game::start(){
	loop();
}

void Game::loop() {

	
	int loop=0;
	while (!m_window->shouldClose())
	{	
		processInput();
		m_timer->start();
		//Networking
		if(loop* 10 > m_fps ){
			networkLogic();
			loop = 0;	
		}
	
 		m_window->clear();
		glm::vec2 pos = GameEngine::InputManager::getMouseCoords().xy;
		const std::vector <glm::vec3>& positions = m_board->getPositions();
		const float& scale = m_board->getScale();
		for (unsigned int i = 0; i< positions.size();i++){
			if(pos.x > positions[i].x && pos.y > positions[i].y && pos.x < positions[i].x + scale && pos.y < positions[i].y + scale){
				if(GameEngine::InputManager::isMouseKeyDown(GLFW_MOUSE_BUTTON_1) && m_selected == 0){
					m_selectedFields[0] = ((int)pos.x /100) + 1;
					m_selectedFields[1] = ((int)pos.y /100) + 1;
					m_selected = 1;
					m_board->setColor(glm::vec3(0.6), i);
				}else if(GameEngine::InputManager::isMouseKeyDown(GLFW_MOUSE_BUTTON_1) && m_selected == 1){
					std::cout<<"ala"<<std::endl;
					int x =  ((int)pos.x /100) + 1;
					int y = ((int)pos.y /100) + 1;
					std::cout<< x << " " << y<<std::endl;
					if(m_selectedFields[0] != x || m_selectedFields[1] != y){
						m_selectedFields[2] = x;
						m_selectedFields[3] = y;
						m_selected = 2;
						m_board->setColor(glm::vec3(0.6,0.4,0.1), i);
					}
				}else if(m_selected == 2){
					if(GameEngine::InputManager::isKeyPressed(GLFW_KEY_ENTER)){
						m_selected = 3;
					}
				}else if(m_selected == 0){
					m_board->setOldColor(i);

				}
					
			}
			
		}
		
 		m_board->update(m_instanceShader); // draws quads

		for(int i =0;i<12;i++){
			m_draughtsOpposite[i]->draw(m_shader);
			m_draughts[i]->draw(m_shader);
		}


		
		m_window->swapBuffers();

		glfwPollEvents();
		
		waitAndShoutFPS();
		loop++;
	}
	m_client->close();
	cleanUp();

}

void Game::networkLogic(){

	Network::data recv;
	if(m_sessionID == 0 ){
		recv = m_client->send("GET_SID", 30000);
		if(!recv.empty){
			std::stringstream str;
			str<<recv.response;
			str>>m_sessionID;
			std::cout<<"Assigned ID"<<m_sessionID<<std::endl;
		
		}else{
			std::cout<<"No connection!       "<<std::endl;
		}
	}else if(m_selected == 3){
		std::string strg = "MOV ";
		strg += std::to_string(m_sessionID);
		for(int i=0;i<4;i++){
			strg += " ";
			strg += std::to_string(m_selectedFields[i]);
		}

		char *cstr = new char[strg.length() + 1];
		strcpy(cstr, strg.c_str());

		recv = m_client->send(cstr);

		delete [] cstr;
		if(!recv.empty){
			
			std::cout<<recv.response<<std::endl;
			m_selected = 0;
		}
	}else{

	recv = m_client->send("GET_BOARD");
		if(!recv.empty){
			
			std::stringstream str;
			str<<recv.response;
			int x;
			
			int i=0;
			while(str>>x){
				m_boardData[i/8][i%8] = x ;
				i++;
			}	
			
			std::cout<<"RESPONSE"<<std::endl;
			int k = 0;
			int m = 0;
			for(int i =0;i<12;i++){
				m_draughts[i]->setPosition(glm::vec2(-100));
				m_draughtsOpposite[i]->setPosition(glm::vec2(-100));
			}
			for(int i =0;i<8;i++){
				for(int j =0;j<8;j++){
					std::cout<<m_boardData[i][j]-2<<"*";
					if(m_boardData[i][j]-2 < 0) {// white 
						m_draughts[k++]->setPosition(glm::vec2(m_draughts[i]->getScale() * j,m_draughts[i]->getScale() * i));
					}else if(m_boardData[i][j]-2 >0){
						m_draughtsOpposite[m++]->setPosition(glm::vec2(m_draughtsOpposite[i]->getScale() * j,m_draughtsOpposite[i]->getScale() * i));
					}else{
						
					}
				}
				std::cout<<std::endl;
			}
			
		}else{
			std::cout<<"No connection!       "<<std::endl;
		}
      }

}

void Game::waitAndShoutFPS(){
		
m_fps = 1.0/m_timer->end();
//std::cout<< m_fps << std::endl;
		m_timer->wait();

}

void Game::gameLogic(){
	
}

void Game::processInput()
{
	if(GameEngine::InputManager::isKeyPressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(m_window->getWindowID(), true);

}


void Game::cleanUp() {
	
	delete m_board;
	//delete m_texturedQuad;
	m_window->closeWindow();
}


Game::~Game()
{
	delete m_window;
	delete m_shader;
	delete m_instanceShader;
	delete m_timer;
	
	std::cout << "Closing game." << std::endl;
}
