#pragma once
#include <glad/glad.h>
#include <string>
#include "errors.h"
#include <stb_image.h>
namespace ge {

	class Texture
	{
	public:
		Texture(std::string path, std::string typeName = "");
		~Texture();

		unsigned int getID() const { return m_texture; }
		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }
		std::string getType() const { return m_type; }
		std::string getPath() const { return m_path; }
		void bind();
		void unbind();
		bool operator<(const Texture &t);
		
	private:
		std::string m_type;
		std::string m_path;
		unsigned int m_texture;
		int m_width, m_height, m_nrChannels;
	};

}

