#include "Planet.h"

Planet::Planet()
{
    //ctor
}

Planet::~Planet()
{
    //dtor
}

Planet::Planet(float raio, Point posicao, float anguloRotacao, float anguloOrbita, float velocidadeOrbita, GLuint *textura) {
    this->raio = raio;
    this->posicao = posicao;
    this->anguloRotacao = anguloRotacao;
    this->anguloOrbita = anguloOrbita;
    this->textura = textura;
    this->velocidadeOrbita = velocidadeOrbita;
}

void Planet::create() {
    GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	list = glGenLists(1); // crear la lista
    glNewList(list, GL_COMPILE);
    glPushMatrix();
    glRotated(270, 1, 0, 0);
    gluSphere(qobj, raio, 32, 32); //creo la esfera
    glPopMatrix();
    glEndList();
}

void Planet::draw() {
    drawOrbita();
    create();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textura);
    glPushMatrix();
    anguloOrbita += velocidadeOrbita;
    anguloRotacao += 0.6f;
    glRotatef(anguloOrbita, 0, 1, 0);
    glTranslatef(-posicao.x, -posicao.y, -posicao.z);

    glRotatef(anguloRotacao, 0, 1, 0);

    glCallList(list);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void Planet::drawOrbita() {
    glBegin(GL_LINE_STRIP);
        for (int i = 0;i < 361;i++) {
            glVertex3f(posicao.x * (float)sin(i*pi/180), 0, posicao.x * (float)cos(i * pi/180));
        }
    glEnd();
}
