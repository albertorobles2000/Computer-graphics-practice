#ifndef _PUERTA_H
#define _PUERTA_H

#include "cube.h"

class _puerta : public _object3D
{
public:
    _cube panel;
    _cube pilar1, pilar2;
    _cube superior;
    _puerta();
    void draw(_mode MODE);
};

#endif // _PUERTA_H
