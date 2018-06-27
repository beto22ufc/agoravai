#include "Star.h"

Star::Star()
{
    //ctor
}

Star::~Star()
{
    //dtor
}

Star::Star(Point posicao) {
    this->posicao = posicao;
}
void Star::criarEstrelas(int quantidade) {
    int conte = 0;
    while (conte != quantidade) {
        float x = (rand()%10000) * (pow(-1, rand()));
        float y = (rand()%10000) * (pow(-1, rand()));
        float z = (rand()%10000) * (pow(1, rand()));
        //if (pow(pow(x, 2) + pow(y, 2) + pow(z, 2), 1 / 3.0f) > 15) {
        estrelas.push_back(Star(Point(x, y, z)));

        //}
        conte++;
    }
}


void Star::draw() {
    glBegin(GL_POINTS);
    glColor3f(1,1,1);
    glPointSize(5);
    for (unsigned int i= 0;i < estrelas.size();i++) {
        glVertex3f(estrelas[i].posicao.x, estrelas[i].posicao.y, estrelas[i].posicao.z);
    }
    glEnd();
}
