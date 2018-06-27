#ifndef SUN_H
#define SUN_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Sun
{
    public:
        Sun();
        virtual ~Sun();
        Sun(float rotacao, GLuint *textura);
        GLuint *textura;
        int list;
        float rotacao;
        void draw();
        void create();
    protected:

    private:
};

#endif // SUN_H
