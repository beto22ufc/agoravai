#include "Camera.h"

Camera::Camera()
{
    //ctor
}

Camera::~Camera()
{
    //dtor
}

void Camera::initCamera(){
    eyex = 0.0f;
    eyey = 2.0f;
    eyez = 5.0f;
    centerx = 0;
    centery = 2;
    centerz = 0;
    div1 = pi / 180;
    div2 = 180 / pi;
    forwardSpeed = 0.3f;
    rotationSpeed = 0.25f;
    look();
}

void Camera::look(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, 0, 1, 0);
}

float Camera::anguloParaRadiano(double angulo) {
    return (float)angulo*div1;
}

float Camera::radianoParaAngulo(double radiano) {
    return (float)radiano * div2;
}

void Camera::mouseCentro() {
    SetCursorPos(12+512, 32+384);
}

void Camera::atualizaDirecaoVetor(){
    k = cos(anguloParaRadiano((double)yaw)); //eje z
    i = -sin(anguloParaRadiano((double)yaw)); // eje x
    j = sin(anguloParaRadiano((double)pitch)); // eje y

    centerz = eyez - (float)k; // calcula a donde esta mirando la camara
    centerx = eyex - (float)i;
    centery = eyey - (float)j;
}

void Camera::atualiza(int button) {

//    #pragma region Aim Camera

    POINT position;
    GetCursorPos(&position);
    int difX = 12 + 512 - position.x;
    int difY = 32 + 384 - position.y;

    if (position.y < 384)
    {
        pitch -= rotationSpeed * difY;
    }
    else
        if (position.y > 384)
        {
            pitch += rotationSpeed * (-difY);
        }
    if (position.x < 512)
    {
        yaw += rotationSpeed * (-difX);
    }
    else
        if (position.x > 512)
        {
            yaw -= rotationSpeed * difX;
        }
    atualizaDirecaoVetor();
    mouseCentro();
    if (button == 1) // se apreto el boton izquierdo de mouse
    {
        eyex -= (float)i * forwardSpeed;
        eyey -= (float)j * forwardSpeed;
        eyez -= (float)k * forwardSpeed;
    }
    else
        if (button == -1) // se apreto el boton derecho del mouse
        {
            eyex += (float)i * forwardSpeed;
            eyey += (float)j * forwardSpeed;
            eyez += (float)k * forwardSpeed;
        }

//    #pragma endregion Aim Camera


    look();
}
