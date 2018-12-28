#include "QuadField.h"
#include <iostream>
namespace ge {


		QuadField::QuadField(float *vertices, unsigned int *indices, size_t vSize, size_t iSize, std::vector<glm::vec3> positions,
		 std::vector<glm::vec3> colors, float scale) : Quad (vertices, indices, vSize, iSize, scale), m_positions(positions),
		m_colors(colors), m_colorsCopy(colors){

			// FLOATS_PER_INSTANCE = 20
		    m_buffer = new float[m_positions.size() * FLOATS_PER_INSTANCE];


			// Generate a VBO
		    glGenBuffers(1, &m_instanceVBO);

			// Always bind buffer in order to modify it
		    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
  
			// Send information about data size (amount * FLOATS_PER_INSTANCE * 4 ) in bytes, and tell that we will provide data in future (nullptr)
		    glBufferData(GL_ARRAY_BUFFER, m_positions.size() * 4 * FLOATS_PER_INSTANCE, nullptr, GL_STREAM_DRAW);

  			// Bind VAO in order to add some attributes into it
		    glBindVertexArray(VAO);
		    // vertex Attributes

		    //We know that we can only store 4 floats in one attribute, so we send our matrix as 4 vec4 columns
		    GLsizei vec4Size = sizeof(glm::vec4);
		    glEnableVertexAttribArray(2);
		    // attribute nr, lenght, type, normalize? , stride, pointer to the data
		    // Our structure (f is float) Buffer = { block_1 ([f,f,f,f], [f,f,f,f], [f,f,f,f], [f,f,f,f], [f,f,f,1.0f]) ... block_n(...)}
		    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 5 * vec4Size, (void*)0);
		    glEnableVertexAttribArray(2);
		    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 5 * vec4Size, (void*)((size_t)vec4Size));
		    glEnableVertexAttribArray(3);
		    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 5 * vec4Size, (void*)((size_t)(2 * vec4Size)));
		    glEnableVertexAttribArray(4);
		    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 5 * vec4Size, (void*)((size_t)(3 * vec4Size)));
		    glEnableVertexAttribArray(5);
		    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 5 * vec4Size, (void*)((size_t)(4 * vec4Size)));

		    // 2nd argument 1 - move to another block after 1 instance

		    glVertexAttribDivisor(2, 1);
		    glVertexAttribDivisor(3, 1);
		    glVertexAttribDivisor(4, 1);
		    glVertexAttribDivisor(5, 1);
		    glVertexAttribDivisor(6, 1);

			// Just for safety unbind vao after editionsX
		    glBindVertexArray(0);

		}

		void QuadField::setColor(glm::vec3 color, int index){
			m_colors[index] = color;


		}

		QuadField::~QuadField(){
			delete[] m_buffer;
			glDeleteBuffers(1, &m_instanceVBO);
		}

		void QuadField::update(Shader* shader){
			// Use our shader
			shader->use();

			// Enable vertex attributes and use VAO
			prepare();

			// Reset iteration index
			index = 0;

			// Update matrices and store them in float array
			updateTransformations();

			// Send updated data to GPU
			updateVBO();

			// Eventually draw our instanced quads
			drawNoUpdate();

			// Disable vertex attributes
			stop();
		}

		void QuadField::drawNoUpdate(){
				glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0,
				m_positions.size());
		}

		void QuadField::updateTransformations(){
			for(unsigned int i=0; i<m_positions.size();i++){
				m_model = glm::mat4(1.0);
				m_model = glm::translate(m_model, m_positions[i]);
				m_model = glm::scale(m_model, glm::vec3(m_scale));
				m_buffer[index++]=(m_model[0][0]);
				m_buffer[index++]=(m_model[0][1]);
				m_buffer[index++]=(m_model[0][2]);
				m_buffer[index++]=(m_model[0][3]);

				m_buffer[index++]=(m_model[1][0]);
				m_buffer[index++]=(m_model[1][1]);
				m_buffer[index++]=(m_model[1][2]);
				m_buffer[index++]=(m_model[1][3]);

				m_buffer[index++]=(m_model[2][0]);
				m_buffer[index++]=(m_model[2][1]);
				m_buffer[index++]=(m_model[2][2]);
				m_buffer[index++]=(m_model[2][3]);

				m_buffer[index++]=(m_model[3][0]);
				m_buffer[index++]=(m_model[3][1]);
				m_buffer[index++]=(m_model[3][2]);
				m_buffer[index++]=(m_model[3][3]);

				m_buffer[index++]=(m_colors[i].x);
				m_buffer[index++]=(m_colors[i].y);
				m_buffer[index++]=(m_colors[i].z);
				m_buffer[index++]=1.0f;
			}
		}

		void QuadField::setColor(int i, glm::vec3 col){
			m_colors[i] = col;
		}

		void QuadField::prepare() {

			glBindVertexArray(VAO);
			for (int i = 0; i < 7; i++)
				glEnableVertexAttribArray(i);

		}

		void QuadField::stop(){
			for (int i = 0; i < 7; i++)
				glDisableVertexAttribArray(i);

			glBindVertexArray(0);
		}

		void QuadField::updateVBO(){
			glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
			//glBufferData(GL_ARRAY_BUFFER, m_positions.size() * 4 * FLOATS_PER_INSTANCE, nullptr, GL_STATIC_DRAW);
			// Send data to GPU
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_positions.size() *  4 * FLOATS_PER_INSTANCE,  m_buffer);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}


}
