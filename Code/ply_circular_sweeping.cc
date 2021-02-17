#include "ply_circular_sweeping.h"
#include "file_ply_stl.h"

void _ply_circular_sweeping::Lee_Fichero(const string &File_name,vector<_vertex3f> & Vert,int & rotaciones, int & axis){

    _file_ply file;
    file.open(File_name);
    vector<float> Coordinates;
    vector<unsigned int> Parametros;
    file.read(Coordinates,Parametros);
    file.close();

    int factor;
    Vert.resize(Coordinates.size()/3);
    for(unsigned int i=0; i<Vert.size(); ++i){
        factor = 3*i;
        Vert[i] = _vertex3f(Coordinates[factor+0],Coordinates[factor+1],Coordinates[factor+2]);
    }
    rotaciones = Parametros[0];
    axis = Parametros[1];

}


