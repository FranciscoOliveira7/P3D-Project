#include "renderer.h"
#include "table.h"

void Renderer::Render(vec3 position, vec3 orientation)
{
    WorldTrans world;
    world.SetPosition(position);
    world.SetRotation(orientation.x, orientation.y, orientation.z);

    mat4 mvp = projection * camera_.GetViewMatrix() * world.GetMatrix();

    shader_->SetUniformMatrix4fv("MVP", mvp);

    model_->vao_->Bind();

    glDrawElements(GL_TRIANGLES, model_->index_buffer_->Count(), GL_UNSIGNED_INT, (void*)0);
}

void Renderer::Install(void) {

    model_->vao_ = new VertexArray();

    model_->vertex_buffer_ = new VertexBuffer(vertices, sizeof(vertices));
    model_->color_buffer_  = new VertexBuffer(cores, sizeof(cores));
    model_->index_buffer_  = new IndexBuffer(indices, sizeof(indices) / sizeof(GLuint));

    model_->vertex_buffer_->Bind();
    model_->AttribPointer(3, 0); // Location 0: vPositions
    model_->color_buffer_->Bind();
    model_->AttribPointer(3, 1); // Location 1: vColors
}

void Renderer::Load(const std::string obj_model_filepath)
{
}

