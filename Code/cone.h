#ifndef _CONE_H
#define _CONE_H

#include "circular_sweeping.h"

class _cone:public _circular_sweeping
{
public:
    _cone( int rotaciones=30, int rotation_axis=1, float altura=1.0, float diametro=1.0);
    _cone(const string & File_name);
};

#endif // _CONE_H
