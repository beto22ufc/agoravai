#ifndef SOL_H
#define SOL_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <Textura.h>
#include <iostream>
#include <Geometry.h>

using namespace std;
class Sol
{
    public:
        Sol();
        virtual ~Sol();
        Sol(float raio, Point position, float rotacao, float time, GLuint texture);
        GLuint texture;
        Textura textura;
        Point position;
        float time;
        float raio;
        float rotacao;
        void draw();
    protected:

    private:
};

#endif // SOL_H
