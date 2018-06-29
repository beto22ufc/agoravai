#ifndef OBJECT_H
#define OBJECT_H

#include <Geometry.h>

class Object
{
    public:
        Object();
        virtual ~Object();
        Object(Point p);
        Point posicao;
    protected:

    private:
};

#endif // OBJECT_H
