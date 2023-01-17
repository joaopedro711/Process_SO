#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

/* Struct da estrutura da mensagem */
struct msgp{
	long mtype;
	time_t tempo;
	int pid;
	int vezes;
};

typedef struct msgp Buff;
int main(int argc,char* argv[]){
	int idFilaAtual;
	if(argc!=2){
		printf("Numero de argumentos invalido!");
	}

	/* Caso de erro na obtenção da fila de mensagem, usando a matricula, Joao Pedro = 190057807 como chave */
	if (idFilaAtual = msgget(190057807, 0x1FF) == -1){
		printf("Erro na criacao da fila\n");
		exit(1);
	}

	Buff* mensagem = (Buff*)malloc(sizeof(Buff*));
	(*mensagem).mtype = 4;
	(*mensagem).pid = atoi(argv[1]);

  /* envia mensagem para terminar o processo... */
	msgsnd(idFilaAtual, mensagem, sizeof(Buff) - 4,0);
	printf("Mensagem de terminar processo %s enviada! \n",argv[1]);
	return 0;
}
