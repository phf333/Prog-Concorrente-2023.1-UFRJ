//lab 3
// Paulo Henrique de França Araujo Cunha - 117277009


import java.util.Scanner;  // Import the Scanner class
import java.lang.Math; // import class math



//--PASSO 1: cria uma classe que estende a classe Thread 
class CalculaPi extends Thread {
   private int n;
   private int id;
   private int numero_threads;
   private double soma;
   
   //--construtor
   public CalculaPi(int n,int numero_threads,int id) { 
      this.n = n;
      this.id = id;
      this.numero_threads = numero_threads;
   }
    
   //--metodo executado pela thread
   public void run() {
       for (int i=id; i<this.n; i+=this.numero_threads) {
            soma+=((Math.pow(-1,i))*(1.0/((2*i)+1)));
            //System.out.println((Math.pow(-1,i))*(1/((2*i)+1))); 
   }
   }

   public double getSoma(){
      return soma;
   }
}

//--classe do metodo main
class GeraPi {

    

   public static void main (String[] args) {

      
      


      //criar um objeto da classe scanner para podermos pegar informação do usuario
      Scanner sc = new Scanner(System.in);
      System.out.print("Digite a quantidade de Threads: ");
      int numero_threads = sc.nextInt();

      System.out.print("e o N para gerar a aproximação de PI: ");
      int n = sc.nextInt();

      //sc.close();
      
      //--reserva espaço para um vetor de threads
      Thread[] threads = new Thread[numero_threads];
    
      //--PASSO 2: cria threads da classe que estende Thread
      for (int i=0; i<threads.length; i++) {
         //final String m = "Ola da thread " + i;
         threads[i] = new CalculaPi(n,numero_threads,i);
      }

      //--PASSO 3: iniciar as threads
      for (int i=0; i<threads.length; i++) {
         threads[i].start();
      }

      //--PASSO 4: esperar pelo termino de todas as threads
      for (int i=0; i<threads.length; i++) {
         try { threads[i].join(); } 
         catch (InterruptedException e) { return; }
      }

      
      // capturar todas o resultados das somas e printar o valor aproximado de PI
      
      double pi = 0.0;
      for (int i=0 ; i<threads.length; i++){
         CalculaPi var=(CalculaPi) threads[i];
         pi+=var.getSoma();
      }


      pi=4*pi;
      
      // tive que transformar o pi em string pra poder apresentar os valores com mais casas decimais
      System.out.printf("Valor de Pi aproximado com n igual a %d e calculado usando %d Threads: %s \n",n,numero_threads,String.valueOf(pi));
      
      System.out.printf("Erro aproximado: %s \n",(String.valueOf(Math.PI-(pi))));
      

      
   }
}