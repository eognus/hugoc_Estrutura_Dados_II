// Aluno: Hugo Araujo Corona. Turma CC6M
#include <stdio.h>
#include <stdlib.h>

struct No {
  int dado;
  struct No *direita;
  struct No *esquerda;
};

void insere(int valor, struct No *raiz);
void exclui(int valor, struct No *raiz);
struct No *buscaBinaria(struct No *raiz, int valor);

int main(void) {
  int valor;
  struct No *raiz;
  printf("Hello World\n");
  printf("Qual valor quer adicionar a arvore?");
  scanf("%i", &valor);
  insere(valor, buscaBinaria(raiz, valor));
  exclui(valor, buscaBinaria(raiz, valor));
  return 0;
}

void insere(int valor, struct No *raiz) {
  if (raiz == NULL) {
    struct No *no = (struct No *)malloc(sizeof(struct No));
    no->direita = NULL;
    no->dado = valor;
    no->esquerda = NULL;
  } else
    printf("Valor já existente na árvore");
}

void exclui(int valor, struct No *raiz) {
  if (raiz == NULL) {
    printf("Valor não existente na árvore");
  } else {
    struct No *noesq = raiz;
    raiz = raiz->direita;
    struct No *temp = raiz;
    while (temp->esquerda != NULL) {
      temp = temp->esquerda;
    }
    temp->esquerda = noesq;
    free(temp);
    free(noesq);
  }
}

// Função que dá ou o ponteiro do nó do valor ou o ponteiro de onde deve ser inserido o valor
struct No *buscaBinaria(struct No *raiz, int valor) {
  if (raiz == NULL) {
    return raiz;
  }
  if (raiz->dado > valor) {
    if (raiz->direita == NULL)
      return raiz->direita;
    else
      buscaBinaria(raiz->direita, valor);
  } else if (raiz->dado == valor) {
    return raiz;
  } else {
    if (raiz->esquerda == NULL)
      return raiz->direita;
    else
      buscaBinaria(raiz->esquerda, valor);
  }
}
