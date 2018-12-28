#include "ge.h"
#include "Quad.h"
#include <iostream>
namespace ge{
  void Quad::setRotation(float r){
	this->m_rotation = r;
   }

  Quad::Quad(float *vertices, unsigned int *indices, size_t vSize, size_t iSize, glm::vec2 position, glm::vec3 color, float scale) : Renderable(), m_position(position), m_color(color), m_scale(scale){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
  }

  Quad::Quad(float *vertices, unsigned int *indices, size_t vSize, size_t iSize, float scale) : Quad(vertices, indices, vSize, iSize, glm::vec2(), glm::vec3(), scale){}

  Quad::~Quad(){
    
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
  }

  void Quad::setColor(glm::vec3 color){
    this->m_color = color;
  }

  void Quad::setPosition(glm::vec2 position){
    this->m_position = position;
  }

  void Quad::move(glm::vec2 dr){
	this->m_position += dr;

  }

  void Quad::setScale(float scale){
    this->m_scale = scale;
  }

  void Quad::draw(Shader* shader){
    shader->use();
    m_model = glm::mat4(1.0); // glm why? :(
    m_model = glm::translate(m_model, glm::vec3(m_position.x, m_position.y, 0));

    m_model = glm::scale(m_model, glm::vec3(m_scale));
    shader->setFloat("useTexture", 0.0f);
    shader->setMat4("model", m_model);
    shader->setVec3("color", m_color);
    //shader.setMat4("view", view);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
}
