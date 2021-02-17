/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "object3d.h"

using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_line()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_TRIANGLES);
    for (unsigned int i=0;i<Triangles.size();i++){
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_fill()
{
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);
    for (int i=0;i<(int)Triangles.size();i++){
      /*if(i==triangle){
          cout << "Pinto triangulo amarillo" << endl;
          glColor3f(1,1,0);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
          glColor3fv((GLfloat *) &BLUE);
      }
      else{
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
      }*/
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_chess()
{
  glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned int i=0;i<Triangles.size();i++){
      if(i%2)
        glColor3f(1,1,0);
      else
        glColor3f(0,1,1);
      
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glEnd();
}

void _object3D::draw(_mode MODE){
    switch (MODE) {
        case _mode::POINT_MODE:
            draw_point();
            break;
        case _mode::LINE_MODE:
            draw_line();
            break;
        case _mode::FILL_MODE:
            draw_fill();
            break;
        case _mode::CHESS_MODE:
            draw_chess();
            break;
        case _mode::FLAT_SHADING_MODE:
            draw_lighting_flat_shading();
            break;
        case _mode::SMOOTH_SHADING_MODE:
            draw_lighting_smooth_shading();
            break;
        case _mode::TEXTURA_MODE:
            draw_textura();
            break;
        case _mode::TEXTURA_FLAT_SHADING_MODE:
            draw_textura_flat_shading();
            break;
        case _mode::TEXTURA_SMOOTH_SHADING_MODE:
            draw_textura_smooth_shading();
            break;
    }
}

void _object3D::calcularNormalesTriangulos(){
  NormalTriangulos.resize(Triangles.size());

  for(int i=0; i<(int)Triangles.size();i++){
    _vertex3f primerVector = Vertices.at(Triangles[i]._0) - Vertices.at(Triangles[i]._1);
    _vertex3f segundoVector = Vertices.at(Triangles[i]._1) - Vertices.at(Triangles[i]._2);
    _vertex3f normal = primerVector.cross_product(segundoVector);
    //cout << normal._0<<"/"<<normal._1 <<"/"<< normal._2 << endl;
    normal.normalize();
    NormalTriangulos[i] = normal;

  }

}

void _object3D::calcularNormalesVertices(){
    vector<int> numTriangulosVertice(Vertices.size(),0);

    NormalVertices.resize(Vertices.size(),0);
    for(int i=0; i<(int)Triangles.size(); ++i){
        numTriangulosVertice[Triangles[i]._0]++;
        numTriangulosVertice[Triangles[i]._1]++;
        numTriangulosVertice[Triangles[i]._2]++;

        //Sumamos todos las normales en sus respectivos vertices
        NormalVertices[Triangles[i]._0] += NormalTriangulos[i];
        NormalVertices[Triangles[i]._1] += NormalTriangulos[i];
        NormalVertices[Triangles[i]._2] += NormalTriangulos[i];

    }

    for(int i=0; i<(int)NormalVertices.size(); i++){
        if(numTriangulosVertice[i]!=0)
            NormalVertices[i] = NormalVertices[i] / numTriangulosVertice[i];
        NormalVertices[i].normalize();

    }

}

void _object3D::draw_lighting_flat_shading(){

        glPolygonMode(GL_FRONT,GL_FILL);
        glBegin( GL_TRIANGLES);
        glShadeModel(GL_FLAT);
        for (unsigned int i=0;i<Triangles.size();i++)
        {
          glNormal3fv((GLfloat *) &NormalTriangulos[i]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
        glEnd();
}

void _object3D::draw_lighting_smooth_shading(){


      glPolygonMode(GL_FRONT,GL_FILL);
      glBegin( GL_TRIANGLES);
      glShadeModel(GL_SMOOTH);
      for (unsigned int i=0;i<Triangles.size();i++)
      {
        glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._0]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);

        glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._1]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);

        glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._2]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);

      }
      glEnd();
}

void _object3D::draw_textura(){
    glEnable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBegin(GL_TRIANGLES);
        for(unsigned int i = 0; i < Triangles.size(); ++i){
          glTexCoord2fv((GLfloat *) &Textura[Triangles[i]._0]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);

          glTexCoord2fv((GLfloat *) &Textura[Triangles[i]._1]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);

          glTexCoord2fv((GLfloat *) &Textura[Triangles[i]._2]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void _object3D::draw_textura_smooth_shading(){


    glEnable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBegin(GL_TRIANGLES);
        glShadeModel(GL_SMOOTH);
        for(unsigned int i = 0; i < Triangles.size(); ++i){

          glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._0]);
          glTexCoord2fv((GLfloat *) &Textura[Triangles[i]._0]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);

          glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._1]);
          glTexCoord2fv((GLfloat *) &Textura[Triangles[i]._1]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);

          glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._2]);
          glTexCoord2fv((GLfloat *) &Textura[Triangles[i]._2]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void _object3D::draw_textura_flat_shading(){


    glEnable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBegin(GL_TRIANGLES);
        glShadeModel(GL_FLAT);
        for(unsigned int i = 0; i < Triangles.size(); ++i){

          glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._0]);
          glTexCoord2fv((GLfloat *) &Textura[Triangles[i]._0]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);

          glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._1]);
          glTexCoord2fv((GLfloat *) &Textura[Triangles[i]._1]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);

          glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._2]);
          glTexCoord2fv((GLfloat *) &Textura[Triangles[i]._2]);
          glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
        glEnd();
    glDisable(GL_TEXTURE_2D);
}
/*
void _object3D::setTrianguloSeleccionado(int triangulo){
    this->triangle = triangulo;
    this->triangleSelected = true;

}

void _object3D::draw_for_selection(){
    float r,g,b;
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned int i=0;i<Triangles.size();i++){
      r = (i & 0x00FF0000) >> 16;
      g = (i & 0x0000FF00) >> 8;
      b = (i & 0x000000FF);
      glColor3f(r/255,g/255,b/255);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glEnd();
}
*/

