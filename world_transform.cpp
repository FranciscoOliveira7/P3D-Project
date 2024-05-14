#include "world_transform.h"

void WorldTrans::SetScale(float scale)
{
    scale_ = scale;
}


void WorldTrans::SetRotation(float x, float y, float z)
{
    rotation_.x = x;
    rotation_.y = y;
    rotation_.z = z;
}


void WorldTrans::SetPosition(float x, float y, float z)
{
    pos_.x = x;
    pos_.y = y;
    pos_.z = z;
}


void WorldTrans::Rotate(float x, float y, float z)
{
    rotation_.x += x;
    rotation_.y += y;
    rotation_.z += z;
}


mat4 WorldTrans::GetMatrix()
{
    mat4 model = mat4(1.0f);

    model = scale(model, vec3(scale_, scale_, scale_));

    // there's probably a way to make optimize this, might fix later
    model = rotate(model, rotation_.x, vec3(1, 0, 0));
    model = rotate(model, rotation_.y, vec3(0, 1, 0));
    model = rotate(model, rotation_.z, vec3(0, 0, 1));
    // ---

    model = translate(model, vec3(pos_.x, pos_.y, pos_.z));

    return model;
}