#ifndef _LUZ_H
#define _LUZ_H

#include <GL/gl.h>
#include <vector>
#include "vertex.h"

class _Luz
{
private:

    vector<GLfloat> posiciones;
public:
    _Luz(int num_luces=2);
    void encenderLuz(int numLuz);
    void apagarLuz(int numLuz);
    void setPosicionLuz(int numLuz ,GLfloat x, GLfloat y, GLfloat z, GLfloat NoInf, bool guardar=false);
    void setEspecular(int numLuz ,GLfloat x, GLfloat y, GLfloat z, GLfloat NoInf);
    void setAmbiental(int numLuz ,GLfloat x, GLfloat y, GLfloat z, GLfloat NoInf);
    void setDifusa(int numLuz ,GLfloat x, GLfloat y, GLfloat z, GLfloat NoInf);
    GLfloat getPosicion_X(int numLuz);
    GLfloat getPosicion_Y(int numLuz);
    GLfloat getPosicion_Z(int numLuz);

};

#endif // _LUZ_H
