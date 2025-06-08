/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2025                          **/
/**   Prof. Luciano Digiampietri                                    **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   Arthur de Lima Hernandes                   15552518           **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define INFINITO 999999
typedef int bool;

typedef struct {
    int numVertices;
    int numArestas;
    bool** matriz;
} Grafo;

void printf123(){
    // Funcao usada pelo sistema de correcao automatica (nao mexer)
}

/* Estrutura para representar elementos de uma lista ligada de vertices */
typedef struct aux{
  int vertice;
  struct aux* prox;
} ElementoLista, *PONT;

/* Estrutura para representar elementos de uma lista ligada com arestas (pares de vertices)*/
typedef struct aux2{
  int origem;
  int destino;
  struct aux2* prox;
} ArestaLista, * PONT2;

bool inicializaGrafo(Grafo* g, int vertices){
  if (g==NULL || vertices<1) return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->matriz = (bool**) malloc(sizeof(bool*)*vertices);
  for (x=0; x<vertices; x++){
    g->matriz[x] = (bool*) malloc(sizeof(bool)*vertices);
    for (y=0; y<vertices; y++){
      g->matriz[x][y] = false;
    }
  }
  return true;
}

bool liberaGrafo(Grafo* g){
  if (g==NULL) return false;
  int x;
  for (x=0; x<g->numVertices; x++)
    free(g->matriz[x]);
  free(g->matriz);
  g->numVertices = 0;
  g->numArestas = 0;
  g->matriz = NULL;
  return true;
}

bool insereAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;
  if (g->matriz[v1][v2] == false){
      g->matriz[v1][v2] = true;
      g->numArestas++;
  }
  return true;
}

bool removeAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  g->matriz[v1][v2] = false;
  g->numArestas--;
  return true;
}

Grafo* criaGrafoAleatorio(int numVertices, int numArestas){
  int x, y, a, total;
  if (numVertices < 1 || numArestas >= numVertices*numVertices/2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;  
  }
  Grafo* g = (Grafo*)malloc(sizeof(Grafo));
  inicializaGrafo(g,numVertices);

  a = 0;
  while(a<numArestas){
    x = rand()%numVertices;
    y = rand()%numVertices;
    if (g->matriz[x][y] == false){
      g->matriz[x][y] = true;
      a++;
    }
  }
  g->numArestas = numArestas;
  return g;
}

void exibeGrafo(Grafo* g){
  if(!g) return;
  int x, y;
  printf("\nImprimindo grafo (v=%i; a=%i)\n   ", g->numVertices, g->numArestas);
  for (x=0;x<g->numVertices;x++) printf(" %3i",x);
  printf("\n");
  for (x=0;x<g->numVertices;x++){
    printf("%3i",x);
    for (y=0;y<g->numVertices;y++)
      printf(" %3i",g->matriz[x][y]);  
    printf("\n");
  }
  printf("\n");
}

void calculaDistanciaFloydWarshall(Grafo* g, int** dist, int** pred){
  int i, j, k, n;
  n = g->numVertices;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      if(g->matriz[i][j] != false){
        dist[i][j] = g->matriz[i][j];
        pred[i][j] = i;
      }else{
        dist[i][j] = INFINITO;
        pred[i][j] = -1;
      }
  for(i=0;i<n;i++) {
    dist[i][i] = 0;
    pred[i][i] = i;
  }

  for(k=0;k<n;k++)
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        if(dist[i][j] > dist[i][k] + dist[k][j]){
          dist[i][j] = dist[i][k] + dist[k][j];
          pred[i][j] = pred[k][j];
        }
}

void exibeMatrizDistancias(int** matriz, int n){
  printf("Exibindo matriz de distancias.\n");
  int x, y;
  for (x=0; x<n; x++) printf("\t%3i", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%i", x);
    for (y=0; y<n; y++){
      if (matriz[x][y] == INFINITO) printf("\t-");
      else printf("\t%3i",matriz[x][y]);
    }
    printf("\n");
  }
  printf("\n");
}

void exibeMatrizPredecessores(int** matriz, int n){
  printf("Exibindo matriz de predecessores.\n");
  int x, y;
  for (x=0; x<n; x++) printf("\t%3i", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%i", x);
    for (y=0; y<n; y++){
      printf("\t%3i",matriz[x][y]);
    }
    printf("\n");
  }
  printf("\n");
}

void exibeArranjoReais(double* arranjo, int n){
  int x;
  for (x=0; x<n; x++) printf("  v%i\t", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%4.3f\t",arranjo[x]);
  }
  printf("\n\n");
}

void zerarArray(double* array, int n){
  for(int i = 0; i<n; i++){
    array[i] = 0;
  }
}

