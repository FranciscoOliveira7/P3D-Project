#include "world_transform.h"

namespace objr {

    mat4 WorldTrans::GetMatrix(void) {

        mat4 model = mat4(1.0f);

        model = scale(model, scale_);

        // do this with quaternions or whatever it's called
        model = rotate(model, rotation_.x, vec3(1, 0, 0));
        model = rotate(model, rotation_.y, vec3(0, 1, 0));
        model = rotate(model, rotation_.z, vec3(0, 0, 1));
        // ---

        model = translate(model, pos_);

        model = rotate(model, spin_.x, vec3(1, 0, 0));
        model = rotate(model, spin_.y, vec3(0, 1, 0));
        model = rotate(model, spin_.z, vec3(0, 0, 1));

        return model;
    }
}