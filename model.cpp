#include "model.h"

Model::~Model()
{
	delete vertex_buffer_;
	delete color_buffer_;
	delete normal_buffer_;
	delete index_buffer_;

	
}

void Model::AttribPointer(int size, unsigned int location) {

	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);
}