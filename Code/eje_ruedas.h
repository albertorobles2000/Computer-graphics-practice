#ifndef _EJE_RUEDAS_H
#define _EJE_RUEDAS_H

#include "rueda.h"
#include "cylinder.h"

class _eje_ruedas : public _object3D
{
public:

    _rueda rueda1, rueda2;
    _cylinder eje_central;
    _eje_ruedas();
    void draw(_mode MODE, float angle_ruedas=0);
};

#endif // _EJE_RUEDAS_H
