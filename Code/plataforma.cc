#include "plataforma.h"

_plataforma::_plataforma()
{

}
void _plataforma::draw(_mode MODE, float angulo_ruedas, float desplazamiento_asiento){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

        //Base
        glPushMatrix();
            glColor3f(0.6,0.6,0.6);
            glScalef(6,0.5,11);
            base.draw(MODE);
        glPopMatrix();

        //Eje delantero
        glPushMatrix();
            glTranslated(0,-0.4,3.3);
            delantero.draw(MODE,angulo_ruedas);
        glPopMatrix();

        //Eje trasero
        glPushMatrix();
            glTranslated(0,-0.4,-3.3);
            trasero.draw(MODE,angulo_ruedas);
        glPopMatrix();

        //Asiento izquierda
        glPushMatrix();
            glTranslated(1,0.5,1.5);
            asientoi.draw(MODE);
        glPopMatrix();

        //Asiento derecha
        glPushMatrix();
            glTranslated(-1,0.5,desplazamiento_asiento);
            asientod.draw(MODE);
        glPopMatrix();

    glPopMatrix();
}
