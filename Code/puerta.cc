#include "puerta.h"

_puerta::_puerta()
{

}

void _puerta::draw(_mode MODE){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glColor3f(0.6,0.6,0.6);
        //Panel principal
        glPushMatrix();

            glScalef(2,1.5,0.2);
            panel.draw(MODE);
        glPopMatrix();
        //pilar 1
        glPushMatrix();
            glColor3f(0.7,0.7,0.7);
            glTranslated(-0.90,1.25,0);
            glScalef(0.2,1,0.2);
            pilar1.draw(MODE);
        glPopMatrix();

        //pilar 2
        glPushMatrix();
            glColor3f(0.7,0.7,0.7);
            glTranslated(0.76,1.25,0);
            glRotated(15,0,0,1);
            glScalef(0.2,1.1,0.199);
            pilar2.draw(MODE);
        glPopMatrix();

        //Superior
        glPushMatrix();
            glColor3f(0.6,0.6,0.6);
            glTranslated(-0.13,1.85,0);
            glScalef(1.725,0.2,0.2);
            superior.draw(MODE);
        glPopMatrix();

    glPopMatrix();
}
