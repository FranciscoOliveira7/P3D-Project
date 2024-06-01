#pragma region includes

// Libraries

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL\glew.h>

#include <GLFW\glfw3.h>

// Others

#include "shader.h"
#include "model.h"
#include "lights/point_light.h"
#include "lights/directional_light.h"
#include "lights/ambient_light.h"
#include "lights/spot_light.h"
#include "physics/physic_object.h"
#include "camera.h"

#pragma endregion

using namespace objr;

#define WIDTH 640
#define HEIGHT 480

void print_error(int error, const char* description);
void init(std::vector<Model>& models);
void draw(std::vector<Model>& models);
void set_ball_pos();
void resize(int height, int width);
float lerp(float min, float max, float t);

std::vector<PhysicsObject> balls;

double deltaTime = 0.0f;
double oldTime = 0.0f;

// Animação do taco
float taco_position = 0.0f;

bool animation = false;
float elapsed_time = 0.0f;

typedef struct KeyFrame {
    float start, end;
    float duration;

    KeyFrame(float s, float e, float d) : start{ s }, end{ e }, duration{ d } {}
} KeyFrame;

// Animação do taco
std::vector<KeyFrame> taco_animation = {
    KeyFrame(0.0f, -8.0f, 1500.0f),
    KeyFrame(-8.0f, 0.0f, 1000.0f),
    KeyFrame(0.0f, -15.0f, 500.0f),
    KeyFrame(-15.0f, 2.0f, 500.0f),
};

int current_keyframe = 0;

// Lights Sources
AmbientLight ambient_light;
PointLight point_light;
DirectionalLight directional_light;
SpotLight spot_light;

Camera camera((float)WIDTH / (float)HEIGHT);

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
        camera_pos -= static_cast<float>(deltaY) / HEIGHT * 10;
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

// Lights toggle

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_1: ambient_light.Toggle(); break;
            case GLFW_KEY_2: directional_light.Toggle(); break;
            case GLFW_KEY_3: point_light.Toggle(); break;
            case GLFW_KEY_4: spot_light.Toggle(); break;
            case GLFW_KEY_W: balls[0].AddVelocity(vec3(0.0f, 0.0f, -0.01f)); break;
            case GLFW_KEY_A: balls[0].AddVelocity(vec3(-0.01f, 0.0f, 0.0f)); break;
            case GLFW_KEY_S: balls[0].AddVelocity(vec3(0.0f, 0.0f, 0.01f)); break;
            case GLFW_KEY_D: balls[0].AddVelocity(vec3(0.01f, 0.0f, 0.0f)); break;
            case GLFW_KEY_SPACE:
                animation = true;
                break;
            case GLFW_KEY_R:
                for (int i = 0; i < balls.size(); i++) {
                    balls[i].Stop(); balls[i].ResetPosition();
                }
                break;
            default: break;
        }
    }
}

