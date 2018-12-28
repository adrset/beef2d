#ifndef QUAD_H_
#define QUAD_H_

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Renderable.h"

namespace ge{
  class Quad : public Renderable{
  public:
    Quad(float *vertices, unsigned int *indices, size_t vSize, size_t iSize, float scale);
    Quad(float *vertices, unsigned int *indices, size_t vSize, size_t iSize, glm::vec2 position, glm::vec3 color, float scale);
    ~Quad();
    glm::vec2 getPosition() const { return m_position; }
    float getScale() const { return m_scale; }
    glm::vec3 getColor() const { return m_color; }
    void setPosition(glm::vec2 position);
    float getRotation() const { return this->m_rotation;}
    void setRotation(float r);
    void setScale(float scale);
    void setColor(glm::vec3);
    void draw(Shader* shader);
    void move(glm::vec2 dr);
    unsigned int getEBO() const { return EBO; }
    unsigned int getVBO() const { return VBO; } // only positions stored
    unsigned int getVAO() const { return VAO; }
  protected:
    float m_rotation = 0;
    glm::mat4 m_model; //Reusable mat4
    unsigned int VBO, VAO, EBO;
    glm::vec2 m_position;
    glm::vec3 m_color;
    float m_scale;
  };



}

#endif
