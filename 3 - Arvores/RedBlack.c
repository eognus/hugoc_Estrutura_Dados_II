/*
Aluno: Hugo Araujo Corona
Turma: CC6M
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RED 1
#define BLACK 0
// Declaração da estrutura de Nó
struct No{
  int dado;
  struct No *direita;
  struct No *esquerda;
  int cor;
};

// PROTOTIPAÇÃO
// Função que troca cor de sub-árvores
void trocacor(struct No* raiz);

struct No* removemenor(struct No* raiz);

int buscacor(struct No* raiz);
// Função que varre árvore realizando balanceamento
struct No* buscarots(struct No* raiz);

// direcao = 1 -> rotacao pra esquerda, direcao = 2 -> rotacao pra direita
// Função de rotação redblack
struct No* rot(int direcao,struct No* raiz);
// Função de rotação dupla redblack
struct No* rot2(int direcao,struct No* raiz);
// Função de inserção de nó
struct No* insercao(struct No* raiz, int valor);
struct No* insercaoinit(struct No* raiz, int valor);
// Função de exclusão de nó
struct No* exclusao(struct No*raiz, int valor);
// Funções abaixo somente para visualização da árvore, diretas do código da branch principal. 
void mostraArvore(struct No *a, int b);
void imprimeNo(int c, int b);

int main()
{
    int opcao=1, valor;
    struct No* base = NULL;
    printf("----  Bem-vindo à árvore Red Black  ----");
    while(opcao != 5){
        printf("\nEscolha dentre as opções abaixo o que você deseja fazer:\n");
        printf("1 - Inserir Nó\n");
        printf("2 - Inserir Nó em Sequência\n");
        printf("3 - Excluir Nó\n");
        printf("4 - Excluir Nó em Sequência\n");
        printf("5 - Sair\n");
        scanf("%i",&opcao);
        if(opcao == 1){
            printf("\nDigite o valor a ser inserido na árvore: ");
            scanf("%i",&valor);
            base = insercaoinit(base, valor);
            mostraArvore(base, 0);
        }
        else if(opcao == 2){
            while(1){
                scanf("%i",&valor);
                if(valor == -1){
                    break;
                }
                base = insercaoinit(base, valor);
                mostraArvore(base, 0);
            }
        }
        else if(opcao == 3){
            printf("Digite o valor a ser excluído da árvore: ");
            scanf("%i",&valor);
            base = exclusao(base,valor);
            mostraArvore(base,0);
        }
        else if(opcao == 4){
            while(valor != 1){
                scanf("%i",&valor);
                if(valor == -1){
                    break;
                }
                base = exclusao(base, valor);
                mostraArvore(base, 0);
            }
        }
        else if(opcao != 5){
            printf("Opção inválida.\n");
        }
    }
    printf("Fim.");
    return 0;
}

int buscacor(struct No* raiz){
    if(raiz == NULL){
        return BLACK;
    }
    return raiz->cor;
}

struct No* exclusao(struct No *raiz, int valor){
    if(raiz != NULL){
        if(raiz->dado > valor){
            if(buscacor(raiz->esquerda) == BLACK && buscacor(raiz->esquerda->esquerda) == BLACK){
                raiz = rot2(1, raiz);
            }
            raiz->esquerda = exclusao(raiz->esquerda, valor);
        }
        else{
            
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                raiz = NULL;
            }
            else if(raiz->esquerda == NULL){
                raiz = raiz->direita;
            }
            else if(raiz->direita == NULL){
                raiz = raiz->esquerda;
            }
            else{
                if(buscacor(raiz->esquerda) == RED){
                    raiz = rot(2,raiz);
                }
                if(raiz->dado == valor && raiz->direita == NULL){
                    free(raiz);
                    return NULL;
                }
                if(buscacor(raiz) == BLACK && buscacor(raiz->direita->esquerda) == BLACK){
                    raiz = rot2(2,raiz);
                }
                if(raiz->dado == valor){
                    struct No* temp = raiz->direita;
                    while(temp->esquerda != NULL){
                        temp = temp->esquerda;
                    }
                    raiz->dado = temp->dado;
                    raiz->direita = removemenor(raiz->direita);
                }
                else{
                    raiz->direita = exclusao(raiz->direita, valor);
                }
            }
            printf("\nValor excluído\n");
        }
    }
    else{
        printf("\nValor não existente\n");
    }
    return buscarots(raiz);
}

// A função de inserção insere um nó não duplicado na árvore, senão não é inserido.
struct No* insercao(struct No* raiz, int valor){
    if(raiz == NULL){
        raiz = (struct No *) realloc(raiz,sizeof(struct No));
        raiz->dado = valor;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
        raiz->cor = RED;
        printf("\nnew no\n");
    }
    else{
        if(raiz->dado > valor || raiz->dado < valor){
            if(raiz->dado > valor){
                raiz->esquerda = insercao(raiz->esquerda, valor);
            }
            else{
                raiz->direita = insercao(raiz->direita, valor);
            }
            if(raiz->direita->cor == RED && raiz->esquerda->cor == BLACK){
                raiz = rot(1, raiz);
            }
            if(raiz->esquerda->cor == RED && raiz->esquerda->esquerda->cor == RED){
                raiz = rot(2, raiz);
            }
            if(raiz->direita->cor == RED && raiz->esquerda->cor == RED){
                trocacor(raiz);
            }
        }
        else{
            printf("\nValor já existente\n");
        }
    }
    return raiz;
}
struct No* insercaoinit(struct No* raiz, int valor){
    if(raiz == NULL){
        raiz->cor = BLACK;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
        raiz->dado = valor;
    }
    else{
        raiz = insercao(raiz, valor);
    }
    return raiz;
}

// A função de busca realiza a busca,correção de cores e rotação dos nós após qualquer inserção, exclusão ou rotação.
struct No* buscarots(struct No* raiz){
    if(buscacor(raiz->direita) == RED){
        raiz = rot(1, raiz);
    }
    if(raiz->esquerda != NULL && buscacor(raiz->esquerda) == RED && buscacor(raiz->esquerda->esquerda) == RED){
        raiz = rot(1,raiz);
    }
    if(buscacor(raiz->esquerda) == RED && buscacor(raiz->direita) == RED){
        trocacor(raiz);
    }
    return raiz;
}

// A função de rotação realiza a rotação de nós de uma subárvore. Recebe uma direção em que 1 = à esquerda, 2 = à direita.
struct No* rot(int direcao,struct  No* raiz){
    if(direcao == 1){
        // PRA ESQUERDA
        struct No* temp= raiz->direita; 
        raiz->direita = temp->esquerda;
        temp->esquerda = raiz;
        temp->cor = raiz->cor;
        raiz->cor = RED;
    }
    else if(direcao == 2){
        // PRA DIREITA
        struct No* temp= raiz->esquerda; 
        raiz->esquerda = temp->direita;
        temp->direita = raiz;
        temp->cor = raiz->cor;
        raiz->cor = RED;
    }
    else{
        printf("Argumentos inválidos");
    }
    return raiz;
}

struct No* rot2(int direcao,struct  No* raiz){
    if(direcao == 1){
        // PRA ESQUERDA
        trocacor(raiz);
        if(buscacor(raiz->direita->esquerda) == RED){
            raiz->direita = rot(2,raiz->direita);
            raiz = rot(1,raiz);
            trocacor(raiz);
        }
    }
    else if(direcao == 2){
        // PRA DIREITA
        trocacor(raiz);
        if(buscacor(raiz->esquerda->esquerda) == RED){
            raiz = rot(2,raiz);
            trocacor(raiz);
        }
    }
    else{
        printf("Argumentos inválidos");
    }
    return raiz;
}

// Função que troca cor de um nó para seu inverso e de seus filhos também
void trocacor(struct No* raiz){
    raiz->cor = !raiz->cor;
    if(raiz->esquerda != NULL){
        trocacor(raiz->esquerda);
    }
    if(raiz->direita != NULL){
        trocacor(raiz->direita);
    }
}

struct No* removemenor(struct No* raiz){
    if(raiz->esquerda == NULL){
        free(raiz);
        return NULL;
    }
    if(buscacor(raiz->esquerda) == BLACK && buscacor(raiz->esquerda->esquerda) == BLACK){
        raiz = rot2(1,raiz);
    }
    raiz->esquerda = removemenor(raiz->esquerda);
    return buscarots(raiz);
}

// As funções abaixo foram introduzida por um contexto mero ilustrativo, podendo ser removidas do código se desejável.
void mostraArvore(struct No *a, int b)
{
    if (a != NULL) // Verifica se o nó atual não é nulo
    {
        // Chama a função recursivamente para percorrer a subárvore direita
        mostraArvore(a->direita, b + 1);
        // Imprime o nó atual com um espaçamento proporcional à sua profundidade
        imprimeNo(a->dado, b);
        // Chama a função recursivamente para percorrer a subárvore esquerda
        mostraArvore(a->esquerda, b + 1);
    }
}
void imprimeNo(int c, int b)
{
    int i;
    for (i = 0; i < b; i++) // Loop para imprimir espaços proporcionais à profundidade
        printf("   ");
    printf("%i\n", c); // Imprime o valor do nó com a devida indentação
}
