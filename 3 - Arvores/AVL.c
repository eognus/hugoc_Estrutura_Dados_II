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
void reiniciabusca(struct No* raiz);
// direcao = 1 -> rotacao pra esquerda, direcao = 2 -> rotacao pra direita
void rotsimples(int direcao,struct No* raiz);
void rotdupla(int direcao,struct No* raiz);
struct No* insercao(struct No* raiz, int valor);
void exclusao(struct No* base,struct No*raiz, int valor);

int main()
{
    int opcao=1, valor;
    struct No* base;
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
        }
        else if(opcao == 2){
            while(valor != -1){
                scanf("%i",&valor);
                base = insercao(base, valor);
                buscarots(base);
            }
        }
        else if(opcao == 3){
            printf("Digite o valor a ser excluído da árovre: ");
            scanf("%i",&valor);
            exclusao(base, base, valor);
        }
        else if(opcao == 4){
            while(valor != 1){
                scanf("%i",&valor);
                exclusao(base, base, valor);
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
        raiz = (struct No *) malloc(sizeof(struct No));
        raiz->dado = valor;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
    }
    else{
        if(raiz->dado > valor){
            raiz->esquerda = insercao(raiz->esquerda, valor);
            
        }
        else if(raiz->dado == valor){
            printf("Valor já existente  ");
        }
        else{
            raiz->direita = insercao(raiz->direita, valor);
        }
    }
    return raiz;
}
void reiniciabusca(struct No* raiz){
    while(buscarots(raiz) != -1){
        buscarots(raiz);
    }
}
int buscarots(struct No* raiz){
    if(raiz == NULL){
        return 0;
    }
    if(raiz->direita == NULL && raiz->esquerda == NULL){
        return 1;
    }
    
    alturadir = buscarots(raiz->direita);
    alturaesq = buscarots(raiz->esquerda);
    if(alturadir == -1 || alturaesq == -1){
        return -1;
    }
    raiz->fb = alturaesq - alturadir;
    raiz->altura = fmax(alturaesq, alturadir) + 1;
    if(fb >= 2){
        // rotação pra direita
        if(raiz->esquerda->fb > 0){
            rotsimples(2,raiz)
        }
        else{
            rotdupla(2,raiz)
        }
        return -1;
    }
    else if (fb <= -2){
        // rotação pra esquerda
        if(raiz->direita->fb < 0){
            rotsimples(1,raiz)
        }
        else{
            rotdupla(1,raiz)
        }
        return -1;
    }
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
