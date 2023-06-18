#/* Disciplina: Programacao Concorrente */
#/* Prof.: Silvana Rossetto */
#/* Módulo 4 - Laboratório: 7 */
#/* Paulo Henrique de França Araujo Cunha - 117277009 */ 
#/* Atividade 5 */ 


from threading import Thread
from threading import Lock
import time
import math




class Pi():
    def __init__(self):
        self.pi = 0
        self.lock = Lock()

    def incrementa(self,valor):
        self.lock.acquire()
        self.pi += valor
        self.lock.release()

    def getValor(self):
        return (self.pi*4)


class CalculaPI(Thread):
    def __init__(self, id):
        super().__init__()
        self.id=id
        self.lock = Lock()

        

    def run(self):
        for i in range(self.id,n,nthreads):
            self.lock.acquire()
            pi.incrementa(((pow(-1,i))*(1/((2*i)+1))))
            self.lock.release()


if __name__ == '__main__':

    #alterado conforme testes
    nthreads=4
    n=100000

    threads = [CalculaPI(i) for i in range(0,nthreads)]
    start = time.time()

    #cria variavel compartilhada
    pi = Pi()


    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()


    print("Pi é igual a: ",pi.getValor())
    print("Tempo de execução: ",time.time() - start)
    ##print("erro: ",math.pi - pi.getValor() )







