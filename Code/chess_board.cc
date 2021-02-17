#include "chess_board.h"

_chess_board::_chess_board(float Size)
{
    Vertices.resize(4);
      Vertices[0]=_vertex3f(-Size/2,-Size/2,0);
      Vertices[1]=_vertex3f(+Size/2,-Size/2,0);
      Vertices[2]=_vertex3f(-Size/2,+Size/2,0);
      Vertices[3]=_vertex3f(+Size/2,+Size/2,0);

      Triangles.resize(2);
      Triangles[0]=_vertex3ui(0,1,2);
      Triangles[1]=_vertex3ui(3,2,1);

      calcularTexturas();

      calcularNormalesTriangulos();
      calcularNormalesVertices();
}

void _chess_board::calcularTexturas(){
    Textura.resize(4);
    Textura[0]=_vertex2f(0.0f, 0.0f);//Abajo Izquierda
    Textura[1]=_vertex2f(1.0f, 0.0f);//Abajo Derecha
    Textura[2]=_vertex2f(0.0f, 1.0f);//Arriba Izquierda
    Textura[3]=_vertex2f(1.0f, 1.0f);//Arriba Derecha
}
