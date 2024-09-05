#include <stdio.h>
#include <stdlib.h>

struct No {
  int dado;
  struct No *direita;
  struct No *esquerda;
};

void buscarots(No* raiz);
void atualizafb(No* raiz);

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
