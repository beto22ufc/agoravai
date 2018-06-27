/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <Sol.h>
#include <Planeta.h>
#include <Sun.h>
#include <Planet.h>
#include <Star.h>
#include <Camera.h>
#include <Saturno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <Textura.h>
#include <iostream>
#define pi 4*atan(1)
#include <Ship.h>
#include <Geometry.h>
#include <vector>
#include <Asteroid.h>

using namespace std;
void readFile(std::vector <Point> *points, char *fileDir);
std::vector<Point> shipPoints;
Textura textura;
GLuint texturas[21];
static int slices = 16;
static int stacks = 16;
GLint rox=30,roy=0,roz=0,ang;
GLfloat angle, fAspect;
Ship ship(Point(0,5,10));

int wx = 0, wy = 0;
int movimento = 0;
//Planeta(float raio, Point posicao, float anguloOrbita, float velocidadeOrbita, GLuint *textura)
/*

    Sistema solar 1

*/
Planeta mercurio(1.0f, Point(-22.0f, 0.0f, -0.6f), 0.0f, 0.01f, &texturas[1]);
Planeta venus(1.5f, Point(-33.0f, 0.0f, -0.6f), 0.0f, 0.009f, &texturas[2]);
Planeta terra(2.0f, Point(-54.0f, 0.0f, -0.6f), 0.0f, 0.007f, &texturas[3]);
Planeta marte(1.7f, Point(-65.0f, 0.0f, -0.6f), 0.0f, 0.005f, &texturas[4]);
Planeta jupter(4.0f, Point(-87.0f, 0.0f, -0.6f), 0.0f, 0.003f, &texturas[5]);
Saturno saturno(3.0f, Point(-108.0f, 0.0f, -0.6f), 0.0f, 0.0025f, &texturas[6]);
Planeta urano(2.4f, Point(-129.0f, 0.0f, -0.6f), 0.0f, 0.0022f, &texturas[7]);
Planeta neturno(1.9f, Point(-139.0f, 0.0f, -0.6f), 0.0f, 0.0020f, &texturas[8]);
Planeta plutao(1.3f, Point(-150.0f, 0.0f, -0.6f), 0.0f, 0.0018f, &texturas[9]);
Sol sol(5, Point(0, 0, 0), 45.0f, 1000.0f, texturas[0]);
/*

    Sistema solar 2

*/
//Planeta(float raio, Point posicao, float anguloOrbita, float velocidadeOrbita, GLuint *textura)
Sol sol2(7, Point(200, 0, 0), 45.0f, 1000.0f, texturas[19]);
Planeta p1(1.3f, Point(-220.0f, 0.0f, -0.6f), 0.0f, 0.0018f, &texturas[10]);
Planeta p2(2.3f, Point(-250.0f, 0.0f, -0.6f), 0.0f, 0.0018f, &texturas[11]);
Planeta p3(1.7f, Point(-260.0f, 0.0f, -0.6f), 0.0f, 0.0018f, &texturas[12]);
Planeta p4(0.9f, Point(-280.0f, 0.0f, -0.6f), 0.0f, 0.0018f, &texturas[13]);
Planeta p5(4.3f, Point(-350.0f, 0.0f, -0.6f), 0.0f, 0.0018f, &texturas[14]);
Star stars;

Asteroid asteroids;
/* GLUT callback Handlers */



void FreeCreatedTexture(GLuint texture)
{
    glDeleteTextures(1, &texture);
}

