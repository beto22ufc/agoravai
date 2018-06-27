#ifndef CAMERA_H
#define CAMERA_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define pi 4*atan(1)

#include <math.h>
#include <windows.h>

class Camera
{
    public:
        Camera();
        virtual ~Camera();
        //Camera(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float yaw, float pitch);
        double div1;
        double div2;
        float eyex, eyey, eyez;
        float centerx, centery, centerz;
        float forwardSpeed;
        float yaw, pitch;
        float rotationSpeed;
        double i, j, k;
        void initCamera();
        void look();
        float anguloParaRadiano(double angulo);
        float radianoParaAngulo(double radiano);
        void mouseCentro();
        void atualizaDirecaoVetor();
        void atualiza(int button);
    protected:

    private:
};

#endif // CAMERA_H
