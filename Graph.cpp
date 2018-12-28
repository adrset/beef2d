#include "Graph.h"
namespace ge{
  Graph::Graph() {
      init = false;
      m_points = new float[MAX_POINTS * 2];
      m_lastUpdated = 0;
      glGenVertexArrays(1, &m_vao);
      glGenBuffers(1, &m_vbo);

      glBindVertexArray(m_vao);

      glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
      glBufferData(GL_ARRAY_BUFFER, MAX_POINTS * 2 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);

      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glBindVertexArray(0);

  }

  Graph::~Graph(){
    delete m_points;
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
  }

  void Graph::addPoint(float x, float y){
    if(!init ){
      maxX = x;
      maxY = y;
      minX = x;
      minY = y;
      init = true;
    }
    if(iter / 2 == MAX_POINTS ){
      iter = 0;
    }
    if(x>maxX)  maxX = x;
    if(y>maxY)  maxY = y;
    if(x<minX)  minX = x;
    if(y<minY)  minY = y;

    m_points[iter++] = x;
    m_points[iter++] = y;
    m_lastUpdated = 1;

  }

  void Graph::draw(Shader* shader){
      glBindVertexArray(m_vao);
      glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
      // Bad approach
      if(m_lastUpdated > 0){
        m_lastUpdated = 0;
        glBufferSubData(GL_ARRAY_BUFFER,0, MAX_POINTS * 2 * sizeof(float), m_points);
      }
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      shader->use();
      shader->setVec2("min", glm::vec2(minX, minY));
      shader->setVec2("max", glm::vec2(maxX, maxY));
      glDrawArrays(GL_LINE_STRIP, 0, iter / 2);
      glBindVertexArray(0);

  }
}
