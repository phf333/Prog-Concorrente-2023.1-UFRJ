// Programação Concorrente - 2023.1

// Alunos:
// Clayton Junior da Silva Portal - 117256689
// Paulo Henrique de França Araujo Cunha - 117277009




#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100000
#define NUM_THREADS 2

typedef struct {
  int inicio;
  int fim;
  int *vetor;
  int ID;
} ParametroThread;


// função para criar vetor com elementos aleatório
int *criarVetor() {
  int *vetor = (int *)malloc(SIZE * sizeof(int));

  if (vetor == NULL) {
    printf("Erro ao alocar memória para o vetor\n");
    return NULL;
  }

  srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

  for (int i = 0; i < SIZE; i++) {
    vetor[i] = rand() % 100000; // Preenche o vetor com valores aleatórios
  }

  return vetor;
}

// função para criar vetor ordenado
int *criarVetorOrdenado() {
  int *vetor = (int *)malloc(SIZE * sizeof(int));

  if (vetor == NULL) {
    printf("Erro ao alocar memória para o vetor\n");
    return NULL;
  }

  srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

  for (int i = 0; i < SIZE; i++) {
    vetor[i] = i; // Preenche o vetor com valores aleatórios
  }

  return vetor;
}

// Divide o vetor em duas partes e mescla as partes ordenadamente
void merge(int inicio, int meio, int fim, int *vetor) {

  int tamEsq = meio - inicio + 1;
  int tamDir = fim - meio;

  // Aloca memória para as duas partes
  int *esquerda = (int *)malloc(tamEsq * sizeof(int));
  int *direita = (int *)malloc(tamDir * sizeof(int));

  // Copia os elementos para as partes esquerda e direita
  for (int i = 0; i < tamEsq; i++) {
    esquerda[i] = vetor[inicio + i];
  }

  for (int i = 0; i < tamDir; i++) {
    direita[i] = vetor[meio + 1 + i];
  }

  int i = 0, j = 0, k = inicio;

  // Mescla as duas partes ordenadamente
  while (i < tamEsq && j < tamDir) {
    if (esquerda[i] <= direita[j]) {
      vetor[k] = esquerda[i];
      i++;
    } else {
      vetor[k] = direita[j];
      j++;
    }
    k++;
  }

  // Copia os elementos restantes da parte esquerda, se houver
  while (i < tamEsq) {
    vetor[k] = esquerda[i];
    i++;
    k++;
  }

  // Copia os elementos restantes da parte direita, se houver
  while (j < tamDir) {
    vetor[k] = direita[j];
    j++;
    k++;
  }

  // Libera a memória alocada para as partes
  free(esquerda);
  free(direita);
}

// Ordena o vetor usando o algoritmo de merge sort
void mergeSort(int inicio, int fim, int *vetor) {
  if (inicio < fim) {
    int meio = (inicio + fim) / 2;

    // Ordena a primeira metade
    mergeSort(inicio, meio, vetor);

    // Ordena a segunda metade
    mergeSort(meio + 1, fim, vetor);

    // Mescla as duas metades ordenadas
    merge(inicio, meio, fim, vetor);
  }
}

// função que imprime os valores de um array
void imprimirArray(int *vetor) {
  // Imprime os elementos do vetor
  for (int i = 0; i < SIZE; i++) {
    printf("%d \n", vetor[i]);
  }
  printf("\n");
}

// Função executada por cada thread para realizar o merge sort em uma parte do
// vetor
void *mergeSortThread(void *params) {
  ParametroThread *parametros = (ParametroThread *)params;
  int inicio = parametros->inicio;
  int fim = parametros->fim;
  int *vetor = parametros->vetor;
  int ID = parametros->ID;

  // printf("ID da thread %d\n", ID);
  //  Executa o merge sort na parte do vetor
  mergeSort(inicio, fim, vetor);

  pthread_exit(NULL);
}

// Função que realiza o merge final dos resultados parciais das threads
void merge_final(ParametroThread parametros[]) {
  int *vetor = parametros[0].vetor;

  // Realiza o merge final dos resultados parciais das threads
  for (int salto = 1; salto < NUM_THREADS; salto *= 2) {
    for (int inicio = 0; inicio < NUM_THREADS - salto; inicio += 2 * salto) {
      int meio = inicio + salto - 1;
      int fim = inicio + 2 * salto - 1;

      if (fim >= NUM_THREADS)
        fim = NUM_THREADS - 1;

      merge(parametros[inicio].inicio, parametros[meio].fim,
            parametros[fim].fim, vetor);
    }
  }
}

