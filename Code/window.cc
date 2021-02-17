/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include <QApplication>
#include <QAction>
#include <QMenuBar>
#include <QFrame>
#include <QCheckBox>
#include <QLabel>
#include <QTimer>
#include <QGroupBox>
#include <QRadioButton>
#include <QSlider>
#include <QPushButton>

#include "window.h"
#include "glwidget.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_window::_window()
{

  QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);

  QWidget *Central_widget = new QWidget(this);
  setCentralWidget(Central_widget);
  setWindowTitle(tr("Practica 1"));
  resize(800,800);

  GL_widget = new _gl_widget(this);
  GL_widget->setSizePolicy(Q);
  GL_widget->setMinimumSize(600,600);
  QTabWidget * pestanias = new QTabWidget;
  pestanias->setMaximumWidth(400);
  pestanias->setMinimumWidth(200);
  QWidget * modos_widget = new QWidget;
  QWidget * objetos_widget = new QWidget;
  QWidget * camara_widget = new QWidget;

  pestanias->addTab(modos_widget,"Modos");
  pestanias->addTab(objetos_widget,"Objetos");
  pestanias->addTab(camara_widget,"Camaras");

  //MODOS **************************************************
  QGridLayout * vBox_modos = new QGridLayout;
  QVBoxLayout * modos_layout = new QVBoxLayout;

  modos_widget->setLayout(vBox_modos);

  QCheckBox * puntos_cb = new QCheckBox(tr("Puntos"));
  QCheckBox * lineas_cb = new QCheckBox(tr("Lineas"));
  QCheckBox * fill_cb = new QCheckBox(tr("Fill"));
  QCheckBox * chess_cb = new QCheckBox(tr("Chess"));
  QCheckBox * flat_shading_cb = new QCheckBox(tr("Flat shading"));
  QCheckBox * smooth_shading_cb = new QCheckBox(tr("Gouraud shading"));
  QCheckBox * textura_cb = new QCheckBox(tr("Textura"));
  QCheckBox * textura_flat_cb = new QCheckBox(tr("Textura Flat"));
  QCheckBox * textura_smooth_cb = new QCheckBox(tr("Textura Gouraud"));

  lineas_cb->setChecked(true);

  modos_layout->addWidget(puntos_cb);
  modos_layout->addWidget(lineas_cb);
  modos_layout->addWidget(fill_cb);
  modos_layout->addWidget(chess_cb);
  modos_layout->addWidget(flat_shading_cb);
  modos_layout->addWidget(smooth_shading_cb);
  modos_layout->addWidget(textura_cb);
  modos_layout->addWidget(textura_flat_cb);
  modos_layout->addWidget(textura_smooth_cb);

  connect(puntos_cb,SIGNAL(stateChanged(int)),GL_widget,SLOT(puntosPulsado(int)));
  connect(lineas_cb,SIGNAL(stateChanged(int)),GL_widget,SLOT(lineasPulsado(int)));
  connect(fill_cb,SIGNAL(stateChanged(int)),GL_widget,SLOT(fillPulsado(int)));
  connect(chess_cb, SIGNAL(stateChanged(int)),GL_widget, SLOT(chessPulsado(int)));
  connect(flat_shading_cb,SIGNAL(stateChanged(int)),GL_widget,SLOT(FlatShadingPulsado(int)));
  connect(smooth_shading_cb,SIGNAL(stateChanged(int)),GL_widget,SLOT(SmoothShadingPulsado(int)));
  connect(textura_cb,SIGNAL(stateChanged(int)),GL_widget,SLOT(TexturaPulsado(int)));
  connect(textura_flat_cb,SIGNAL(stateChanged(int)),GL_widget,SLOT(TexturaFlatShadingPulsado(int)));
  connect(textura_smooth_cb,SIGNAL(stateChanged(int)),GL_widget,SLOT(TexturaSmoothShadingPulsado(int)));


  QGroupBox * widget_modos = new QGroupBox("Modos");
  widget_modos->setLayout(modos_layout);
  vBox_modos->addWidget(widget_modos,0,0);


  // //////////////////////////////////////////
  QGroupBox *groupLight = new QGroupBox(tr("Lights"));
  vBox_modos->addWidget(groupLight,1,0);
  QCheckBox * Luz_1_bt = new QCheckBox(tr("Luz 0"));
  QCheckBox * Luz_2_bt = new QCheckBox(tr("Luz 1"));

  QVBoxLayout *vboxLight = new QVBoxLayout;
      vboxLight->addWidget(Luz_1_bt);
      vboxLight->addWidget(Luz_2_bt);

      vboxLight->addStretch(1);
      groupLight->setLayout(vboxLight);

      connect(Luz_1_bt, SIGNAL(stateChanged(int)), GL_widget, SLOT(Luz0Pulsada(int)));
      connect(Luz_2_bt, SIGNAL(stateChanged(int)), GL_widget, SLOT(Luz1Pulsada(int)));

