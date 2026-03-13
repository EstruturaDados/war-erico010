#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
    Estrutura que representa um território do mapa.
    Cada território possui:
    - nome
    - cor do exército que o controla
    - quantidade de tropas
*/
struct territorio{
    char nome[50];
    char cor[30];
    int tropas;
};

/*
    Função que simula um ataque entre dois territórios.

    Parâmetros:
    mapa -> ponteiro para o vetor de territórios
    atacante -> índice do território atacante
    defensor -> índice do território defensor
*/
void atacar(struct territorio *mapa, int atacante, int defensor){

    // gera números aleatórios de 1 a 6 simulando dados
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n*** BATALHA ***\n");

    printf("Território atacante: %s", mapa[atacante].nome);
    printf("Território defensor: %s", mapa[defensor].nome);

    printf("Dado de ataque: %d\n", dadoAtaque);
    printf("Dado de defesa: %d\n", dadoDefesa);

    // se o dado de ataque for maior ou igual ao de defesa
    if (dadoAtaque >= dadoDefesa){

        // reduz uma tropa do defensor
        if(mapa[defensor].tropas > 0){
            mapa[defensor].tropas--;
        }

        printf("O ataque venceu!\n");

        // se o território ficar sem tropas ele é conquistado
        if(mapa[defensor].tropas <= 0){

            printf("Território conquistado!\n");

            // muda a cor do território para a do atacante
            strcpy(mapa[defensor].cor, mapa[atacante].cor);

            // deixa pelo menos uma tropa no território conquistado
            mapa[defensor].tropas = 1;
        }

    }else{

        // defesa venceu, atacante perde uma tropa
        if(mapa[atacante].tropas > 0){
            mapa[atacante].tropas--;
        }

        printf("A defesa venceu!\n");
    }
}

//Função principal do programa

int main(){

    // inicializa o gerador de números aleatórios
    srand(time(NULL));

    int total = 5;

    // alocação dinâmica de memória para os territórios
    struct territorio *territorios;
    territorios = calloc(total, sizeof(struct territorio));


    //Cadastro dos territórios
    for (int i = 0; i < total; i++)
    {
        printf("\n*** CADASTRO DO TERRITÓRIO %d ***\n", i + 1);

        printf("Nome do território:\n");
        fgets(territorios[i].nome, 50, stdin);

        printf("Cor do exército (ex: AZUL, VERDE...):\n");
        fgets(territorios[i].cor, 30, stdin);

        printf("Número de tropas:\n");
        scanf("%d", &territorios[i].tropas);

        getchar(); // limpa o ENTER do buffer
    }

    int atacante, defensor;

    
    //Loop principal do jogo
    while (1){

        printf("\n*** MAPA ***\n");

        // mostra todos os territórios cadastrados
        for(int i = 0; i < total; i++){

            printf("\nTerritório %d\n", i + 1);
            printf("Nome: %s", territorios[i].nome);
            printf("Cor: %s", territorios[i].cor);
            printf("Tropas: %d\n", territorios[i].tropas);
        }

        printf("\nEscolha o território atacante (1 a %d) ou 0 para sair: ", total);
        scanf("%d", &atacante);

        if(atacante == 0){
            printf("Saindo do jogo...\n");
            break;
        }

        printf("Escolha o território defensor (1 a %d): ", total);
        scanf("%d", &defensor);

        // impede um território de atacar a si mesmo
        if(atacante == defensor){
            printf("Um território não pode atacar a si mesmo!\n");
            continue;
        }

        // chama a função de batalha
        atacar(territorios, atacante - 1, defensor - 1);
    }

    // libera a memória alocada
    free(territorios);

    return 0;
}