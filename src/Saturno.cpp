#include "Saturno.h"

Saturno::Saturno()
{
    //ctor
}

Saturno::~Saturno()
{
    //dtor
}

Saturno::Saturno(float rotacao, float translacao, float time, float *color, float raio, float distanciaSol, GLuint *textura) : Planeta(rotacao, translacao, time, color, raio, distanciaSol, textura) {

}

Saturno::Saturno(float raio, Point posicao, float anguloOrbita, float velocidadeOrbita, GLuint *textura) : Planeta(raio, posicao, anguloOrbita, velocidadeOrbita, textura){

}

void Saturno::draw(){
    drawOrbita();
    double t = glutGet(GLUT_ELAPSED_TIME) / time;
    float a = t * rotacao;
    GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, textura.LoadBitmapA(texturaN));
	glBindTexture(GL_TEXTURE_2D, *textura);
    glPushMatrix();
        //glTranslatef((distanciaSol * cos(2.0 * 3.14 * a*1.9 / 100)),(3.4 + 3.4 * sin(2.0 * 3.14 * a*1.9 / 100)), 0);
        /*
        glTranslated(x,0.0,z);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);*/
        anguloOrbita += velocidadeOrbita;
        anguloRotacao += 0.6f;
        glRotatef(anguloOrbita, 0, 1, 0);
        glTranslatef(posicao.x * (float)sin(inc*pi/180), 0, posicao.x * (float)cos(inc * pi/180));
        glRotatef(anguloRotacao, 0, 1, 0);
        gluSphere(qobj, raio, 16, 100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glColor3d(1.0, 0.5, 0.0);
   /* glPushMatrix();

        glTranslated(x,-0.1, z);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glRotatef(anguloOrbita, 0, 1, 1);
        glTranslatef(posicao.x * (float)sin(inc*pi/180), -0.1, posicao.x * (float)cos(inc * pi/180));
        glRotatef(anguloRotacao, 0, 1, 0);
        glutSolidTorus(0.1,0.4,2,40);
    glPopMatrix();*/
    if (inc == 360) {
        inc = 0;
    } else {
        inc += velocidadeOrbita;
    }
}

void Saturno::timer(int value)
{


    x = distanciaSol * (5*cos(teta));
    z=-0.6 + (-10*sin(teta));
    //teta = teta*180/pi + 1;
    teta=teta+0.01;
    //if (teta==2*pi) teta=0;
    spinDisplay();
}

