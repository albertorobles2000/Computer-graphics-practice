#include "rueda.h"

_rueda::_rueda()
{
}

void _rueda::draw(_mode MODE){

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glRotatef(90,0,0,1);
        glPushMatrix();
            glColor3f(0,0,0);
            glScalef(1.7,0.79,1.7);
            neumatico.draw(MODE);
        glPopMatrix();

        glPushMatrix();
            glColor3f(0.62,0.62,0.62);
            glScalef(1.5,0.8,1.5);
            llanta.draw(MODE);
        glPopMatrix();

        glColor3f(0.12,0.35,0.61);

        glPushMatrix();
            glTranslated(0,0.4,0);
            //glRotatef(90,0,0,1);
            glPushMatrix();
                glRotatef(90,0,0,1);
                glScalef(0.05,1.5,0.05);
                radio1.draw(MODE);
            glPopMatrix();

            glPushMatrix();
                glRotatef(90,1,0,0);
                glScalef(0.05,1.5,0.05);
                radio2.draw(MODE);
            glPopMatrix();

            glPushMatrix();
                glRotatef(45,0,1,0);
                glRotatef(90,0,0,1);
                glScalef(0.05,1.5,0.05);
                radio3.draw(MODE);
            glPopMatrix();

            glPushMatrix();
                glRotatef(-45,0,1,0);
                glRotatef(90,0,0,1);
                glScalef(0.05,1.5,0.05);
                radio4.draw(MODE);
            glPopMatrix();
          glPopMatrix();
    glPopMatrix();
}
