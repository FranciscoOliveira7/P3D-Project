#include "renderer.h"
#include "table.h"

void Renderer::Render(vec3 position, vec3 orientation)
{
    WorldTrans world;
    world.SetPosition(position);
    world.SetRotation(orientation.x, orientation.y, orientation.z);

    mat4 mvp = projection * camera_.GetViewMatrix() * world.GetMatrix();

    shader_->SetUniformMatrix4fv("MVP", mvp);

    model_->vao_.Bind();
    std::cout << model_->vao_.GetId() << std::endl;

    glDrawElements(GL_TRIANGLES, model_->index_buffer_->Count(), GL_UNSIGNED_INT, (void*) 0);
}

void Renderer::Install(bool test) {

    GLint vaoid;

    model_->vao_.Bind();
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoid);

    glBindVertexArray(1);
    std::cout << model_->vao_.GetId() << std::endl;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoid);

    if (!test) {
        model_->vertex_buffer_ = new VertexBuffer(vertices, sizeof(vertices));
        model_->color_buffer_ = new VertexBuffer(cores, sizeof(cores));
        model_->index_buffer_ = new IndexBuffer(indices, sizeof(indices) / sizeof(GLuint));
    }
    else {
        model_->vertex_buffer_ = new VertexBuffer(vertexes.data(), vertexes.size() * sizeof(vec3));
        model_->color_buffer_ = new VertexBuffer(colors.data(), colors.size() * sizeof(vec3));
        model_->index_buffer_ = new IndexBuffer(vertexIndices.data(), vertexIndices.size());
    }

    model_->AttribPointer();

    glBindVertexArray(0);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoid);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //glUseProgram(0);
    //glBindTexture(GL_TEXTURE_2D, 0);

    //model_->vao_.Unbind();
}

void Renderer::Load(const std::string &obj_model_filepath) {

    std::ifstream file(obj_model_filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << obj_model_filepath << std::endl;
        return;
    }

    std::string dir = obj_model_filepath.substr(0, obj_model_filepath.find_last_of('/'));
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            vertexes.push_back(vertex);

            glm::vec3 color(1.0f, 1.0f, 1.0f);
            colors.push_back(color);
        }
        else if (prefix == "vt") {
            glm::vec2 uv;
            ss >> uv.x >> uv.y;
            uvs.push_back(uv);
        }
        else if (prefix == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }
        else if (prefix == "f") {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            char slash;
            for (int i = 0; i < 3; ++i) {
                ss >> vertexIndex[i] >> slash >> uvIndex[i] >> slash >> normalIndex[i];
                vertexIndices.push_back(vertexIndex[i] - 1);
                uvIndices.push_back(uvIndex[i] - 1);
                normalIndices.push_back(normalIndex[i] - 1);
            }
        }
        else if (prefix == "mtllib") {
            std::string mtlFile;
            ss >> mtlFile;
            //loadMTL(dir + "/" + mtlFile);
        }
    }

    //std::cout << vertexes.size() << std::endl;
    //std::cout << colors.size() << std::endl;
    //std::cout << uvs.size() << std::endl;
    //std::cout << normals.size() << std::endl;
    //std::cout << vertexIndices.size() << std::endl;

    file.close();
}