void window_size_callback(GLFWwindow* window, int width, int height) { resize(height, width); }

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
     //glfwSwapInterval(0);

    // Inicia o gestor de extensões GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    std::vector<Model> models;

    // Table
    Model goofy_table;
    models.push_back(goofy_table);

    Model goofy_taco;
    models.push_back(goofy_taco);

    // Balls
    for (int i = 0; i < 16; i++) {
        Model ball;
        models.push_back(ball);
    }

    init(models);

    //TODO Input Manager (or maybe not, I'll probably just leave it like this)
    glfwSetScrollCallback(window, scrollCallBack);
    glfwSetCursorPosCallback(window, cursorCallBack);
    glfwSetMouseButtonCallback(window, mouseCallBack);
    glfwSetKeyCallback(window, keyCallBack);
    glfwSetWindowSizeCallback(window, window_size_callback);

    while (!glfwWindowShouldClose(window)) {
        // Delta time para que as físicas não sejam fps based
        deltaTime = clock() - oldTime;
        double fps = (1 / deltaTime) * 1000;
        oldTime = clock();

        // Taco animation
        if (animation) {
            elapsed_time += deltaTime;
            if (current_keyframe == taco_animation.size()) {
                animation = false;
                current_keyframe = 0;
                float nigga = ((rand() % 4) - 2) / 100.0f;
                balls[0].SetVelocity(vec3(0.07f, 0.0f, nigga));
            }
            else {
                if (elapsed_time > taco_animation[current_keyframe].duration) {
                    current_keyframe++;
                    elapsed_time = 0.0f;
                }
                taco_position = lerp(taco_animation[current_keyframe].start, taco_animation[current_keyframe].end, elapsed_time / taco_animation[current_keyframe].duration);
            }
        }

        // Calulate balls physics
        for (int i = 0; i < balls.size(); i++) {
            balls[i].Update(balls, static_cast<float>(deltaTime));
            models[i + 2].SetSpin(vec3(balls[i].GetRotation().x, 0.0f, balls[i].GetRotation().y));
        }

        draw(models);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Interpolação quadrática para a animação do taco (https://www.youtube.com/watch?v=6vHHlLcUPCM)
float lerp(float min, float max, float t) {

    return (max - min) * t * t + min;
}

void resize(int height, int width) {
    glViewport(0, 0, GLsizei(width), GLsizei(height));
    camera.SetRatio((float)width / (float)height);
}

void init(std::vector<Model>& models) {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // Por defeito está desativado
    glCullFace(GL_BACK); // GL_FRONT, [GL_BACK], GL_FRONT_AND_BACK
    glClearColor(0.2f, 0.2f, 0.25f, 1.0f);

    // Shaders type and locations
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER,   "shaders/phong.vert" },
        { GL_FRAGMENT_SHADER, "shaders/phong.frag" },
        { GL_NONE, NULL }
    };

    Shader shader;
    shader.Create(shaders);

    // Fonte de luz ambiente global
    ambient_light.SetShader(shader);
    ambient_light.SetAmbient(vec3(0.8f, 0.8f, 0.8f));
    ambient_light.Update();

    // Fonte de luz direcional
    directional_light.SetShader(shader);
    directional_light.Update();

    // Fonte de luz pontual
    point_light.SetShader(shader);
    point_light.Update();

    // Fonte de luz cónica
    spot_light.SetShader(shader);
    spot_light.Update();

    // Load Table
    models[0].SetShader(shader);
    models[0].Load("Models\\Table.obj");
    models[0].Install();
    models[0].SetScale(2.2f);
    models[0].SetCamera(&camera);

    // Load Taco
    models[1].SetShader(shader);
    models[1].Load("Models\\taco.obj");
    models[1].Install();
    models[1].SetScale(0.5f);
    models[1].SetSpin(vec3(0.0f, radians(-90.0f), 0.0f));
    models[1].SetCamera(&camera);

    // Load Balls
    for (int i = 2; i < models.size(); i++) {
        models[i].Load("Models\\Ball" + std::to_string(i - 2) + ".obj");
        models[i].Install();
        models[i].SetShader(shader);
        models[i].SetScale(0.6f);
        models[i].SetCamera(&camera);
    }

    // White ball
    PhysicsObject white_ball(vec3(-13.0f, -6.5f, 0));
    balls.push_back(white_ball);

    set_ball_pos();
}

void draw(std::vector<Model>& models) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update Camera
    camera.SetPosition(0.0f, 1.0f, camera_pos);
    camera.SetFov(zoom);

    // Draw each object
    for (int i = 0; i < models.size(); i++) {
        // Table
        if (i == 0) models[i].Render(vec3(0.0f, -2.0f, 0), vec3(0.0f, rotation, 0.0f));
        // Taco
        else if (i == 1) models[i].Render(vec3(-28.0f + taco_position, -10.0f, 0), vec3(0.0f, rotation, -0.1f));
        // Balls
        else models[i].Render(balls[i - 2].GetPosition(), vec3(0.0f, rotation, 0.0f));
    }
}

void set_ball_pos() {
    // Posição das bola, calculado pelo zés e o gaio
    for (int i = 1; i < 6; i++) {
        for (int j = 0; j < i; j++) {
            vec3 position = vec3(4.0f + i * 1.75f /*sin(60)*/, -6.5f /*table pos*/, (i - 1.0f) - j * 2.0f);

            balls.push_back(PhysicsObject(position));
            //if (balls.size() == 2) return;
        }
    }
    
    vec3 aux = balls[5].GetPosition();
    balls[5].SetPosition(balls[8].GetPosition());
    balls[8].SetPosition(aux);
}

void print_error(int error, const char* description) {
    std::cout << description << std::endl;
}