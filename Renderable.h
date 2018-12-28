#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include "Shader.h"

namespace ge{

	class Renderable{
		public:
			Renderable();
			virtual ~Renderable(){}
			virtual void draw(Shader* shader)=0;

	};
}

#endif
