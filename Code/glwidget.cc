/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "glwidget.h"
#include "window.h"

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;




/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
  Object = _object::OBJECT_TETRAHEDRON;
}


/*****************************************************************************//**
 * Evento tecla pulsada
 *
 *
 *
 *****************************************************************************/

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{

  switch(Keyevent->key()){
  case Qt::Key_1:Object=OBJECT_TETRAHEDRON;break;
  case Qt::Key_2:Object=OBJECT_CUBE;break;
  case Qt::Key_3:Object=OBJECT_CONE;break;
  case Qt::Key_4:Object=OBJECT_CYLINDER;break;
  case Qt::Key_5:Object=OBJECT_SPHERE;break;
  case Qt::Key_6:Object=OBJECT_PLY;break;
  case Qt::Key_7:Object=OBJECT_JERAQUICO;break;
  case Qt::Key_8:Object=OBJECT_CHESS_BOARD;break;
  case Qt::Key_9:Object=OBJECT_TOROIDE;break;


  case Qt::Key_P:Draw_point=!Draw_point;break;
  case Qt::Key_L:Draw_line=!Draw_line;break;
  case Qt::Key_F:Draw_fill=!Draw_fill;break;
  case Qt::Key_C:Draw_chess=!Draw_chess;break;
  case Qt::Key_F1:Draw_fill=!Draw_fill;break;
  case Qt::Key_F2:Draw_chess=!Draw_chess;break;
  case Qt::Key_F3:Draw_flat_shading=!Draw_flat_shading;break;
  case Qt::Key_F4:Draw_smooth_shading=!Draw_smooth_shading;break;
  case Qt::Key_F5:Draw_textura=!Draw_textura;break;
  case Qt::Key_F6:Draw_textura_flat_shading=!Draw_textura_flat_shading;break;
  case Qt::Key_F7:Draw_textura_smooth_shading=!Draw_textura_smooth_shading;break;    

  case Qt::Key_Q:angle_puerta+=incrementoPuerta;break;
  case Qt::Key_W:angle_puerta-=incrementoPuerta;break;
  case Qt::Key_S:angle_ruedas+=incrementoRuedas;
                 traslacion_coche+=incrementoRuedas*0.02;break;
  case Qt::Key_D:angle_ruedas-=incrementoRuedas;
                 traslacion_coche-=incrementoRuedas*0.02;break;
  case Qt::Key_Z:desplazamiento_asiento+=incrementoAsiento;break;
  case Qt::Key_X:desplazamiento_asiento-=incrementoAsiento;break;

  case Qt::Key_E:incrementoPuerta++;break;
  case Qt::Key_R:incrementoPuerta--;break;
  case Qt::Key_T:incrementoRuedas++;break;
  case Qt::Key_Y:incrementoRuedas--;break;
  case Qt::Key_U:incrementoAsiento+=0.5;break;
  case Qt::Key_I:incrementoAsiento-=0.5;break;

  case Qt::Key_A:MovimientoAsientoAutomatico=!MovimientoAsientoAutomatico;
      MovimientoPuertaAutomatico=MovimientoAsientoAutomatico;
      MovimientoRuedasAutomatico=MovimientoAsientoAutomatico;
      MoveLuz=!MoveLuz;
      break;




  case Qt::Key_J:luz0=!luz0;break;
  case Qt::Key_K:luz1=!luz1;break;

  case Qt::Key_M:cambiarMaterialPulsado();break;


  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
  case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
  case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
  case Qt::Key_PageUp:Observer_distance*=1.2;break;
  case Qt::Key_PageDown:Observer_distance/=1.2;break;
    }
  update();
}


/*****************************************************************************//**
 * Limpiar ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}



/*****************************************************************************//**
 * Funcion para definir la transformación de proyeccion
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  // Front_plane>0  Back_plane>PlanoDelantero)
  //glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);

    // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
    // Front_plane>0  Back_plane>PlanoDelantero)

    if(!proyeccionParalela){
      //proyeccion perspectiva
      glFrustum(X_MIN, X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
    }else{
      float multiplicador = Observer_distance*6.5;
      //Proyeccion paralela
      glOrtho(X_MIN*multiplicador, X_MAX*multiplicador ,Y_MIN*multiplicador ,Y_MAX*multiplicador, FRONT_PLANE_PERSPECTIVE, BACK_PLANE_PERSPECTIVE);
    }
}



/*****************************************************************************//**
 * Funcion para definir la transformación de vista (posicionar la camara)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}


/*****************************************************************************//**
 * Funcion que dibuja los objetos
 *
 *
 *
 *****************************************************************************/

