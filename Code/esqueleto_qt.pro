HEADERS += \
  asiento.h \
  chasis.h \
  chess_board.h \
  circular_sweeping.h \
  coche.h \
  colors.h \
  basic_object3d.h \
  cone.h \
  cube.h \
  cylinder.h \
  eje_ruedas.h \
  file_ply_stl.h \
  luz.h \
  object3d.h \
  axis.h \
  pared_ventana.h \
  plataforma.h \
  ply.h \
  ply_circular_sweeping.h \
  puerta.h \
  rueda.h \
  sphere.h \
  tetrahedron.h \
  glwidget.h \
  toroide.h \
  window.h

SOURCES += \
  asiento.cc \
  basic_object3d.cc \
  chasis.cc \
  chess_board.cc \
  circular_sweeping.cc \
  coche.cc \
  cone.cc \
  cube.cc \
  cylinder.cc \
  eje_ruedas.cc \
  file_ply_stl.cc \
  luz.cc \
  object3d.cc \
  axis.cc \
  pared_ventana.cc \
  plataforma.cc \
  ply.cc \
  ply_circular_sweeping.cc \
  puerta.cc \
  rueda.cc \
  sphere.cc \
  tetrahedron.cc \
  main.cc \
  glwidget.cc \
  toroide.cc \
  window.cc

#Windows
LIBS += -L/usr/X11R6/lib64 -lopengl32
#Linux
#LIBS += -L/usr/X11R6/lib64 -lGL



CONFIG += c++11
QT += widgets
