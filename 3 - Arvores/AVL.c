/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
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
struct No* rotsimples(int direcao,struct No* raiz);
struct No* rotdupla(int direcao,struct No* raiz);
struct No* insercao(struct No* raiz, int valor);
void exclusao(struct No* base,struct No*raiz, int valor);
void mostraArvore(struct No *a, int b);
void imprimeNo(int c, int b);
int main()
{
    int opcao=1, valor;
    struct No* base = NULL;
    printf("----  Bem-vindo à árvore AVL  ----");
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
            base = insercao(base, valor);
            buscarots(base);
            mostraArvore(base, 0);
        }
        else if(opcao == 2){
            while(valor != -1){
                scanf("%i",&valor);
                base = insercao(base, valor);
                buscarots(base);
                mostraArvore(base, 0);
            }
        }
        else if(opcao == 3){
            printf("Digite o valor a ser excluído da árvore: ");
            scanf("%i",&valor);
            exclusao(base, base, valor);
            mostraArvore(base, 0);
        }
        else if(opcao == 4){
            while(valor != 1){
                scanf("%i",&valor);
                exclusao(base, base, valor);
            mostraArvore(base, 0);
            }
        }
        else if(opcao != 5){
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
/**void insercao(struct No* base, int valor){
    struct No* temp;
    struct No* temp;
    temp = base;
    while(temp != NULL){
        aux = temp;
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
    temp->dado = valor;
    printf("\nValor inserido com sucesso. %i", temp->dado);
} **/

struct No* insercao(struct No* raiz, int valor){
    if(raiz == NULL){
        raiz = (struct No *) realloc(raiz,sizeof(struct No));
        raiz->dado = valor;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
        raiz->altura = 1;
        raiz->fb = 0;
        printf("new no ");
    }
    else{
        if(raiz->dado > valor){
            raiz->esquerda = insercao(raiz->esquerda, valor);
        }
        else if(raiz->dado == valor){
            printf("Valor já existente");
        }
        else{
            raiz->direita = insercao(raiz->direita, valor);
        }
    }
    return raiz;
}

int buscarots(struct No* raiz){
    if(raiz == NULL){
        return 0;
    }
    if(raiz->direita == NULL && raiz->esquerda == NULL){
        printf("   this %i", raiz->altura);
        raiz->altura = 1;
        return raiz->altura;
    }
    int alturadir, alturaesq;    
    if(raiz->direita == NULL){
        alturadir = 0;
        alturaesq = buscarots(raiz->esquerda);
        printf("a");
    }
    else if(raiz->esquerda == NULL){
        alturaesq = 0;
        printf("b");
        alturadir = buscarots(raiz->direita);
    }
    else{
        alturadir = buscarots(raiz->direita);
        alturaesq = buscarots(raiz->esquerda);
        printf("c");
    }
    printf("that");
    raiz->fb = alturaesq - alturadir;
    raiz->altura = (int) fmax(alturaesq, alturadir) + 1;
    printf("  altura: %i, fb: %i, alturaesq = %i, alturadir = %i \n",raiz->altura, raiz->fb,alturaesq, alturadir);
    if(raiz->fb >= 2 || raiz->fb <=-2){
        if(raiz->fb >= 2){ // rotação pra direita
            
            if(raiz->esquerda->fb > 0){
                rotsimples(2,raiz);
            }
            else{
                rotdupla(2,raiz);
            }
        }
        else{// rotação pra esquerda
            
            if(raiz->direita->fb < 0){
                rotsimples(1,raiz);
            }
            else{
                rotdupla(1,raiz);
            }
        }  
        if(raiz->direita == NULL){
            alturadir = 0;
            alturaesq = buscarots(raiz->esquerda);
            printf("a");
        }
        else if(raiz->esquerda == NULL){
            alturaesq = 0;
            printf("b");
            alturadir = buscarots(raiz->direita);
        }
        else{
            alturadir = buscarots(raiz->direita);
            alturaesq = buscarots(raiz->esquerda);
            printf("c");
        }
        raiz->fb = alturaesq - alturadir;
        raiz->altura = fmax(alturaesq, alturadir) + 1;
    }
    mostraArvore(raiz, 0);
    return raiz->altura;
}
struct No* rotsimples(int direcao,struct  No* raiz){
    printf("d");
    struct No* temp = (struct No*) malloc(sizeof(struct No));
    temp = raiz; // temp e raiz = 3
    if(direcao == 1){
        // PRA ESQUERDA
        raiz = raiz->direita;
        if(raiz->esquerda != NULL){
            temp->direita = raiz->esquerda;
        }
        else{
            raiz->esquerda = (struct No*) malloc(sizeof(struct No));
        }
        raiz->esquerda = temp;
    }
    else if(direcao == 2){
        // PRA DIREITA
        raiz = raiz->esquerda; 
        if(raiz->direita != NULL){
            temp->esquerda = raiz->direita;
        }
        else{
            raiz->direita = (struct No*) malloc(sizeof(struct No));
        }
        raiz->direita = temp; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        printf("here %i", raiz->direita->dado);
    }
    else{
        printf("Argumentos inválidos");
    }
    return raiz;
}
struct No* rotdupla(int direcao,struct No* raiz){
    if(direcao == 1){
        raiz->direita = rotsimples(2, raiz->direita);
        raiz = rotsimples(1,raiz);
    }
    else if(direcao == 2){
        raiz->esquerda = rotsimples(1, raiz->esquerda);
        raiz = rotsimples(2,raiz);
    }
    else{
        printf("Argumentos inválidos");
    }
    return raiz;
}
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
