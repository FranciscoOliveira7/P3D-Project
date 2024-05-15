#include "renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::BindModel(Model* model)
{
	model_ = model;
}

void Renderer::Render(vec3 position, vec3 orientation)
{
    WorldTrans world;
    world.SetPosition(position);
    world.SetRotation(orientation.x, orientation.y, orientation.z);

    camera_.SetPosition(0.0f, 0.0f, 10.0f);

    mat4 mvp = projection * camera_.GetViewMatrix() * world.GetMatrix();

    GLint mpvId = glGetProgramResourceLocation(model_->program_, GL_UNIFORM, "MVP");
    glProgramUniformMatrix4fv(model_->program_, mpvId, 1, GL_FALSE, value_ptr(mvp));

    model_->Draw();
}

void Renderer::Install(void)
{
}

void Renderer::Load(const std::string obj_model_filepath)
{
}

