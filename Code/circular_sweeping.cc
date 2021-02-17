#include "circular_sweeping.h"
#include <algorithm>




void _circular_sweeping::rotate(vector<_vertex3f> & Perfil, int num_rotations, bool upper_cover,
                                bool lower_cover, int rotation_axis,float grados, bool cerrar_objeto_h, bool cerrar_objeto_v){
    corrige_el_orden(Perfil, rotation_axis);

    int num_vertices = rellena_vertices(Perfil,upper_cover,lower_cover, num_rotations, rotation_axis, grados);

    rellena_triangulos(Perfil.size(),num_vertices,upper_cover, lower_cover, num_rotations, grados, cerrar_objeto_h, cerrar_objeto_v);

}

int _circular_sweeping::rellena_vertices(vector<_vertex3f> & Perfil, bool upper_cover,
                                         bool lower_cover, int num_rotations, int rotation_axis, float grados){

    int num_columnas = num_rotations;
    if(grados<360)
        num_columnas++;

    //Calculamos el numero de vertices y reservamos espacio
    int num_vertices;
    if(upper_cover && lower_cover){
        num_vertices = ((Perfil.size()-2)*num_columnas)+2;
    }
    else{
        if(upper_cover ^ lower_cover)
            num_vertices = ((Perfil.size()-1)*num_columnas)+2;
        else
            num_vertices = Perfil.size()*num_columnas;
    }
    Vertices.resize(num_vertices);

    //Calculamos el primer y el ultimo elemento del perfil
    int first_element = 0;
    if(upper_cover){
        first_element++;
    }

    int last_element = Perfil.size();
    if(lower_cover){
        last_element--;
    }
    //Rellenamos la matriz de vertices
    float alpha;
    float radianes = (grados * (M_PI * 2)) / 360.0;
    for(int i=0; i<num_columnas; ++i){
        alpha = (radianes/num_rotations) * i;
        int k=0;
        for(int j=first_element; j<last_element; ++j, ++k){
            switch(rotation_axis)
            {
                case 0:
                    Vertices[i+num_columnas*k]._0 = Perfil[j]._0;
                    Vertices[i+num_columnas*k]._1 = Perfil[j]._1 * cos(alpha);
                    Vertices[i+num_columnas*k]._2 = -1 * Perfil[j]._1 * sin(alpha);
                break;
                case 1:
                    Vertices[i+num_columnas*k]._0 = Perfil[j]._0 * cos(alpha);
                    Vertices[i+num_columnas*k]._1 = Perfil[j]._1;
                    Vertices[i+num_columnas*k]._2 = -1 * Perfil[j]._0 * sin(alpha);
                break;
                case 2:
                    Vertices[i+num_columnas*k]._0 = Perfil[j]._0 * cos(alpha);
                    Vertices[i+num_columnas*k]._1 = -1 * Perfil[j]._0 * sin(alpha);
                    Vertices[i+num_columnas*k]._2 = Perfil[j]._2;
                break;
            }
        }
    }
    //Excepciones upper_cover y lower_cover
    if(upper_cover)
        Vertices[num_vertices-2] = Perfil[0];
    if(lower_cover)
        Vertices[num_vertices-1] = Perfil[Perfil.size()-1];

    return num_vertices;

}

void _circular_sweeping::rellena_triangulos(int elementos_perfil, int num_vertices,
                         bool upper_cover, bool lower_cover, int num_rotations, float grados,bool cerrar_objeto_h, bool cerrar_objeto_v){

    int num_columnas = num_rotations;
    if(grados<360)
        num_columnas++;
    int iteraciones_h = num_columnas;
    if(!cerrar_objeto_h)
        iteraciones_h--;

    int iteraciones_v = elementos_perfil;
    if(cerrar_objeto_v)
        iteraciones_v++;

    //Creamos espacio triangulos
    int num_triangulos;
    if(!upper_cover && !lower_cover)
        num_triangulos = (iteraciones_v-1)*iteraciones_h*2;
    if(upper_cover^lower_cover)
        num_triangulos = (iteraciones_v-2)*iteraciones_h*2+(iteraciones_h);
    if(upper_cover && lower_cover)
        num_triangulos = ((iteraciones_v-3)*iteraciones_h*2)+(iteraciones_h*2);
    Triangles.resize(num_triangulos);

    //Rellenamos Triangles
    int num_filas = elementos_perfil;
    if(upper_cover) num_filas--;
    if(lower_cover) num_filas--;
    if(cerrar_objeto_v) num_filas++;

    int num_actual_triangles = 0;
    int actual, inferior, derecha, derecha_inferior;

    for(int i=0; i<num_filas-1; i++){
        for(int j=0; j<iteraciones_h;j++,num_actual_triangles+=2){

            actual = i*num_columnas+j;
            inferior = (((i+1)%elementos_perfil)*num_columnas+j);
            derecha = (i*num_columnas+((j+1)%num_columnas));
            derecha_inferior = (((i+1)%elementos_perfil)*num_columnas+((j+1)%num_columnas));

            Triangles[num_actual_triangles] = _vertex3ui(actual,inferior,derecha_inferior);
            Triangles[num_actual_triangles+1] = _vertex3ui(derecha,actual,derecha_inferior);
        }
    }


    if(upper_cover){
        int posicion_upper = num_vertices-2;
        for(int i=0; i<iteraciones_h; i++, num_actual_triangles++){
            actual = i;
            derecha = (actual+1)%num_columnas;
            Triangles[num_actual_triangles] = _vertex3ui(posicion_upper,actual,derecha);
        }
    }

    if(lower_cover){
        int posicion_lower = num_vertices-1;
        for(int i=0; i<iteraciones_h; i++,num_actual_triangles++){
            actual = i+(num_filas-1)*num_columnas;
            derecha = ((i+1)%num_columnas)+(num_filas-1)*num_columnas;
            Triangles[num_actual_triangles] = _vertex3ui(actual,posicion_lower,derecha);
        }
    }
}

