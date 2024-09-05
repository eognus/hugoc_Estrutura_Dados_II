#include <stdio.h>
#include <stdlib.h>

struct No {
  int dado;
  struct No *direita;
  struct No *esquerda;
};

void buscarots(No* raiz);
// direcao = 1 -> rotacao pra esquerda, direcao = 2 -> rotacao pra direita
void rotsimples(int direcao, No* raiz);
void rotdupla(int direcao, No* raiz);

int main()
{
    printf("Hello World");

    return 0;
}
int buscarots(No* raiz){
    if(raiz == NULL){
        return 0;
    }
    if(raiz->direita == NULL && raiz->esquerda == NULL){
        return 1;
    }
    int alturadir=0, alturaesq=0;
    
    alturadir = buscarots(raiz->direita);
    alturaesq = buscarots(raiz->esquerda);
    raiz->fb = alturaesq - alturadir;
    raiz->altura = max(alturaesq, alturadir) + 1;
    
    return altura;
}
void rotdupla(int direcao, No* raiz){
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
void rotsimples(int direcao, No* raiz){
    
}
