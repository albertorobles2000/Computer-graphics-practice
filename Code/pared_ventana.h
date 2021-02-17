#ifndef _PARED_VENTANA_H
#define _PARED_VENTANA_H

#include "cube.h"

class _pared_ventana : public _object3D
{
public:
    _cube tabiqueIT;
    _cube panelIS, panelII, panelIC;
    _pared_ventana();
    void draw(_mode MODE);
};

#endif // _PARED_VENTANA_H