void _gl_widget::draw_objects()
{

  Axis.draw_line();

  if (Draw_point){
    glPointSize(5);
    glColor3fv((GLfloat *) &BLACK);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_point();break;
    case OBJECT_CUBE:Cube.draw_point();break;
    case OBJECT_CONE:Cone.draw_point();break;
    case OBJECT_CYLINDER:Cylinder.draw_point();break;
    case OBJECT_SPHERE:Sphere.draw_point();break;
    case OBJECT_PLY:Ply.draw_point();break;
    case OBJECT_JERAQUICO:objeto.draw(_mode::POINT_MODE,traslacion_coche,angle_puerta,angle_ruedas,desplazamiento_asiento);break;
    case OBJECT_CHESS_BOARD:ChessBoard.draw_point();break;
    case OBJECT_TOROIDE:Toroide.draw_point();break;
    default:break;
    }
  }

  if (Draw_line){
    glLineWidth(3);
    glColor3fv((GLfloat *) &MAGENTA);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_line();break;
    case OBJECT_CUBE:Cube.draw_line();break;
    case OBJECT_CONE:Cone.draw_line();break;
    case OBJECT_CYLINDER:Cylinder.draw_line();break;
    case OBJECT_SPHERE:Sphere.draw_line();break;
    case OBJECT_PLY:Ply.draw_line();break;
    case OBJECT_JERAQUICO:objeto.draw(_mode::LINE_MODE,traslacion_coche,angle_puerta,angle_ruedas,desplazamiento_asiento);break;
    case OBJECT_CHESS_BOARD:ChessBoard.draw_line();break;
    case OBJECT_TOROIDE:Toroide.draw_line();break;
    default:break;
    }
  }

  if (Draw_fill){
    glColor3fv((GLfloat *) &BLUE);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_fill();break;
    case OBJECT_CUBE:Cube.draw_fill();break;
    case OBJECT_CONE:Cone.draw_fill();break;
    case OBJECT_CYLINDER:Cylinder.draw_fill();break;
    case OBJECT_SPHERE:Sphere.draw_fill();break;
    case OBJECT_PLY:Ply.draw_fill();break;
    case OBJECT_JERAQUICO:objeto.draw(_mode::FILL_MODE,traslacion_coche,angle_puerta,angle_ruedas,desplazamiento_asiento);break;
    case OBJECT_CHESS_BOARD:ChessBoard.draw_fill();break;
    case OBJECT_TOROIDE:Toroide.draw_fill();break;
    default:break;
    }
  }

  if (Draw_chess){

    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_chess();break;
    case OBJECT_CUBE:Cube.draw_chess();break;
    case OBJECT_CONE:Cone.draw_chess();break;
    case OBJECT_CYLINDER:Cylinder.draw_chess();break;
    case OBJECT_SPHERE:Sphere.draw_chess();break;
    case OBJECT_PLY:Ply.draw_chess();break;
    case OBJECT_JERAQUICO:objeto.draw(_mode::CHESS_MODE,traslacion_coche,angle_puerta,angle_ruedas,desplazamiento_asiento);break;
    case OBJECT_CHESS_BOARD:ChessBoard.draw_chess();break;
    case OBJECT_TOROIDE:Toroide.draw_chess();break;
    default:break;
    }
  }

   if (Draw_flat_shading || Draw_smooth_shading){
     activarLuces();
     actualizarMaterial();
     if(Draw_flat_shading){
         switch (Object){
             case OBJECT_TETRAHEDRON:Tetrahedron.draw_lighting_flat_shading();break;
             case OBJECT_CUBE:Cube.draw_lighting_flat_shading();break;
             case OBJECT_CONE:Cone.draw_lighting_flat_shading();break;
             case OBJECT_CYLINDER:Cylinder.draw_lighting_flat_shading();break;
             case OBJECT_SPHERE:Sphere.draw_lighting_flat_shading();break;
             case OBJECT_PLY:Ply.draw_lighting_flat_shading();break;
             case OBJECT_JERAQUICO:objeto.draw(_mode::FLAT_SHADING_MODE,traslacion_coche,angle_puerta,angle_ruedas,desplazamiento_asiento);break;
             case OBJECT_CHESS_BOARD:ChessBoard.draw_lighting_flat_shading();break;
             case OBJECT_TOROIDE:Toroide.draw_lighting_flat_shading();break;

             default:break;
         }
     }
     if(Draw_smooth_shading){
         switch (Object){
             case OBJECT_TETRAHEDRON:Tetrahedron.draw_lighting_smooth_shading();break;
             case OBJECT_CUBE:Cube.draw_lighting_smooth_shading();break;
             case OBJECT_CONE:Cone.draw_lighting_smooth_shading();break;
             case OBJECT_CYLINDER:Cylinder.draw_lighting_smooth_shading();break;
             case OBJECT_SPHERE:Sphere.draw_lighting_smooth_shading();break;
             case OBJECT_PLY:Ply.draw_lighting_smooth_shading();break;
             case OBJECT_JERAQUICO:objeto.draw(_mode::SMOOTH_SHADING_MODE,traslacion_coche,angle_puerta,angle_ruedas,desplazamiento_asiento);break;
             case OBJECT_CHESS_BOARD:ChessBoard.draw_lighting_smooth_shading();break;
             case OBJECT_TOROIDE:Toroide.draw_lighting_smooth_shading();break;

             default:break;
         }
     }
     desactivarLuces();
   }



  if(Draw_textura || Draw_textura_flat_shading || Draw_textura_smooth_shading){

      glColor3fv((GLfloat *) &WHITE);
      if(!imagenCargada){
          QString File_name("texturas/chess.jpg");
          QImage Image;
          QImageReader Reader(File_name);
          Reader.setAutoTransform(true);
          Image = Reader.read();
          if (Image.isNull()) {
            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                     tr("Cannot load %1.").arg(QDir::toNativeSeparators(File_name)));
            exit(-1);
          }
          Image=Image.mirrored();
          Image=Image.convertToFormat(QImage::Format_RGB888);
          glTexImage2D(GL_TEXTURE_2D,0,3,Image.width(),Image.height(),0,GL_RGB,GL_UNSIGNED_BYTE,Image.bits());
         imagenCargada = true;
      }
    if(Draw_textura){
      switch (Object){

          //case OBJECT_SPHERE:Sphere.draw_textura();break;
          case OBJECT_CHESS_BOARD:ChessBoard.draw_textura();break;
          default:break;
      }
    }

    if(Draw_textura_flat_shading || Draw_textura_smooth_shading){
          activarLuces();
          actualizarMaterial();
          if(Draw_textura_flat_shading){
              switch (Object){
                  //case OBJECT_SPHERE:Sphere.draw_textura_flat_shading();break;
                  case OBJECT_CHESS_BOARD:ChessBoard.draw_textura_flat_shading();break;
                  default:break;
              }
          }
          if(Draw_textura_smooth_shading){
              switch (Object){
                  //case OBJECT_SPHERE:Sphere.draw_textura_smooth_shading();break;
                  case OBJECT_CHESS_BOARD:ChessBoard.draw_textura_smooth_shading();break;
                  default:break;
              }
          }
          desactivarLuces();
     }
  }
}