// Movimiento Luz
      QGroupBox *groupLightMove = new QGroupBox(tr("Light movement"));
      vBox_modos->addWidget(groupLightMove,2,0);
      QCheckBox * Move_luz_1_bt = new QCheckBox(tr("Activar Move"));
      QRadioButton * Move_X = new QRadioButton(tr("X"));
      QRadioButton * Move_Y = new QRadioButton(tr("Y"));
      QRadioButton * Move_Z = new QRadioButton(tr("Z"));

      Move_Y->setChecked(true);

      QVBoxLayout *vboxLightMove = new QVBoxLayout;
          vboxLightMove->addWidget(Move_luz_1_bt);
          vboxLightMove->addWidget(Move_X);
          vboxLightMove->addWidget(Move_Y);
          vboxLightMove->addWidget(Move_Z);


      vboxLightMove->addStretch(1);
      groupLightMove->setLayout(vboxLightMove);

      connect(Move_luz_1_bt, SIGNAL(stateChanged(int)), GL_widget, SLOT(MoverLuz1Pulsada(int)));
      connect(Move_X, SIGNAL(clicked()), GL_widget, SLOT(MoverLuz1SobreX()));
      connect(Move_Y, SIGNAL(clicked()), GL_widget, SLOT(MoverLuz1SobreY()));
      connect(Move_Z, SIGNAL(clicked()), GL_widget, SLOT(MoverLuz1SobreZ()));


      //Create the button
      QGroupBox *groupMateriales = new QGroupBox(tr("Materials"));
      vBox_modos->addWidget(groupMateriales,3,0);
      QPushButton *botonCambiarMaterial = new QPushButton("Change", this);
      //set size and location of the button
      botonCambiarMaterial->setGeometry(QRect( QPoint(100, 100),QSize(50,20)));
      QVBoxLayout *vboxMaterials = new QVBoxLayout;
          vboxMaterials->addWidget(botonCambiarMaterial);


      vboxMaterials->addStretch(1);
      groupMateriales->setLayout(vboxMaterials);


      connect(botonCambiarMaterial, SIGNAL (released()),GL_widget, SLOT (cambiarMaterialPulsado()));

    //OBJETOS **************************************************

  QGridLayout *grid = new QGridLayout;

   //SELECCION OBJETO
  QGroupBox *groupBox = new QGroupBox(tr("Objetos"));
  grid->addWidget(groupBox,0,0);
  QRadioButton * tetraedro_bt = new QRadioButton(tr("Tetraedro"));
  QRadioButton * cubo_bt = new QRadioButton(tr("Cubo"));
  QRadioButton * cono_bt = new QRadioButton(tr("Cono"));
  QRadioButton * cilindro_bt = new QRadioButton(tr("Cilindro"));
  QRadioButton * esfera_bt = new QRadioButton(tr("Esfera"));
  QRadioButton * ply_bt = new QRadioButton(tr("Ply"));
  QRadioButton * jerarquico_bt = new QRadioButton(tr("Jerarquico"));
  QRadioButton * chess_board_bt = new QRadioButton(tr("Chess Board"));
  QRadioButton * toroide_bt = new QRadioButton(tr("Toroide"));
  tetraedro_bt->setChecked(true);
  QVBoxLayout *vbox = new QVBoxLayout;
      vbox->addWidget(tetraedro_bt);
      vbox->addWidget(cubo_bt);
      vbox->addWidget(cono_bt);
      vbox->addWidget(cilindro_bt);
      vbox->addWidget(esfera_bt);
      vbox->addWidget(ply_bt);
      vbox->addWidget(jerarquico_bt);
      vbox->addWidget(chess_board_bt);
      vbox->addWidget(toroide_bt);




      vbox->addStretch(1);
      groupBox->setLayout(vbox);


   connect(tetraedro_bt, SIGNAL(clicked()), GL_widget, SLOT(tetraedroPulsado()));
   connect(cubo_bt, SIGNAL(clicked()), GL_widget, SLOT(cuboPulsado()));
   connect(cono_bt, SIGNAL(clicked()), GL_widget, SLOT(conoPulsado()));
   connect(cilindro_bt, SIGNAL(clicked()), GL_widget, SLOT(cilindroPulsado()));
   connect(esfera_bt, SIGNAL(clicked()), GL_widget, SLOT(esferaPulsado()));
   connect(ply_bt, SIGNAL(clicked()), GL_widget, SLOT(plyPulsado()));
   connect(jerarquico_bt, SIGNAL(clicked()), GL_widget, SLOT(jerarquicoPulsado()));
   connect(chess_board_bt, SIGNAL(clicked()), GL_widget, SLOT(chessBoardPulsado()));
   connect(toroide_bt, SIGNAL(clicked()), GL_widget, SLOT(toroidePulsado()));

   //SELECCION MOVIMIENTO AUTOMATICO
   QGroupBox *groupBox1 = new QGroupBox(tr("Movimiento automatico"));
   grid->addWidget(groupBox1,1,0);
   QCheckBox * puerta_bt = new QCheckBox(tr("Puerta"));
   QCheckBox * ruedas_bt = new QCheckBox(tr("Acelerar"));
   QCheckBox * asiento_bt = new QCheckBox(tr("Asiento"));

   QVBoxLayout *vbox1 = new QVBoxLayout;
       vbox1->addWidget(puerta_bt);
       vbox1->addWidget(ruedas_bt);
       vbox1->addWidget(asiento_bt);

       vbox1->addStretch(1);
       groupBox1->setLayout(vbox1);

       objetos_widget->setLayout(grid);

    connect(puerta_bt, SIGNAL(stateChanged(int)), GL_widget, SLOT(puertaAutomaticPulsado(int)));
    connect(ruedas_bt, SIGNAL(stateChanged(int)), GL_widget, SLOT(ruedasAutomaticPulsado(int)));
    connect(asiento_bt, SIGNAL(stateChanged(int)), GL_widget, SLOT(asientoAutomaticPulsado(int)));

    ////////////////////////////////////
    /// \brief groupBox1
    ///

    //QVBoxLayout *vbox_modos = new QVBoxLayout;
    QGridLayout *sliders_layout = new QGridLayout;
    QGroupBox *groupBox2 = new QGroupBox("Movimiento manual");

     grid->addWidget(groupBox2,2,0);

     groupBox2->setLayout(sliders_layout);

   //vbox_modos->addStretch();
   sliders_layout->addWidget(new QLabel("Puerta"));
   QSlider * slider_puerta = new QSlider(Qt::Horizontal);
   sliders_layout->addWidget(slider_puerta);
   sliders_layout->addWidget(new QLabel("Ruedas"));
   QSlider * slider_ruedas = new QSlider(Qt::Horizontal);
   sliders_layout->addWidget(slider_ruedas);
   sliders_layout->addWidget(new QLabel("Asiento"));
   QSlider * slider_asiento = new QSlider(Qt::Horizontal);
   sliders_layout->addWidget(slider_asiento);


   connect(slider_puerta,SIGNAL(sliderMoved(int)),GL_widget,SLOT(puertaManual(int)));
   connect(slider_ruedas,SIGNAL(sliderMoved(int)),GL_widget,SLOT(ruedasManual(int)));
   connect(slider_asiento,SIGNAL(sliderMoved(int)),GL_widget,SLOT(asientoManual(int)));


