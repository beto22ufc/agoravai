#include "Asteroid.h"

Asteroid::Asteroid()
{
    //ctor
}

Asteroid::~Asteroid()
{
    //dtor
}

Asteroid::Asteroid(Point posicao) {
    this->posicao = posicao;
}
void Asteroid::criarAsteroids(int quantidade) {
    int conte = 0;
    while (conte != quantidade) {
        float x = (rand()%500) * (pow(-1, rand()));
        float y = (rand()%500) * (pow(-1, rand()));
        float z = (rand()%500) * (pow(-1, rand()));
        asteroids.push_back(Asteroid(Point(x, y, z)));
        eixo = rand()%3;
        size = rand()%3;
        conte++;
    }
}


void Asteroid::draw() {
    glColor3f(0.75f, 0.75f,0.75f);

    for (unsigned int i= 0;i < asteroids.size();i++) {
        glPushMatrix();
            Asteroid asteroid = asteroids[i];
            if (asteroid.eixo == 0) {
                asteroid.posicao.x += 2.5;
            } else if (asteroid.eixo == 1) {
                asteroid.posicao.y += 2.5;
            } else {
                asteroid.posicao.z += 2.5;
            }
            glTranslated(asteroid.posicao.x, asteroid.posicao.y, asteroid.posicao.z);
            glRotated(60,1,0,0);
            glRotated(45,0,0,1);
            if (asteroid.eixo == 0) {
                glScaled(0.5, 0.5, 0.5);
            } else if (asteroid.eixo == 1) {
                glScaled(1.0, 1.0, 1.0);
            } else {
                glScaled(1.5, 1.5, 1.5);
            }
            glutSolidDodecahedron();
        glPopMatrix();
    }

}
