/******************************************************************************

Aluno: Hugo Araujo Corona

Texto contendo os inputs necessários para simulação da árvore da branch main usando este código:
2
30
24
20
35
27
33
38
25
22
34
40
29
31
15
23
-1
4
24
35
-1
1
24
3
27
1
32
3
30
1
21
5

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Declaração da estrutura de Nó
struct No{
  int dado;
  struct No *direita;
  struct No *esquerda;
  int altura;
  int fb;
};

// PROTOTIPAÇÃO
// Função que varre árvore calculando alturas, fb e gerando rotações
struct No* buscarots(struct No* raiz);
// direcao = 1 -> rotacao pra esquerda, direcao = 2 -> rotacao pra direita
// Função de rotação simples
struct No* rotsimples(int direcao,struct No* raiz);
// Função de rotação dupla
struct No* rotdupla(int direcao,struct No* raiz);
// Função de inserção de nó
struct No* insercao(struct No* raiz, int valor);
// Função de exclusão de nó
struct No* exclusao(struct No*raiz, int valor);
// Funções abaixo somente para visualização da árvore, diretas do código da branch principal. Não me responsabilizo por quaisquer defeitos.
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
            base = buscarots(base);
            mostraArvore(base, 0);
        }
        else if(opcao == 2){
            while(1){
                scanf("%i",&valor);
                if(valor == -1){
                    break;
                }
                base = insercao(base, valor);
                base = buscarots(base);
                mostraArvore(base, 0);
            }
        }
        else if(opcao == 3){
            printf("Digite o valor a ser excluído da árvore: ");
            scanf("%i",&valor);
            base = exclusao(base,valor);
            base = buscarots(base);
            mostraArvore(base,0);
        }
        else if(opcao == 4){
            while(valor != 1){
                scanf("%i",&valor);
                if(valor == -1){
                    break;
                }
                base = exclusao(base, valor);
                base = buscarots(base);
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

// A função de exclusão substitui nós internos pelo valor mais à esquerda da sub-árvore da direita
struct No* exclusao(struct No *raiz, int valor){
    if(raiz != NULL){
        if(raiz->dado > valor){
            raiz->esquerda = exclusao(raiz->esquerda, valor);
        }
        else if(raiz->dado < valor){
            raiz->direita = exclusao(raiz->direita, valor);
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
                struct No* temp = raiz->direita;
                if(temp->esquerda != NULL){
                    if(temp->esquerda->esquerda != NULL){
                        while(temp->esquerda->esquerda != NULL){
                            temp = temp->esquerda->esquerda;
                        }
                        
                    }  
                    struct No* aux = temp;
                    temp = temp->esquerda;
                    aux->esquerda = NULL;
                }
                temp->esquerda = raiz->esquerda;
                if(temp->direita != NULL && raiz->direita != temp){
                    
                    struct No* temp2;
                    temp2 = temp->direita;
                    if(temp2->direita != NULL){
                        while(temp2->direita != NULL){
                            temp2 = temp2->direita;
                        }
                    }
                    temp2->direita = raiz->direita;
                }
                else if(temp->direita == NULL){
                    temp->direita = raiz->direita;
                }
                *raiz = *temp;
            }
            printf("\nValor excluído\n");
        }
    }
    else{
        printf("\nValor não existente\n");
    }
    return raiz;
}

// A função de inserção insere um nó não duplicado na árvore, senão não é inserido.
struct No* insercao(struct No* raiz, int valor){
    if(raiz == NULL){
        raiz = (struct No *) realloc(raiz,sizeof(struct No));
        raiz->dado = valor;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
        raiz->altura = 1;
        raiz->fb = 0;
        printf("\nnew no\n");
    }
    else{
        if(raiz->dado > valor){
            raiz->esquerda = insercao(raiz->esquerda, valor);
        }
        else if(raiz->dado == valor){
            printf("\nValor já existente\n");
        }
        else{
            raiz->direita = insercao(raiz->direita, valor);
        }
    }
    return raiz;
}

// A função de busca realiza a busca,correção de alturas e fbs e rotação dos nós após qualquer inserção, exclusão ou rotação.
struct No* buscarots(struct No* raiz){
    if(raiz == NULL){
        return raiz;
    }
    int dado = raiz->dado;
    if(raiz->direita == NULL && raiz->esquerda == NULL){
        raiz->altura = 1;
        return raiz;
    }
    int alturadir, alturaesq;    
    alturadir = 0;
    alturaesq = 0;
    if(raiz->esquerda != NULL){
        raiz->esquerda = buscarots(raiz->esquerda);
        alturaesq = raiz->esquerda->altura;
    }
    if(raiz->direita != NULL){
        raiz->direita = buscarots(raiz->direita);
        alturadir = raiz->direita->altura;
    }
    raiz->fb = alturaesq - alturadir;
    raiz->altura = (int) fmax(alturaesq, alturadir) + 1;
    if(raiz->fb >= 2 || raiz->fb <=-2){
        if(raiz->fb >= 2){ // rotação pra direita
            if(raiz->esquerda->fb > 0){
                raiz = rotsimples(2,raiz);
            }
            else{
                raiz = rotdupla(2,raiz);
            }
        }
        else{// rotação pra esquerda
            
            if(raiz->direita->fb < 0){
                raiz = rotsimples(1,raiz);
            }
            else{
                raiz = rotdupla(1,raiz);
            }
        }  
        
        alturadir = 0;
        alturaesq = 0;
        if(raiz->esquerda != NULL){
            raiz->esquerda = buscarots(raiz->esquerda);
            alturaesq = raiz->esquerda->altura;
        }
        if(raiz->direita != NULL){
            raiz->direita = buscarots(raiz->direita);
            alturadir = raiz->direita->altura;
        }
        raiz->fb = alturaesq - alturadir;
        raiz->altura = fmax(alturaesq, alturadir) + 1;
    }
    return raiz;
}

// A função de rotação simples realiza a rotação de nós de uma subárvore. Recebe uma direção em que 1 = à esquerda, 2 = à direita.
struct No* rotsimples(int direcao,struct  No* raiz){
    struct No* temp= raiz; 
    if(direcao == 1){
        // PRA ESQUERDA
        raiz = raiz->direita;
        if(raiz->esquerda == NULL){
            raiz->esquerda = (struct No*) malloc(sizeof(struct No));
            temp->direita = NULL;
        }
        else{
            temp->direita = raiz->esquerda;
        }
        raiz->esquerda = temp;
    }
    else if(direcao == 2){
        // PRA DIREITA
        raiz = raiz->esquerda; 
        if(raiz->direita == NULL){
            raiz->direita = (struct No*) malloc(sizeof(struct No));
            temp->esquerda = NULL;
        }
        else{
            temp->esquerda = raiz->direita;
        }
        raiz->direita = temp;
    }
    else{
        printf("Argumentos inválidos");
    }
    return raiz;
}

// A função de rotação dupla realiza a rotação dupla dos nós da subárvore, obedecendo a mesma regra de direção citada acima.
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
