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
};

typedef struct msgp Buff;
int main(){

	int idFilaAtual;
	/* idFila é utilizada para detectar erro ao obter fila de mensagem utilizando a chave padrão */
	/* Foi utilizada a chave matricula do João Pedro = 190012358, */
	if ((idFilaAtual = msgget(190057807, 0x1FF)) < 0) {
		/* Como nao conseguiu o msqid, retornou -1. */
		printf("Falha em obter Identificador da Fila\n");
		exit(1);
	}
  
	/* Caso encontrar idFilaAtual (msqid) */
	Buff* mensagem = (Buff*)malloc(sizeof(Buff*));
	(*mensagem).mtype = 9;	// Definição para que execprocd possa entender que recebeu a terminação de seu processo e poder parar.
	(*mensagem).pid = 0;
	msgsnd(idFilaAtual,mensagem,sizeof(Buff) - 4,0);	// o 0 aqui é para definir que é uma mensagem vazia, apenas uma indicação de ação para o execprocd
	printf("Mensagem de terminar execprocd enviada! \n");
	return 0;
}
