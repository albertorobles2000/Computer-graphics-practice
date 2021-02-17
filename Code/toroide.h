#ifndef _TOROIDE_H
#define _TOROIDE_H

#include "circular_sweeping.h"
class _toroide:public _circular_sweeping
{
public:
    _toroide(int rotaciones = 70, int rotation_axis=1,float Size=1.0, int Particiones_perfil = 50);
};

#endif // _TOROIDE_H
