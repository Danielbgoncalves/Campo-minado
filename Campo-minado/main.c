#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void introducao(){
    printf("\n\n\n\n");
    printf("---------------- CAMPO MINADO ----------------");
    printf("\n\n\n\n Funciona assim: Voce escolhe o tamanho da batalha, um tabuleiro 5x5 ? 10x10? Pode escolher !!!");
    printf("\n Recomendo 6x6 mas se esta confiante vai em um maior");
    printf("\n\n Ao receber o tabuleiro, escolha uma coordenada de linha e coluna para jogar, a contagem de ambos inicia pelo 0, entao");
    printf("\n lembre-se que a primeira linha eh 0, a segunda, 1");
    printf("\n\n legendas:");
    printf("\n 0 indicam casas que nao foram exploradas; ");
    printf("\n 20, casas seguras, nao ha bombas nos arredores; ");
    printf("\n Outros numeros, como 1, 2, 3 indicam o numero de bombas perto dessa casa, pode estar em qualquer uma das 8 casas ao seu redor");
    printf("\n Recomendo tentar achar todas as 20 primeiramente, boa sorte S2 ");

    printf("\n Quando achar q ganhou digite 555 nas coordenadas e recebera o 'gabarito' do mapa ");
    printf("\n\n Tamanho (um unico numero, 5 ou maior) => ");
}

int iniciar(int tamanho,  int matrix[tamanho][tamanho], int matrixVisivel[tamanho][tamanho]){
    srand(time(NULL));

    int nmrCasasSeguras = 0;

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            matrix[i][j] = rand() % 10;
            matrixVisivel[i][j] = 0; 
        }
    }

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            if( i != 0 && i != tamanho-1 && j != 0 && j !=tamanho-1 && (matrix[i][j] == 5 || matrix[i][j] == 4)){
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
                nmrCasasSeguras++;
            }
        }
    }


    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            if(matrix[i][j] == 1){
                matrixVisivel[i-1][j-1]++;
                matrixVisivel[i-1][j]++;
                matrixVisivel[i-1][j+1]++;
                matrixVisivel[i][j-1]++;
                matrixVisivel[i][j] = 10;
                matrixVisivel[i][j+1]++;
                matrixVisivel[i+1][j-1]++;
                matrixVisivel[i+1][j]++;
                matrixVisivel[i+1][j+1]++;
            }
        }
    }

    return nmrCasasSeguras;

}

void mostra(int tamanho, int matrix[tamanho][tamanho], int matrixVisivel[tamanho][tamanho]){
    system("cls");
    printf("matrix real \n");
    printf("0 para nao virados e 20 para virados e seguros \n");
    for(int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("   %2d  ",matrix[i][j]);
        }
        printf("\n\n\n");
    }    

}

void zeraCampo(int tamanho, int matrix[tamanho][tamanho]){
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            matrix[i][j] = 0; 
        }
    }
}

void fazerJogada(int *jogadaEmi, int *jogadaEmj){
    printf("Onde planeja jogar ?\n");
    printf("Coordenada linha: ");
    int a,b;
    scanf("%d", &a);
    *jogadaEmi = a;
    printf("Coordenada coluna: ");
    scanf("%d", &b);
    *jogadaEmj = b;
    
}

void teste(int tamanho, int matrixVisivel[tamanho][tamanho], int *jogadaEmi, int *jogadaEmj, int matrix[tamanho][tamanho], int *fimDeJogo, int seguras){


     if(*jogadaEmi == 555){
        printf("\n ___ Matrix visivel _____ \n");
        printf("\n 0 para espacos vazios \n");
        printf("\n 1, 2, 3 para casas perigosas \n");
        printf("\n numeros maiores que 10 para bombas \n");
        for(int i = 0; i < tamanho; i++) {
            for (int j = 0; j < tamanho; j++) {
                printf("   %2d   ",matrixVisivel[i][j]);
            }
            printf("\n\n");
        }
    }


    if(matrixVisivel[*jogadaEmi][*jogadaEmj] == 0 ){
        matrix[*jogadaEmi][*jogadaEmj] = 20; // 20 para aberto e vazio
        seguras -= 1;
    } else if (matrixVisivel[*jogadaEmi][ *jogadaEmj] > 0 && matrixVisivel[*jogadaEmi][*jogadaEmj] < 10 ){
        matrix[*jogadaEmi][*jogadaEmj] = matrixVisivel[*jogadaEmi][*jogadaEmj];
        seguras -= 1;
    } else if (matrixVisivel[*jogadaEmi][*jogadaEmj] >= 10) {
        printf("\n\n");
        printf("Voce perdeu, tinha uma bomba ali\n"); 
        printf("Espero que tenha gostado"); 
        fimDeJogo = 1;
        main();
    }

}

int main()
{
    int fimDeJogo = 0; //0 continua, 1 acabou
    if(fimDeJogo == 1){
        printf("Voce perdeu, tinha uma bomba ali"); 
        return 0;
    }
    introducao();
    int tamanho;
    scanf("%d", &tamanho);
    int campo[tamanho][tamanho];
    int visivel[tamanho][tamanho];

    int nmmrCasasSeguras = iniciar(tamanho, campo, visivel);
    zeraCampo(tamanho, campo);
    mostra(tamanho,campo, visivel);
    while(fimDeJogo == 0){
        int jogadaEmi;
        int jogadaEmj;
        fazerJogada(&jogadaEmi, &jogadaEmj);
        teste(tamanho, visivel, &jogadaEmi, &jogadaEmj, campo, &fimDeJogo, nmmrCasasSeguras);
        mostra(tamanho,campo, visivel);
    }
    return 0;
}