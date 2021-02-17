#include "toroide.h"

_toroide::_toroide(int rotaciones, int rotation_axis,float Size, int Particiones_perfil)
{
    vector<_vertex3f> Vert;
    Vert.resize(Particiones_perfil);

    float incremento = Size/(Particiones_perfil/2);
    float radio = Size/2;
    for(int i=0; i<Particiones_perfil; i++){
        if(i<Particiones_perfil/2){
            Vert[i]._0 = (-(Size/2)+i*incremento);//y
            Vert[i]._1 = sqrt(pow(radio,2)-pow(Vert[i]._0,2));//x
            Vert[i]._2 = 0;//z

         }
         else{
            Vert[i]._0 = ((Size/2)-(i-(Particiones_perfil/2))*incremento);//y
            Vert[i]._1 = -sqrt(pow(radio,2)-pow(Vert[i]._0,2));//x
            Vert[i]._2 = 0;//z
        }
    }

    for(int i=0; i<(int)Vert.size(); ++i){
        Vert[i]._0 = Vert[i]._0+Size;
    }

    Corregir_perfil(Vert,rotation_axis);
    rotate(Vert,rotaciones, false, false, rotation_axis,360,true,true);

    calcularNormalesTriangulos();
    calcularNormalesVertices();

}
