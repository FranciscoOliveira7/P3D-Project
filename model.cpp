#include "model.h"
#include "texture.h"

namespace objr {

    void Model::Delete() const {
        vertex_buffer_.Delete();
        uv_buffer_.Delete();
        normal_buffer_.Delete();
        texture_.Delete();
        vao_.Delete();
    }

    void Model::Render(vec3 position, vec3 orientation) {

        transform_.SetPosition(position);
        transform_.SetRotation(orientation);

        shader_.SetUniformMatrix4fv("Projection", camera_->GetProjectionMatrix());
        shader_.SetUniformMatrix4fv("View", camera_->GetViewMatrix());
        shader_.SetUniformMatrix4fv("Model", transform_.GetMatrix());

        vao_.Bind();
        shader_.Bind();
        texture_.Bind();

        SetUniforms();

        glDrawArrays(GL_TRIANGLES, 0, vertices_.size());
    }

    void Model::SetUniforms() {

        shader_.SetUniformMatrix3fv("NormalMatrix", inverseTranspose(mat3(camera_->GetViewMatrix() * transform_.GetMatrix())));

        shader_.SetUniform3fv("material.emissive", vec3(0.0));
        shader_.SetUniform3fv("material.ambient", material_.ambient);
        shader_.SetUniform3fv("material.specular", material_.specular);
        shader_.SetUniform1f("material.shininess", material_.shininess);
    }

    void Model::Install() {

        vao_.Create();

        vertex_buffer_.Create(vertices_.data(), vertices_.size() * sizeof(vec3));
        uv_buffer_.Create(uvs_.data(), uvs_.size() * sizeof(vec2));
        normal_buffer_.Create(normals_.data(), normals_.size() * sizeof(vec3));

        vao_.AddBuffer(vertex_buffer_, 3, 0);
        vao_.AddBuffer(uv_buffer_, 2, 1);
        vao_.AddBuffer(normal_buffer_, 3, 2);
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
}