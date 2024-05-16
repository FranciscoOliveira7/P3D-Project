#include "shader.h"

Shader::Shader(ShaderInfo* shaders)
{
    // Compile and Load shaders to program (código feito pelo stor)
    program_ = LoadShaders(shaders);
    if (!program_) exit(EXIT_FAILURE);
    glUseProgram(program_);
}

void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 mat)
{
    GLint location = GetUniformLocation(name);
    glProgramUniformMatrix4fv(program_, location, 1, GL_FALSE, value_ptr(mat));
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
    GLint location = glGetProgramResourceLocation(program_, GL_UNIFORM, name.c_str());
    if (location == -1) std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
    return location;
}


GLchar* Shader::ReadShader(const char* filename) {
	// Abre o ficheiro 'filename' em binário, e coloca-se na última posição do ficheiro.
	std::ifstream ficheiro(filename, std::ifstream::ate | std::ifstream::binary);
	// Se o ficheiro foi aberto.
	if (ficheiro.is_open()) {
		// Leitura da próxima posição de leitura.
		std::streampos tamanhoDoFicheiroEmBytes = ficheiro.tellg();
		// Reposiciona a leitura do ficheiro no seu início.
		ficheiro.seekg(0, std::ios::beg);

		// Alocação de espaço de memória para dados do ficheiro.
		GLchar* source = new GLchar[int(tamanhoDoFicheiroEmBytes) + 1];
		// Leitura do ficheiro para o array 'source'.
		ficheiro.read(source, tamanhoDoFicheiroEmBytes);
		// Fecha a string.
		source[tamanhoDoFicheiroEmBytes] = 0;

		// Fecha o ficheiro.
		ficheiro.close();

		// Retorna o endereço da string alocada.
		return const_cast<GLchar*>(source);
	}
	else {
		std::cerr << "Erro ao abrir o ficheiro '" << filename << "'" << std::endl;
	}

	return nullptr;
}

GLuint Shader::LoadShaders(ShaderInfo* shaders) {
	if (shaders == nullptr) return 0;

	// Cria um objeto de programa
	GLuint program = glCreateProgram();

	for (GLint i = 0; shaders[i].type != GL_NONE; i++) {
		// Cria um objeto shader
		shaders[i].shader = glCreateShader(shaders[i].type);

		// Efetua a leitura do código do shader
		const GLchar* source = ReadShader(shaders[i].filename);
		// Se não conseguir ler o código
		if (source == NULL) {
			DestroyShaders(shaders);

			return 0;
		}

		// Carrega o código do shader
		glShaderSource(shaders[i].shader, 1, &source, NULL);
		delete[] source;

		// Compila o shader
		glCompileShader(shaders[i].shader);

		// Verifica o estado da compilação
		GLint compiled;
		glGetShaderiv(shaders[i].shader, GL_COMPILE_STATUS, &compiled);
		// Em caso de erro na compilação
		if (!compiled) {
#ifdef _DEBUG
			GLsizei len;
			glGetShaderiv(shaders[i].shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shaders[i].shader, len, &len, log);
			std::cerr << "Shader compilation failed: " << log << std::endl;
			delete[] log;
#endif /* DEBUG */

			DestroyShaders(shaders);

			return 0;
		}

		// Anexa o shader ao programa
		glAttachShader(program, shaders[i].shader);
	}

	// Linka o programa
	glLinkProgram(program);

	// Verifica o estado do processo de linkagem
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	// Em caso de erro na linkagem
	if (!linked) {
#ifdef _DEBUG
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		std::cerr << "Shader linking failed: " << log << std::endl;
		delete[] log;
#endif /* DEBUG */

		DestroyShaders(shaders);

		return 0;
	}

	return program;
}

void Shader::DestroyShaders(ShaderInfo* shaders) {
	// Destrói os shaders que tinham criados
	for (int j = 0; shaders[j].type != GL_NONE; j++) {
		// Se tem um shader válido (i.e., != 0)
		if (shaders[j].shader != 0)
			glDeleteShader(shaders[j].shader);
		shaders[j].shader = 0;
	}
}