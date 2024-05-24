#include "model.h"
#include "table.h"
#include "texture.h"

void Model::Delete() {
	vertex_buffer_.Delete();
	color_buffer_.Delete();
	normal_buffer_.Delete();
	index_buffer_.Delete();
}

void Model::Render(vec3 position, vec3 orientation) {

    transform_.SetPosition(position);
    transform_.SetRotation(orientation.x, orientation.y, orientation.z);

    mat4 mvp = camera_.GetProjectionMatrix() * camera_.GetViewMatrix() * transform_.GetMatrix();

    shader_.SetUniformMatrix4fv("MVP", mvp);

    vao_.Bind();
    shader_.Bind();

    mat4 NormalMatrix;
    NormalMatrix = inverseTranspose(mat3(transform_.GetMatrix()));

    if (index_buffer_.Count() > 0) {
        shader_.SetUniformMatrix4fv("View", camera_.GetViewMatrix());
        shader_.SetUniformMatrix4fv("ModelView", camera_.GetViewMatrix() * transform_.GetMatrix());
        shader_.SetUniformMatrix4fv("NormalMatrix", NormalMatrix);
        shader_.SetUniformMaterial("material", material_);
        shader_.SetUniform3fv("asdas", vec3(0.0f));
        glDrawElements(GL_TRIANGLES, index_buffer_.Count(), GL_UNSIGNED_INT, (void*) 0);
    }
    else {
        texture_.Bind();
        //glUniform1i(3, texture_.GetId());
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexes.size()));
    }
}

void Model::Install(bool test) {

    vao_.Create();

    if (!test) {
        vertex_buffer_.Create(vertices, sizeof(vertices));
        color_buffer_.Create(cores, sizeof(cores));
        normal_buffer_.Create(normais, sizeof(normais));
        index_buffer_.Create(indices, sizeof(indices) / sizeof(GLuint));
    }
    else {
        vertex_buffer_.Create(vertexes.data(), vertexes.size() * sizeof(vec3));
        uv_buffer_.Create(uvs.data(), uvs.size() * sizeof(vec2));
        //normal_buffer_.Create(normals.data(), normals.size() * sizeof(vec3));
    }

    AttribPointer();
}

// Not the most abstract implementation ever but I'm lazy
void Model::AttribPointer() const {

	// I'm just assuming the layout for each buffer

	vertex_buffer_.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(0);

    if (index_buffer_.Count() > 0) {
        color_buffer_.Bind();
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glEnableVertexAttribArray(1);

        normal_buffer_.Bind();
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glEnableVertexAttribArray(3);
    }
    else {
        uv_buffer_.Bind();
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glEnableVertexAttribArray(2);
    }
}

void Model::Load(const std::string& path) {

    std::vector<vec3> tmp_vertexes;
    std::vector<vec2> tmp_uvs;
    std::vector<vec3> tmp_normals;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open obj file: " << path << std::endl;
        return;
    }

    std::string dir = path.substr(0, path.find_last_of('\\'));
    std::string line;

    while (std::getline(file, line)) {

        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            tmp_vertexes.push_back(vertex);
        }
        else if (prefix == "vt") {
            glm::vec2 uv;
            ss >> uv.x >> uv.y;
            tmp_uvs.push_back(uv);
        }
        else if (prefix == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            tmp_normals.push_back(normal);
        }
        else if (prefix == "f") {
            vec3 color = vec3(1.0f, 1.0f, 1.0f);
            unsigned int vertexIndex, uvIndex, normalIndex;
            char slash;
            for (int i = 0; i < 3; ++i) {
                ss >> vertexIndex >> slash >> uvIndex >> slash >> normalIndex;

                // Criar um novo array com a ordem dos indices

                vertexes.push_back(tmp_vertexes.at(vertexIndex - 1));
                uvs.push_back(tmp_uvs.at(uvIndex - 1));
                normals.push_back(tmp_normals.at(normalIndex - 1));
            }
        }
        else if (prefix == "mtllib") {
            std::string mtlFile;
            ss >> mtlFile;
            LoadMaterial(dir + "/" + mtlFile);
        }
    }

    file.close();
}

void Model::LoadMaterial(const std::string& path) {

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open mtl file: " << path << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "newmtl") {
            ss >> material_.name;
        }
        else if (prefix == "Ka") {
            ss >> material_.ambient.r >> material_.ambient.g >> material_.ambient.b;
        }
        else if (prefix == "Kd") {
            ss >> material_.diffuse.r >> material_.diffuse.g >> material_.diffuse.b;
        }
        else if (prefix == "Ks") {
            ss >> material_.specular.r >> material_.specular.g >> material_.specular.b;
        }
        else if (prefix == "Ns") {
            ss >> material_.shininess;
        }
        else if (prefix == "map_Kd") {
            std::string texture_file;
            ss >> texture_file;

            std::string texture_path = path.substr(0, path.find_last_of('/')) + "/" + texture_file;

            texture_.Create();
            texture_.Load(texture_path);
        }
    }

    file.close();
}
