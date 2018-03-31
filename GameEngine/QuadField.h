#ifndef QUADFIELD_H_
#define QUADFIELD_H_
#include <glm/glm.hpp>
#include <vector>
#include "Quad.h"

namespace GameEngine {
	
	class QuadField : public Quad {
	public:
		QuadField(float *vertices, unsigned int *indices, size_t vSize, size_t iSize, std::vector<glm::vec3> positions, std::vector<glm::vec3> colors,
		 float scale);
		~QuadField();
		void update(Shader* shader);
		void addInstanceAttribute(int vao, int vbo, int attribute, int dataSize, int dataLength, int offset);
		void prepare();
		void setColor(int i, glm::vec3 col);
	private:
		void stop();
		void updateVBO();
		int index = 0;
		void updateTransformations();
		static const unsigned int FLOATS_PER_INSTANCE = 20; // mat4 + vec3
		std::vector <glm::vec3> m_positions;
		std::vector <glm::vec3> m_colors;
		std::vector <glm::mat4> m_models;
		float* m_buffer;
		unsigned int m_instanceVBO;
	};

}

#endif