/*****************************************************************************//**
 * Evento de dibujado
 *
 *
 *
 *****************************************************************************/

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_objects();
}


/*****************************************************************************//**
 * Evento de cambio de tamaño de la ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0,0,Width1,Height1);
}


/*****************************************************************************//**
 * Inicialización de OpenGL
 *
 *
 *
 *****************************************************************************/

void _gl_widget::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
  }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";


  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);;

  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;

  Draw_point=false;
  Draw_line=true;
  Draw_fill=false;
  Draw_chess=false;
  Draw_flat_shading=false;
  Draw_smooth_shading=false;
  Draw_textura=false;
  Draw_textura_flat_shading=false;
  Draw_textura_smooth_shading=false;

  proyeccionParalela=false;

  crearLuces();
  crearTexturas();

}

//MODOS
void _gl_widget::puntosPulsado(int x){
    if(x == Qt::Checked)Draw_point = true;
    else Draw_point = false;
    update();
}
void _gl_widget::lineasPulsado(int x){
    if(x == Qt::Checked) Draw_line = true;
    else Draw_line = false;
    update();
}
void _gl_widget::fillPulsado(int x){
    if(x == Qt::Checked) Draw_fill = true;
    else Draw_fill = false;
    update();
}
void _gl_widget::chessPulsado(int x){
    if(x == Qt::Checked) Draw_chess = true;
    else Draw_chess = false;
    update();
}

