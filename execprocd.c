#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <signal.h>
 struct msgp{
    long mtype;
    time_t tempo; // Usado na parte dos processos
    int pid;
 };

typedef struct msgp Buff;
int main(){

    int idfila;
     // O hexa 0x1FF faz referência as permissôes dadas a fila de mensagens criada, no caso tem permissao de leitura pelo dono, execução pelo dono, execução em grupo e por terceiros.
    idfila = msgget(190057807, IPC_CREAT | 0x1FF);
    if (idfila == -1) {
    printf("Fila não foi criada! Erro na criação\n");
    exit(1);
    }
    Buff* msg = (Buff*)malloc(sizeof(Buff*));
    int Processo=0,Shutdown=0, Cancelamento=0; 
    while(1){

        //recebe termino de execprodc
        if((Shutdown = msgrcv(idfila,msg,sizeof(Buff) - 4,9,IPC_NOWAIT)) >0 ){  // Recebe o msgtyp 9 que indica o final do processo geral
            printf("Shutdown no execprocd \n");
            //Encerramento de todos os processo de todas as prioridades
            while((Shutdown = msgrcv(idfila,msg,sizeof(Buff) - 4,1,IPC_NOWAIT)) >0){ // type 1 
                printf("O pid do processo prioridade 1 era: %d \n", (*msg).pid);
                kill((*msg).pid,SIGKILL);
            }
            while((Shutdown= msgrcv(idfila,msg,sizeof(Buff) - 4,2,IPC_NOWAIT)) >0){ // type 2
                printf("O pid do processo prioridade 2 era: %d \n", (*msg).pid);
                kill((*msg).pid,SIGKILL);
            }
            while((Shutdown = msgrcv(idfila,msg,sizeof(Buff) - 4,3,IPC_NOWAIT)) >0){ // type 3
                printf("O pid do processo prioridade 3 era: %d \n", (*msg).pid);
                kill((*msg).pid,SIGKILL);
            }
            //remove a fila
            msgctl(idfila,IPC_RMID,NULL); // Primitiva de controle de remoção de fila
            exit(9);
        }
        //recebe sinal de cancelamento
        if((Cancelamento = msgrcv(idfila,msg,sizeof(Buff) - 4,4,IPC_NOWAIT)) >0){ // Msgtyp do tipo 4 faz referencia ao cancelamento de processos
            printf("Processamento da mensagem de cancelamento para o processo de Pid :%d \n",(*msg).pid); 
            kill((*msg).pid,SIGKILL);
        }
        // Recebe sinal de execução de processo -> Retirado da entrega final por estar truncando a execução e gerando seg fault. 

    }
    return 0;
}
