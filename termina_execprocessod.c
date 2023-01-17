#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
// Struct da estrutura da mensagem
 struct msgp{
 	long mtype;
 	time_t tempo;
 	int pid;
 	int vezes;
 };

typedef struct msgp Buff;
int main(){

	int idfila;
	// Caso de erro na obtenção da fila de mensagem, usando a matricula, Joao Pedro = 190057807 como chave
	if ((idfila = msgget(190057807, 0x1FF)) < 0)  // Como nao conseguiu o msqid, retornou -1.
		{
		printf("Falha em obter Identificador da Fila\n");
		exit(1);
		}
    // Continuação depois de achar o idfila (msqid);

	Buff* mensagem = (Buff*)malloc(sizeof(Buff*));
	mensagem->mtype = 9; // Definição para que execprocd possa entender que recebeu a terminação de seu processo e poder parar.
	mensagem->pid = 0;
	msgsnd(idfila,mensagem,sizeof(Buff) - 4,0); // o 0 aqui é para definir que é uma mensagem vazia, apenas uma indicação de ação para o execprocd
	printf("Mensagem de terminar execprocd enviada! \n");
	return 0;
}