void _circular_sweeping::corrige_el_orden(vector<_vertex3f> & Perfil, int rotation_axis){
    bool hay_que_invertir = false;

    switch (rotation_axis)
    {
        case 0:
            if(Perfil[0]._0>Perfil[Perfil.size()-1]._0)
                hay_que_invertir = true;

        break;
        case 1:
            if(Perfil[0]._1<Perfil[Perfil.size()-1]._1)
                hay_que_invertir = true;

        break;
        case 2:
            if(Perfil[0]._2>Perfil[Perfil.size()-1]._2)
                hay_que_invertir = true;

        break;
    }
    if(hay_que_invertir)
        std::reverse(Perfil.begin(),Perfil.end());
}

bool _circular_sweeping::is_upper_cover(vector<_vertex3f> & Perfil, int rotation_axis){
    bool cover = false;
    int value;
    //float max_x, max_y, max_z;
    switch(rotation_axis)
    {
        case 0: value=Perfil[0]._1;
        break;
        case 1: value=Perfil[0]._0;
        break;
        case 2: value=Perfil[0]._0;
        break;
    }
    if(value==0){
        cover = true;
    }
    return cover;
}
bool _circular_sweeping::is_lower_cover(vector<_vertex3f> & Perfil, int rotation_axis){
    bool cover = false;
    int value;
    switch(rotation_axis)
    {
        case 0: value=Perfil[Perfil.size()-1]._1;
        break;
        case 1: value=Perfil[Perfil.size()-1]._0;
        break;
        case 2: value=Perfil[Perfil.size()-1]._0;
        break;
    }
    if(value==0){
        cover = true;
    }
    return cover;
}

void _circular_sweeping::Corregir_perfil(vector<_vertex3f> & Vert, int axis)
{

    float x, y, z;
    switch (axis) {
        case 0:
            for(int i=0; i<(int)Vert.size(); ++i){
                x = -Vert[i]._1;
                y = Vert[i]._0;
                z = Vert[i]._2;
                Vert[i] = _vertex3f(x,y,z);

            }
        break;
        case 1: //No se hace nada, por defecto vienen en la posicion y
        break;
        case 2:
            for(int i=0; i<(int)Vert.size(); ++i){
                x = Vert[i]._0;
                y = Vert[i]._2;
                z = Vert[i]._1;
                Vert[i] = _vertex3f(x,y,z);
            }
        break;

    }
}

