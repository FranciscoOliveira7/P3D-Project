#pragma once

#include <iostream>
#include <fstream>
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr
#include <GL/glew.h>
#include <string>

/*****************************************************************************
					 GLuint LoadShaders(ShaderInfo*);

Descrição:
----------
Recebe um array de estruturas ShaderInfo.
Cada estrutura contém:
- tipo de shader. No OpenGL 4.x poderá ser um dos seguintes valores:
  - GL_COMPUTE_SHADER
  - GL_VERTEX_SHADER
  - GL_TESS_CONTROL_SHADER
  - GL_TESS_EVALUATION_SHADER
  - GL_GEOMETRY_SHADER
  - GL_FRAGMENT_SHADER
- apontador para uma C-string, que contém o nome do ficheiro com código do shader
- valor que referencia o objeto shader criado

O array de estruturas deverá terminar com o valor GL_NONE no campo 'type'.
Exemplo:
ShaderInfo  shaders[] = {
	{ GL_VERTEX_SHADER, "triangles.vert" },
	{ GL_FRAGMENT_SHADER, "triangles.frag" },
	{ GL_NONE, NULL }
};

Retorno:
--------
Em caso de sucesso, a função retorna o valore que referencia o objeto programa.
Em caso de erro, será retornado o valor zero (0).

*****************************************************************************/
typedef struct {
	GLenum      type;
	const char* filename;
	GLuint      shader;
} ShaderInfo;

typedef struct Material {
	std::string name;

	glm::vec3 ambient;  // Ka
	glm::vec3 diffuse;  // kd
	glm::vec3 specular; // ke
	float shininess;    // Expoente de reflexão especular

	Material() : name("N/A"), ambient(glm::vec3(0.0f)), diffuse(glm::vec3(0.0f)), specular(glm::vec3(0.0f)), shininess(0.0f) {}
} Material;

class Shader {
private:
	GLuint program_;

public:
	void Create(ShaderInfo* shaders);

	void Bind() { glUseProgram(program_); }

	void SetUniformMatrix4fv(const std::string& name, glm::mat4 mat);

	void SetUniform3fv(const std::string& name, glm::vec3 idk);

	void SetUniformMaterial(const std::string& name, Material material);

	unsigned int GetUniformLocation(const std::string& name);

	// Funções criadas pelo stor
	GLchar* ReadShader(const char* filename);
	GLuint LoadShaders(ShaderInfo* shaders);
	void DestroyShaders(ShaderInfo* shaders);
};