#include "cone.h"
#include "circular_sweeping.h"
#include "ply_circular_sweeping.h"

_cone::_cone( int rotaciones, int rotation_axis, float altura, float diametro)
{
    vector<_vertex3f> Vert;
    Vert.resize(3);

    Vert[0] = _vertex3f(0,altura/2,0);
    Vert[1] = _vertex3f(diametro/2,-altura/2,0);
    Vert[2] = _vertex3f(0,-altura/2,0);

    Corregir_perfil(Vert,rotation_axis);
    bool upper_cover = is_upper_cover(Vert,rotation_axis);
    bool lower_cover = is_lower_cover(Vert,rotation_axis);
    rotate(Vert,rotaciones, upper_cover, lower_cover, rotation_axis,360);

    calcularNormalesTriangulos();
    calcularNormalesVertices();
}

_cone::_cone(const string & File_name){
    //const string File_name = "C:/Users/alber/OneDrive/Escritorio/IG/ply_models/cone.ply";
    vector<_vertex3f> Vert;
    int rotaciones;
    int axis;
    _ply_circular_sweeping lector_ply;

    lector_ply.Lee_Fichero(File_name,Vert,rotaciones, axis);
    Corregir_perfil(Vert,axis);
    bool upper_cover = is_upper_cover(Vert,axis);
    bool lower_cover = is_lower_cover(Vert,axis);
    rotate(Vert,rotaciones, upper_cover, lower_cover, axis);

    calcularNormalesTriangulos();
    calcularNormalesVertices();
}


