/* Parâmetros
 *    V: conjunto de vértices
 *    Adj: lista de adjacência de cada vértice
 *    w: função que mapeia uma aresta ao seu peso
 *    r: raíz da árvore
 */
/*
MST-PRIM(V, Adj, w, r)
1 para cada v pertencente a V:
2    v.key = INF;
3    v.pi = NIL; // pai de v na AGM
4 r.key = 0;
5 Q = V; // fila de prioridades
6 enquanto Q ≠ Ø:
7    u = EXTRACT-MIN(Q);
8    para cada v pertencente a Adj[u]:
9       se v pertence a Q e w(u,v) < v.key:
10         v.pi = u;
11         v.key = w(u,v);
*/

#include<utility>
#include<vector>
#include<iostream>
#include <queue>
using namespace std;

typedef pair<int, int> ii; // pares de inteiros
typedef vector<int> vi; // vetor de inteiros
typedef vector<ii> vii; // vetor de pares de inteiros




/* variaveis globais */

//vetor de resultados 
vii resultados;

// funcao que atualiza a fila de prioridades
void atualizaFila(int u, vi& explorado,vector<vii>& LA, priority_queue<ii>& Q)
{
    explorado[u] = 1;
    for(int j = 0; j < LA[u].size(); j++)
    {
        ii v = LA[u][j];
        if(!explorado[v.first])
          /* valor: peso; chave: id do vertice
           * o valor negativo se deve ao fato de
           * que a heap do C++ eh implementada como
           * uma heap-max, e para desempate, prioriza-se
           * aqui o id de menor indice
           */
          Q.push(ii(-v.second, -v.first)); 
    }
}

int prim(vi& explorado, int& n, int& uRemove, int& vRemove, int& wRemove, int& acrescimo,vector<vii>& LA, priority_queue<ii>& Q)
{
    explorado.assign(n, 0);
    atualizaFila(0,  explorado, LA, Q);
    
    // custo da AGM
    int resultado = 0;
 
    // peso de uma aresta em cada iteracao
    int w;
 
    while(!Q.empty())
    {
        ii u = Q.top(); // O(1)
        Q.pop(); // O(logn)

        int w = -u.first; // retirando o negativo cadastrado na heap
        int v = -u.second;

        
        if(!explorado[v])
        {
            ii ku = Q.top(); // O(1)
            int kw = -ku.first; // retirando o negativo cadastrado na heap
            int kv = -ku.second;
            if((kw - w) < acrescimo){
            
              acrescimo = (kw - w);
              uRemove = vRemove;
              vRemove = v;
              wRemove = w;
            
            }
            resultado += w;         
            atualizaFila(v, explorado, LA, Q); // O(logn)
        }
    }
 
    return resultado;
}

int main()
{

    int testes;
    cin >> testes;
    for(int i=0 ; i < testes ; i++)
    {
        // armazena a informacao se o vertice foi explorado ou nao
        vi explorado;
        // heap que armazena o vertices e suas prioridades a cada iteracao
        priority_queue<ii> Q;
        // lista de adjacencia
        vector<vii> LA;
        // numero de vertices
        int n;
        // numero de arestas
        int m;
        //acréscimo na AGM
        int acrescimo =999999;
        int uRemove = 0, vRemove = 0,wRemove = 0;

        cin >> n >> m;
 
        for(int i = 0; i < n; i++)
        {
        vii lista;
        LA.push_back(lista);
        }
        
        int u, v, w; // extremos das arestas, e peso de cada aresta
        for(int i = 0; i < m; i++)
        {
          cin >> u  >> v  >> w;
        u--;
        v--;

        int contador = 0, continua = 0;
        for(vector<vii>::iterator it = LA.begin(); it != LA.end() && continua < 2; ++it)
        {
          if(contador == u) 
          {
            ii par1(v, w);
            (*it).push_back(par1);    
            continua++;
          }
       
          else if(contador == v)
          {
            ii par2(u, w);
            (*it).push_back(par2);    
            continua++;
          }
          contador++;
        }
        }
        
        ii v3;

         v3.first = prim(explorado, n, uRemove, vRemove, wRemove, acrescimo, LA, Q);

        for(int j = 0; j < LA[uRemove].size(); j++)
        {
        ii v2 = LA[uRemove][j];
        if(v2.first == vRemove and v2.second == wRemove) 
        {
            LA[uRemove].erase(LA[uRemove].begin() +j);
        }
        }


        for(int j = 0; j < LA[vRemove].size(); j++)
        {
        ii v2 = LA[vRemove][j];
        if(v2.first == uRemove and v2.second == wRemove) 
        {
        LA[vRemove].erase(LA[vRemove].begin() +j);
        }   
        }

        v3.second = prim(explorado, n, uRemove, vRemove, wRemove, acrescimo, LA, Q);

        resultados.push_back(v3);
    }

        for(int i =0 ; i < resultados.size() ; i++)
        {
            cout << resultados[i].first << " " << resultados[i].second << endl;
        }
    return 0;
}
