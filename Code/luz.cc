#include "luz.h"
#include <iostream>

using namespace std;
_Luz::_Luz(int num_luces)
{
    posiciones.resize(num_luces*4);
}

void _Luz::encenderLuz(int numLuz){
    switch (numLuz) {
    case 0:glEnable(GL_LIGHT0);
        break;

    case 1:glEnable(GL_LIGHT1);
        break;
    }
}

void _Luz::apagarLuz(int numLuz){
    switch (numLuz) {
    case 0: glDisable(GL_LIGHT0);
        break;

    case 1: glDisable(GL_LIGHT1);
        break;
    }
}

void _Luz::setPosicionLuz(int numLuz, GLfloat x, GLfloat y, GLfloat z, GLfloat NoInf, bool guardar){

    GLfloat PosicionLuz[4];
    PosicionLuz[0] = x;
    PosicionLuz[1] = y;
    PosicionLuz[2] = z;
    PosicionLuz[3] = NoInf;

    if(guardar){
        for(int i=0; i<4; i++){
            posiciones[numLuz*4+i] = PosicionLuz[i];
        }
    }

    switch (numLuz) {
    case 0: glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz);
        break;

    case 1: glLightfv(GL_LIGHT1, GL_POSITION, PosicionLuz);
        break;
    }

}
void _Luz::setEspecular(int numLuz, GLfloat x, GLfloat y, GLfloat z, GLfloat NoInf){
    GLfloat LuzEspecular[4];
    LuzEspecular[0] = x;
    LuzEspecular[1] = y;
    LuzEspecular[2] = z;
    LuzEspecular[3] = NoInf;

    switch (numLuz) {
    case 0: glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular);
        break;

    case 1: glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular);
        break;
    }
}

void _Luz::setAmbiental(int numLuz, GLfloat x, GLfloat y, GLfloat z, GLfloat NoInf){
    GLfloat LuzAmbiental[4];
    LuzAmbiental[0] = x;
    LuzAmbiental[1] = y;
    LuzAmbiental[2] = z;
    LuzAmbiental[3] = NoInf;

    switch (numLuz) {
    case 0: glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiental);
        break;

    case 1: glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiental);
        break;
    }
}

void _Luz::setDifusa(int numLuz, GLfloat x, GLfloat y, GLfloat z, GLfloat NoInf){
    GLfloat LuzDifusa[4];
    LuzDifusa[0] = x;
    LuzDifusa[1] = y;
    LuzDifusa[2] = z;
    LuzDifusa[3] = NoInf;

    switch (numLuz) {
    case 0: glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
        break;

    case 1: glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa);
        break;
    }
}

GLfloat _Luz::getPosicion_X(int numLuz){
    return posiciones[numLuz*4+0];
}
GLfloat _Luz::getPosicion_Y(int numLuz){
    return posiciones[numLuz*4+1];
}
GLfloat _Luz::getPosicion_Z(int numLuz){
    return posiciones[numLuz*4+2];
}

