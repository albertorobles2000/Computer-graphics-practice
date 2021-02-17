#ifndef _TABLERO_H
#define _TABLERO_H

#include "object3d.h"

class _chess_board:public _object3D
{
public:
    _chess_board(float Size=1.0);
    void calcularTexturas();
};

#endif // _TABLERO_H
