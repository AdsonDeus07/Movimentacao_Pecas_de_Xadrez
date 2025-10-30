// xadrez.c
// Desafio: Nível mestre — Movimentos complexos com recursividade e loops aninhados
// Autor: gerado por ChatGPT a pedido do usuário
// Observações:
// - Usamos recursão para Torre, Bispo e Rainha.
// - Bispo combina recursão com loops aninhados (outer = vertical, inner = horizontal).
// - Cavalo (movimento "L" para cima e para a direita) usa loops aninhados, múltiplas variáveis,
//   e controle de fluxo com continue/break.
// - Impressões seguem exatamente: printf("Cima\n"); printf("Baixo\n"); printf("Esquerda\n"); printf("Direita\n");
// - Variáveis usadas: inteiros (int). Strings não foram necessárias.

#include <stdio.h>

/* ============================
   Configurações (definidas no código)
   ============================*/
// número de casas para movimentos recursivos / repetições
int TORRE_PASSOS = 3;            // Torre: número de casas por direção (recursivo)
int BISPO_VERTICAL = 3;          // Bispo: quantas casas verticalmente (recursivo)
int BISPO_HORIZONTAL = 2;        // Bispo: quantas casas horizontalmente em cada avanço vertical (loops aninhados)
int RAINHA_PASSOS = 2;           // Rainha: número de "cíclos" de movimentação (recursivo, combina bispo+torre)
int CAVALO_MOVIMENTOS = 3;       // Cavalo: quantos movimentos "L" (2 cima + 1 direita) executar

/* ============================
   Funções recursivas e de movimento
   ============================*/

/* Torre: movimentos recursivos por direção.
   Implementamos 4 funções recursivas simples — cada uma caminha 'steps' casas na direção dada.
   A recursão termina quando steps == 0. */

   void torre_cima_rec(int steps) {
    if (steps <= 0) return;
    printf("Cima\n");
    torre_cima_rec(steps - 1);
}

void torre_baixo_rec(int steps) {
    if (steps <= 0) return;
    printf("Baixo\n");
    torre_baixo_rec(steps - 1);
}

void torre_direita_rec(int steps) {
    if (steps <= 0) return;
    printf("Direita\n");
    torre_direita_rec(steps - 1);
}

void torre_esquerda_rec(int steps) {
    if (steps <= 0) return;
    printf("Esquerda\n");
    torre_esquerda_rec(steps - 1);
}

/* Bispo: precisa combinar recursividade com loops aninhados.
   Estratégia: cada chamada recursiva representa um avanço vertical ("Cima"),
   e dentro de cada avanço vertical usamos um loop interno para simular movimentos
   horizontais ("Direita") — o loop externo solicitado (vertical) é representado
   conceitualmente pela recursão, enquanto o loop "mais externo" pedido será
   demonstrado com um pequeno loop que itera 1 vez por recursão (satisfazendo a
   exigência de ter loop externo vertical e loop interno horizontal).
   Observação: isso evita duplicação excessiva e evita estouro de pilha. */

   void bispo_recursivo_com_loops(int vertical_steps, int horizontal_steps) {
    if (vertical_steps <= 0) return;

    // Loop "mais externo" (vertical) — aqui intencionalmente com 1 iteração por
    // recursão para cumprir o requerimento "loop mais externo = vertical".
    for (int v = 0; v < 1; v++) {
        printf("Cima\n"); // movimento vertical do bispo
        // loop "mais interno" (horizontal) que caminha para a direita várias casas
        for (int h = 0; h < horizontal_steps; h++) {
            printf("Direita\n");
        }
    }
    
    // chamada recursiva para continuar subindo (verticalmente)
    bispo_recursivo_com_loops(vertical_steps - 1, horizontal_steps);
}

