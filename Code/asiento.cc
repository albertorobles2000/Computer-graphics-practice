#include "asiento.h"


_asiento::_asiento()
{

}

void _asiento::draw(_mode MODE, float angle_asiento)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

        glPushMatrix();
            glColor3f(0,0,0);
            glTranslated(0,-0.25,0);
            glScalef(0.7,0.25,0.7);
            sujeccion.draw(MODE);
        glPopMatrix();

        glColor3f(0.92,0.83,0.6);

        glPushMatrix();
            glScalef(1,0.25,1);
            base.draw(MODE);
        glPopMatrix();

        glTranslated(0,-0.03,-0.50);
        glRotatef(angle_asiento,1,0,0);

        glPushMatrix();
            glTranslated(0,0.68,-0.1);
            glRotatef(-4,1,0,0);
            glScalef(0.99,1.5,0.25);
            respaldo.draw(MODE);
        glPopMatrix();

        glPushMatrix();


            glTranslated(0,1.75,-0.15);
            glPushMatrix();
                glRotatef(90,0,0,1);
                glScalef(0.3,0.75,0.2);
                reposa_cabezas.draw(MODE);
            glPopMatrix();

            glColor3f(0.62,0.62,0.62);
            glPushMatrix();
                glTranslated(-0.20,-0.2,0);
                glScalef(0.05,0.3,0.05);
                sujeta_repos_1.draw(MODE);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0.20,-0.2,0);
                glScalef(0.05,0.3,0.05);
                sujeta_repos_2.draw(MODE);

           glPopMatrix();

       glPopMatrix();

    glPopMatrix();
}
