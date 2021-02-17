#ifndef _CIRCULAR_SWEEPING_H
#define _CIRCULAR_SWEEPING_H

#include <vector>
#include <math.h>
#include "vertex.h"
#include "object3d.h"

class _circular_sweeping:public _object3D
{
public:

    void rotate(vector<_vertex3f> & Perfil, int num_rotations, bool upper_cover, bool lower_cover,
                int rotation_axis, float grados=360.0, bool cerrar_objeto_h=true, bool cerrar_objeto_v=false);
    void Corregir_perfil(vector<_vertex3f> & Vert, int axis);
    void corrige_el_orden(vector<_vertex3f> & Perfil, int rotation_axis);
    bool is_upper_cover(vector<_vertex3f> & Perfil, int rotation_axis);
    bool is_lower_cover(vector<_vertex3f> & Perfil, int rotation_axis);
private:
    int rellena_vertices(vector<_vertex3f> & Perfil,
                          bool upper_cover, bool lower_cover, int num_rotations, int rotation_axis, float grados);
    void rellena_triangulos(int elementos_perfil,
                          int num_vertices, bool upper_cover, bool lower_cover, int num_rotations, float grados, bool cerrar_objeto_h,
                            bool cerrar_objeto_v);
};

#endif // _CIRCULAR_SWEEPING_H
