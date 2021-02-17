#ifndef PLY_H
#define PLY_H

#include <string>
#include "object3d.h"

class _ply:public _object3D
{
public:
    _ply(const string &File_name);
};

#endif // PLY_H
