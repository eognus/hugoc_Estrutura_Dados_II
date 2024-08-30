// Aluno: Hugo Araujo Corona. Turma CC6M
#include <stdio.h>
#include <stdlib.h>

// Criação da estrutura de nó
struct No {
  int dado;
  struct No *direita;
  struct No *esquerda;
};

// Prototipação das funções
void insere(int valor, struct No *raiz);
void exclui(int valor, struct No *raiz);
struct No *buscaBinaria(struct No *raiz, int valor);

// Função main apenas servindo para mostrar a funcionalida das funções de inserção, exclusão e busca binária. Nota-se que as funções de inserção e exclusão usam a função da busca binária para achar o nó alvo.
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

// Função de inserção de nó na árvore
void insere(int valor, struct No *raiz) {
  if (raiz == NULL) {
    struct No *no = (struct No *)malloc(sizeof(struct No));
    no->direita = NULL;
    no->dado = valor;
    no->esquerda = NULL;
  } else
    printf("Valor já existente na árvore");
}

// Função de exclusão de nó na árvore
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
