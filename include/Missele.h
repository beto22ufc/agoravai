#ifndef MISSELE_H
#define MISSELE_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <Geometry.h>
#include <iostream>
#include <vector>
#include <Asteroid.h>
#include <math.h>

using namespace std;

class Missele
{
    public:
        Missele();
        virtual ~Missele();
        Missele(Point posicao, Vector forward, float velocidade);
        void fly();
        void draw();
        void collide_with(std::vector<Asteroid> &asteroids);
        float velocidade;
        float distance(Point p1, Point p2);
        bool alive;
        Point posicao;
        Point end;
        Vector forward;
    protected:

    private:
};

#endif // MISSELE_H
