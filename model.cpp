#include "model.h"
#include "texture.h"

namespace objr {

    // Apaga os recursos associados ao modelo
    void Model::Delete() const {
        vertex_buffer_.Delete();
        uv_buffer_.Delete();
        normal_buffer_.Delete();
        texture_.Delete();
        vao_.Delete();
    }

    // Renderiza o modelo na posição e orientação especificadas
    void Model::Render(vec3 position, vec3 orientation) {
        // Vincula o VAO, shader e textura
        vao_.Bind();
        shader_.Bind();
        texture_.Bind();

        // Configura a transformação do modelo
        transform_.SetPosition(position);
        transform_.SetRotation(orientation);

        // Define os uniformes necessários para o shader
        SetUniform();

        // Desenha os vértices do modelo
        glDrawArrays(GL_TRIANGLES, 0, vertices_.size());
    }

    // Define os uniformes do shader
    void Model::SetUniform() {
        // Define as matrizes de projeção e visualização (MVP)
        shader_.SetUniformMatrix4fv("Projection", camera_->GetProjectionMatrix());
        shader_.SetUniformMatrix4fv("View", camera_->GetViewMatrix());

        mat4 model_view = camera_->GetViewMatrix() * transform_.GetMatrix();
        shader_.SetUniformMatrix4fv("ModelView", model_view);

        // Define a matriz normal para calcular a iluminação Phong
        shader_.SetUniformMatrix3fv("NormalMatrix", inverseTranspose(mat3(model_view)));

        // Define os uniformes dos materiais
        shader_.SetUniform3fv("material.emissive", vec3(0.0));
        shader_.SetUniform3fv("material.ambient", material_.ambient);
        shader_.SetUniform3fv("material.specular", material_.specular);
        shader_.SetUniform1f("material.shininess", material_.shininess);
    }

    // Instala o modelo criando e configurando buffers
    void Model::Install() {
        // Cria o VAO
        vao_.Create();

        // Cria os buffers de vértices, UVs e normais
        vertex_buffer_.Create(vertices_.data(), vertices_.size() * sizeof(vec3));
        uv_buffer_.Create(uvs_.data(), uvs_.size() * sizeof(vec2));
        normal_buffer_.Create(normals_.data(), normals_.size() * sizeof(vec3));

        // Configura os atributos do VAO
        vao_.AddBuffer(vertex_buffer_, 3, 0);
        vao_.AddBuffer(uv_buffer_, 2, 1);
        vao_.AddBuffer(normal_buffer_, 3, 2);
    }

    // Carrega um modelo a partir de um arquivo
    void Model::Load(const std::string path) {
        FILE* file;

        // Abre o arquivo .obj
        if (fopen_s(&file, path.c_str(), "r")) {
            std::cerr << "Failed to open obj file: " << path << std::endl;
            return;
        }

        std::vector<vec3> tmp_vertexes;
        std::vector<vec2> tmp_uvs;
        std::vector<vec3> tmp_normals;

        vec3 vec = vec3(0.0f);
        unsigned int vertexIndex[3]{}, uvIndex[3]{}, normalIndex[3]{};

        constexpr int buffer_size = 128;
        char buffer[buffer_size]{};

        // Lê os dados do arquivo .obj
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
                fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

                for (int i = 0; i < 3; ++i) {
                    vertices_.push_back(tmp_vertexes.at(vertexIndex[i] - 1));
                    uvs_.push_back(tmp_uvs.at(uvIndex[i] - 1));
                    normals_.push_back(tmp_normals.at(normalIndex[i] - 1));
                }
            }
            else if (!strcmp(buffer, "mtllib")) {
                // Obtém o diretório atual do arquivo .obj
                std::string dir = path.substr(0, path.find_last_of('\\'));

                char mtlFile[128]{};
                fscanf_s(file, "%s\n", mtlFile, 128);
                LoadMaterial(dir + "/" + mtlFile);
            }
        }

        fclose(file);
    }

    // Carrega materiais a partir de um arquivo
    void Model::LoadMaterial(const std::string path) {
        FILE* file;

        // Abre o arquivo de material
        if (fopen_s(&file, path.c_str(), "r")) {
            std::cerr << "Failed to open obj file: " << path << std::endl;
            return;
        }

        constexpr int buffer_size = 128;
        char buffer[buffer_size]{};

        // Lê os dados do arquivo de material
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
