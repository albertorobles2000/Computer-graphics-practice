/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "basic_object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

typedef enum {POINT_MODE,LINE_MODE,FILL_MODE,CHESS_MODE, FLAT_SHADING_MODE,
              SMOOTH_SHADING_MODE, TEXTURA_MODE,
             TEXTURA_FLAT_SHADING_MODE, TEXTURA_SMOOTH_SHADING_MODE} _mode;

class _object3D:public _basic_object3D
{
  public:
  vector<_vertex3ui> Triangles;

  vector<_vertex3f> NormalVertices;
  vector<_vertex3f> NormalTriangulos;

  vector<_vertex2f>Textura;

  //bool triangleSelected = false;
  //int triangle = -1;

  void draw_line();
  void draw_fill();
  void draw_chess();
  void draw(_mode MODE);
  void draw_lighting_flat_shading();
  void draw_lighting_smooth_shading();
  void draw_textura();
  void draw_textura_flat_shading();
  void draw_textura_smooth_shading();
  //void draw_for_selection();

  //void setTrianguloSeleccionado(int triangulo);

  void calcularNormalesTriangulos();
  void calcularNormalesVertices();

};

#endif // OBJECT3D_H
