#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...

using namespace glm;

class Camera {
public:

    // Construtor que inicializa a c�mera com a raz�o de aspecto fornecida
    Camera(float ratio) : ratio_{ ratio } {
        center_ = vec3(0.0f, -5.0f, 0.0f);  // Ponto para onde a c�mera est� olhando
        up_ = vec3(0.0f, 1.0f, 0.0f);       // Vetor que define a dire��o "para cima"

        // Configura a matriz de visualiza��o
        view_ = lookAt(vec3(0.0f), center_, up_);
        // Configura a matriz de proje��o
        projection_ = perspective(radians(45.0f), ratio, 1.0f, 100.0f);
    }

    // Define a posi��o da c�mera
    void SetPosition(float x, float y, float z) {
        view_ = lookAt(vec3(x, y, z), center_, up_);
    }

    // Define o campo de vis�o da c�mera
    void SetFov(float fov) {
        fov_ = fov;
        UpdateProjection();
    }

    // Define a raz�o de aspecto da c�mera
    void SetRatio(float ratio) {
        ratio_ = ratio;
        UpdateProjection();
    }

    // Retorna a matriz de proje��o
    mat4 GetProjectionMatrix(void) const { return projection_; }

    // Retorna a matriz de visualiza��o
    mat4 GetViewMatrix(void) const { return view_; }

private:
    // Atualiza a matriz de proje��o com os novos par�metros
    void UpdateProjection() { projection_ = perspective(radians(fov_), ratio_, 1.0f, 100.0f); }

    vec3 center_;   // Ponto para onde a c�mera est� olhando
    vec3 up_;       // Vetor que define a dire��o "para cima"

    float ratio_ = 0.0f;  // Raz�o de aspecto da c�mera
    float fov_ = 45.0f;   // Campo de vis�o da c�mera

    mat4 projection_;  // Matriz de proje��o
    mat4 view_;        // Matriz de visualiza��o
};