#include "model.h"
#include "table.h"

void Model::Delete()
{
	vertex_buffer_.Delete();
	color_buffer_.Delete();
	normal_buffer_.Delete();
	index_buffer_.Delete();
}

void Model::Install(bool test) {

    //GLint vaoid;

    //model_.vao_.Bind();
    //glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoid);

    //glBindVertexArray(1);
    //std::cout << model_.vao_.GetId() << std::endl;
    //glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoid);

    vao_.Create();

    if (!test) {
        vertex_buffer_.Create(vertices, sizeof(vertices));
        color_buffer_.Create(cores, sizeof(cores));
        index_buffer_.Create(indices, sizeof(indices) / sizeof(GLuint));
    }
    else {
        vertex_buffer_.Create(vertexes.data(), vertexes.size() * sizeof(vec3));
        color_buffer_.Create(colors.data(), colors.size() * sizeof(vec3));
        index_buffer_.Create(vertexIndices.data(), static_cast<unsigned int>(vertexIndices.size()));
    }

    AttribPointer();

    //glBindVertexArray(0);
    //glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoid);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //glUseProgram(0);
    //glBindTexture(GL_TEXTURE_2D, 0);

    //model_.vao_.Unbind();
}

void Model::Render(vec3 position, vec3 orientation)
{
    WorldTrans world;
    world.SetPosition(position);
    world.SetRotation(orientation.x, orientation.y, orientation.z);

    mat4 mvp = projection * camera_.GetViewMatrix() * world.GetMatrix();

    shader_->SetUniformMatrix4fv("MVP", mvp);

    vao_.Bind();

    glDrawElements(GL_TRIANGLES, index_buffer_.Count(), GL_UNSIGNED_INT, (void*) 0);
}

// Not the most abstract implementation ever but I'm too lazy
void Model::AttribPointer() const {

	// I'm just assuming the layout for each buffer

	vertex_buffer_.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(0);

	color_buffer_.Bind();
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(1);
}

void Model::Load(const std::string& obj_model_filepath) {

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