// Função que verifica se o vetor está ordenado
void VerificaVetorOrdenado(int *vetor, int tamanho) {
  int EstaOrdenado = 0;
  for (int i = 0; i < tamanho; i++) {
    if ((i + 1) == tamanho) {
      break;
    }
    if (vetor[i] <= vetor[i + 1]) {
      continue;
    } else {
      EstaOrdenado++;
    }
  }
  if (EstaOrdenado == 0) {
    printf("O Vetor está ordenado!\n");
  } else {
    printf("O Vetor não está ordenado!\n");
  }
}

// função que verifica igualdade entre vetores
void VerificaVetorIgual(int *vetor, int *vetor_copia, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    if ((i + 1) == tamanho) {
      break;
    }
    if (vetor[i] != vetor_copia[i]) {
      printf("O Vetor não está ordenado!\n");
      break;
    } else {
      continue;
    }
  }
  printf("Os Vetores são iguais!\n");
}

// Função principal
int main() {
  clock_t temp_inicio, temp_fim;
  double tempoConcorrente, tempoSequencial;

  int *vetor;
  int *vetor_copia;

  

  
  // cria vetor que será usado no código
  vetor = criarVetor();

  // criando copia do vetor
  vetor_copia = (int *)malloc(SIZE * sizeof(int));
  memcpy(vetor_copia, vetor, SIZE * sizeof(int));

  // cria um vetor de threads
  pthread_t threads[NUM_THREADS];

  // cria um vetor de struct que possui o inicio/final
  // da parte de cada thread
  ParametroThread parametros[NUM_THREADS];

  // tamanho da parte da thread
  int tamanhoParte = SIZE / NUM_THREADS;
  int resto = SIZE % NUM_THREADS;
  int inicio = 0;
  int fim = -1;
  int ID;

  ///////  *** MERGE SORT CONCORRENTE **** ///////////

  temp_inicio = clock();

  // Divide o vetor em partes e cria as threads
  // para realizar o merge sort em cada parte
  for (int i = 0; i < NUM_THREADS; i++) {
    inicio = fim + 1;
    fim = inicio + tamanhoParte - 1;

    if (resto > 0) {
      fim++;
      resto--;
    }

    // Define os parâmetros da thread
    parametros[i].inicio = inicio;
    parametros[i].fim = fim;
    parametros[i].vetor = vetor;
    parametros[i].ID = i;

    // Cria a thread e inicia a execução da função mergeSortThread
    pthread_create(&threads[i], NULL, mergeSortThread, (void *)&parametros[i]);
  }

  // Aguarda a conclusão de todas as threads
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  // ordenação final do vetor
  merge_final(parametros);

  temp_fim = clock();

  // printf("Array depois do merge sort: \n");
  // imprimirArray(vetor);

  tempoConcorrente = ((double)(temp_fim - temp_inicio)) / CLOCKS_PER_SEC;

  ///////  *** FIM MERGE SORT CONCORRENTE **** ///////////



  
  ///////  *** MERGE SORT SEQUENCIAL **** ///////////

  temp_inicio = clock();
  mergeSort(0, SIZE - 1, vetor_copia);
  temp_fim = clock();

  tempoSequencial = ((double)(temp_fim - temp_inicio)) / CLOCKS_PER_SEC;

  ///////  *** FIM MERGE SORT SEQUENCIAL **** ///////////



  
  //------ Conjunto de testes: ------//

  
  
  printf("Tempo de execução (Merge Sort Concorrente):\n\nNTHREADS = "
         "%d\nNumelementos = %d\n%.10f segundos\n\n",
         NUM_THREADS, SIZE, tempoConcorrente);
  //VerificaVetorOrdenado(vetor, SIZE);

  printf("Tempo de execução (Merge Sort Sequencial):\n\nNum elementos "
         "=%d\n%.10f segundos\n\n",
         SIZE, tempoSequencial);
  //VerificaVetorOrdenado(vetor_copia, SIZE);

  //VerificaVetorIgual(vetor, vetor_copia, SIZE);}


  printf("------------------------------------- \n");

  free(vetor);
  free(vetor_copia);
  
  

  return 0;
}

