#pragma once

#include <GL/glew.h>

namespace Puly {
	struct Point {
		GLfloat x, y, z;

		Point(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z){}
	};
}