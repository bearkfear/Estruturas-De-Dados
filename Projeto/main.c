#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define TAM 10
#define CALCULO_HASH(valor) valor % TAM
#include "alunos.h"


int main(int argc, char *argv[]) {
  
  setlocale(LC_ALL,"");

	struct aluno alunos[TAM], *ponteiro;
	struct listaDM *lista = NULL;
	ponteiro = alunos;
	
  for (int i = 0; i < TAM; i++) {
    (ponteiro+i)->prox = NULL;
    (ponteiro+i)->matricula = 0;
  }
	unsigned short int opcao;
  while (1) {
    system("cls");
    printf("===================================================================\n");
    printf("==================== REGISTRO DE ALUNOS - UFSM ====================\n");
    printf("===================================================================\n\n");
    printf("\t1.Inserir \n");
    printf("\t2.Remover \n");
    printf("\t3.Visualizar\n");
    printf("\t4.Sair. ");
    printf("(1, 2, 3, 4): ");
    scanf("%hu", &opcao);
    clsBuffer();

    switch (opcao) {
      case 1: {
        lista = insert(ponteiro, lista);
        break;
      }
      case 2: {
        lista = removerAlunos(ponteiro, lista);
        break;
      }
      case 3: {
        watch(ponteiro, lista);
        break;
      }
      case 4: {
        printf("Saindo...!\n");
        return 0;
      }
      default: {
        printf("Valor invalido!\n");
        break;
      }
    }
  }
}
