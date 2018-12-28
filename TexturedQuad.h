#ifndef TEXTURED_QUAD_H
#define TEXTURED_QUAD_H
#include "Quad.h"
#include "ResourceManager.h"

namespace ge{

class TexturedQuad: public Quad {
public:

	TexturedQuad(float *vertices, unsigned int *indices, size_t vSize, size_t iSize, glm::vec2 position, glm::vec3 color, float scale, std::string texturePath);
 	void draw(Shader* shader);
	~TexturedQuad();
private:
	Texture* m_texture;

};


}

#endif
