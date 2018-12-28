#include "TexturedQuad.h"

namespace ge{



	TexturedQuad::TexturedQuad(float *vertices, unsigned int *indices, size_t vSize, size_t iSize, glm::vec2 position, glm::vec3 color, float scale, std::string texturePath):  Quad (vertices, indices, vSize, iSize, position, color, scale), m_texture(new Texture(texturePath)){
	
}

 void TexturedQuad::draw(Shader* shader){
    shader->use();
    m_model = glm::mat4(1.0); // glm why? :(

    m_model = glm::translate(m_model, glm::vec3(m_position.x, m_position.y, 0));
    m_model = glm::rotate(m_model, glm::radians(m_rotation), glm::vec3(0.0, 0.0, 1.0));
    m_model = glm::scale(m_model, glm::vec3(m_scale));
    shader->setFloat("useTexture", 1.0f);
    shader->setMat4("model", m_model);
    shader->setVec3("color", m_color);
    m_texture->bind();
    //shader.setMat4("view", view);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //m_texture->unbind();
    glBindVertexArray(0);
  }
  TexturedQuad::~TexturedQuad(){
    
  }




}

