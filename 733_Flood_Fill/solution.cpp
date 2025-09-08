/*
733. Flood Fill: https://leetcode.com/problems/flood-fill/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem usamos Busca em Largura (BFS) para simular
a ferramenta de "balde de tinta":

1. Identificação da cor inicial:
   Antes de pintar, verificamos a cor original do pixel de partida.
   Se já for igual à nova cor, retornamos a imagem sem alterações.

2. Uso de fila para BFS:
   Utilizamos uma queue para armazenar os pixels que precisam ser pintados.
   A cada iteração, retiramos um pixel da fila, pintamos e
   enfileiramos seus vizinhos válidos.

3. Expansão por 4 direções:
   Cada pixel tem até 4 vizinhos (cima, baixo, esquerda, direita).
   Se o vizinho ainda tiver a cor original, ele é colocado na fila.

O processo continua até não existirem mais pixels a serem pintados.
Isso garante que todos os pixels conectados à região inicial
recebam a nova cor.
*/
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int m = image.size();
        int n = image[0].size();
        int startColor = image[sr][sc];

        /*
        Caso especial:
        Se o pixel inicial já possui a cor desejada, não há nada a fazer.
        */
        if (startColor == color) return image;

        /*
        Fila para BFS.
        Cada elemento representa um pixel (linha, coluna) que precisa ser processado.
        */
        queue<pair<int,int>> q;
        q.push({sr, sc});

        /*
        Vetor de direções possíveis:
        cima (-1,0), baixo (1,0), esquerda (0,-1), direita (0,1).
        */
        vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

        /*
        Loop principal do BFS:
        Enquanto existirem pixels na fila:
        - Pinta o pixel atual
        - Enfileira os vizinhos que ainda têm a cor original
        */
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            // Pinta o pixel com a nova cor
            image[r][c] = color;

            // Explora os 4 vizinhos
            for (auto [dr, dc] : dirs) {
                int nr = r + dr;
                int nc = c + dc;

                // Verifica limites da matriz e cor do vizinho
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && image[nr][nc] == startColor) {
                    q.push({nr, nc});
                }
            }
        }

        return image;
    }
};