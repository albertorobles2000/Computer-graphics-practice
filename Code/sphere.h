#ifndef _SPHERE_H
#define _SPHERE_H

#include "object3d.h"
#include "circular_sweeping.h"

class _sphere:public _circular_sweeping
{
public:
    _sphere(int rotaciones = 30, int rotation_axis=1,float Size=1.0, int Particiones_perfil = 10);
    void calcularNormalesTriangulos(int rotaciones, int perfil);
    void calcularNormalesVertices();
    //void calcularTexturas();
};

#endif // _SPHERE_H
