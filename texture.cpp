#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace objr {

    void Texture::Load(const std::string& path) const {

        int width, height, channels;

        // Configura a biblioteca stb_image para inverter a imagem verticalmente durante o carregamento
        stbi_set_flip_vertically_on_load(true);
        unsigned char* imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);

        // Verifica se a imagem foi carregada corretamente
        if (!imageData) {
            std::cerr << "Falha ao carregar a textura: " << path << " - " << stbi_failure_reason() << std::endl;
            return;
        }

        // Carrega a imagem na textura OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imageData);

        // Define os parâmetros da textura
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // Define o modo de repetição para a coordenada S
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // Define o modo de repetição para a coordenada T
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Define o filtro de minificação
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Define o filtro de magnificação

        // Gera os mipmaps para a textura
        glGenerateMipmap(GL_TEXTURE_2D);

#ifdef _DEBUG
        // Se estiver em modo de depuração, imprime uma mensagem indicando que a textura foi carregada com sucesso
        std::cout << "Textura carregada: " << path << " com ID: " << id_ << std::endl;
        stbi_image_free(imageData); // Libera a memória da imagem carregada
#endif /* DEBUG */
}