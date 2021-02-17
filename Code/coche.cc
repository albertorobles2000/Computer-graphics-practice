#include "coche.h"

_coche::_coche()
{

}

void _coche::draw(_mode MODE, float traslacion_coche,float angle_puerta, float angle_ruedas, float desplazamiento_asiento){

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

        //Panel principal
        glTranslated(0,0,traslacion_coche);
        glPushMatrix();
            chasis.draw(MODE,angle_puerta, angle_ruedas, desplazamiento_asiento);
        glPopMatrix();

        glColor3f(0.94,0.92,0.56);
        glPushMatrix();
            glTranslatef(-2,1,5.5);
            glRotated(90,1,0,0);
            glScalef(0.5,0.2,0.5);
            luzD.draw(MODE);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2,1,5.5);
            glRotated(90,1,0,0);
            glScalef(0.5,0.2,0.5);
            luzI.draw(MODE);
        glPopMatrix();

        glPushMatrix();
            glColor3f(0.8,0.8,0.8);
            glTranslatef(0,0.40,5.5);
            glScalef(2,0.5,0.2);
            matricula.draw(MODE);
        glPopMatrix();

    glPopMatrix();
}