void _gl_widget::FlatShadingPulsado(int x){
    if(x == Qt::Checked) Draw_flat_shading = true;
    else Draw_flat_shading = false;
    update();
}
void _gl_widget::SmoothShadingPulsado(int x){
    if(x == Qt::Checked) Draw_smooth_shading = true;
    else Draw_smooth_shading = false;
    update();
}
void _gl_widget::TexturaPulsado(int x){
    if(x == Qt::Checked) Draw_textura = true;
    else Draw_textura = false;
    update();
}
void _gl_widget::TexturaFlatShadingPulsado(int x){
    if(x == Qt::Checked) Draw_textura_flat_shading = true;
    else Draw_textura_flat_shading = false;
    update();
}
void _gl_widget::TexturaSmoothShadingPulsado(int x){
    if(x == Qt::Checked) Draw_textura_smooth_shading = true;
    else Draw_textura_smooth_shading = false;
    update();
}

//LUCES
void _gl_widget::Luz0Pulsada(int x){
    if (x == Qt::Checked) luz0 = true;
    else luz0 = false;
    update();
}
void _gl_widget::Luz1Pulsada(int x){
    if (x == Qt::Checked) luz1 = true;
    else luz1 = false;
    update();
}

void _gl_widget::MoverLuz1Pulsada(int x){
    if (x == Qt::Checked) MoveLuz = true;
    else MoveLuz = false;
    update();
}

void _gl_widget::MoverLuz1SobreX(){
    numRotation=0;
    rotarLuzSobreEje = 0;
}
void _gl_widget::MoverLuz1SobreY(){
    numRotation=0;
    rotarLuzSobreEje = 1;
}
void _gl_widget::MoverLuz1SobreZ(){
    numRotation=0;
    rotarLuzSobreEje = 2;
}
//MATERIALES
void _gl_widget::cambiarMaterialPulsado(){
    contadorMaterial += 1;
    contadorMaterial = contadorMaterial % 3;
}

void _gl_widget::cambiarProyeccionPulsado(){
    proyeccionParalela =! proyeccionParalela;
    update();
}
//OBJETOS
void _gl_widget::tetraedroPulsado(){
   Object = _object::OBJECT_TETRAHEDRON;
   update();
}

void _gl_widget::cuboPulsado(){
    Object = _object::OBJECT_CUBE;
    update();
}
void _gl_widget::conoPulsado(){
    Object = _object::OBJECT_CONE;
    update();
}
void _gl_widget::cilindroPulsado(){
    Object = _object::OBJECT_CYLINDER;
    update();
}
void _gl_widget::esferaPulsado(){
    Object = _object::OBJECT_SPHERE;
    update();
}
void _gl_widget::plyPulsado(){
    Object = _object::OBJECT_PLY;
    update();
}
void _gl_widget::jerarquicoPulsado(){
    Object = _object::OBJECT_JERAQUICO;
    update();
}
void _gl_widget::chessBoardPulsado(){
    Object = _object::OBJECT_CHESS_BOARD;
    update();
}
void _gl_widget::toroidePulsado(){
    Object = _object::OBJECT_TOROIDE;
    update();
}

void _gl_widget::puertaAutomaticPulsado(int x){
    if (x == Qt::Checked)
        MovimientoPuertaAutomatico = true;
    else
        MovimientoPuertaAutomatico = false;
}
void _gl_widget::ruedasAutomaticPulsado(int x){
    if (x == Qt::Checked)
        MovimientoRuedasAutomatico = true;
    else
        MovimientoRuedasAutomatico = false;
}
void _gl_widget::asientoAutomaticPulsado(int x){
    if (x == Qt::Checked)
        MovimientoAsientoAutomatico = true;
    else
        MovimientoAsientoAutomatico = false;
}

