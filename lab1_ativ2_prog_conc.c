// lab 1 - Programação Concorrente (ICP361)
// Paulo Henrique de França Araujo Cunha - 117277009
// atividade 2


#include <stdio.h>
#include <pthread.h>

//cria vetor de longs de 10000 posições
long vetor[10000];


// função que irá multiplicar por 2 todos os elementos do vetor
void *multiplica_vetor(void *arg){

    printf("Thread %ld executando...\n", arg);

    if ( arg == 0){
        for(int i=0 ; i < 5000 ; i++) {
        long auxiliar=vetor[i] * 2;
        vetor[i]=auxiliar;
        }
    }

    if ( arg  == 1){
        for(int i=5000 ; i < 10000 ; i++) {
        long auxiliar=vetor[i] * 2;
        vetor[i]=auxiliar;
        }
    }

    pthread_exit(NULL);
}

// função que verificar se todos os elementos "3" do vetor de 10k posições foram multiplicados 
// por 2
void verificar(long *vet){
     for(int i=0 ; i < 10000 ; i++) {
        //printf("%ld\n",vet[i]);
        if (vet[i] != 6){
            printf("Houve algum problema\n");
            break;
        }     
    }
    printf("Tudo ok\n");
}

int main(){

    // laço para preencher com o elemento "3" as 10000 posições do vetor
    for(int i=0 ; i < 10000 ; i++) {
        vetor[i]=3;    
    }

    
    pthread_t threads[2];

    for (long i = 0; i < 2; i++) {
    pthread_create(&threads[i], NULL, multiplica_vetor, (void *) i);
  }

    for (int i = 0; i < 2; i++) {
    pthread_join(threads[i], NULL);
  }

    // chama função para verificar se as operações pedidas foram feitas corretamente
    verificar(vetor);
    
    


}