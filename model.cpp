#include "model.h"
#include "table.h"
#include "texture.h"

void Model::Delete() const {
	vertex_buffer_.Delete();
	color_buffer_.Delete();
	normal_buffer_.Delete();
	index_buffer_.Delete();
    texture_.Delete();
}

void Model::Render(vec3 position, vec3 orientation)
{
    world_.SetPosition(position);
    world_.SetRotation(orientation.x, orientation.y, orientation.z);

    mat4 mvp = camera_.GetProjectionMatrix() * camera_.GetViewMatrix() * world_.GetMatrix();

    shader_.SetUniformMatrix4fv("MVP", mvp);

    vao_.Bind();
    shader_.Bind();

    if (index_buffer_.Count() > 0) {
        glDrawElements(GL_TRIANGLES, index_buffer_.Count(), GL_UNSIGNED_INT, (void*) 0);
    }
    else {
        texture_.Bind();
        //glUniform1i(3, texture_.GetId());
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices_.size()));
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
        vertex_buffer_.Create(vertices_.data(), vertices_.size() * sizeof(vec3));
        uv_buffer_.Create(uvs_.data(), uvs_.size() * sizeof(vec2));
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
    }
    else {
        uv_buffer_.Bind();
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glEnableVertexAttribArray(2);
    }
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

    // Used fscanf_s instead of ifstream for double the performance
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
            // Uncomment for debug
            //if (results != 9) {
            //    std::cerr << "Failed to read face information from file: " << path << std::endl;
            //    return;
            //}

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
