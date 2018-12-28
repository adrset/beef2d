#ifndef RANDOMSTRING_H_
#define RANDOMSTRING_H_
#include <random>
namespace ge {
class RandomString {
    public:
		static const std::string m_chars;
        static std::mt19937 m_generator;
        static std::uniform_int_distribution<int> m_distribution;
        static std::string getString(unsigned int length = 8);

};



}

#endif
