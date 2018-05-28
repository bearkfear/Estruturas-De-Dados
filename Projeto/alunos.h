/*
*   Trabalho da cadeira de ESTRUTURAS DE DADOS.
*   Professor: Jonas B. Gassen
*   Aluno: Enrico Da Silva.
*   UFSM. Politécnico, 2018;
*/
/*============================================================================*/
/*============================         REGISTROS      ========================*/
/*============================================================================*/
// Registro de alunos
struct aluno {
	unsigned int matricula;
	char nome[100];
	char uNome[100];
	char email[100];
	struct aluno *prox;
};
// Lista simplesmente encadeada dinâmica
struct listaDM {
  short int chave;
  struct listaDM *prox;
};

/*============================================================================*/
/*============================ Protótipos: GENÉRICOS =========================*/
/*============================================================================*/
void clsBuffer (void);
/*!--------------------------------------------------------------------------!*/

/*============================================================================*/
/*============================ Protótipos: INSERÇÃO ==========================*/
/*============================================================================*/
void clsBuffer (void);
short int verificaCadastro (unsigned int matricula, unsigned int original);
struct listaDM *listaDinamica (struct listaDM *ponteiro, const unsigned short int *chave);
struct aluno *insereLista (struct aluno *n, unsigned int *matricula);
struct listaDM *insert (struct aluno *ponteiro, struct listaDM *lista);
/*!--------------------------------------------------------------------------!*/

/*============================================================================*/
/*=========================== Protótipos: VISUALIZAÇÃO =======================*/
/*============================================================================*/
void watchInfoAluno(struct aluno *ponteiro);
void watchSubList (struct aluno *ponteiro, unsigned int matricula, unsigned short *conta);
void watchList (struct listaDM *lista, struct aluno *ponteiro);
void watch(struct aluno *ponteiro, struct listaDM *lista);
/*!--------------------------------------------------------------------------!*/

/*============================================================================*/
/*=========================== Protótipos: REMOÇÃO ============================*/
/*============================================================================*/
struct aluno *removeNaListaDoVetor (struct aluno *ponteiro, unsigned int mat);
struct listaDM *removerAlunos(struct aluno *ponteiro, struct listaDM *lista);
/*!--------------------------------------------------------------------------!*/

void clsBuffer (void) {
  while (getchar() != '\n');
}

/*-------------------------------------------------------------------------!*/

void watchInfoAluno(struct aluno *ponteiro) {
  printf("\t==========================================================\n\n");
  printf("\t\tMatrícula: %u\n", ponteiro->matricula);
  printf("\t\tNome: %s", ponteiro->nome);
  printf("\t\tSobrenome: %s", ponteiro->uNome);
  printf("\t\tE-mail: %s", ponteiro->email);
  printf("\n\t==========================================================\n");
}

void watchSubList (struct aluno *ponteiro, unsigned int matricula, unsigned short *conta) {
  
  /*!---------------------------------------------------------------------------
    Função responsável por chamar a função que imprime, e também responsavel por
    percorrer a lista encadeada dentro de cada chave. Caso haja uma chave, será
    utilizada para visualização a partir da matricula.
  !---------------------------------------------------------------------------*/
  
  if (matricula) {
    unsigned short int chave = CALCULO_HASH(matricula);
    ponteiro = ponteiro+chave;
    if (ponteiro->matricula == matricula) {
      (*conta)++;
      watchInfoAluno(ponteiro);
    } else {
      while (ponteiro->prox != NULL && ponteiro->matricula != matricula) {
        ponteiro = ponteiro->prox;
        (*conta)++;
      }
      if (ponteiro->matricula == matricula) {
        watchInfoAluno(ponteiro);
        (*conta)++;
      } else {
        printf("\tMatrícula não encontrada!\n");
      }
    }
  } else {
    watchInfoAluno(ponteiro);
    if (ponteiro->prox) {
      while (ponteiro->prox) {
        ponteiro = ponteiro->prox;
        watchInfoAluno(ponteiro);
      }
    }
  }
}

void watchList (struct listaDM *lista, struct aluno *ponteiro) {
  
  /*---------------------------------------------------------------------------!
    Função escrava, no qual comanda se o processo vai ser continuado. Verifica
    se existe algo na lista, caso exisa. Questiona se é necessário percorre-la
    ou é de chave única.
  !---------------------------------------------------------------------------*/
  
  if (lista) {
    if (lista->prox) {
      struct listaDM *p;
      p = lista;
      short aux;
      watchSubList(ponteiro+lista->chave, 0, NULL);
      while (p->prox) {
        p = p->prox;
        aux = p->chave;
        watchSubList(ponteiro+aux, 0, NULL);
      }
    } else {
      watchSubList(ponteiro+lista->chave, 0, NULL);
    }
  } else {
    printf("\n\tVazio!\n");
  }
}

