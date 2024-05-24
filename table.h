#pragma once

#define GLEW_STATIC
#include <GL\glew.h>

/*
NumVertices: 6 faces * 4 v�rtices
NumIndices: 6 faces * 2 tri�ngulos/face * 3 v�rtices/tri�ngulo
*/

// Mesa de Bilhar (fiz isto manualmente (not fun)) - Zes
GLfloat vertices[][3] = {
    {-9.0f,  0.5f,  5.5f }, { 9.0f,  0.5f,  5.5f },
    {-9.0f, -0.5f,  5.5f }, { 9.0f, -0.5f,  5.5f },

    {-9.0f,  0.5f, -5.5f }, { 9.0f,  0.5f, -5.5f },
    {-9.0f, -0.5f, -5.5f }, { 9.0f, -0.5f, -5.5f },
};

GLfloat cores[][3] = {
    { 0.5f,  0.85f, 0.6f  }, { 0.29f, 0.77f, 0.35f },
    { 0.32f, 0.75f, 0.41f }, { 0.4f,  0.8f,  0.5f },

    { 0.41f, 0.81f, 0.52f }, { 0.4f,  0.8f,   0.5f },
    { 0.4f,  0.8f,  0.5f  }, { 0.22f, 0.55f, 0.29f },
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
    // Tr�s
    4, 5, 6, 5, 7, 6,
    // Cima
    0, 4, 1, 4, 5, 1
};