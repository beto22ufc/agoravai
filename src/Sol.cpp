#include "Sol.h"

Sol::Sol()
{
    //ctor
}

Sol::~Sol()
{
    //dtor
}

Sol::Sol(float raio, Point position, float rotacao, float time, GLuint texture) {
    this->rotacao = rotacao;
    this->time = time;
    this->texture = texture;
    this->raio = raio;
    this->position = position;
}

void Sol::draw(){
    glColor3d(1,1,0);
    double t = glutGet(GLUT_ELAPSED_TIME) / time;
    float a = t * rotacao;
    GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\sol.bmp"));
    glBindTexture(GL_TEXTURE_2D, texture);
    glPushMatrix();
        glTranslated(position.x, position.y, position.z);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        gluSphere(qobj, raio, 16, 16);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


