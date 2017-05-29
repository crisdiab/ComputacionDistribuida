// Funcionamiento de hilos, programa obtenido de 
// http://cortesfernando.blogspot.com/2011/11/linux-threads.html
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t m;


struct param{
char *frase;
int numero;
};

/*Funcion que indica el procedimiento de los hilos*/
void hiloMensaje(struct param *mensa){
//printf("prueba y error");
printf("%s %d \n", mensa->frase, mensa->numero);



}


void tablas(int num){
int i=0;

//bloqueando con mutex
pthread_mutex_lock(&m);
while(i<6)
{
printf("%d * %d = %d \n",num,i,(i*i));
i++;
}

// implementacion para consumir cpu y medir el tiempo

float a = 254 , b =65651,c=484515;
int cont=0;
while (cont<100000000 ){
//printf(" hola \n");
a=b*c;
b=(c*c*c + a)/365 ;
cont++;
}


// medir eficiencia 
    char str[200] = "ps -aux | grep mutex_hilos ";
    system(str);


//Desbloqueando
pthread_mutex_unlock(&m);

}


int main(){
system("clear");




pthread_t tid[2];

struct param parametro1 ={"I am the thread number ",1 };
struct param parametro2 ={"I am other thread, I am the ",2 };

int p1= 14;
int p3 = 7;
// probar crear con un while
pthread_create(&(tid[0]) ,NULL,(void*)tablas, (void*) p1 );

pthread_create(&(tid[1]) ,NULL,(void*)tablas, (void*) p3 );

//Esperamos la finalizacion de los hilos
pthread_join(tid[0],NULL );

pthread_join(tid[1], NULL);





return 0;
}
