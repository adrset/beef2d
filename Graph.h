#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "Renderable.h"

namespace ge{

  class Graph : public Renderable{
  public:
    Graph();
    ~Graph();
    void draw(Shader* shader);
    void addPoint(float x, float y);
  private:
    bool init;
    unsigned int iter = 0;
    float maxX, minX;
    float maxY, minY;
    const unsigned int MAX_POINTS = 10000;
    unsigned int m_vao, m_vbo;
    float* m_points;
    unsigned int m_lastUpdated;

  };

}

#endif
