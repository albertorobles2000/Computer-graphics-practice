#ifndef _FURGONETA_H
#define _FURGONETA_H

#include "plataforma.h"
#include "puerta.h"
#include "pared_ventana.h"
class _chasis
{
public:
    _plataforma plataforma;
    _cube motor;
    _pared_ventana paredI, paredD;
    _puerta puertaI, puertaD;
    _cube tabiqueDD, tabiqueID;
    _cube maletero;
    _cube techo;
    _chasis();
    void draw(_mode MODE, float angle_puerta=0, float angle_ruedas=0, float desplazamiento_asiento=1.5);
};

#endif // _FURGONETA_H
