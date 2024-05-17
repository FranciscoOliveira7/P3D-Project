#include "model.h"

Model::~Model()
{
	delete vertex_buffer_;
	delete color_buffer_;
	delete normal_buffer_;
	delete index_buffer_;
}

// Not the most abstract implementation ever but I'm too lazy
void Model::AttribPointer() const {

	// I'm just assuming the layout for each buffer

	if (vertex_buffer_ != nullptr) {
		vertex_buffer_->Bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}
	if (color_buffer_ != nullptr) {
		color_buffer_->Bind();
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
}