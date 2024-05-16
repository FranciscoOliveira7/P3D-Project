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

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
}

void Renderer::Install(void) {

    vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
    colorBuffer  = new VertexBuffer(cores, sizeof(cores));
    ib           = new IndexBuffer(indices, 36);

    GLint coordsId = model_->GetInputLocation(model_->program_, "vPosition");
    GLint coresId = model_->GetInputLocation(model_->program_, "vColors");

    vertexBuffer->Bind();
    model_->AttribPointer(0, 3, coordsId);
    colorBuffer->Bind();
    model_->AttribPointer(1, 3, coresId);
}

void Renderer::Load(const std::string obj_model_filepath)
{
}