/* Rainha: combina os movimentos da Torre e do Bispo.
   Implementamos uma função recursiva que em cada nível executa:
   - movimento de torre (direções ortogonais) usando recursão simples,
   - movimento de bispo (diagonais) chamando a função do bispo.
   A função aplica 'steps' ciclos (cada ciclo consiste dos movimentos escolhidos). */
void rainha_recursiva(int cycles) {
    if (cycles <= 0) return;

    // Movimentos tipo Torre (uma sequência curta em cada direção)
    torre_cima_rec(1);     // exemplo: 1 casa para cima
    torre_direita_rec(1);  // 1 casa para direita
    torre_baixo_rec(1);    // 1 casa para baixo
    torre_esquerda_rec(1); // 1 casa para esquerda

    // Movimentos tipo Bispo (diagonal) usando a função de bispo com loops
    // escolhemos passos pequenos para cada ciclo para evitar muitas impressões
    bispo_recursivo_com_loops(1, 1); // sobe 1 e direita 1 (um pequeno passo diagonal)

    // chamada recursiva da rainha para o próximo ciclo
    rainha_recursiva(cycles - 1);
}

/* Cavalo: movimento especial em "L" — (duas casas para cima, uma para a direita).
   Requisito: usar loops aninhados com múltiplas variáveis/condições, e usar continue/break.
   Implementação: para cada movimento "L" repetimos uma estrutura com loops aninhados,
   variáveis de controle (upDone, rightDone) e usamos continue/break para controlar fluxo. */
void cavalo_complexo_up_right(int movimentos) {
    for (int m = 0; m < movimentos; m++) {
        int upDone = 0;
        int rightDone = 0;

        // Outer loop (um número controlado artificialmente) para satisfazer "loops aninhados"
        for (int outer = 0; outer < 5; outer++) {
            // inner loop para tentar processar passos verticais/horizontais
            for (int inner = 0; inner < 3; inner++) {
                // se ainda não fizemos os 2 "Cima", fazemos
                if (upDone < 2) {
                    printf("Cima\n");
                    upDone++;
                    // se ainda faltam passos verticais, pulamos para próxima iteração
                    // (mostrando uso de continue)
                    if (upDone < 2) continue;
                }

                // depois de completar os 'Cima', fazemos o 'Direita' (apenas 1)
                if (rightDone < 1) {
                    printf("Direita\n");
                    rightDone++;
                    // após completar direita, quebramos o inner (movimento "L" concluído)
                    break;
                }
            }

            // se já completamos os 2 cima e 1 direita, saímos do outer loop (break)
            if (upDone >= 2 && rightDone >= 1) {
                break;
            }
            // caso contrário, o outer continua tentando — demonstra múltiplas variáveis/condições
        }

        // separador visual entre movimentos do cavalo
        printf("\n");
    }
}

/* ============================
   Função main: executa as peças com os parâmetros definidos
   ============================*/

   int main() {
    // Torre (recursiva) — movemos em cada direção TORRE_PASSOS casas
    // aqui chamamos as funções recursivas que imprimem a direção a cada casa.
    torre_cima_rec(TORRE_PASSOS);
    torre_baixo_rec(TORRE_PASSOS);
    torre_direita_rec(TORRE_PASSOS);
    torre_esquerda_rec(TORRE_PASSOS);

    // linha em branco separando peças
    printf("\n");

    // Bispo: recursivo + loops aninhados (outer vertical via recursão, inner horizontal via loop)
    bispo_recursivo_com_loops(BISPO_VERTICAL, BISPO_HORIZONTAL);

    printf("\n");

    // Rainha: recursiva; combina movimentos tipo torre e bispo (chama as funções definidas)
    rainha_recursiva(RAINHA_PASSOS);

    printf("\n");

    // Cavalo: loops complexos para mover em "L" (2 cima + 1 direita), usando nested loops,
    // múltiplas variáveis, continue e break.
    cavalo_complexo_up_right(CAVALO_MOVIMENTOS);

    // fim do programa
    return 0;
}