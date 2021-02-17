#include "chasis.h"

_chasis::_chasis()
{

}

void _chasis::draw(_mode MODE, float angle_puerta, float angle_ruedas, float desplazamiento_asiento){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

        glPushMatrix();
            plataforma.draw(MODE,angle_ruedas, desplazamiento_asiento);
        glPopMatrix();

        if(-angle_puerta>0)
            angle_puerta=0;
        if(-angle_puerta<-75)
            angle_puerta=75;
        //Puerta Izquierda
        glPushMatrix();
            glTranslated(3,1,2.5);
            glRotatef(-angle_puerta,0,1,0);
            glTranslated(-0.1,0,-1);
            glRotatef(-90,0,1,0);
            puertaI.draw(MODE);
        glPopMatrix();

        //Puerta Derecha
        glPushMatrix();
            glTranslated(-2.9,1,1.5);
            glRotatef(-90,0,1,0);
            puertaD.draw(MODE);
        glPopMatrix();


        glColor3f(0.3,0.36,0.72);

        glPushMatrix();
            glTranslated(0,0.98,4);
            glScalef(6,1.45,3);
            motor.draw(MODE);
        glPopMatrix();


        glColor3f(0.40,0.30,0.80);
        //Tabique izquierdo delantero
        glPushMatrix();
            glTranslated(2.9,2.3,2.4);
            glRotatef(-15,1,0,0);
            glScalef(0.201,1.4,0.201);
            tabiqueID.draw(MODE);
        glPopMatrix();

        //Tabique Derecho delantero
        glPushMatrix();
            glTranslated(-2.9,2.3,2.4);
            glRotatef(-15,1,0,0);
            glScalef(0.201,1.4,0.201);
            tabiqueDD.draw(MODE);
        glPopMatrix();

       glColor3f(0.40,0.30,0.80);

        glPushMatrix();
            glTranslated(-2.9,0.77,-0.45);
            paredD.draw(MODE);
        glPopMatrix();

        glPushMatrix();
            glTranslated(2.9,0.77,-0.45);
            paredI.draw(MODE);
        glPopMatrix();
        //Techo
        glPushMatrix();
            glColor3f(0.3,0.36,0.72);
            glTranslated(0,3.05,-1.6);
            glScalef(6,0.2,7.9);
            techo.draw(MODE);
        glPopMatrix();

        //maletero
        glPushMatrix();
            glColor3f(0.4,0.83,0.42);
            glTranslated(0,1.6,-5.4);
            glScalef(5.6,2.7,0.2);
            maletero.draw(MODE);
        glPopMatrix();



    glPopMatrix();
}
