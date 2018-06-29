#ifndef SHIP_H
#define SHIP_H

#include <Geometry.h>
#include <Object.h>
#include <Missele.h>
#include <iostream>
#include <Asteroid.h>
#include <vector>

using namespace std;

class Ship : Object{
  Missele m;
  Point position;
  Vector forward, up, right;
  double speed;
public:
  Ship(Point initialPosition = Point(0, 0, 0));
  Point getPosition() {return position;}
  void fly() {position += speed * forward;}
  void teleport(Point newPosition) {position = newPosition;}
  Vector getDirection() {return forward;}
  Vector getVertical() {return up;}
  void pitch(double angle);
  void roll(double angle);
  void yaw(double angle);
  void draw();
  void fire(int &flag, std::vector<Asteroid> &asteroids);
  double getSpeed() {return speed;}
  void setSpeed(double newSpeed) {speed = newSpeed;}
};

inline Ship::Ship(Point initialPosition):
  position(initialPosition),
  forward(0, 0, -1),
  up(0, 1, 0),
  right(1, 0, 0),
  speed(0.01)
{
}


inline void Ship::draw() {
    /*glColor3d(0,1,0);
    Point at(getPosition() + getDirection());
    Vector up(getVertical());
    glPushMatrix();
        glTranslated(position.x, position.y, position.z-1);
        glScaled(0.5, 0.1, 0.7);
        glRotated(0.2f, at.x, at.y, at.z);
        glRotated(0.2f, up.i, up.j, up.k);
        glutSolidTetrahedron();
    glPopMatrix();*/
    glColor3d(1,0,0);
    cout << position.x << " " << position.y << " " << position.z <<"\n";
    glBegin(GL_LINES);
   //     glVertex3d(position.x, position.y, position.z);
    //    glVertex3d(position.x, position.y, position.z-5);
    glVertex3f(position.x, position.y-2, position.z);
        glVertex3f(position.x, position.y-2, position.z-20);
    glEnd();
}

inline void Ship::fire(int &flag, std::vector<Asteroid> &asteroids) {
    if (m.alive) {
        if (position.distanceTo(m.posicao) >= 0.01) {
            m.alive = false;
            flag = 0;
            //cout << "Missel destruido!\n";
        }
        m.collide_with(asteroids);
        //cout << "Missel ativo\n";
    } else {
        //cout << "Criando novo missel!\n";
        m.posicao = position;
        m.forward = forward;
        m.velocidade = 10;
        m.alive = true;
    }
    m.draw();
    m.fly();
    //cout << "Posição: " << m.posicao.x << " " << m.posicao.y << " " << m.posicao.z;
    cout << "Aqui fire ";

}

inline void Ship::pitch(double angle) {
  forward = unit(forward * cos(angle) + up * sin(angle));
  up = right.cross(forward);
}

inline void Ship::roll(double angle) {
  right = unit(right * cos(angle) + up * sin(angle));
  up = right.cross(forward);
}

inline void Ship::yaw(double angle) {
  right = unit(right * cos(angle) + forward * sin(angle));
  forward = up.cross(right);
}

#endif
