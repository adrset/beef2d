#include "ResourceManager.h"

namespace ge{
std::map <std::string, Texture> ResourceManager::m_textures;
Texture* ResourceManager::loadTexture(std::string texturePath){
	std::map<std::string, Texture>::iterator it;

	it = m_textures.find(texturePath);

	if(it == m_textures.end()){
		Texture t = Texture(texturePath);
		m_textures.insert(std::pair<std::string,Texture>(texturePath, t));
		it = m_textures.end();
		return &it->second;

	}else{
		return &it->second;

	}

}





}
