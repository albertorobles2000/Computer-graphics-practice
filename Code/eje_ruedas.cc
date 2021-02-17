#include "eje_ruedas.h"

_eje_ruedas::_eje_ruedas()
{
}

void _eje_ruedas::draw(_mode MODE, float angle_ruedas){

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

        glPushMatrix();
            glColor3f(0,0,0);
            glRotatef(90,0,0,1);
            glScalef(0.25,8,0.25);
            eje_central.draw(MODE);
        glPopMatrix();

        glRotatef(angle_ruedas,1,0,0);
        glPushMatrix();
            glTranslated(3.55,0,0);
            glRotatef(180,0,0,1);
            rueda1.draw(MODE);
        glPopMatrix();

        glPushMatrix();
            glTranslated(-3.55,0,0);
            rueda2.draw(MODE);
        glPopMatrix();

    glPopMatrix();
}
