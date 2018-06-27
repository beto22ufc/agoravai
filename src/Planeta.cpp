#include "Planeta.h"
#include <math.h>

Planeta::Planeta()
{
    //ctor
    x = 0.0;
    z = 0.0f;
    teta = 0.0;

}

Planeta::~Planeta()
{
    //dtor
}

Planeta::Planeta(float rotacao, float translacao, float time, float *color, float raio, float distanciaSol, GLuint *textura) {
    this->rotacao = rotacao;
    this->translacao = translacao;
    this->time = time;
    this->color = color;
    this->textura = textura;
    this->raio = raio;
    this->distanciaSol = distanciaSol;
    this->x = 0.0;
    this->z = 0.0f;
    this->teta = 0.0;
}

Planeta::Planeta(float raio, Point posicao, float anguloOrbita, float velocidadeOrbita, GLuint *textura) {
    this->raio = raio;
    this->posicao = posicao;
    this->anguloRotacao = 0;
    this->anguloOrbita = anguloOrbita;
    this->textura = textura;
    this->inc = 0;
    this->velocidadeOrbita = velocidadeOrbita;
}

void Planeta::draw(){
    drawOrbita();
    double t = glutGet(GLUT_ELAPSED_TIME) / time;
    float a = t * rotacao;
    GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *textura);
    glPushMatrix();
        /*
        glTranslated(x,0.0,z);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        */
        anguloOrbita += velocidadeOrbita;
        anguloRotacao += 0.6f;
        glRotatef(anguloOrbita, 0, 1, 0);
        glTranslatef(posicao.x * (float)sin(inc*pi/180), 0, posicao.x * (float)cos(inc * pi/180));
        glRotatef(anguloRotacao, 0, 1, 0);
        gluSphere(qobj, raio, 32, 32);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    if (inc == 360) {
        inc = 0;
    } else {
        inc += velocidadeOrbita;
    }
}

void Planeta::spinDisplay(void)
{
  year = (year + 1);
  day  = (day + 2 );
  glutPostRedisplay();
}

void Planeta::timer(int value)
{
    x = distanciaSol + (5*cos(teta));
    z = -0.6 + (-10*sin(teta));
    //teta = (teta * 180/pi) +0.1;
    teta=teta+0.01;
    spinDisplay();
}

void Planeta::drawOrbita() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
        for (int i = 0;i < 361;i++) {
            glVertex3f(posicao.x * (float)sin(i*pi/180), 0, posicao.x * (float)cos(i * pi/180));
        }
    glEnd();
}
