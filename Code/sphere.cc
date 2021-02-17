#include "sphere.h"
#include "circular_sweeping.h"

_sphere::_sphere( int rotaciones, int rotation_axis, float Size, int Particiones_perfil)
{
    vector<_vertex3f> Vert;
    Vert.resize(Particiones_perfil+1);

    float incremento = Size/Particiones_perfil;
    float radio = Size/2;
    for(int i=0; i<Particiones_perfil+1; i++){
        Vert[i]._1 = (-(Size/2)+i*incremento);//y
        Vert[i]._0 = sqrt(pow(radio,2)-pow(Vert[i]._1,2));//x
        Vert[i]._2 = 0;//z
    }
    Corregir_perfil(Vert,rotation_axis);
    bool upper_cover = is_upper_cover(Vert,rotation_axis);
    bool lower_cover = is_lower_cover(Vert,rotation_axis);
    rotate(Vert,rotaciones, upper_cover, lower_cover, rotation_axis,360,true);

    calcularNormalesTriangulos(rotaciones,Particiones_perfil);
    calcularNormalesVertices();

    //calcularTexturas();
}

void _sphere::calcularNormalesTriangulos(int rotaciones, int perfil){
    int triangulos_dobles = rotaciones * (perfil-2);
    NormalTriangulos.resize(Triangles.size());
    for(int i=0; i<triangulos_dobles; i+=2){
        _vertex3f primerVector = Vertices.at(Triangles[i]._0) + Vertices.at(Triangles[i]._2);
        _vertex3f normal = primerVector / 2.0;
        normal.normalize();
        NormalTriangulos[i] = normal;
        NormalTriangulos[i+1] = normal;
    }
    for(int i=triangulos_dobles; i<(int)Triangles.size(); i++ ){
        _vertex3f primerVector = Vertices.at(Triangles[i]._0) - Vertices.at(Triangles[i]._1);
        _vertex3f segundoVector = Vertices.at(Triangles[i]._1) - Vertices.at(Triangles[i]._2);
        _vertex3f normal = primerVector.cross_product(segundoVector);
        normal.normalize();
        NormalTriangulos[i] = normal;
    }


}

void _sphere::calcularNormalesVertices(){
    NormalVertices.resize(Vertices.size());
    for(int i=0; i<(int)NormalVertices.size();++i){
        NormalVertices[i] = Vertices[i];
        NormalVertices[i].normalize();
    }


}

/*void _sphere::calcularTexturas(){
    Textura.resize(Vertices.size());
    for(int i=0; i<(int)Vertices.size(); i++){
        float alpha = atan2(Vertices[i].z, Vertices[i].x);
        float beta = atan2(Vertices[i].y, sqrt(pow(Vertices[i].x, 2.) + pow(Vertices[i].z, 2.)));
        Textura[i] = _vertex2f(1.0/2.0 + alpha / (2.0f * M_PI), 1.0/2.0 + beta / (M_PI));
    }
}
*/
