#ifndef PLANET_H
#define PLANET_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <Textura.h>
#include <iostream>
#include <math.h>
#include <Point.h>

#define pi 4*atan(1)

#define X 0
#define Y 1
#define Z 2

using namespace std;


class Planet
{
    public:
        Planet();
        virtual ~Planet();
        Planet(float raio, Point posicao, float anguloRotacao, float anguloOrbita, float velocidadeOrbita, GLuint *textura);
        float raio;
        int list;
        Point posicao;
        float anguloRotacao;
        float anguloOrbita;
        float velocidadeOrbita;
        GLuint *textura;
        void create();
        void draw();
        void drawOrbita();
    protected:

    private:
};

#endif // PLANET_H
