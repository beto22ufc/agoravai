#include "Missele.h"

Missele::Missele()
{
    //ctor
}

Missele::~Missele()
{
    //dtor
}


Missele::Missele(Point p, Vector forward, float velocidade){
    posicao = p;
    this->forward = forward;
    this->velocidade = velocidade;
    alive = false;
}

void Missele::fly(){
    posicao += velocidade * forward;
}

void Missele::draw() {
    glColor3d(0, 1, 0);
    glLineWidth(19.0f);
    end = posicao + 10 * forward;
    glBegin(GL_LINES);
        glVertex3d(posicao.x, posicao.y-1, posicao.z);
        glVertex3d(end.x, end.y-1, end.z);
    glEnd();
    glLineWidth(1.0f);
}

float Missele::distance(Point p1, Point p2) {
    float dist = 0;
    dist = sqrt(pow((p2.x - p1.x),2) + pow((p2.y - p1.y),2) + pow((p2.z - p1.z),2));
    return dist;
}

void Missele::collide_with(std::vector<Asteroid> &asteroids) {
    for (unsigned int i = 0;i < asteroids.size();i++) {
        Asteroid a = asteroids[i];
        //cout << end.distanceTo(a.posicao) << "<=" << a.raio << "\n";

        if (distance(a.posicao, end) <= a.raio) {
            asteroids.erase(asteroids.begin()+i);
            alive = false;
            break;
        }
    }
}

