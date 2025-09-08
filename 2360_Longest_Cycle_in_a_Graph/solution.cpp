/*
2360. Longest Cycle in a Graph: https://leetcode.com/problems/longest-cycle-in-a-graph/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
A solução percorre cada nó simulando o caminho a partir dele, seguindo os ponteiros
definidos pelo vetor "edges". Não é uma DFS clássica, pois aqui cada nó tem no máximo
uma aresta de saída, logo o caminho é sempre linear (uma trilha única), sem necessidade
de explorar múltiplos vizinhos recursivamente. 
Durante a simulação, marcamos em qual iteração cada nó foi visitado e em qual passo da trilha.
Se voltarmos a um nó visto na mesma iteração, encontramos um ciclo e calculamos seu tamanho.
Se chegarmos a um nó já processado em outra iteração, interrompemos pois não haverá ciclo novo.
Assim, a detecção de ciclos é feita por simulação de caminhos, e não por uma DFS completa.
*/
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int quantidade_nos = (int)edges.size();

        // Para cada nó do grafo, guardamos:
        // - "iteracao_visitado": em qual busca (partida) o nó foi visto.
        // - "passo_na_trilha": em que passo dentro da trilha esse nó apareceu.
        // Obs: usamos isso para saber se um nó já pertence ao caminho atual.
        vector<int> iteracao_visitado(quantidade_nos, -1);
        vector<int> passo_na_trilha(quantidade_nos, -1);

        // Marca nós já totalmente processados (não precisam ser reexplorados)
        vector<bool> no_processado(quantidade_nos, false);

        int id_iteracao = 0;         // identificador da busca atual
        int maior_ciclo = -1;        // resposta: tamanho do maior ciclo

        // Testamos começar uma trilha a partir de cada nó
        for (int no_inicial = 0; no_inicial < quantidade_nos; ++no_inicial) {
            if (no_processado[no_inicial]) continue; // nó já processado → pula

            int no_atual = no_inicial;
            int passo_atual = 0; // contador de passos na trilha corrente

            // Caminha pelo grafo até não haver mais aresta ou encontrar repetição
            while (no_atual != -1) {
                // Caso 1: nó já foi visto na trilha atual → ciclo detectado
                if (iteracao_visitado[no_atual] == id_iteracao) {
                    int tamanho_ciclo = passo_atual - passo_na_trilha[no_atual];
                    maior_ciclo = max(maior_ciclo, tamanho_ciclo);
                    break; // encerra esta trilha
                }

                // Caso 2: nó já foi processado em outra trilha → não há ciclo novo
                if (no_processado[no_atual]) {
                    break; // encerra esta trilha
                }

                // Marca este nó como visitado na trilha atual
                iteracao_visitado[no_atual] = id_iteracao;
                passo_na_trilha[no_atual] = passo_atual;
                no_processado[no_atual] = true;

                // Avança para o próximo nó
                ++passo_atual;
                no_atual = edges[no_atual]; // pode virar -1 se não houver saída
            }

            // Finaliza esta busca; incrementa o id de iteração
            ++id_iteracao;
        }

        return maior_ciclo; // devolve o maior ciclo encontrado (ou -1 se nenhum)
    }
};
