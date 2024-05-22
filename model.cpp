#include "model.h"
#include "table.h"

#define STB_IMAGE_IMPLEMENTATION

void Model::Delete()
{
	vertex_buffer_.Delete();
	color_buffer_.Delete();
	normal_buffer_.Delete();
	index_buffer_.Delete();
}

void Model::Render(vec3 position, vec3 orientation)
{
    world_.SetPosition(position);
    world_.SetRotation(orientation.x, orientation.y, orientation.z);

    mat4 mvp = projection * camera_.GetViewMatrix() * world_.GetMatrix();

    shader_->SetUniformMatrix4fv("MVP", mvp);

    vao_.Bind();

    if (index_buffer_.Count() > 0) {
        glDrawElements(GL_TRIANGLES, index_buffer_.Count(), GL_UNSIGNED_INT, (void*)0);
    }
    else {
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexes.size()));
    }
}

void Model::Install(bool test) {

    vao_.Create();

    if (!test) {
        vertex_buffer_.Create(vertices, sizeof(vertices));
        color_buffer_.Create(cores, sizeof(cores));
        index_buffer_.Create(indices, sizeof(indices) / sizeof(GLuint));
    }
    else {
        vertex_buffer_.Create(vertexes.data(), vertexes.size() * sizeof(vec3));
        color_buffer_.Create(colors.data(), colors.size() * sizeof(vec3));
    }

    AttribPointer();
}

// Not the most abstract implementation ever but I'm lazy
void Model::AttribPointer() const {

	// I'm just assuming the layout for each buffer

	vertex_buffer_.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(0);

    color_buffer_.Bind();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
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

    std::string dir = path.substr(0, path.find_last_of('/'));
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
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            char slash;
            for (int i = 0; i < 3; ++i) {
                ss >> vertexIndex[i] >> slash >> uvIndex[i] >> slash >> normalIndex[i];

                // Criar um novo array com a ordem dos indices
                colors.push_back(color);
                vertexes.push_back(tmp_vertexes[vertexIndex[i] - 1]);
                uvs.push_back(tmp_uvs[vertexIndex[i] - 1]);
                normals.push_back(tmp_normals[vertexIndex[i] - 1]);
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
            ss >> material.name;
        }
        else if (prefix == "Ka") {
            ss >> material.ambient.r >> material.ambient.g >> material.ambient.b;
        }
        else if (prefix == "Kd") {
            ss >> material.diffuse.r >> material.diffuse.g >> material.diffuse.b;
        }
        else if (prefix == "Ks") {
            ss >> material.specular.r >> material.specular.g >> material.specular.b;
        }
        else if (prefix == "Ns") {
            ss >> material.shininess;
        }
        else if (prefix == "map_Kd") {
            std::string texture_file;
            ss >> texture_file;

            std::string texture_path = path.substr(0, path.find_last_of('/')) + "/" + texture_file;
            int width, height, channels;

            unsigned char* imageData = stbi_load(texture_path.c_str(), &width, &height, &channels, 0);

            if (!imageData) {
                std::cerr << "Failed to load texture: " << texture_path << " - " << stbi_failure_reason() << std::endl;
                continue;
            }
            if (imageData) {
                glGenTextures(1, &material.diffuseTexture);
                glBindTexture(GL_TEXTURE_2D, material.diffuseTexture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imageData);

                // Set texture parameters here
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                std::cout << "Loaded texture: " << texture_path << " with ID: " << material.diffuseTexture << std::endl;
                stbi_image_free(imageData);
            }
            else {
                std::cerr << "Failed to load texture: " << texture_path << std::endl;
            }
        }
    }

    file.close();
}
