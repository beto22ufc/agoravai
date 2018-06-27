#ifndef SATURNO_H
#define SATURNO_H
#include <Planeta.h>
#include <math.h>
class Saturno : Planeta
{
    public:
        Saturno();
        virtual ~Saturno();
        Saturno(float rotacao, float translacao, float time, float *color, float raio, float distanciaSol, GLuint* textura);
        Saturno(float raio, Point posicao, float anguloOrbita, float velocidadeOrbita, GLuint *textura);
        void draw();
        void timer(int value);
        float x,z;
        int year, day;
        float teta;
    protected:

    private:
};

#endif // SATURNO_H
