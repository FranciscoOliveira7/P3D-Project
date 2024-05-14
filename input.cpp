#include "input.h"

Input::Input()
{
}

Input::~Input()
{
}


//void Input::CursorCallBack(GLFWwindow* window, double xpos, double ypos) {
//    xPos = xpos;
//    if (isPressing) {
//        double deltaX = xpos - prevXpos;
//        rotation += static_cast<float>(deltaX) / WIDTH * mouse_sensitivity;
//        prevXpos = xpos;
//    }
//}
//
//void Input::MouseCallBack(GLFWwindow* window, int button, int action, int mods) {
//    if (button == GLFW_MOUSE_BUTTON_LEFT) {
//        if (action == GLFW_PRESS) {
//            isPressing = true;
//            prevXpos = xPos;
//        }
//        else if (action == GLFW_RELEASE) isPressing = false;
//    }
//}

//void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);