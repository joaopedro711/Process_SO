/* 
	Após compilar o arquivo, deve ser rodado da seguinte maneira: 
	./nomeArquivoExecutavel arquivoTeste prioridade (diretiv para rodar programa em background)
	./execproc teste 1 &
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <signal.h>

/* Struct para salvar dados */
struct msgp{
	long mtype;
	time_t tempo;
	int pid;
	int vezes;
};
typedef struct msgp Buff;

/* Função Main */
int main(int argc, char* argv[]){

	/* Verificar se a prioridade recebida é valida (1 alta, 2 média, 3 baixa) */
	if((atoi(argv[2]) < 1) || (atoi(argv[2]) > 3)){
		printf("Prioridade recebida é inválida!\n");
		exit(2);
	}

	/* Verificação para ver se o argumento de entreda é válido */
	if(argc<3){
		printf("Quantidade de argumentos inválidos!\n");
		exit(1);
	}

	int idFilaAtual, pid, i;
	/* Caso de erro na obtenção da fila de mensagem, usando a matricula, Joao Pedro = 190057807 como chave */
	if (idFilaAtual = msgget(190057807, 0x1FF) < 0){
		printf("Erro ao receber fila!\n");
		exit(1);
	}

	/* Os argumentos recebidos do pragrama executado serão salvos no vetor */
	char **vetorAuxiliar;
	vetorAuxiliar = (char**) malloc ((argc-2)*sizeof(char*));

	for(i = 0; i < (argc-2); i++){
		vetorAuxiliar[i] = (char *) malloc (100);
		vetorAuxiliar[i][0] = '\0';
	}

	/* Prioridade é salva em vetorAuxiliar*/
	for(i = 0; i < (argc-2); i++){
		strcpy(vetorAuxiliar[i], argv[i+2]);
		printf("%s \n", vetorAuxiliar[i]);
	}

	if((pid = fork()) < 0){
		printf("Erro no fork! \n");
		exit(1);
	}

	if(pid == 0){
		/* Se processo atual for o filho */
		execv(argv[1],vetorAuxiliar);
	}else{
		/* Se processo atual não for o filho, o pai */
		/* Alocação dinâmica para salvar mensagem na fila */
		Buff* mensagem = (Buff*) malloc (sizeof(Buff*));

		mensagem->mtype = atoi(argv[2]);
		mensagem->pid = pid;
		mensagem->vezes = 0;
		mensagem->tempo = time(NULL);
		msgsnd(idFilaAtual, mensagem, sizeof(Buff) - 4, 0);
		printf("Mensagem enviada com sucesso!\n");
		kill(pid, SIGTSTP);
	}
	return 0;
}
