#include "model.h"
#include "table.h"

void Model::Delete()
{
	vertex_buffer_.Delete();
	color_buffer_.Delete();
	normal_buffer_.Delete();
	index_buffer_.Delete();
}

void Model::Install(bool test) {

    //GLint vaoid;

    //model_.vao_.Bind();
    //glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoid);

    //glBindVertexArray(1);
    //std::cout << model_.vao_.GetId() << std::endl;
    //glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoid);

    vao_.Create();

    vertex_buffer_.Create(vertices, sizeof(vertices));
    color_buffer_.Create(cores, sizeof(cores));
    index_buffer_.Create(indices, sizeof(indices) / sizeof(GLuint));

    AttribPointer();

    //glBindVertexArray(0);
    //glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoid);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //glUseProgram(0);
    //glBindTexture(GL_TEXTURE_2D, 0);

    //model_.vao_.Unbind();
}

void Model::Render(vec3 position, vec3 orientation)
{
    WorldTrans world;
    world.SetPosition(position);
    world.SetRotation(orientation.x, orientation.y, orientation.z);

    mat4 mvp = projection * camera_.GetViewMatrix() * world.GetMatrix();

    shader_->SetUniformMatrix4fv("MVP", mvp);

    vao_.Bind();

    glDrawElements(GL_TRIANGLES, index_buffer_.Count(), GL_UNSIGNED_INT, (void*) 0);
}

// Not the most abstract implementation ever but I'm too lazy
void Model::AttribPointer() const {

	// I'm just assuming the layout for each buffer

	vertex_buffer_.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(0);

	color_buffer_.Bind();
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(1);
}