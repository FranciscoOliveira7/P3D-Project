#include "model.h"
#include "table.h"

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
        glDrawArrays(GL_TRIANGLES, 0, vertexes.size());
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

    std::vector<vec3> tmp_vertexes;
    std::vector<vec2> tmp_uvs;
    std::vector<vec3> tmp_normals;

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
            //loadMTL(dir + "/" + mtlFile);
        }
    }

    file.close();
}
