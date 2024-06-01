#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...

using namespace glm;

class Camera {
public:

    // Construtor que inicializa a câmera com a razão de aspecto fornecida
    Camera(float ratio) : ratio_{ ratio } {
        center_ = vec3(0.0f, -5.0f, 0.0f);  // Ponto para onde a câmera está olhando
        up_ = vec3(0.0f, 1.0f, 0.0f);       // Vetor que define a direção "para cima"

        // Configura a matriz de visualização
        view_ = lookAt(vec3(0.0f), center_, up_);
        // Configura a matriz de projeção
        projection_ = perspective(radians(45.0f), ratio, 1.0f, 100.0f);
    }

    // Define a posição da câmera
    void SetPosition(float x, float y, float z) {
        view_ = lookAt(vec3(x, y, z), center_, up_);
    }

    // Define o campo de visão da câmera
    void SetFov(float fov) {
        fov_ = fov;
        UpdateProjection();
    }

    // Define a razão de aspecto da câmera
    void SetRatio(float ratio) {
        ratio_ = ratio;
        UpdateProjection();
    }

    // Retorna a matriz de projeção
    mat4 GetProjectionMatrix(void) const { return projection_; }

    // Retorna a matriz de visualização
    mat4 GetViewMatrix(void) const { return view_; }

private:
    // Atualiza a matriz de projeção com os novos parâmetros
    void UpdateProjection() { projection_ = perspective(radians(fov_), ratio_, 1.0f, 100.0f); }

    vec3 center_;   // Ponto para onde a câmera está olhando
    vec3 up_;       // Vetor que define a direção "para cima"

    float ratio_ = 0.0f;  // Razão de aspecto da câmera
    float fov_ = 45.0f;   // Campo de visão da câmera

    mat4 projection_;  // Matriz de projeção
    mat4 view_;        // Matriz de visualização
};