void watch(struct aluno *ponteiro, struct listaDM *lista) {
  
  /*---------------------------------------------------------------------------!
    Função chamadora das funções persistentes de visualização
  ---------------------------------------------------------------------------!*/
  
  system("cls");
  printf("========================== VISUALIZAÇÃO ==========================\n");
  short int aux;
  while (1) {
    printf("\n\t1.Exibir o aluno com base em sua matricula.\n");
    printf("\t2.Exibir todos os alunos armazenados\n");
    printf("\t3.Voltar.\n");
    printf("\tOpção (1, 2, 3): ");
    scanf("%hi", &aux);
    clsBuffer();
    switch (aux) {
      case 1: {
        unsigned int mat;
        printf("\n\tPesquisa por matrícula: ");
        scanf("%u", &mat);
        clsBuffer();
        if (!mat) {
          printf("\tValor invalido!\n");
        } else {
          short int conta = 0;
          watchSubList(ponteiro, mat, &conta);
          printf("\n\tNúmero de passos dados: %hi", conta);
          printf("\n");
        }
        break;
      }
      case 2: {
        watchList(lista, ponteiro);
        break;
      }
      case 3: {
        return;
      }
      default: {
        printf("\tValor invalido!\n");
        break;
      }
    }
  }
  printf("\n\t");
  system("pause");
}

/*-------------------------------------------------------------------------!*/
void removeNoInicioDoVetor (struct aluno *ponteiro, unsigned int mat) {

  struct aluno *p = ponteiro->prox;

  ponteiro->matricula = p->matricula;
  strcpy(ponteiro->email, p->email);
  strcpy(ponteiro->nome, p->nome);
  strcpy(ponteiro->uNome, p->uNome);

  ponteiro->prox = ponteiro->prox->prox;
  free(p);
}
struct aluno *removeNaListaDoVetor (struct aluno *ponteiro, unsigned int mat){
  struct aluno *ant = NULL;
  struct aluno *p = ponteiro;

  while (p && p->matricula != mat) {
    ant = p;
    p = p->prox;
  }

  if (!p) {
    return ponteiro;
  }
  if (!ant) {
    ponteiro = p->prox;
  } else {
    ant->prox = p->prox;
  }
  free(p);
  return ponteiro;
}

struct listaDM *removerAlunos(struct aluno *ponteiro, struct listaDM *lista) {
  
  system("cls");
  printf("========================== REMOVER ALUNOS ==========================\n");
  
  printf("\n\tDigite o número da matrícula: ");
  unsigned int mat;
  scanf("%u", &mat);
  clsBuffer();
  
  if (!mat) {
    printf("\tValor invalido!\n");
    system("pause");
    return lista;
  }
  
  short int chave = CALCULO_HASH(mat);
  ponteiro = ponteiro+chave;
  
  if (!ponteiro->matricula) {
    printf("\tMatrícula não existe...\n\t");
    system("pause");
    return lista;
  }
    
  if (!ponteiro->prox) {
    if (ponteiro->matricula != mat) {
      printf("\tMatrícula não existe...\n\t");
      system("pause");
      return lista;
    }
    // DELETA DO VETOR E PROCURA NA LISTA ENCADEADA
    //DELETA VETOR
    ponteiro->matricula = 0;

    //?? DELETA DA LISTA
    struct listaDM *ant = NULL;
    struct listaDM *p = lista;

    while (p && p->chave != chave) {
      ant = p;
      p = p->prox;
    }

    if (!p) {
      return lista;
    }
    if (!ant) {
      lista = p->prox;
    } else {
      ant->prox = p->prox;
    }
    free(p);
    return lista;
  }
  // PROCURA E DELETA NO VETOR COM A CHAVE E LISTA ENCADEADA.
  if (ponteiro->matricula == mat) {
    removeNoInicioDoVetor(ponteiro, mat);
  } else {
    ponteiro->prox = removeNaListaDoVetor(ponteiro->prox, mat);
  }
  return lista;
}
void infoPessoa(struct aluno *pessoa) {
  printf("\tPrimeiro nome: ");
  fgets(pessoa->nome, 100, stdin);
  printf("\tUltimo nome: ");
  fgets(pessoa->uNome, 100, stdin);
  printf("\tEmail: ");
  fgets(pessoa->email, 100, stdin);
//  strcpy(pessoa->nome, "Padrão");
//  strcpy(pessoa->uNome, "Padrão");
//  strcpy(pessoa->email, "Padrão");
  printf("\n==================================================================\n");
}

