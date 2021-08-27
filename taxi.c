#include <stdio.h>
#include <time.h>
#include <math.h>



// typedef struct Taxi {
//    int  ocupado;
//    int  posicionInicial[2];
//    int  taxi_id;
// } Taxi;



int rand();
int srand();
int valorModulo(int  a[] , int b[]);

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

int puedeSerAtendido( int a[] ,int b[] , int limite){
    int distancia = valorModulo(a,b);
    int bandera = 0;
    if ( distancia < limite){
        bandera = 1;
    }
    printf(" la bandera es %d :" , bandera);
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
    // int x[2] = {1,-2};
    // int y[2] = {5,-5};
    // valorModulo(x,y);
    // tiempoViaje(2 , x , y );
    // puedeSerAtendido(x,y,4);

    // Taxi me = { .taxi_id = 1,
    //               .ocupado = 1,
    //               .posicionInicial = y   };

    // printf(" Taxi numero: %d\n EstadoOcupado: %d\n Posicion Inicial%d\n",  me.taxi_id, me.ocupado ,me.posicionInicial);

    }

