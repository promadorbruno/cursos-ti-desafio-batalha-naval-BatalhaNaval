#include <stdio.h>
#include <stdlib.h>

#define TAM 10  // Tamanho do tabuleiro 10x10

/*
Valores do tabuleiro:
0 → água
3 → navio
5 → área afetada pela habilidade
*/

// Função para imprimir o tabuleiro na tela
void imprimir_tabuleiro(int tab[TAM][TAM]) {
    printf("\nTabuleiro (0 = água, 3 = navio, 5 = área afetada):\n\n");
    for (int l = 0; l < TAM; l++) {
        for (int c = 0; c < TAM; c++) {
            printf("%d ", tab[l][c]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
Função para construir uma matriz em formato de CONE.
A matriz é construída de forma dinâmica com laços e condicionais.
O cone aponta para baixo, com o vértice (topo) na parte superior
e se expandindo para baixo.
*/
void construir_cone(int tam, int mat[tam][tam]) {
    int meio = tam / 2;
    for (int l = 0; l < tam; l++) {
        for (int c = 0; c < tam; c++) {
            mat[l][c] = 0;
            // Cria a forma de cone expandindo conforme desce
            if (l >= meio) {
                int largura = l - meio;
                if (c >= meio - largura && c <= meio + largura) {
                    mat[l][c] = 1;
                }
            }
        }
    }
}

/*
Função para construir uma matriz em formato de CRUZ.
A linha e a coluna centrais são marcadas com 1.
*/
void construir_cruz(int tam, int mat[tam][tam]) {
    int meio = tam / 2;
    for (int l = 0; l < tam; l++) {
        for (int c = 0; c < tam; c++) {
            if (l == meio || c == meio)
                mat[l][c] = 1;
            else
                mat[l][c] = 0;
        }
    }
}

/*
Função para construir uma matriz em formato de OCTAEDRO (losango).
Cada posição é avaliada pelo cálculo da distância de Manhattan,
formando o losango em torno do centro.
*/
void construir_octaedro(int tam, int mat[tam][tam]) {
    int meio = tam / 2;
    int raio = meio; // define o tamanho do losango
    for (int l = 0; l < tam; l++) {
        for (int c = 0; c < tam; c++) {
            int distancia = abs(l - meio) + abs(c - meio);
            if (distancia <= raio)
                mat[l][c] = 1;
            else
                mat[l][c] = 0;
        }
    }
}

/*
Função para sobrepor a habilidade ao tabuleiro principal.
A posição (origem_l, origem_c) representa o centro da habilidade.
A matriz de habilidade é colocada sobre o tabuleiro,
marcando com o valor 5 as posições afetadas (valor 1 na matriz).
*/
void aplicar_habilidade(int tab[TAM][TAM], int tam_hab, int hab[tam_hab][tam_hab],
                        int origem_l, int origem_c) {
    int meio = tam_hab / 2;

    for (int l = 0; l < tam_hab; l++) {
        for (int c = 0; c < tam_hab; c++) {
            if (hab[l][c] == 1) {
                int linha_tab = origem_l - meio + l;
                int coluna_tab = origem_c - meio + c;

                // Verifica se está dentro dos limites do tabuleiro
                if (linha_tab >= 0 && linha_tab < TAM && coluna_tab >= 0 && coluna_tab < TAM) {
                    // Marca a posição como afetada pela habilidade
                    tab[linha_tab][coluna_tab] = 5;
                }
            }
        }
    }
}

int main(void) {
    // 1) Criar tabuleiro 10x10 preenchido com água (0)
    int tab[TAM][TAM];
    for (int l = 0; l < TAM; l++) {
        for (int c = 0; c < TAM; c++) {
            tab[l][c] = 0;
        }
    }

    // 2) Colocar alguns navios (valor 3) em posições fixas
    tab[1][2] = 3; tab[1][3] = 3;
    tab[4][4] = 3; tab[5][4] = 3; tab[6][4] = 3;
    tab[8][7] = 3; tab[8][8] = 3; tab[8][9] = 3;

    // 3) Tamanho das matrizes de habilidade (ímpar para ter centro)
    const int TAM_HAB = 7;
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octa[TAM_HAB][TAM_HAB];

    // 4) Construir as três habilidades
    construir_cone(TAM_HAB, cone);
    construir_cruz(TAM_HAB, cruz);
    construir_octaedro(TAM_HAB, octa);

    // Mostrar as matrizes das habilidades (0/1)
    printf("Matriz CONE (1 = afetado):\n");
    for (int l = 0; l < TAM_HAB; l++) {
        for (int c = 0; c < TAM_HAB; c++) printf("%d ", cone[l][c]);
        printf("\n");
    }

    printf("\nMatriz CRUZ (1 = afetado):\n");
    for (int l = 0; l < TAM_HAB; l++) {
        for (int c = 0; c < TAM_HAB; c++) printf("%d ", cruz[l][c]);
        printf("\n");
    }

    printf("\nMatriz OCTAEDRO (1 = afetado):\n");
    for (int l = 0; l < TAM_HAB; l++) {
        for (int c = 0; c < TAM_HAB; c++) printf("%d ", octa[l][c]);
        printf("\n");
    }

    // 5) Definir as posições de origem das habilidades (fixas)
    int origem_cone_l = 2, origem_cone_c = 5;
    int origem_cruz_l = 5, origem_cruz_c = 2;
    int origem_octa_l = 7, origem_octa_c = 6;

    // 6) Aplicar as habilidades no tabuleiro
    aplicar_habilidade(tab, TAM_HAB, cone, origem_cone_l, origem_cone_c);
    aplicar_habilidade(tab, TAM_HAB, cruz, origem_cruz_l, origem_cruz_c);
    aplicar_habilidade(tab, TAM_HAB, octa, origem_octa_l, origem_octa_c);

    // 7) Exibir o tabuleiro final
    imprimir_tabuleiro(tab);

    return 0;
}
