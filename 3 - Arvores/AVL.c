/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct No{
  int dado;
  struct No *direita;
  struct No *esquerda;
  int altura;
  int fb;
};

int buscarots(struct No* raiz);
// direcao = 1 -> rotacao pra esquerda, direcao = 2 -> rotacao pra direita
void rotsimples(int direcao,struct No* raiz);
void rotdupla(int direcao,struct No* raiz);
void insercao(struct No* base,int valor);
void exclusao(struct No* base,struct No*raiz, int valor);

int main()
{
    int opcao=1, valor;
    struct No* base;
    printf("----  Bem-vindo à árvore AVL  ----");
    while(opcao != 0){
        printf("\nEscolha dentre as opções abaixo o que você deseja fazer:\n");
        printf("1 - Inserir Nó\n");
        printf("2 - Excluir Nó\n");
        scanf("%i",&opcao);
        printf("%i",opcao);
        if(opcao == 1){
            printf("\nDigite o valor a ser inserido na árvore: ");
            scanf("%i",&valor);
            insercao(base, valor);
        }
        else if(opcao == 2){
            printf("Digite o valor a ser excluído da árovre: ");
            scanf("%i",&valor);
            printf("valor");
            exclusao(base, base, valor);
        }
        else{
            printf("Opção inválida.\n");
        }
    }
    
    return 0;
}
void exclusao(struct No* base,struct No *raiz, int valor){
    if(raiz != NULL){
        if(raiz->dado > valor){
            exclusao(base, raiz->esquerda, valor);
        }
        else if(raiz->dado < valor){
            exclusao(base, raiz->direita, valor);
        }
        else{
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                raiz = NULL;
            }
            else if(raiz->esquerda == NULL){
                raiz = raiz->direita;
            }
            else if(raiz->direita == NULL){
                raiz = raiz->esquerda;
            }
            else{
                struct No* temp = (struct No*) malloc(sizeof(struct No));
                temp = raiz->direita;
                while(temp->esquerda != NULL){
                    temp = temp->esquerda;
                }
                temp->esquerda = raiz->esquerda;
                temp->direita = raiz->direita;
                *raiz = *temp;
                buscarots(base);
                free(temp);
            }
            printf("Valor excluído");
        }
    }
    else{
        printf("Valor não existente");
    }
}
void insercao(struct No* base, int valor){
    struct No* temp;
    temp = base;
    while(temp != NULL){
        printf("a");
        if(temp->dado > valor){
            printf("3");
            temp = temp->esquerda;
        }
        else if(temp->dado == valor){
            printf("2");
            printf("Valor já existente");
            return;
        }
        else{
            printf("1");
            temp = temp->direita;
        }
    }
    struct No* aux = (struct No*) malloc(sizeof(struct No));
    temp = aux;
    temp->dado = valor;
    printf("\nValor inserido com sucesso. %i", temp->dado);
}
int buscarots(struct No* raiz){
    if(raiz == NULL){
        printf("%i",raiz->dado);
        return 0;
    }
    if(raiz->direita == NULL && raiz->esquerda == NULL){
        printf("2");
        return 1;
    }
    int alturadir=0, alturaesq=0;
    
    alturadir = buscarots(raiz->direita);
    alturaesq = buscarots(raiz->esquerda);
    raiz->fb = alturaesq - alturadir;
    raiz->altura = fmax(alturaesq, alturadir) + 1;
    
    return raiz->altura;
}
void rotdupla(int direcao,struct No* raiz){
    if(direcao == 1){
        rotsimples(2, raiz->direita);
        rotsimples(1,raiz);
    }
    else if(direcao == 2){
        rotsimples(1, raiz->esquerda);
        rotsimples(2,raiz);
    }
    else{
        printf("Argumentos inválidos");
    }
}
void rotsimples(int direcao,struct  No* raiz){
    struct No* temp = (struct No*) malloc(sizeof(struct No));
    temp = raiz;
    if(direcao == 1){
        raiz = raiz->direita;
        temp->direita = raiz->esquerda;
        raiz->esquerda = temp;
    }
    else if(direcao == 2){
        raiz = raiz->esquerda;
        temp->esquerda = raiz->direita;
        raiz->direita = temp;
    }
    else{
        printf("Argumentos inválidos");
    }
    free(temp);
}
