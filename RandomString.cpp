#include "RandomString.h"

namespace ge{
				std::mt19937 RandomString::m_generator(80);
				std::uniform_int_distribution<int> RandomString::m_distribution;
				const std::string RandomString::m_chars("abcdefghijklmnoprstuwxyzABCDEFGHIJKLMNLOPRSTUWXY0123456789!@#$%^&*_+=-");
				
				std::string RandomString::getString(unsigned int length /*= 8 */){
					std::string tmp;
					
					int rand;
					for(unsigned int i=0; i<length;i++){
						rand = m_distribution(m_generator) % m_chars.size(); 
						tmp += m_chars[rand];
					}
					
					return tmp;
					
				}

	
}
