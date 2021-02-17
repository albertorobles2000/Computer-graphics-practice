#ifndef _CYLINDER_H
#define _CYLINDER_H

#include "circular_sweeping.h"
class _cylinder: public _circular_sweeping
{
public:
    _cylinder(int rotaciones=30, int rotation_axis=1,int particiones=5,float altura=1.0, float diametro=1.0);
    _cylinder(const string File_name);

};

#endif // _CYLINDER_H
