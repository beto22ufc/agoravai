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
#include <GL/glext.h>
#include <Cockpit.h>


#define BACK_ID		0									// The texture ID for the back side of the cube
#define FRONT_ID	1									// The texture ID for the front side of the cube
#define BOTTOM_ID	2									// The texture ID for the bottom side of the cube
#define TOP_ID		3									// The texture ID for the top side of the cube
#define LEFT_ID		4									// The texture ID for the left side of the cube
#define RIGHT_ID	5

using namespace std;
void readFile(std::vector <Point> *points, char *fileDir);
void CreateSkyBox(float x, float y, float z, float width, float height, float length);
bool CreateTexture(GLuint &textureID, LPTSTR szFileName);
std::vector<Point> shipPoints;
Textura textura;
GLuint texturas[16];
UINT g_Texture[6];
static int slices = 16;
static int stacks = 16;
GLint rox=30,roy=0,roz=0,ang;
GLfloat angle, fAspect;
Ship ship(Point(0,5,10));
Cockpit cockpit(ship);
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
    cockpit.draw();
    /*

    Sistema solar 2

    */


    //CreateSkyBox(0, 0, 0, 400, 200, 400);

    glColor3d(1,1,1);
    glPointSize(5);
    stars.draw();
    asteroids.draw();
    //ship.draw();
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

	CreateTexture(g_Texture[BACK_ID], "C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\Back.bmp");
	CreateTexture(g_Texture[FRONT_ID], "C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\Front.bmp");
	CreateTexture(g_Texture[BOTTOM_ID], "C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\Bottom.bmp");
	CreateTexture(g_Texture[TOP_ID], "C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\Top.bmp");
	CreateTexture(g_Texture[LEFT_ID], "C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\Left.bmp");
	CreateTexture(g_Texture[RIGHT_ID], "C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\Right.bmp");
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
	texturas[10] = textura.LoadBitmapA("C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\bitmap\\far.bmp");
	texturas[11] = textura.LoadBitmapA("C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\bitmap\\near.bmp");
	texturas[12] = textura.LoadBitmapA("C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\bitmap\\bottom.bmp");
	texturas[13] = textura.LoadBitmapA("C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\bitmap\\left.bmp");
	texturas[14] = textura.LoadBitmapA("C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\bitmap\\top.bmp");
	texturas[15] = textura.LoadBitmapA("C:\\Users\\Wallison\\Desktop\\agoravai-1\\texturas\\bitmap\\right.bmp");


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

void CreateSkyBox(float x, float y, float z, float width, float height, float length)
{
	// This is the most important function of this tutorial.  This function
	// used to just create a silly colored cube in the RotateCube tutorial,
	// but now it creates something beautiful.  You'll notice we added
	// some more parameters to the function.  This way we can change the perspective
	// of the sky box.  It doesn't really look good if it's a perfect cube.  Some
	// textures look better at different ratios.  We assign the sky box textures
	// to each side of the box creating the illusion of a detailed 3D world.
	// You will notice I had to change the texture coordinates for every one
	// to be flipped correctly.  Also, depending on your culling, the vertex
	// order might need to be changed around.  I don't use culling in this tutorial
	// so it will work fine here, but be sure to remember this if you do.

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, g_Texture[BACK_ID]);

	// Since we want the sky box to be centered around X, Y, and Z for ease,
	// we do a little math to accomplish this.  We just change the X, Y and Z
	// to perform this task.  If we just minus half the width, height and length
	// from x, y and z it will give us the desired result.  Now when we create the
	// box it will center it around (x, y, z)

	// This centers the sky box around (x, y, z)
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

		// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the BACK Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y,			z);

	glEnd();

	// Bind the FRONT texture of the sky map to the FRONT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[FRONT_ID]);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the FRONT Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height, z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z + length);
	glEnd();

	// Bind the BOTTOM texture of the sky map to the BOTTOM side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[BOTTOM_ID]);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the BOTTOM Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,			z + length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
	glEnd();

	// Bind the TOP texture of the sky map to the TOP side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[TOP_ID]);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the TOP Side
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y + height,	z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height,	z);

	glEnd();

	// Bind the LEFT texture of the sky map to the LEFT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[LEFT_ID]);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the LEFT Side
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height,	z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height,	z + length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);

	glEnd();

	// Bind the RIGHT texture of the sky map to the RIGHT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[RIGHT_ID]);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the RIGHT Side
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,			z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height,	z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height,	z);
	glEnd();
}

bool CreateTexture(GLuint &textureID, LPTSTR szFileName)                          // Creates Texture From A Bitmap File
{
	HBITMAP hBMP;                                                                 // Handle Of The Bitmap
	BITMAP  bitmap;																  // Bitmap Structure

	glGenTextures(1, &textureID);                                                 // Create The Texture
	hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBMP)                                                                    // Does The Bitmap Exist?
		  return FALSE;                                                           // If Not Return False

	GetObject(hBMP, sizeof(bitmap), &bitmap);                                     // Get The Object
																				  // hBMP:        Handle To Graphics Object
																				  // sizeof(bitmap): Size Of Buffer For Object Information
																				  // &bitmap:        Buffer For Object Information

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);                                        // Pixel Storage Mode (Word Alignment / 4 Bytes)

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, textureID);                                      // Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);			  // Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);			  // Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, 3, bitmap.bmWidth, bitmap.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap.bmBits);
																				  // MUST NOT BE INDEX BMP, BUT RGB
	DeleteObject(hBMP);                                                           // Delete The Object

	return TRUE;                                                                  // Loading Was Successful
}

