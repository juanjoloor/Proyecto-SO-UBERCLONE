#include <stdio.h>
#include <time.h>

int rand();
int srand();

typedef struct Cliente {
   int  posicionActual;
   int  cliente_id;
} Cliente;



int printRandoms(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void posicionAleatoriaActual(int x){
    int posGrilla = x * x;
    int posInicial [2];
    posInicial[0] = printRandoms(-posGrilla,posGrilla);
    posInicial[1] = printRandoms(-posGrilla,posGrilla);
    printf("posicion inicial %d,%d",posInicial[0],posInicial[1]);
}


void posicionAleatoriaFinal(int x ){
    int posGrilla = x * x;
    int posFinal [2];
    posFinal[0] = printRandoms(-posGrilla,posGrilla);
    posFinal[1] = printRandoms(-posGrilla,posGrilla);
    printf("posicion final %d,%d",posFinal[0],posFinal[1]);

}



int main(){
    printf("soy cliente ");
    // srand(time(0));
    // posicionAleatoriaActual(5);
    // posicionAleatoriaFinal(5);
      int y[2] = {5,-5};
    // valorModulo(x,y);
    // tiempoViaje(2 , x , y );
    // puedeSerAtendido(x,y,4);

    Cliente me = { .cliente_id = 1,
                  .posicionActual = y   };


    printf(" Cliente numero: %d\n Posicion Actual%d\n", me.cliente_id , me.posicionActual);

    }



