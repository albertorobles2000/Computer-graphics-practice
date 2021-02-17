#ifndef _PERSONA_H
#define _PERSONA_H

#include "cylinder.h"

class _rueda : public _object3D
{
public:
    _cylinder neumatico, llanta;
    _cylinder radio1, radio2, radio3, radio4;
    _rueda();
    void draw(_mode MODE);
};

#endif // _PERSONA_H