/* ------------------------------------------------------------------------------------------------------------- */

void centralidadeDeGrau(Grafo* g, double* valores) {
  if(g->numVertices < 2)
    return; // não é possível analisar centralidade em um grafo onde não há relacionamentos

  int n = g->numVertices;
  zerarArray(valores, n);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(g->matriz[j][i] && i!=j){
        valores[i]++;
      }
    }
    valores[i] = valores[i] / (n-1);
  }
}

void centralidadeDeProximidade(Grafo* g, double* valores) {
  if(g->numVertices < 2)
    return; // não é possível analisar centralidade em um grafo onde não há relacionamentos

  int n = g->numVertices;
  zerarArray(valores, n);
  int** dist = (int**)malloc(sizeof(int*)*n);
  int** pred = (int**)malloc(sizeof(int*)*n);

  for(int i = 0; i < n; i++){
    dist[i] = (int*)malloc(sizeof(int)*n);
    pred[i] = (int*)malloc(sizeof(int)*n);
  }

  calculaDistanciaFloydWarshall(g, dist, pred);

  for(int j = 0; j < n; j++){
    for(int k = 0; k < n; k++){
      valores[j] += dist[j][k];
    }
    if(valores[j] != 0)
      valores[j] = (n-1) / valores[j];
  }
}

void centralidadeDeIntermediacao(Grafo* g, double* valores) {
  /* COMPLETE/IMPLEMENTE ESTA FUNCAO */
}

void centralidadePageRank(Grafo* g, double* valores, int iteracoes) {
  /* COMPLETE/IMPLEMENTE ESTA FUNCAO */
}

int main(){
  double* valores = (double*)malloc(sizeof(double)*5);
  Grafo g1;

  inicializaGrafo(&g1, 5);
  insereAresta(&g1,0,1);
  insereAresta(&g1,1,2);
  insereAresta(&g1,2,3);
  insereAresta(&g1,3,4);
  insereAresta(&g1,4,0);
  insereAresta(&g1,0,2);
  insereAresta(&g1,1,4);
  insereAresta(&g1,1,3);

  exibeGrafo(&g1);
  centralidadeDeProximidade(&g1, valores);
  exibeArranjoReais(valores, 5);

  return 0;
}

void testaFuncoes(Grafo* g, int n){
  double* valoresReais = (double*)malloc(sizeof(double)*n);

  printf("Centralidade de Grau:\n");
  centralidadeDeGrau(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade de Proximidade:\n");
  centralidadeDeProximidade(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade de Intermediacao:\n");
  centralidadeDeIntermediacao(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 0 iteracoes\n");
  centralidadePageRank(g, valoresReais, 0);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 1 iteracao\n");
  centralidadePageRank(g, valoresReais, 1);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 10 iteracoes\n");
  centralidadePageRank(g, valoresReais, 10);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 100 iteracoes\n");
  centralidadePageRank(g, valoresReais, 100);
  exibeArranjoReais(valoresReais, n);

  free(valoresReais);
}

/*int main() {

  int n = 5;
  double* valoresReais = (double*)malloc(sizeof(double)*n);
  
  Grafo g1;

  printf("PRIMEIRO EXEMPLO\n");

  inicializaGrafo(&g1, n);
  insereAresta(&g1,0,1);
  insereAresta(&g1,1,2);
  insereAresta(&g1,2,3);
  insereAresta(&g1,3,4);
  insereAresta(&g1,4,0);
  insereAresta(&g1,0,2);
  insereAresta(&g1,1,4);
  insereAresta(&g1,1,3);

  exibeGrafo(&g1);

  testaFuncoes(&g1, n);

  printf("\n\nSEGUNDO EXEMPLO [auto-lacos]\n");
  insereAresta(&g1,0,0);
  insereAresta(&g1,2,2);

  exibeGrafo(&g1);

  testaFuncoes(&g1, n);

  printf("\n\nTERCEIRO EXEMPLO\n");
  Grafo g2;
  inicializaGrafo(&g2, n);
  insereAresta(&g2,0,2);
  insereAresta(&g2,1,2);
  insereAresta(&g2,3,2);
  insereAresta(&g2,4,2);
  insereAresta(&g2,2,0);
  insereAresta(&g2,2,1);
  insereAresta(&g2,2,3);
  insereAresta(&g2,2,4);

  exibeGrafo(&g2);

  testaFuncoes(&g2, n);

  printf("\n\nQUARTO EXEMPLO (grafo aleatorio)\n\n");
  n = 10;
  int arestas = 40;
  
  Grafo* g3 = criaGrafoAleatorio(n,arestas);

  exibeGrafo(g3);
 
  testaFuncoes(g3, n);

  return 0;  
}*/