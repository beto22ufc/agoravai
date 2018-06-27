#include "Sun.h"

Sun::Sun()
{
    //ctor
}

Sun::~Sun()
{
    //dtor
}

Sun::Sun(float rotacao, GLuint *textura) {
    this->rotacao = rotacao;
    this->textura = textura;
}

void Sun::create(){
    GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    //Gl.glDisable(Gl.GL_LIGHTING);
    gluSphere(qobj, 3, 32, 32);
    //Gl.glEnable(Gl.GL_LIGHTING);
    glPopMatrix();
    glEndList();
}

void Sun::draw() {
    create();
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textura);
    glPushMatrix();
    rotacao += 0.05f;
    glRotatef(rotacao, 0, 1, 0);
    glCallList(list);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
