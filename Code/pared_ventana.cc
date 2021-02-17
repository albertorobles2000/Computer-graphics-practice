#include "pared_ventana.h"

_pared_ventana::_pared_ventana()
{

}

void _pared_ventana::draw(_mode MODE){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();


        glColor3f(0.40,0.30,0.80);
        //Tabique izquierdo delantero
        //Tabique Izquierdo trasero
        glPushMatrix();
            glTranslated(0,0.83,-4.05);
            glScalef(0.2,2.7,2);
            tabiqueIT.draw(MODE);
        glPopMatrix();

        //Panel izquierdo inferior
        glPushMatrix();
            glTranslated(0,0,-1.05);
            glScalef(0.2,1,4);
            panelII.draw(MODE);
        glPopMatrix();

        //Panel izquierdo superior
        glPushMatrix();
            glTranslated(0,1.93,-1.05);
            glScalef(0.2,0.5,4);
            panelIS.draw(MODE);
        glPopMatrix();

        //Panel izquierdo central
        glPushMatrix();
            glTranslated(0,1.08,0);
            glScalef(0.2,1.20,1.9);
            panelIC.draw(MODE);
        glPopMatrix();


    glPopMatrix();
}