void _gl_widget::puertaManual(int x){
    MovimientoPuertaAutomatico=false;
    angle_puerta = x*75/100;
}

void _gl_widget::ruedasManual(int x){
    MovimientoRuedasAutomatico=false;
    angle_ruedas = 3.5*x;

}
void _gl_widget::asientoManual(int x){
    MovimientoPuertaAutomatico=false;
    float incr = (-4-1.5)/100.0;
    desplazamiento_asiento= 1.5+(incr*x);


}


void _gl_widget::timerActivado(){
    if(MovimientoPuertaAutomatico)
        activarPuerta();
    if(MovimientoRuedasAutomatico)
        activarRuedas(5);
    if(MovimientoAsientoAutomatico)
        activarAsiento();
    if(MoveLuz)
        rotarLuz(1,rotarLuzSobreEje,30);

    update();
}


void _gl_widget::activarAsiento(float incremento){
    if(desplazamiento_asiento>=1.5)
        estadoAsiento = false;
    if(desplazamiento_asiento<-4)
        estadoAsiento = true;

    if(estadoAsiento)
        desplazamiento_asiento+=incremento;
    else
        desplazamiento_asiento-=incremento;
}

void _gl_widget::activarRuedas(float incremento){
    if(traslacion_coche<=-30)
        estadoAceleracion = true;

     if(traslacion_coche>=30)
        estadoAceleracion = false;

    if(estadoAceleracion){
        traslacion_coche+=0.1;
        angle_ruedas+=incremento;
    }
    else{
        traslacion_coche-=0.1;
        angle_ruedas-=incremento;
     }

}

void _gl_widget::activarPuerta(float incremento){
    if(-angle_puerta>0)
        estadoPuerta = true;
    if(-angle_puerta<-75)
        estadoPuerta = false;

    if(estadoPuerta)
        angle_puerta+=incremento;
    else
        angle_puerta-=incremento;

}

void _gl_widget::crearLuces(){
  //const GLfloat LUZ_AMBIENTAL_BLANCA[] =  {1.0f, 1.0f, 1.0f, 0.0f};
  //const GLfloat LUZ_DIFUSA_MAGENTA[] =    {1.0f, 0.0f, 1.0f, 1.0f};
  //const GLfloat LUZ_ESPECULAR_MAGENTA[] = {1.0f, 0.0f, 1.0f, 1.0f};


 //Luz.setPosicionLuz(0,10.0f, 10.0f, 10.0f, 1.0f);
 //Luz.setEspecular(0,1.0f, 0.0f, 1.0f, 1.0f);
 Luz.setAmbiental(0,1.0f, 1.0f, 1.0f, 0.0f);
 //Luz.setPosicionLuz(1,10.0f,10.0f,10.0f,0,true);
 //Luz.setDifusa(0,1.0f, 0.0f, 1.0f, 1.0f);
 PosicionLuz[0] = 10.0f;
 PosicionLuz[1] = 10.0f;
 PosicionLuz[2] = 10.0f;
 PosicionLuz[3] = 1.0f;

 Luz.setPosicionLuz(1,PosicionLuz[0],PosicionLuz[1],PosicionLuz[2],PosicionLuz[3], true);
 Luz.setEspecular(1,1.0f, 0.0f, 1.0f, 1.0f);
 Luz.setAmbiental(1,0.0f, 0.0f, 0.0f, 0.0f);
 Luz.setDifusa(1,1.0f, 0.0f, 1.0f, 1.0f);

}

void _gl_widget::activarLuces(){
    glEnable(GL_LIGHTING);
    if(luz0){
        Luz.setAmbiental(0,1.0f, 1.0f, 1.0f, 0.0f);
        Luz.setPosicionLuz(0,10.0f,10.0f,10.0f,0.0f,true);
        Luz.encenderLuz(0);
    }

    else {
        Luz.apagarLuz(0);
    }

    if(luz1){
        if(MoveLuz)
            Luz.setPosicionLuz(1,PosicionLuz[0],PosicionLuz[1],PosicionLuz[2],PosicionLuz[3], false);
        else
            Luz.setPosicionLuz(1,10.0f,10.0f,10.0f,1.0f,true);
        Luz.setEspecular(1,1.0f, 0.0f, 1.0f, 1.0f);
        Luz.setAmbiental(1,0.0f, 0.0f, 0.0f, 0.0f);
        Luz.setDifusa(1,1.0f, 0.0f, 1.0f, 1.0f);
        Luz.encenderLuz(1);
    }
    else{
        Luz.apagarLuz(1);
    }





}

