/*
79. Word Search: https://leetcode.com/problems/word-search/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem usamos uma busca em profundidade (DFS) com backtracking,
combinada com otimizações:

1. **Pruning por frequência**:
   Antes de iniciar a busca, verificamos se o board possui caracteres suficientes
   para formar a palavra. Se faltar algum caractere, retornamos false imediatamente.

2. **Heurística de ordem**:
   Para reduzir o branching, verificamos qual letra (primeira ou última da palavra)
   é mais rara no board. Se a última for mais rara, invertemos a palavra
   e começamos a busca por ela.

3. **DFS com máscara de bits**:
   Em vez de copiar o board ou usar uma matriz visited[][], representamos as
   células visitadas com um inteiro (bitmask). Como o board tem no máximo 6x6=36
   células, cada célula é mapeada para um bit na máscara.
   Isso reduz o uso de memória e acelera a checagem de visitados.

A DFS tenta expandir a palavra caractere por caractere,
explorando até 4 direções (cima, baixo, esquerda, direita).
Se chegarmos ao último caractere, retornamos true.
*/

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int m, n;
    vector<vector<char>> board;
    string word;
    vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

    /*
    Função auxiliar que transforma uma célula (i, j) em um índice de bit
    único dentro da máscara.
    */
    int cellToBit(int i, int j) { 
        return i * n + j; 
    }

    /*
    Função DFS recursiva:
    - x, y: posição atual
    - k: índice atual na palavra
    - mask: bitmask de células já visitadas

    Se k == último índice da palavra, significa que conseguimos
    formar a palavra → retornamos true.

    Caso contrário, exploramos 4 direções e continuamos a busca.
    */
    bool dfs(int x, int y, int k, long long mask) {
        if (k == word.size() - 1) return true;

        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
                int bit = cellToBit(nx, ny);
                // Checa se célula não foi visitada e se letra bate
                if (!(mask & (1LL << bit)) && board[nx][ny] == word[k+1]) {
                    if (dfs(nx, ny, k+1, mask | (1LL << bit))) return true;
                }
            }
        }
        return false;
    }

    bool exist(vector<vector<char>>& b, string w) {
        board = b; 
        word = w;
        m = board.size();
        n = board[0].size();

        /*
        1. Pruning por frequência:
        Verifica se o board contém todas as letras necessárias.
        */
        unordered_map<char,int> freqWord, freqBoard;
        for (char c : word) freqWord[c]++;
        for (auto& row : board) 
            for (char c : row) freqBoard[c]++;
        for (auto& [c, cnt] : freqWord) 
            if (cnt > freqBoard[c]) return false;

        /*
        2. Heurística de ordem:
        Inverte a palavra se a última letra for mais rara que a primeira.
        */
        if (freqBoard[word.back()] < freqBoard[word.front()]) {
            reverse(word.begin(), word.end());
        }

        /*
        3. Inicia a busca a partir de todas as células possíveis.
        */
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    long long mask = 0;
                    mask |= (1LL << cellToBit(i,j));
                    if (dfs(i, j, 0, mask)) return true;
                }
            }
        }

        return false;
    }
};
