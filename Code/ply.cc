#include "ply.h"
#include "file_ply_stl.h"

_ply::_ply(const string &File_name)
{
    _file_ply file;
    file.open(File_name);
    vector<float> Coordinates;
    vector<unsigned int> Position;
    file.read(Coordinates,Position);
    file.close();

    int factor;
    Vertices.resize(Coordinates.size()/3);
    for(unsigned int i=0; i<Vertices.size(); ++i){
        factor = 3*i;
        Vertices[i] = _vertex3f(Coordinates[factor+0],Coordinates[factor+1],Coordinates[factor+2]);
    }

    Triangles.resize(Position.size()/3);
    for(unsigned int i=0; i<Triangles.size(); ++i){
        factor = 3*i;
        Triangles[i] = _vertex3ui(Position[factor+0],Position[factor+1],Position[factor+2]);
    }

    calcularNormalesTriangulos();
    calcularNormalesVertices();
}
