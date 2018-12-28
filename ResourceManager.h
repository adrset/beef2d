#ifndef RESOURCE_CACHE_
#define RESOURCE_CACHE_
#include <map>
#include "Texture.h"
namespace ge{

class ResourceManager{
	public:
	static Texture* loadTexture(std::string);
	private: 
	static std::map <std::string, Texture> m_textures;
	
};

}
#endif
