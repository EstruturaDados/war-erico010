#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h> //Manipulação de caracteres

//Struct do territórios
struct territorio{
    char nome[50];
    char cor[30];
    int tropas;
};

//Remove \n
void limparEnter(char *str){
    str[strcspn(str, "\n")] = 0;
}

//Deixa tudo maiúsculo
void maiusculo(char *str){
    for(int i = 0; str[i]; i++){
        str[i] = toupper(str[i]);
    }
}

//Void cadastro
void cadastrarTerritorios(struct territorio *mapa, int total){

    for (int i = 0; i < total; i++)
    {
        printf("\n*** CADASTRO DO TERRITÓRIO %d ***\n", i + 1);

        printf("Nome do território:\n");
        fgets(mapa[i].nome, 50, stdin);
        limparEnter(mapa[i].nome);

        printf("Cor do exército (ex: AZUL, VERDE...):\n");
        fgets(mapa[i].cor, 30, stdin);
        limparEnter(mapa[i].cor);
        maiusculo(mapa[i].cor);

        printf("Número de tropas:\n");
        scanf("%d", &mapa[i].tropas);

        getchar(); //limpa enter
    }
}

//Void do mapa
void mostrarMapa(const struct territorio *mapa, int total){

    printf("\n*** MAPA ***\n");

    for(int i = 0; i < total; i++){
        printf("\n[%d]\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

//Void do ataque
void atacar(struct territorio *mapa, int atacante, int defensor, int *conquistas){

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n*** BATALHA ***\n");

    printf("Atacante: %s\n", mapa[atacante].nome);
    printf("Defensor: %s\n", mapa[defensor].nome);

    printf("Dado ataque: %d\n", dadoAtaque);
    printf("Dado defesa: %d\n", dadoDefesa);

    if (dadoAtaque >= dadoDefesa){

        mapa[defensor].tropas--;

        printf("Ataque venceu!\n");

        if(mapa[defensor].tropas <= 0){

            printf("Território conquistado!\n");

            strcpy(mapa[defensor].cor, mapa[atacante].cor);
            mapa[defensor].tropas = 1;

            (*conquistas)++;
        }

    }else{

        mapa[atacante].tropas--;

        printf("Defesa venceu!\n");
    }
}

//Void de missão dinnâmica
void gerarMissao(int *tipoMissao, char *alvo, struct territorio *mapa, int total){

    *tipoMissao = rand() % 2;

    if(*tipoMissao == 0){
        int indice = rand() % total;
        strcpy(alvo, mapa[indice].cor);
    }
}

//Mostrar missão
void mostrarMissao(int missao, const char *alvo){

    printf("\n*** MISSÃO ***\n");

    if(missao == 0)
        printf("Destruir o exército %s\n", alvo);
    else
        printf("Conquistar 3 territórios\n");
}

//Verificador de missão
int verificarMissao(const struct territorio *mapa, int total, int missao, int conquistas, const char *alvo){

    if(missao == 0){
        for(int i = 0; i < total; i++){
            if(strcmp(mapa[i].cor, alvo) == 0){
                return 0;
            }
        }
        return 1;
    }

    if(missao == 1){
        return conquistas >= 3;
    }

    return 0;
}

//Void do menu
void menu(struct territorio *mapa, int total){

    int opcao;
    int atacante, defensor;
    int conquistas = 0;

    int missao;
    char alvo[30];

    gerarMissao(&missao, alvo, mapa, total);

    do{
        mostrarMapa(mapa, total);

        printf("\n1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        getchar();

        switch(opcao){

            case 1:
                printf("Atacante (1 a %d): ", total);
                scanf("%d", &atacante);

                printf("Defensor (1 a %d): ", total);
                scanf("%d", &defensor);

                getchar();

                if(atacante == defensor){
                    printf("Território inválido!\n");
                    break;
                }

                atacar(mapa, atacante - 1, defensor - 1, &conquistas);
                break;

            case 2:
                mostrarMissao(missao, alvo);

                if(verificarMissao(mapa, total, missao, conquistas, alvo)){
                    printf("\n*** MISSÃO CUMPRIDA! VOCÊ VENCEU! ***\n");
                    return;
                } else {
                    printf("Missão ainda não concluída.\n");
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    }while(opcao != 0);
}

//Funçao principal
int main(){

    srand(time(NULL));

    int total = 5;

    struct territorio *territorios;
    territorios = calloc(total, sizeof(struct territorio));

    cadastrarTerritorios(territorios, total);

    menu(territorios, total);

    free(territorios);

    return 0;
}