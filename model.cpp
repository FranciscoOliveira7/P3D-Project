#include "model.h"

void Model::AttribPointer(int size, unsigned int location) {

	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);
}