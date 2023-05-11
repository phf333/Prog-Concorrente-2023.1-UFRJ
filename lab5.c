/* Disciplina: Programação Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 5 */
/* Codigo: Uso de variáveis de condição e suas operações básicas para sincronização por condição */
// ATIVIDADE 4
// Paulo Henrique de França Araujo Cunha - 117277009 



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  5

/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond1;
pthread_cond_t x_cond2;




/* Thread A */
void *A (void *t) {
  
  printf("“Oi Maria!\n");

  pthread_mutex_lock(&x_mutex);
  x++;
  if (x==2) {
      printf("A:  x = %d, vai sinalizar a condicao \n", x);
      pthread_cond_signal(&x_cond1);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

/* Thread B */
void *B (void *t) {

  printf("“Oi José!\n");

  pthread_mutex_lock(&x_mutex);
  x++;
  if (x == 2) { 
     printf("B:  x = %d, vai sinalizar a condicao \n", x);;
     pthread_cond_signal(&x_cond1);
     //printf("B: sinal recebido e mutex realocado, x = %d\n", x);
  }
  
  pthread_mutex_unlock(&x_mutex); 
  pthread_exit(NULL);
}

/* Thread C */
void *C (void *t) {
  

  pthread_mutex_lock(&x_mutex);
  while (x < 2) { 
     printf("C: x= %d, vai se bloquear...\n", x);
     pthread_cond_wait(&x_cond1, &x_mutex);
  }

  
  printf("“Sente-se por favor.\n");
  x++;
  
  if (x > 2) { 
     printf("C: x= %d, manda broadcast...\n", x);
     pthread_cond_broadcast(&x_cond2);
  }

  pthread_mutex_unlock(&x_mutex); 

  pthread_exit(NULL);
}

/* Thread D */
void *D (void *t) {
  
  

  pthread_mutex_lock(&x_mutex);
  while (x <= 2) { 
     printf("D: x= %d, vai se bloquear...\n", x);
     pthread_cond_wait(&x_cond2, &x_mutex);
  }
  printf("“Ate mais José! %d\n",x);
  pthread_mutex_unlock(&x_mutex); 
  pthread_exit(NULL);
}

/* Thread E */
void *E (void *t) {

  
  pthread_mutex_lock(&x_mutex);
  while (x <= 2) { 
     printf("E: x= %d, vai se bloquear...\n", x);
     pthread_cond_wait(&x_cond2, &x_mutex);
  }
  printf("“Ate mais Maria! %d”\n",x);
  pthread_mutex_unlock(&x_mutex); 
  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond1, NULL);
  pthread_cond_init (&x_cond2, NULL);


  /* Cria as threads */
  pthread_create(&threads[0], NULL, A, NULL);
  pthread_create(&threads[1], NULL, B, NULL);
  pthread_create(&threads[2], NULL, C, NULL);
  pthread_create(&threads[3], NULL, D, NULL);
  pthread_create(&threads[4], NULL, E, NULL);


  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("\nFIM\n");

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond1);
  pthread_cond_destroy(&x_cond2);

}
