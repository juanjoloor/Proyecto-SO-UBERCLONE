#include <stdio.h>
#include <time.h>
#include <math.h>

int rand();
int srand();

int printRandoms(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void posicionAleatoria(int x){
    int posGrilla = x * x;
    int posInicial [2];
    posInicial[0] = printRandoms(-posGrilla,posGrilla);
    posInicial[1] = printRandoms(-posGrilla,posGrilla);
    printf("posicion inicial %d,%d",posInicial[0],posInicial[1]);
}

int puedeSerAtendido( int z){
    int bandera = 0;
    int des1= 10;
    if ( des1 < z){
        bandera = 1;
    }
    return bandera;
}

int valorModulo( int  a[] , int b[]){
    int distance;
    distance = ((b[0]-a[0])*(b[0]-a[0]))+((b[1]-a[1])*(b[1]-a[1]));
    distance = sqrt(distance);
    printf("distancia: %d ",distance);
    return distance;
}

int tiempoViaje(int t , int x[], int y[]){
    int dis =valorModulo(x,y);
    int tiempo = t * dis;
    printf("\n tiempo :%d \n ",tiempo);
    return tiempo;
}

int main(){
    srand(time(0));
    int x[2] = {1,-2};
    int y[2] = {5,-5};
    valorModulo(x,y);
    tiempoViaje(2 , x , y );
    }

