#ifndef _PLATAFORMA_H
#define _PLATAFORMA_H

#include "eje_ruedas.h"
#include "cube.h"
#include "asiento.h"

class _plataforma : public _object3D
{
public:
    _eje_ruedas delantero, trasero;
    _cube base;
    _asiento asientod, asientoi;
    _plataforma();
    void draw(_mode MODE, float angulo_ruedas=0, float desplazamiento_asiento=1.5);
};

#endif // _PLATAFORMA_H
