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
#define d 0.85
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

/* minhas funções auxiliares */

void zerarArray(double* array, int n){
  for(int i = 0; i<n; i++){
    array[i] = 0;
  }
}

void inicializarArrayPageRank(double* array, int n){
  for(int i = 0; i<n; i++){
    array[i] = 1.00/n;
  }
}

void inicializarArrayCaminho(int* array, int n){
  for(int i = 0; i<n; i++){   
    array[i] = -1;
  }
}

void executarFloydWarshall(Grafo* g, int*** dist, int*** pred){
  int n = g->numVertices;
  *dist = (int**)malloc(sizeof(int*) *n);
  *pred = (int**)malloc(sizeof(int*) *n);

  for(int i = 0; i < n; i++){
    (*dist)[i] = (int*)malloc(sizeof(int) *n);
    (*pred)[i] = (int*)malloc(sizeof(int) *n);
  }

  calculaDistanciaFloydWarshall(g, *dist, *pred);
}

void liberarMemoriaFW(int n, int*** dist, int*** pred){
  for(int i = 0; i < n; i++){
    free((*dist)[i]);
    free((*pred)[i]);
    (*dist)[i] = NULL;
    (*pred)[i] = NULL;
  }
  free(*dist);
  free(*pred);
  (*dist) = NULL;
  (*pred) = NULL;
}

void CalcularGrausDeSaida(Grafo* g, int* valores){
  for(int i = 0; i < g->numVertices; i++){
    valores[i] = 0;
    for(int j = 0; j < g->numVertices; j++){
      if(g->matriz[i][j] && i!=j){
        valores[i]++;
      }
    }
  }
}

/* ------------------------------------------------------------------------------------------------------------- */

void centralidadeDeGrau(Grafo* g, double* valores) {
  int n = g->numVertices;
  zerarArray(valores, n);

  if(g->numVertices < 2)
    return; // não é possível analisar centralidade em um grafo onde não há relacionamentos

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
  int n = g->numVertices;
  zerarArray(valores, n);

  if(g->numVertices < 2)
    return; // não é possível analisar centralidade em um grafo onde não há relacionamentos

  int** dist; int** pred;
  executarFloydWarshall(g, &dist, &pred);

  for(int j = 0; j < n; j++){
    for(int k = 0; k < n; k++){
      valores[j] += dist[j][k];
    }
    if(valores[j] != 0)
      valores[j] = (n-1) / valores[j];
  }

  liberarMemoriaFW(n, &dist, &pred);
  return;
}

void centralidadeDeIntermediacao(Grafo* g, double* valores) {
  int n = g->numVertices;
  zerarArray(valores, n);

  if(g->numVertices <= 2)
    return; // não é possível analisar centralidade em um grafo onde não há relacionamentos

  double fator = 1.0 / ((n - 1) * (n - 2)); // usado para a normalização do valor durante a execução
  int** dist; int** pred;

  int* caminho = (int*)malloc(sizeof(int) * n); // esse caminho será usado para armazenar os vértices que compoem o caminho minimo entre j e k, reconstruído apartir da matriz de predecessores. Lembrando que esse caminho está invertido, portanto seu preenchimento será por exemplo [k, ..., ..., j, -1]. -1 representa o fim do caminho
  inicializarArrayCaminho(caminho, n);

  executarFloydWarshall(g, &dist, &pred);

  // o processamento mais custoso é recriar o caminho (tirando a execução do FW)
  // Poderíamos fazer um loop em i externo, mas isso faria recriar cada caminho n vezes ao invés de 1. 
  // Da forma implementada, com o loop duplo para cada caminho recriado, fica mais eficiente, pois,
  // o processamento de busca de um vértice no interior de um caminho é bem mais rápido que recriar o caminho
  
  for(int j = 0; j < n; j++){
    for(int k = 0; k < n; k++){
      if(j != k){                 // ignora os caminhos de j pra j
        int h = 0;
        caminho[h] = k;           // a primeira posição é o destino - e a última posição válida (antes dos -1's) é a origem
        while(h < n){
          if(h < dist[j][k])  
            caminho[h+1] = pred[j][caminho[h]];   // preenche o caminho com os vértices que o compõe
          else              
            caminho[h+1] = -1;                    // preenche o resto das posições com -1 (invalido, fora do caminho)
          h++;
        }

        /*// visualizar o caminho completo - apenas para testes
        printf("caminho de %d ate %d: ", j, k);
        for(int y = 0; y < n; y++){
          printf("%d, ", caminho[y]);
        }
        printf("\n");*/
        
        for(int x = 0; x < n; x++){   // pra cada caminho que recriamos vamos analisar a presença de cada vértice no interior do caminho e somar em valores[x] caso esteja presente
          for(int y = 1; y < dist[j][k]; y++){  // começamos a analise no 1 e vamos até antes da distancia real para ignorarmos as pontas, que contém os vértices de saída e destino (que não entram na nossa conta)
            if(caminho[y] == x){
              valores[x] += fator;              // poderia fazer valores[x]++ e normalizar em um loop no final, mas assim eu evito outro loop, pois o algoritmo já está bem pesado
            }
          }
        }
      }
    }
  }

  liberarMemoriaFW(n, &dist, &pred);
  return;
}

// parece razoavelmente correto, apenas não está igual ao do professor ainda
void centralidadePageRank(Grafo* g, double* valores, int iteracoes) {
  int n = g->numVertices;
  if(n <= 2 || iteracoes < 0)
    return;  // não é possível analisar centralidade em um grafo onde não há relacionamentos

  inicializarArrayPageRank(valores, n);

  int* grauDeSaida = (int*)malloc(sizeof(int) *n);
  CalcularGrausDeSaida(g, grauDeSaida);
  
  for(int iteracao = 0; iteracao < iteracoes; iteracao++){
    for(int verticeAtual = 0; verticeAtual < n; verticeAtual++){
      double importancia = 0.00;
      for(int y = 0; y < n; y++){
        if(g->matriz[y][verticeAtual] && verticeAtual != y){
          importancia += valores[y] / grauDeSaida[y];
        }
      }   
      valores[verticeAtual] = ((1-d)/n) + d*importancia;
    }
  }
}

int main(){
  int n = 5;
  double* valores = (double*)malloc(sizeof(double)*n);
  Grafo g1;

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
  centralidadePageRank(&g1, valores, 10);
  exibeArranjoReais(valores, n);

  free(valores);
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