#ifndef ASTEROID_H
#define ASTEROID_H

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

class Asteroid
{
    public:
        Asteroid();
        virtual ~Asteroid();
        Asteroid(Point posicao);
        Point posicao;
        int eixo;
        int size;
        std::vector<Asteroid> asteroids;
        void criarAsteroids(int quantidade);
        void draw();
    protected:

    private:
};

#endif // ASTEROID_H