void _gl_widget::desactivarLuces(){
    glDisable(GL_LIGHTING);
}

void _gl_widget::rotarLuz(int numLuz, int eje, float alpha){

    alpha = ((2*M_PI)/alpha)*numRotation;
    switch(eje)
    {
        case 0:
            PosicionLuz[0] = Luz.getPosicion_X(numLuz);
            PosicionLuz[1] = Luz.getPosicion_Y(numLuz) * cos(alpha);
            PosicionLuz[2] = -1 * Luz.getPosicion_Y(numLuz) * sin(alpha);
        break;

        case 1:
            PosicionLuz[0] = Luz.getPosicion_X(numLuz) * cos(alpha);
            PosicionLuz[1] = Luz.getPosicion_Y(numLuz);
            PosicionLuz[2] = -1 * Luz.getPosicion_X(numLuz) * sin(alpha);
        break;
        case 2:
            PosicionLuz[0] = Luz.getPosicion_X(numLuz) * cos(alpha);
            PosicionLuz[1] = -1 * Luz.getPosicion_X(numLuz) * sin(alpha);
            PosicionLuz[2] = Luz.getPosicion_Z(numLuz);
        break;
    }
    numRotation++;
}

void _gl_widget::crearTexturas(){
  QString File_name("texturas/chess.jpg");
  QImage Image;
  QImageReader Reader(File_name);
  Reader.setAutoTransform(true);
  Image = Reader.read();

  Image=Image.mirrored();
  Image=Image.convertToFormat(QImage::Format_RGB888);

  imagenCargada = false;

  // Code to pass the image to OpenGL to form a texture 2D
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


  // Code to control the application of the texture
  glTexImage2D(GL_TEXTURE_2D,0,3,Image.width(),Image.height(),0,GL_RGB,GL_UNSIGNED_BYTE,Image.bits());
}


void _gl_widget::actualizarMaterial(){
    _vertex4f difuso;
    _vertex4f especular;
    _vertex4f ambiental;
    float shine;

    switch (contadorMaterial){
        case 0:
            difuso = _vertex4f(0.0f,0.50980392f,0.50980392f,1.0f);
            especular = _vertex4f(0.50196078f,0.50196078f,0.50196078f,1.0f);
            ambiental = _vertex4f(0.0f,0.1f,0.06f ,1.0f);
            shine = 32.0f;
        break;
        case 1:
            difuso = _vertex4f(0.07568f, 0.61424f, 0.07568f, 0.55f);
            especular = _vertex4f(0.633f, 0.727811f, 0.633f, 0.55f);
            ambiental = _vertex4f(0.0215f, 0.1745f, 0.0215f, 0.55f);
            shine = 76.8f;
        break;
        case 2:
            difuso = _vertex4f(0.61424f, 0.04136f, 0.04136f, 0.55f);
            especular = _vertex4f(0.727811f, 0.626959f, 0.626959f, 0.55f);
            ambiental = _vertex4f(0.1745f, 0.01175f, 0.01175f, 0.55f);
            shine = 76.84f;
        break;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,(GLfloat*) &difuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,(GLfloat*) &especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,(GLfloat*) &ambiental);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

}

void _gl_widget::mousePressEvent(QMouseEvent *evento){
  if((evento->buttons() & Qt::LeftButton) == Qt::LeftButton){
    posRaton = evento->pos();
  }
/*
  if((evento->buttons() & Qt::RightButton) == Qt::RightButton){

      Selection_position_x = evento->pos().x();
      Selection_position_y = evento->pos().y();
      switch (Object) {
          case OBJECT_TETRAHEDRON:Tetrahedron.draw_for_selection();break;
          case OBJECT_CUBE:Cube.draw_for_selection();break;
          case OBJECT_CONE:Cone.draw_for_selection();break;
          case OBJECT_CYLINDER:Cylinder.draw_for_selection();break;
          case OBJECT_SPHERE:Sphere.draw_for_selection();break;
          case OBJECT_PLY:Ply.draw_for_selection();break;
          case OBJECT_CHESS_BOARD:ChessBoard.draw_for_selection();break;
          case OBJECT_TOROIDE:Toroide.draw_for_selection();break;
          default:break;
      }


      pick();    
  }
  */
  update();
}