/*
void _circular_sweeping::rotate(vector<_vertex3f> & Perfil,
                                vector<_vertex3f> & Vertices,
                                vector<_vertex3ui> & Triangles){
    bool upper_cover = false;
    bool lower_cover = false;
    int first_element = 0;
    int last_element = Perfil.size();

    if(Perfil[0]._0==0){
        upper_cover = true;
        first_element++;
    }

    if(Perfil[Perfil.size()-1]._0==0){
        lower_cover = true;
        last_element--;
    }

    //Calculamos el numero de vertices y reservamos espacio
    int num_vertices;
    if(upper_cover && lower_cover){
        num_vertices = ((Perfil.size()-2)*num_rotations)+2;
    }
    else{
        if(upper_cover ^ lower_cover)
            num_vertices = ((Perfil.size()-1)*num_rotations)+2;
        else
            num_vertices = Perfil.size()*num_rotations;
    }
    Vertices.resize(num_vertices);

    //Rellenamos la matriz de vertices
    float alpha;
    for(int i=0; i<num_rotations; ++i){
        alpha = ((M_PI * 2)/num_rotations) * i;
        int k=0;
        for(int j=first_element; j<last_element; ++j, ++k){
            Vertices[i+num_rotations*k]._0 = Perfil[j]._0 * cos(alpha);
            Vertices[i+num_rotations*k]._1 = Perfil[j]._1;
            Vertices[i+num_rotations*k]._2 = -1 * Perfil[j]._0 * sin(alpha);
        }
    }
    //Excepciones upper_cover y lower_cover
    int posicion_upper = num_vertices-2,
        posicion_lower = num_vertices-1;
    if(upper_cover)
        Vertices[posicion_upper] = Perfil[0];
    if(lower_cover)
        Vertices[posicion_lower] = Perfil[Perfil.size()-1];

    //Creamos espacio triangulos
    int num_triangulos;
    if(!upper_cover && !lower_cover)
        num_triangulos = (Perfil.size()-1)*num_rotations*2;
    if(upper_cover^lower_cover)
        num_triangulos = (Perfil.size()-2)*num_rotations*2+(num_rotations);
    if(upper_cover && lower_cover)
        num_triangulos = ((Perfil.size()-3)*num_rotations*2)+(num_rotations*2);
    Triangles.resize(num_triangulos);

    int num_filas = last_element-first_element;
    int num_actual_triangles = 0;
    int actual, superior, derecha, derecha_superior;
    for(int i=num_filas-1; i>0; i--){
        for(int j=0; j<num_rotations;j++,num_actual_triangles+=2){

            actual = i*num_rotations+j;
            superior = (actual-num_rotations);
            derecha = (i*num_rotations+((j+1)%num_rotations));
            derecha_superior = ((i-1)*num_rotations+((j+1)%num_rotations));

            Triangles[num_actual_triangles] = _vertex3ui(actual,derecha,derecha_superior);
            Triangles[num_actual_triangles+1] = _vertex3ui(superior,actual,derecha_superior);
        }
    }


    if(upper_cover){
        for(int i=0; i<num_rotations; i++, num_actual_triangles++){
            actual = i;
            derecha = (actual+1)%num_rotations;
            superior = posicion_upper;
            Triangles[num_actual_triangles] = _vertex3ui(posicion_upper,actual,derecha);
        }
    }

    if(lower_cover){
        for(int i=0; i<num_rotations; i++,num_actual_triangles++){
            actual = i+(num_filas-1)*num_rotations;
            derecha = ((i+1)%num_rotations)+(num_filas-1)*num_rotations;
            superior = posicion_lower;
            Triangles[num_actual_triangles] = _vertex3ui(actual,posicion_lower,derecha);
        }
    }

}
*/

/*
void _circular_sweeping::rellena_triangulos(vector<_vertex3ui> & Triangles,
                      int elementos_perfil, int num_vertices,
                         bool upper_cover, bool lower_cover){
    //Creamos espacio triangulos
    int num_triangulos;
    if(!upper_cover && !lower_cover)
        num_triangulos = (elementos_perfil-1)*num_rotations*2;
    if(upper_cover^lower_cover)
        num_triangulos = (elementos_perfil-2)*num_rotations*2+(num_rotations);
    if(upper_cover && lower_cover)
        num_triangulos = ((elementos_perfil-3)*num_rotations*2)+(num_rotations*2);
    Triangles.resize(num_triangulos);

    //Rellenamos Triangles
    int num_filas = elementos_perfil;
    if(upper_cover) num_filas--;
    if(lower_cover) num_filas--;

    int num_actual_triangles = 0;
    int actual, superior, derecha, derecha_superior;
    for(int i=num_filas-1; i>0; i--){
        for(int j=0; j<num_rotations;j++,num_actual_triangles+=2){

            actual = i*num_rotations+j;
            superior = (actual-num_rotations);
            derecha = (i*num_rotations+((j+1)%num_rotations));
            derecha_superior = ((i-1)*num_rotations+((j+1)%num_rotations));

            Triangles[num_actual_triangles] = _vertex3ui(actual,derecha,derecha_superior);
            Triangles[num_actual_triangles+1] = _vertex3ui(superior,actual,derecha_superior);
        }
    }


    if(upper_cover){
        int posicion_upper = num_vertices-2;
        for(int i=0; i<num_rotations; i++, num_actual_triangles++){
            actual = i;
            derecha = (actual+1)%num_rotations;
            superior = posicion_upper;
            Triangles[num_actual_triangles] = _vertex3ui(posicion_upper,actual,derecha);
        }
    }

    if(lower_cover){
        int posicion_lower = num_vertices-1;
        for(int i=0; i<num_rotations; i++,num_actual_triangles++){
            actual = i+(num_filas-1)*num_rotations;
            derecha = ((i+1)%num_rotations)+(num_filas-1)*num_rotations;
            superior = posicion_lower;
            Triangles[num_actual_triangles] = _vertex3ui(actual,posicion_lower,derecha);
        }
    }
}
*/
