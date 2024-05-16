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

    model_->Draw();
}

void Renderer::Install(void) {

    model_->InitializeComponents(3); // Vertices, UVs/ Colors and Normals

    model_->BufferStorage(GL_ARRAY_BUFFER, 0, vertices, sizeof(vertices));
    model_->BufferStorage(GL_ARRAY_BUFFER, 1, cores, sizeof(cores));
    model_->BufferStorage(GL_ELEMENT_ARRAY_BUFFER, 2, indices, sizeof(indices));

    GLint coordsId = model_->GetInputLocation(model_->program_, "vPosition");
    GLint coresId = model_->GetInputLocation(model_->program_, "vColors");

    model_->AttribPointer(0, 3, coordsId);
    model_->AttribPointer(1, 3, coresId);
}

void Renderer::Load(const std::string obj_model_filepath)
{
}

