#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
 
struct msgp{
 	long mtype;
 	time_t tempo;
 	int pid;
    int vezes;
};

typedef struct msgp Buff;
int main(int argc,char* argv[]){
	int idfila;
	if(argc!=2){
		printf("Numero de argumentos invalido!");
	}
    //se der erro na criação da fila de mensagem, usando a matricula, Joao Pedro = 190057807 como chave
	if (idfila = msgget(190057807, 0x1FF) == -1){
		printf("erro na criacao da fila\n");
		exit(1);
	}
        
	Buff* msg = (Buff*)malloc(sizeof(Buff*));
	(*msg).mtype = 4;
	(*msg).pid = atoi(argv[1]);

    //envia mensagem para terminar o processo...
	msgsnd(idfila,msg,sizeof(Buff) - 4,0);
	printf("Mensagem de terminar processo %s enviada! \n",argv[1]);
	return 0;
}
