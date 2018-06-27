#ifndef STAR_H
#define STAR_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <Point.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <Geometry.h>

using namespace std;


class Star
{
    public:
        Star();
        virtual ~Star();
        Star(Point posicao);
        Point posicao;
        std::vector<Star> estrelas;
        void criarEstrelas(int quantidade);
        void draw();
    protected:

    private:
};

#endif // STAR_H