//CAMARAS

   QGridLayout *gridCamaras = new QGridLayout;

   camara_widget->setLayout(gridCamaras);
    //SELECCION PROYECCION
   QGroupBox *groupBoxProyeccion = new QGroupBox(tr("Proyecciones"));
   gridCamaras->addWidget(groupBoxProyeccion,0,0);


   QPushButton *botonCambiarProyeccion = new QPushButton("Change", this);
   //set size and location of the button
   botonCambiarProyeccion->setGeometry(QRect( QPoint(100, 100),QSize(50,20)));
   QVBoxLayout *vboxProyecciones = new QVBoxLayout;
       vboxProyecciones->addWidget(botonCambiarProyeccion);

   vboxProyecciones->addStretch(1);
   groupBoxProyeccion->setLayout(vboxProyecciones);

   connect(botonCambiarProyeccion, SIGNAL (released()),GL_widget, SLOT (cambiarProyeccionPulsado()));



  QTimer *timer = new QTimer;
  timer->start(100);
  connect(timer,SIGNAL(timeout()), GL_widget, SLOT(timerActivado()));

  QHBoxLayout * horizontal_layout = new QHBoxLayout;
  horizontal_layout->addWidget(GL_widget);
  horizontal_layout->addWidget(pestanias);

  Central_widget->setLayout(horizontal_layout) ;

}
