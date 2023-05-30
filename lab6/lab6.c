#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <semaphore.h>
#include <unistd.h>



#define PROD  2
#define CONS  4
#define N 10

// Variaveis globais
sem_t bufferVazio,bufferCheio;//condicao
sem_t mutexProd, mutexCons;//exclusao mutua
int Buffer[N];



void Insere (int item) {
    static int in=0;
    
    puts("Produtora verifica se o buffer ta vazio");
    sem_wait(&bufferVazio);
    puts("Produtora avisa que buffer ta vazio"); 

    //exclusao mutua entre produtores
    sem_wait(&mutexProd);
    for (int i=in; i < N; i++){
        Buffer[in] = item;
        printf("colocando elemento na posição %d do buffer \n",in);
        in = (in + 1) % N;
    }

    sem_post(&mutexProd);
    
    puts("Produtora sinaliza buffer ''cheio''(com elemento pra retirar)");
    sem_post(&bufferCheio);

   
}

int Retira (void) {
    int item;
    static int out=0;

    puts("Consumidora verifica se o buffer possui item/esta cheio");
    sem_wait(&bufferCheio);
    puts("Consumidora confirma que o buffer possui item");

    //exclusao mutua entre consumidores

    sem_wait(&mutexCons);
    item = Buffer[out];
    printf("Removendo elemento da posição %d do buffer \n",out);
    out = (out + 1) % N;

    if (out == 0){
        puts("Consumidora sinaliza buffer vazio");
        sem_post(&bufferVazio);
    }
    else{
        puts("Consumidora sinaliza buffer ''cheio''(com elemento pra retirar)");
        sem_post(&bufferCheio);
    }


    sem_post(&mutexCons);

    return item;
}

void *produtor(void * arg) {
    int *tid = (int*) arg;
    int elemento;
    while(1) {
    //produz um elemento....
        printf("Thread produtora %d tenta inserir elemento no buffer\n", *tid);
        Insere(elemento);
         sleep(1);
    }
    pthread_exit(NULL);
}
void *consumidor(void * arg) {
    int *tid = (int*) arg;
    int elemento;
    while(1) {
        printf("Thread consumidora %d tenta remover elemento no buffer\n", *tid);
        elemento = Retira();
        sleep(1);
    //consome o elemento....
    }
    pthread_exit(NULL);
}

//funcao principal
int main(int argc, char *argv[]) {
  //identificadores das threads
    pthread_t tid[PROD+CONS];
    int idCons[CONS];
    int idProd[PROD];

  //inicia os semaforos
    sem_init(&mutexCons, 0, 1);
    sem_init(&mutexProd, 0, 1);
    sem_init(&bufferCheio, 0, 0);
    sem_init(&bufferVazio, 0, 1);
  
    
    //cria as threads produtoras
    for(int i=0; i<PROD; i++) {
        idProd[i] = i;
        if(pthread_create(&tid[i], NULL, produtor, (void *) &idProd[i])) exit(-1);
    } 
    
    //cria as threads consumidoras
    for(int i=0; i<CONS; i++) {
        idCons[i] = i;
        if(pthread_create(&tid[i+PROD], NULL, consumidor, (void *) &idCons[i])) exit(-1);
    } 

    pthread_exit(NULL);

    return 0;
}
