#ifndef _COCHE_H
#define _COCHE_H

#include "chasis.h"
#include "cone.h"

class _coche : public _object3D
{
public:



     _chasis chasis;
    _cylinder luzI, luzD;
    _cube matricula;

    _coche();
    void draw(_mode MODE, float traslacion_coche=0,float angle_puerta=0, float angle_ruedas=0, float desplazamiento_asiento=1.5);
};

#endif // _COCHE_H