static void resize(int width, int height)
{
   glViewport(0, 0, width, height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(60.0, (GLfloat)width/(GLfloat)height, 0.05, 300.0);
      glMatrixMode(GL_MODELVIEW);
}

void timer(int v) {
  ship.fly();
  Point eye(ship.getPosition());
  //cout << eye.x << " " << eye.y << " " << eye.z << "\n";
  Point at(ship.getPosition() + ship.getDirection());
  Vector up(ship.getVertical());
  glLoadIdentity();
  gluLookAt(eye.x, eye.y, eye.z, at.x, at.y, at.z, up.i, up.j, up.k);
  glutPostRedisplay();
  glutTimerFunc(1000/60, timer, v);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //camera.atualiza(movimento);
    /*

    Sistema solar 1

    */
    mercurio.draw();
    venus.draw();
    terra.draw();
    marte.draw();
    jupter.draw();
    saturno.draw();
    urano.draw();
    neturno.draw();
    plutao.draw();
    sol.draw();
    /*

    Sistema solar 2

    */
    /*
    p1.draw();
    p2.draw();
    p3.draw();
    p4.draw();
    p5.draw();
    sol2.draw();*/



    glColor3d(1,1,1);
    glPointSize(5);
    stars.draw();
    asteroids.draw();

    glutSwapBuffers();
    glFlush();
}

static void key(unsigned char key, int x, int y) {
    const double deltaSpeed = 0.01;
    const double angle = 0.02;
    switch(key) {
        case '8': ship.setSpeed(ship.getSpeed() + deltaSpeed); break;
        case 'm': ship.setSpeed(ship.getSpeed() - deltaSpeed); break;
        case 'j': ship.roll(angle); break;
        case 'l': ship.roll(-angle); break;
        case 'h': ship.yaw(angle); break;
        case ';': ship.yaw(-angle); break;
        case 'i': ship.pitch(-angle); break;
        case 'k': ship.pitch(angle);  break;
    }
    glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        movimento = 1;
    } else {
        movimento = -1;
    }

    if (state == GLUT_UP) {
        movimento = 0;
    }
	glutPostRedisplay();
}


static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

void inicializar() {
    stars.criarEstrelas(1000000);
    asteroids.criarAsteroids(1000);
    // Habilitar o uso de texturas
	glEnable ( GL_TEXTURE_2D );
	glEnable(GL_COLOR_MATERIAL);
	// Definir a forma de armazenamento dos pixels na textura (1= alinhamento por byte)
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

	// Definir quantas texturas serão usadas no programa
	//GLuint texture_id[10]; // vetor com os números das texturas
	glGenTextures (10, texturas);  // 1 = uma textura;
					// texture_id = vetor que guarda os números das texturas(para ir trocando depois)
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	texturas[0] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\sol.bmp");
	texturas[1] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\mercurio.bmp");
	texturas[2] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\venus.bmp");
	texturas[3] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\terra.bmp");
	texturas[4] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\marte.bmp");
	texturas[5] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\jupter.bmp");
	texturas[6] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\saturno.bmp");
	texturas[7] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\urano.bmp");
	texturas[8] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\netuno.bmp");
	texturas[9] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\plutao.bmp");
	texturas[10] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\planeta1.bmp");
	texturas[11] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\planeta2.bmp");
	texturas[12] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\planeta3.bmp");
	texturas[13] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\planeta4.bmp");
	texturas[14] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\planeta5.bmp");
	texturas[15] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\planeta6.bmp");
	texturas[16] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\planeta7.bmp");
	texturas[17] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\planeta8.bmp");
	texturas[18] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\planeta9.bmp");
	texturas[19] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\sol1.bmp");
	texturas[20] = textura.LoadBitmapA("C:\\Users\\Wallison\\Documents\\Code Blocks Projects\\SolarSystem\\texturas\\bitmap\\sol2.jpg");

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1400,700);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    readFile(&shipPoints, "C:\\Users\\Wallison\\Documents\\agoravai\\res\\meteoro.txt");
    glutCreateWindow("StarShip");
    inicializar();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(GerenciaMouse);
    glutTimerFunc(100, timer, 0);
    glutIdleFunc(idle);

    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat dark[] = { 0.2, 0.15, 0.2, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = { 0.2, 1.0, 0.5, 0.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);

    glLightfv(GL_LIGHT0, GL_AMBIENT, dark);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);

    glEnable(GL_LIGHTING);                // so the renderer considers light
    glEnable(GL_LIGHT0);                  // turn LIGHT0 on

    glutMainLoop();

    return EXIT_SUCCESS;
}

void readFile(std::vector <Point> *points, char *fileDir) {
    FILE *file;
    file = fopen(fileDir, "rt");
    if (!file) {
        printf("Problemas na CRIACAO do arquivo\n");
        return;
    }
    char id;
    double x, y, z;
    while ((fscanf(file,"%c %f %f %f\n", &id, &x, &z, &y))!=EOF) {
        points->push_back(Point(x, y, z));
    }
    fclose(file);
}
