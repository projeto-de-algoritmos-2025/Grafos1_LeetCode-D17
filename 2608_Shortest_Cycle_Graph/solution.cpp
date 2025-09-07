/*
2608. Shortest Cycle in a Graph: https://leetcode.com/problems/shortest-cycle-in-a-graph/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem usamos como referência o algoritmo BFS para detectar ciclos.
A ideia é: para cada nó do grafo, rodamos um BFS e verificamos se existe um vizinho já visitado 
que não seja o pai direto. Isso significa que encontramos um ciclo, e conseguimos calcular 
o comprimento desse ciclo como dist[u] + dist[v] + 1.
Mantemos sempre o menor ciclo encontrado.
*/

#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        /*
        Construímos o grafo como uma lista de adjacência.
        */
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        /*
        Definimos a resposta inicial como infinito (INT_MAX).
        Se nenhum ciclo for encontrado, retornaremos -1.
        */
        int ans = INT_MAX;

        /*
        Para cada vértice do grafo, realizamos um BFS.
        O BFS vai nos ajudar a calcular distâncias (dist[])
        e manter o controle de pais (parent[]).
        */
        for (int start = 0; start < n; start++) {
            vector<int> dist(n, -1), parent(n, -1);
            queue<int> q;

            dist[start] = 0;
            q.push(start);

            /*
            Enquanto a fila não estiver vazia, exploramos o grafo.
            */
            while (!q.empty()) {
                int u = q.front(); q.pop();

                /*
                Para cada vizinho de u, temos dois casos:
                1. Se o vizinho v ainda não foi visitado:
                   - Definimos sua distância como dist[u] + 1
                   - Definimos seu pai como u
                   - Adicionamos v na fila
                2. Se o vizinho v já foi visitado e não é o pai de u:
                   - Encontramos um ciclo
                   - O tamanho do ciclo é dist[u] + dist[v] + 1
                   - Atualizamos ans se esse ciclo for menor
                */
                for (int v : adj[u]) {
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        parent[v] = u;
                        q.push(v);
                    } else if (parent[u] != v) {
                        ans = min(ans, dist[u] + dist[v] + 1);
                        // Ciclo mínimo possível é 3, podemos sair mais cedo
                        if (ans == 3) return 3;
                    }
                }
            }
        }

        /*
        Caso nenhum ciclo tenha sido encontrado, retornamos -1.
        Caso contrário, retornamos o menor ciclo encontrado.
        */
        return (ans == INT_MAX ? -1 : ans);
    }
};
