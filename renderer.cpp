#include "renderer.h"
#include "table.h"

void Renderer::BindModel(Model* model)
{
	model_ = model;
}

void Renderer::Render(vec3 position, vec3 orientation)
{
    WorldTrans world;
    world.SetPosition(position);
    world.SetRotation(orientation.x, orientation.y, orientation.z);

    mat4 mvp = projection * camera_.GetViewMatrix() * world.GetMatrix();

    GLint mpvId = glGetProgramResourceLocation(model_->program_, GL_UNIFORM, "MVP");
    glProgramUniformMatrix4fv(model_->program_, mpvId, 1, GL_FALSE, value_ptr(mvp));

    glBindVertexArray(model_->vao_);

    glDrawElements(GL_TRIANGLES, model_->index_buffer_->Count(), GL_UNSIGNED_INT, (void*)0);
}

void Renderer::Install(void) {

    model_->vertex_buffer_ = new VertexBuffer(vertices, sizeof(vertices));
    model_->color_buffer_  = new VertexBuffer(cores, sizeof(cores));
    model_->index_buffer_  = new IndexBuffer(indices, 36);

    model_->vertex_buffer_->Bind();
    model_->AttribPointer(0, 3, 0);
    model_->color_buffer_->Bind();
    model_->AttribPointer(1, 3, 1);
}

void Renderer::Load(const std::string obj_model_filepath)
{
}

