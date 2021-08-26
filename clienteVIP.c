#include <stdio.h>
#include <time.h>

int rand();
int srand();

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
    srand(time(0));
    posicionAleatoriaActual(5);
    posicionAleatoriaFinal(5);
    
    }

