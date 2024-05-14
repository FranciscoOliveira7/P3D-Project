#include "camera.h"

Camera::Camera()
{
    eye_ = vec3(0.0f, 0.0f, 10.0f);
    center_ = vec3(0.0f, 0.0f, -1.0f);
    up_ = vec3(0.0f, 1.0f, 0.0f);
}


void Camera::SetPosition(float x, float y, float z)
{
    eye_.x = x;
    eye_.y = y;
    eye_.z = z;
}


mat4 Camera::GetViewMatrix() {
    mat4 ViewTransformation;
    ViewTransformation = lookAt(eye_, center_, up_);

    return ViewTransformation;
}

void Camera::OnKeyboard(unsigned char Key)
{
    //switch (Key) {

    //case GLUT_KEY_UP:
    //    m_pos += (m_target * m_speed);
    //    break;

    //case GLUT_KEY_DOWN:
    //    m_pos -= (m_target * m_speed);
    //    break;

    //case GLUT_KEY_LEFT:
    //{
    //    Vector3f Left = m_target.Cross(m_up);
    //    Left.Normalize();
    //    Left *= m_speed;
    //    m_pos += Left;
    //}
    //break;

    //case GLUT_KEY_RIGHT:
    //{
    //    Vector3f Right = m_up.Cross(m_target);
    //    Right.Normalize();
    //    Right *= m_speed;
    //    m_pos += Right;
    //}
    //break;

    //case GLUT_KEY_PAGE_UP:
    //    m_pos.y += m_speed;
    //    break;

    //case GLUT_KEY_PAGE_DOWN:
    //    m_pos.y -= m_speed;
    //    break;

    //case '+':
    //    m_speed += 0.1f;
    //    printf("Speed changed to %f\n", m_speed);
    //    break;

    //case '-':
    //    m_speed -= 0.1f;
    //    if (m_speed < 0.1f) {
    //        m_speed = 0.1f;
    //    }
    //    printf("Speed changed to %f\n", m_speed);
    //    break;
    //}
}