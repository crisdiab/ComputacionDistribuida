/*
*Para el desarrollo de este programa se tomo como base el programa creado por 
*Jorge Duran para Somos Binarios
* Disponible en: https://www.somosbinarios.es/programacion-paralela-en-c-semaforos/
*/
 
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h> 
/****************************************************************
Funciones auxiliares para inicializar, hacer wait y hacer Signal
Funcionan con arrays de semaforos, si solo hay uno ese parametro es 0
*******************************************************************/
void error(char* errorInfo) {
    fprintf(stderr,"%s",errorInfo);
    exit(1);
}
 
void doSignal(int semid, int numSem) {
    struct sembuf sops; //Signal
    sops.sem_num = numSem;
    sops.sem_op = 1;
    sops.sem_flg = 0;
 
    if (semop(semid, &sops, 1) == -1) {
        perror(NULL);
        error("Error al hacer Signal");
    }
}
 
void doWait(int semid, int numSem) {
    struct sembuf sops;
    sops.sem_num = numSem; /* Sobre el primero, ... */
    sops.sem_op = -1; /* ... un wait (resto 1) */
    sops.sem_flg = 0;
 
    if (semop(semid, &sops, 1) == -1) {
        perror(NULL);
        error("Error al hacer el Wait");
    }
}
 
void initSem(int semid, int numSem, int valor) { //iniciar un semaforo
  
    if (semctl(semid, numSem, SETVAL, valor) < 0) {        
    perror(NULL);
        error("Error iniciando semaforo");
    }
}
 
 
 
 
 
 
int main() {
    puts("Sincronizacion con Semaforos ");
    int semaforo;
    
 
    //Manera de usar semget http://pubs.opengroup.org/onlinepubs/7908799/xsh/semget.html
    //Creamos un semaforo y damos permisos para compartirlo
    if((semaforo=semget(IPC_PRIVATE,1,IPC_CREAT | 0700))<0) {
        perror(NULL);
        error("Semaforo: semget");
    }
    
 
    initSem(semaforo,0,1);
    puts("Hay una plaza libre");
    
    
 
switch (fork())
   {
       case -1:
        error("Error en el fork"); 
        
       
    case 0:  /* Hijo */
        doWait(semaforo,0);
        puts("Entro el hijo, el padre espera");
       
        //implemtacion tabla de multiplicar
int i =0;
int num =7;
while(i<6)
{
printf(" %d * %d = %d \n",num,i,num*i );
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
    char str[200] = "ps -aux | grep semaforos ";
    system(str);


       


        puts("Fin del hijo");
        doSignal(semaforo,0);
        exit(0);
 
    default: /* Padre */
        doWait(semaforo,0);
        puts("Entro el padre, el hijo espera");
//implementacion de tabla de multiplicar 

 i =0;
 num =14;
while(i<6)
{
printf(" %d * %d = %d \n",num,i,num*i );
i++;
}


// implementacion para consumir recursos
 a = 254 , b =65651,c=484515;
 cont=0;
while (cont<100000000 ){
//printf(" hola \n");
a=b*c;
b=(c*c*c + a)/365 ;
cont++;
}




// medir eficiencia 

    char str1[200] = "ps -aux | grep semaforos ";
    system(str1);





        puts("Fin del padre,El padre sale");
        doSignal(semaforo,0);
        
    }       
    
    sleep(1);
    
     //Liberacion del semaforo
     if ((semctl(semaforo, 0, IPC_RMID)) == -1) {
            perror(NULL);
            error("Semaforo borrando");
        }
    return 0;
}
