#include "model.h"
#include "texture.h"

void Model::Delete() const {
    vertex_buffer_.Delete();
    uv_buffer_.Delete();
	normal_buffer_.Delete();
    texture_.Delete();
    vao_.Delete();
}

void Model::Render(vec3 position, vec3 orientation) {

    world_.SetPosition(position);
    world_.SetRotation(orientation.x, orientation.y, orientation.z);

    shader_.SetUniformMatrix4fv("Projection", camera_.GetProjectionMatrix());
    shader_.SetUniformMatrix4fv("View", camera_.GetViewMatrix());
    shader_.SetUniformMatrix4fv("Model", world_.GetMatrix());

    GLuint programa = shader_.GetProgram();

    vao_.Bind();
    shader_.Bind();
    texture_.Bind();

    mat3 NormalMatrix = inverseTranspose(mat3(camera_.GetViewMatrix() * world_.GetMatrix()));

    shader_.SetUniformMatrix3fv("NormalMatrix", NormalMatrix);

    // Fonte de luz ambiente global
    shader_.SetUniform3fv("ambientLight.ambient", vec3(0.1f));
    glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "ambientLight.ambient"), 1, value_ptr(vec3(0.1, 0.1, 0.1)));

    // Fonte de luz direcional
    shader_.SetUniform3fv("directionalLight.direction",vec3(1.0, 0.0, 0.0));
    shader_.SetUniform3fv("directionalLight.ambient", vec3(0.2));
    shader_.SetUniform3fv("directionalLight.diffuse", vec3(1.0));
    shader_.SetUniform3fv("directionalLight.specular", vec3(1.0));

    // Fonte de luz pontual #1
    shader_.SetUniform3fv("pointLight[0].position", vec3(0.0, 0.0, 5.0));
    shader_.SetUniform3fv("pointLight[0].ambient", vec3(0.1));
    shader_.SetUniform3fv("pointLight[0].diffuse", vec3(1.0));
    shader_.SetUniform3fv("pointLight[0].specular", vec3(1.0));
    shader_.SetUniform1f("pointLight[0].constant", 1.0f);
    shader_.SetUniform1f("pointLight[0].linear", 0.06f);
    shader_.SetUniform1f("pointLight[0].quadratic", 0.02f);

    // Fonte de luz pontual #2
    shader_.SetUniform3fv("pointLight[1].position", vec3(-2.0, 2.0, 5.0));
    shader_.SetUniform3fv("pointLight[1].ambient", vec3(0.1));
    shader_.SetUniform3fv("pointLight[1].diffuse", vec3(1.0));
    shader_.SetUniform3fv("pointLight[1].specular", vec3(1.0));
    shader_.SetUniform1f("pointLight[1].constant", 1.0f);
    shader_.SetUniform1f("pointLight[1].linear", 0.06f);
    shader_.SetUniform1f("pointLight[1].quadratic", 0.02f);

    SetMaterialUniforms();

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices_.size()));
}

void Model::SetMaterialUniforms() {

    shader_.SetUniform3fv("material.emissive", vec3(0.0));
    shader_.SetUniform3fv("material.ambient", material_.ambient);
    //shader_.SetUniform3fv("material.diffuse", material_.diffuse);
    shader_.SetUniform3fv("material.specular", material_.specular);
    shader_.SetUniform1f("material.shininess", material_.shininess);
}

void Model::Install() {

    vao_.Create();

    vertex_buffer_.Create(vertices_.data(), vertices_.size() * sizeof(vec3));
    uv_buffer_.Create(uvs_.data(), uvs_.size() * sizeof(vec2));
    normal_buffer_.Create(normals_.data(), normals_.size() * sizeof(vec3));

    AttribPointer();
}

// Not the most abstract implementation ever but I'm lazy
void Model::AttribPointer() const {

	// I'm just assuming the layout for each buffer

	vertex_buffer_.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(0);

    uv_buffer_.Bind();
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray(1);

    normal_buffer_.Bind();
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray(2);
}

void Model::Load(const std::string path) {

    FILE* file;

    if (fopen_s(&file, path.c_str(), "r")) {
        std::cerr << "Failed to open obj file: " << path << std::endl;
        return;
    }

    std::vector<vec3> tmp_vertexes;
    std::vector<vec2> tmp_uvs;
    std::vector<vec3> tmp_normals;

    // All vector will be read to this vec3 and uints
    vec3 vec = vec3(0.0f);
    unsigned int vertexIndex[3]{}, uvIndex[3]{}, normalIndex[3]{};

    constexpr int buffer_size = 128;
    char buffer[buffer_size]{};

    // Used fscanf_s instead of ifstream for twice the performance
    while (fscanf_s(file, "%s", buffer, buffer_size) != EOF) {

        if (!strcmp(buffer, "v")) {
            fscanf_s(file, "%f %f %f\n", &vec.x, &vec.y, &vec.z);
            tmp_vertexes.push_back(vec);
        }
        else if (!strcmp(buffer, "vt")) {
            fscanf_s(file, "%f %f\n", &vec.x, &vec.y);
            tmp_uvs.push_back(vec);
        }
        else if (!strcmp(buffer, "vn")) {
            fscanf_s(file, "%f %f %f\n", &vec.x, &vec.y, &vec.z);
            tmp_normals.push_back(vec);
        }
        else if (!strcmp(buffer, "f")) {
            fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

            for (int i = 0; i < 3; ++i) {
                vertices_.push_back(tmp_vertexes.at(vertexIndex[i] - 1));
                uvs_.push_back(tmp_uvs.at(uvIndex[i] - 1));
                normals_.push_back(tmp_normals.at(normalIndex[i] - 1));
            }
        }
        else if (!strcmp(buffer, "mtllib")) {
            // Get current .obj file directory
            std::string dir = path.substr(0, path.find_last_of('\\'));

            char mtlFile[128]{};
            fscanf_s(file, "%s\n", mtlFile, 128);
            LoadMaterial(dir + "/" + mtlFile);
        }
    }

    fclose(file);
}

void Model::LoadMaterial(const std::string path) {

    FILE* file;

    if (fopen_s(&file, path.c_str(), "r")) {
        std::cerr << "Failed to open obj file: " << path << std::endl;
        return;
    }

    constexpr int buffer_size = 128;
    char buffer[buffer_size]{};

    while (fscanf_s(file, "%s", buffer, buffer_size) != EOF) {

        if (!strcmp(buffer, "Ka")) {
            fscanf_s(file, "%f %f %f", &material_.ambient.r, &material_.ambient.g, &material_.ambient.b);
        }
        else if (!strcmp(buffer, "Kd")) {
            fscanf_s(file, "%f %f %f", &material_.diffuse.r, &material_.diffuse.g, &material_.diffuse.b);
        }
        else if (!strcmp(buffer, "Ks")) {
            fscanf_s(file, "%f %f %f", &material_.specular.r, &material_.specular.g, &material_.specular.b);
        }
        else if (!strcmp(buffer, "Ns")) {
            fscanf_s(file, "%f", &material_.shininess);
        }
        else if (!strcmp(buffer, "map_Kd")) {
            char texture_file[128]{};
            fscanf_s(file, "%s\n", texture_file, 128);
            std::string texture_path = path.substr(0, path.find_last_of('/')) + "/" + texture_file;

            texture_.Create();
            texture_.Load(texture_path);
        }
    }

    fclose(file);
}
