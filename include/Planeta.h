#ifndef PLANETA_H
#define PLANETA_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <Textura.h>
#include <iostream>
#include <Geometry.h>

#define pi 4*atan(1)
//// Macros da posição XY do planeta na órbita
#define Rx(v)   (SE * distanciaSol * (cos(v) - EX))
#define Ry(v)   (SE * distanciaSol * sqrt(1.0 - EX * EX) * sin(v))

using namespace std;

class Planeta
{
    public:
        Planeta();
        virtual ~Planeta();
        Planeta(float rotacao, float translacao, float time, float *color, float raio, float distanciaSol, GLuint *textura);
        Planeta(float raio, Point posicao, float anguloOrbita, float velocidadeOrbita, GLuint *textura);
        float anguloRotacao;
        float anguloOrbita;
        Point posicao;
        float velocidadeOrbita;
        float raio;
        float inc;
        GLuint *textura;
        float distanciaSol;
        float *color;
        float time;
        float rotacao;
        float translacao;
        float x,z;
        int year, day;
        float teta;
        void spinDisplay(void);
        void timer(int value);
        void draw();
        void drawOrbita();
    protected:

    private:
};

#endif // PLANETA_H
