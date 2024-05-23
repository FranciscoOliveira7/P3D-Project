#pragma region includes

// Libraries

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL\glew.h>

#include <gl\GL.h>

#include <GLFW\glfw3.h>

// Others

#include "shader.h"
#include "model.h"

#pragma endregion

#define WIDTH 640
#define HEIGHT 480

void print_error(int error, const char* description);
void init(std::vector<Model>& models);
void draw(std::vector<Model>& models);
void set_ball_pos();

std::vector<vec3> ball_positions;

float zoom = 45.0f;
float camera_pos = 15.0f;

// Table rotation behaviour

GLfloat rotation = 0.0f;
bool isPressing = false;

double prevXpos = 0.0;
double prevYpos = 0.0;
double xPos = 0.0;
double yPos = 0.0;

float mouse_sensitivity = 3.0f;

void cursorCallBack(GLFWwindow* window, double xpos, double ypos) {
    xPos = xpos;
    yPos = ypos;

    if (isPressing) {
        double deltaX = xpos - prevXpos;
        rotation += static_cast<float>(deltaX) / WIDTH * mouse_sensitivity;
        prevXpos = xpos;

        double deltaY = ypos - prevYpos;
        camera_pos += static_cast<float>(deltaY) / HEIGHT * 10;
        camera_pos = std::max<float>(0.5f, std::min<float>(camera_pos, 30.0f));
        prevYpos = ypos;
    }
}

void mouseCallBack(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            isPressing = true;
            prevXpos = xPos;
            prevYpos = yPos;
        }
        else if (action == GLFW_RELEASE) isPressing = false;
    }
}

// Camera zoom behaviour

void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset == 1) zoom -= fabs(zoom) * 0.1f;
    else if (yoffset == -1) zoom += fabs(zoom) * 0.1f;
    zoom = std::max<float>(10.0f, std::min<float>(zoom, 120.0f));
}

int main(void) {
    GLFWwindow* window;

    glfwSetErrorCallback(print_error);

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, "Bilhar", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Uncomment to disable v-sync
    // glfwSwapInterval(0);

    // Inicia o gestor de extensões GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    //TODO Input Manager
    glfwSetScrollCallback(window, scrollCallBack);
    glfwSetCursorPosCallback(window, cursorCallBack);
    glfwSetMouseButtonCallback(window, mouseCallBack);

    std::vector<Model> models;
    Model goofy_table;

    // Balls
    for (int i = 1; i < 16; i++) {
        Model ball;
        models.push_back(ball);
    }

    models.push_back(goofy_table);

    init(models);

    while (!glfwWindowShouldClose(window)) {

        draw(models);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void init(std::vector<Model>& models) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.25f, 1.0f);

    // Shaders type and locations
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER,   "shaders/colored.vert" },
        { GL_FRAGMENT_SHADER, "shaders/colored.frag" },
        { GL_NONE, NULL }
    };

    // Shaders type and locations
    ShaderInfo shaders_ball[] = {
        { GL_VERTEX_SHADER,   "shaders/textured.vert" },
        { GL_FRAGMENT_SHADER, "shaders/textured.frag" },
        { GL_NONE, NULL }
    };

    Shader shader;
    Shader shader_balls;

    shader.Create(shaders);
    shader_balls.Create(shaders_ball);

    models[0].BindShader(shader);
    models[0].Install(0);

    // Load models to renderer
    for (int i = 1; i < models.size(); i++) {
        models[i].Load("PoolBalls\\Ball" + std::to_string(i) + ".obj");
        models[i].Install(1);
        models[i].BindShader(shader_balls);
        models[i].SetScale(0.6f);
    }

    set_ball_pos();
}

void draw(std::vector<Model>& models) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw each object
    for (int i = 0; i < models.size(); i++) {
        models[i].SetCameraPosition(0.0f, 1.0f, camera_pos);
        models[i].SetCameraFov(zoom);
        if (i == 0) models[i].Render(glm::vec3(0.0f, -5.0f, 0), glm::vec3(0.0f, rotation, 0.0f));

        else {
            models[i].Render(ball_positions[i - 1], glm::vec3(0.0f, rotation, 0.0f));
        }
    }
}

void set_ball_pos() {
    int x = 2.0f;

    // Posição das bola, calculado pelo zés e o gaio
    for (int i = 1; i < 6; i++) {
        for (int j = 0; j < i; j++) {
            glm::vec3 position = vec3(x + i * 1.73f /*sin(60) * 2*/, -6.5f /*table pos*/, (i - 1) - j * 2);

            ball_positions.push_back(position);
        }
    }
}

void print_error(int error, const char* description) {
    std::cout << description << std::endl;
}