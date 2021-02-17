#ifndef _ASIENTO_H
#define _ASIENTO_H

#include "cylinder.h"
#include "cube.h"

class _asiento : public _object3D
{
public:
    _cube sujeccion;
    _cube base;
    _cube respaldo;
    _cylinder reposa_cabezas;
    _cylinder sujeta_repos_1, sujeta_repos_2;
    _asiento();
    void draw(_mode MODE, float angle_asiento=0);
};

#endif // _ASIENTO_H