short int verificaCadastro (unsigned int matricula, unsigned int original) {
  
  /*---------------------------------------------------------------------------!
  ========================== SOBRE RETORNOS DA FUNÇÃO ==========================
    CASO A FUNÇÃO RETORNE:
    -1: As matrículas não são iguais;
    1: As matrículas são iguais e deseja-se recadastrar a existente;
    0: As matrículas são iguais mas, deseja-se manter como está.
  ---------------------------------------------------------------------------!*/
  
  if (original == matricula) {
    char aux = 0;
    printf("\n\tMatricula já está cadastrada. Deseja recadastrar? (s/n): ");
    while (1) {
      scanf("%c", &aux);
      clsBuffer();
      switch (aux) {
        case 'S': {
          printf("\n");
          return 1;
          break;
        }
        case 's': {
          printf("\n");
          return 1;
          break;
        }
        case 'N': {
          printf("\n");
          return 0;
          break;
        }
        case 'n': {
          printf("\n");
          return 0;
          break;
        }
        default: {
          printf("\tSeleção inválida.. :(\n\tOpção (s/n): ");
          break;
        }
      }
    }
  }
  return -1;
}

struct listaDM *listaDinamica (struct listaDM *ponteiro, const unsigned short int *chave) {
  if (!ponteiro) {
    struct listaDM *novo = (struct listaDM*) malloc (sizeof(struct listaDM));
    novo->chave = *chave;
    novo->prox = ponteiro;
    return novo;
  } else {
    struct listaDM *p;
    p = ponteiro;
    while (p->prox != NULL && p->chave != *chave) {p = p->prox;}
    if (p->chave == *chave) {
      // Não faz nada;
    } else {
      struct listaDM *novo = (struct listaDM*) malloc (sizeof(struct listaDM));
      novo->chave = *chave;
      novo->prox = p->prox;
      p->prox = novo;
    }
  }
  return ponteiro;
}


struct aluno *insereLista (struct aluno *n, unsigned int *matricula) {
  if (!n) {
    /*-------------------------------------------------------------------------!
      Se a lista estiver vázia, será inserido o elemento em primeiro lugar e
      retornado o valor que foi recebido, que no caso é NULL (Vázio). O elemento
      NULL delimita o fim da lista Encadeada;
    -------------------------------------------------------------------------!*/
    struct aluno *novo = (struct aluno *)malloc (sizeof(struct aluno));
    novo->prox = n;
    novo->matricula = *matricula;
    infoPessoa(novo);
    return novo;
  } else {
    /*-------------------------------------------------------------------------!
      O programa entra nessa condição caso a lista já esteja mais de um elemento
      inserido. Os nós serão verificados, e caso não haja nenhuma matricula
      repetida, será encadeado ao final da lista e o final (que é NULL) será
      mantido em último lugar.
    -------------------------------------------------------------------------!*/
    struct aluno *p;
    p = n;
    while (p->prox != NULL && p->matricula != *matricula) {p = p->prox;}
    int aux = verificaCadastro(p->matricula, *matricula);
    if (aux == -1) {
      struct aluno *novo = (struct aluno *) malloc (sizeof(struct aluno));
      novo->matricula = *matricula;
      infoPessoa(novo);
      p->prox = novo;
      novo->prox = NULL;
    } else if (aux) {
      p->matricula = *matricula;
      infoPessoa(p);
    }
    return n;
  }
}


struct listaDM *insert (struct aluno *ponteiro, struct listaDM *lista) {

  unsigned int matricula;
  system("cls");
  printf("============================ INSERÇÃO ============================\n\n");

  printf("\tMatricula: ");
  scanf("%u", &matricula);
  clsBuffer();
  
  if (!matricula) {
    printf("\tMatrícula invalida!\n\t");
    system("pause");
    return lista;
  } else {
    unsigned short int chave = CALCULO_HASH(matricula);
    ponteiro = ponteiro+chave;
    if (ponteiro->matricula) {

      short int aux = verificaCadastro(matricula, ponteiro->matricula);
      if (aux == -1) {
        ponteiro->prox = insereLista(ponteiro->prox, &matricula);
        return lista;
      } else if (!aux) {
        return lista;
      }
    }
    ponteiro->matricula = matricula;
    infoPessoa(ponteiro);
    return listaDinamica(lista, &chave);
  }
}
