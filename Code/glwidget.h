/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <GL/glew.h>
#include <GL/gl.h>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <iostream>
#include <string>
#include <QAbstractButton>
#include <QImageReader>
#include "vertex.h"
#include "colors.h"
#include "axis.h"
#include "tetrahedron.h"
#include "cube.h"
#include "ply.h"
#include "cone.h"
#include "cylinder.h"
#include "sphere.h"
#include "coche.h"
#include "luz.h"
#include "chess_board.h"
#include "toroide.h"



namespace _gl_widget_ne {

  const float X_MIN=-.1;
  const float X_MAX=.1;
  const float Y_MIN=-.1;
  const float Y_MAX=.1;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;
  const float DEFAULT_DISTANCE=2;
  const float ANGLE_STEP=1;

  typedef enum {MODE_DRAW_POINT,MODE_DRAW_LINE,MODE_DRAW_FILL,MODE_DRAW_CHESS} _mode_draw;
  typedef enum {OBJECT_TETRAHEDRON,OBJECT_CUBE,OBJECT_CONE,
                OBJECT_CYLINDER,OBJECT_SPHERE,OBJECT_PLY,OBJECT_JERAQUICO,
                OBJECT_CHESS_BOARD, OBJECT_TOROIDE} _object;
}

class _window;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _gl_widget : public QOpenGLWidget
{
Q_OBJECT
public:
  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();

  void draw_axis();
  void draw_objects();

protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;

  void crearLuces();
  void activarLuces();
  void desactivarLuces();
  void rotarLuz(int numLuz, int eje, float alpha);

  void crearTexturas();
  void actualizarMaterial();

  void mousePressEvent(QMouseEvent *evento) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent *evento) Q_DECL_OVERRIDE;
  void wheelEvent(QWheelEvent *evento) Q_DECL_OVERRIDE;
  //void pick();

public slots:
  void puntosPulsado(int x);
  void lineasPulsado(int x);
  void fillPulsado(int x);
  void chessPulsado(int x);
  void FlatShadingPulsado(int x);
  void SmoothShadingPulsado(int x);
  void TexturaPulsado(int x);
  void TexturaFlatShadingPulsado(int x);
  void TexturaSmoothShadingPulsado(int x);


  void Luz0Pulsada(int x);
  void Luz1Pulsada(int x);

  void cambiarMaterialPulsado();

  void cambiarProyeccionPulsado();

  void MoverLuz1Pulsada(int x);
  void MoverLuz1SobreX();
  void MoverLuz1SobreY();
  void MoverLuz1SobreZ();

  void tetraedroPulsado();
  void cuboPulsado();
  void conoPulsado();
  void cilindroPulsado();
  void esferaPulsado();
  void plyPulsado();
  void jerarquicoPulsado();
  void chessBoardPulsado();
  void toroidePulsado();


  void puertaAutomaticPulsado(int x);
  void ruedasAutomaticPulsado(int x);
  void asientoAutomaticPulsado(int x);

  void puertaManual(int x);
  void ruedasManual(int x);
  void asientoManual(int x);

  void activarAsiento(float incremento=0.5);
  void activarRuedas(float incremento=2.0);
  void activarPuerta(float incremento=2.0);

  void timerActivado();

private:
  _window *Window;

  QPoint posRaton;
  int Selection_position_x, Selection_position_y;

  _axis Axis;

  _tetrahedron Tetrahedron;
  _cube Cube;

  //_cone(rotaciones,axis,altura,diametro)
  _cone Cone = _cone(30,1,1.0,1.0);
  //_cone Cone = _cone("ply_models/cone.ply");

  //_cylinder(rotaciones,axis,particiones,altura,diametro)
  _cylinder Cylinder= _cylinder(50,1,30,1.0,1.0);
  //_cylinder Cylinder = _cylinder("ply_models/cylinder.ply");

  //_sphere(rotaciones,axis,Size,Particiones_perfil)
  _sphere Sphere = _sphere(60,1,1.0,60);

  //string string_ply = "ply_models/big_dodge.ply";
  string string_ply = "ply_models/beethoven.ply";
  //string string_ply = "ply_models/ant.ply";
  //string string_ply = "ply_models/armadillo.ply";
  //string string_ply = "ply_models/big_porsche.ply";
  //string string_ply = "ply_models/cow.ply";


  _ply Ply = _ply(string_ply);

  _coche objeto;
  _chess_board ChessBoard;
  _toroide Toroide;

  _gl_widget_ne::_object Object;
//Modos
  bool Draw_point;
  bool Draw_line;
  bool Draw_fill;
  bool Draw_chess;
  bool Draw_flat_shading;
  bool Draw_smooth_shading;
  bool Draw_textura;
  bool Draw_textura_flat_shading;
  bool Draw_textura_smooth_shading;

  bool imagenCargada=false;

  bool proyeccionParalela=false;

//Luces
  _Luz Luz;

  bool luz0 = false;
  bool luz1 = false;

  bool MoveLuz = false;
  int rotarLuzSobreEje = 1;
  int numRotation=0;
  GLfloat PosicionLuz[4];

  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance;


//Movimientos jerarquico
  float angle_puerta=0;
  float angle_ruedas=0;
  float traslacion_coche=0;
  float desplazamiento_asiento=1.5;

  float incrementoPuerta=2.0;
  float incrementoRuedas=5.0;
  float incrementoAsiento=0.5;

  bool MovimientoRuedasAutomatico = false;
  bool MovimientoPuertaAutomatico = false;
  bool MovimientoAsientoAutomatico = false;

  bool estadoPuerta;
  bool estadoAceleracion = true;
  bool estadoAsiento;

//Materiales
  int contadorMaterial=0;

};

#endif