void _gl_widget::mouseMoveEvent(QMouseEvent *evento){

  if((evento->buttons() & Qt::LeftButton) == Qt::LeftButton){

    Observer_angle_x += 0.3*(evento->pos().y() - posRaton.y());
    Observer_angle_y += 0.3*(evento->pos().x() - posRaton.x());

    posRaton = evento->pos();
  }
  update();
}

void _gl_widget::wheelEvent(QWheelEvent *evento){
  QPoint anguloRotacion = evento->angleDelta();
  if(!anguloRotacion.isNull()){
    Observer_distance = max(0.0f, Observer_distance - anguloRotacion.y() * 0.0025f);
  }
  update();
}
/*
void _gl_widget::pick()
{
      glewInit();
      makeCurrent();

      // Frame Buffer Object to do the off-screen rendering
      GLuint FBO;
      glGenFramebuffers(1,&FBO);
      glBindFramebuffer(GL_FRAMEBUFFER,FBO);

      // Texture for drawing
      GLuint Color_texture;
      glGenTextures(1,&Color_texture);
      glBindTexture(GL_TEXTURE_2D,Color_texture);
      // RGBA8
      glTexStorage2D(GL_TEXTURE_2D,1,GL_RGBA8, this->width(),this->height());
      // this implies that there is not mip mapping
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

      // Texure for computing the depth
      GLuint Depth_texture;
      glGenTextures(1,&Depth_texture);
      glBindTexture(GL_TEXTURE_2D,Depth_texture);
      // Float
      glTexStorage2D(GL_TEXTURE_2D,1,GL_DEPTH_COMPONENT24, this->width(),this->height());
      cout << "1Boton derecho pulsado" << endl;
      // Attatchment of the textures to the FBO

      glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,Color_texture,0);
      glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,Depth_texture,0);

      cout << "No" << endl;
      // OpenGL will draw to these buffers (only one in this case)
      static const GLenum Draw_buffers[]={GL_COLOR_ATTACHMENT0};
      glDrawBuffers(1,Draw_buffers);



      // get the pixel
      int Color;
      glReadBuffer(GL_FRONT);
      glPixelStorei(GL_PACK_ALIGNMENT,1);
      glReadPixels(Selection_position_x,Selection_position_y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,&Color);


      // convertir de RGB a identificador
      uint  R = uint((Color & 0x000000FF)),
            G = uint((Color & 0x0000FF00) >> 8),
            B = uint((Color & 0x00FF0000) >> 16);

      int triangulo_seleccionado = (R << 16) + (G << 8) + (B);

      cout << triangulo_seleccionado << endl;
      // actualizar el identificador de la parte seleccionada en el objeto
      switch (Object) {
          case OBJECT_TETRAHEDRON:Tetrahedron.setTrianguloSeleccionado(triangulo_seleccionado);break;
          case OBJECT_CUBE:Cube.setTrianguloSeleccionado(triangulo_seleccionado);break;
          case OBJECT_CONE:Cone.setTrianguloSeleccionado(triangulo_seleccionado);break;
          case OBJECT_CYLINDER:Cylinder.setTrianguloSeleccionado(triangulo_seleccionado);break;
          case OBJECT_SPHERE:Sphere.setTrianguloSeleccionado(triangulo_seleccionado);break;
          case OBJECT_PLY:Ply.setTrianguloSeleccionado(triangulo_seleccionado);break;
          case OBJECT_CHESS_BOARD:ChessBoard.setTrianguloSeleccionado(triangulo_seleccionado);break;
          case OBJECT_TOROIDE:Toroide.setTrianguloSeleccionado(triangulo_seleccionado);break;
          default:break;

      }



      glDeleteTextures(1,&Color_texture);
      glDeleteTextures(1,&Depth_texture);
      glDeleteFramebuffers(1,&FBO);
      // the normal framebuffer takes the control of drawing
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER,defaultFramebufferObject());

}
*/
