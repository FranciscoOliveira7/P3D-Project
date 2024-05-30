#include "world_transform.h"

namespace objr {

    mat4 Transform::GetMatrix(void) const {

        mat4 model = mat4(1.0f);

        model = scale(model, scale_);

        // Rodar antes para rodar em torno da origem
        model = rotate(model, rotation_.x, vec3(1, 0, 0));
        model = rotate(model, rotation_.y, vec3(0, 1, 0));
        model = rotate(model, rotation_.z, vec3(0, 0, 1));

        model = translate(model, pos_);

        // Rodar depois para rodar no seu próprio eixo
        model = rotate(model, spin_.x, vec3(1, 0, 0));
        model = rotate(model, spin_.y, vec3(0, 1, 0));
        model = rotate(model, spin_.z, vec3(0, 0, 1));

        return model;
    }
}