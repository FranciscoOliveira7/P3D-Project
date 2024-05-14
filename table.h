#pragma once

#define GLEW_STATIC
#include <GL\glew.h>

/*
NumVertices: 6 faces * 4 vértices
NumIndices: 6 faces * 2 triângulos/face * 3 vértices/triângulo
*/

// Mesa de Bilhar (fiz isto manualmente (not fun)) - Zes
GLfloat vertices[][3] = {
    {-9.0f,  0.5f,  5.5f }, { 9.0f,  0.5f,  5.5f },
    {-9.0f, -0.5f,  5.5f }, { 9.0f, -0.5f,  5.5f },

    {-9.0f,  0.5f, -5.5f }, { 9.0f,  0.5f, -5.5f },
    {-9.0f, -0.5f, -5.5f }, { 9.0f, -0.5f, -5.5f },
};

GLfloat cores[][3] = {
    { 0.5f, 0.85f, 0.6f }, { 0.29, 0.77, 0.35 },
    { 0.32, 0.75, 0.41 }, { 0.4f, 0.8f, 0.5f },

    { 0.41, 0.81, 0.52 }, { 0.4f, 0.8f, 0.5f },
    { 0.4f, 0.8f, 0.5f }, { 0.22, 0.55, 0.29 },
};

GLuint indices[] = {
    // Frente
    0, 1, 2, 1, 3, 2,
    // Direita
    1, 3, 7, 1, 5, 7,
    // Baixo
    2, 3, 6, 3, 6, 7,
    // Esquerda
    0, 2, 4, 2, 6, 4,
    // Trás
    4, 5, 6, 5, 7, 6,
    // Cima
    0, 4, 1, 4, 5, 1
};