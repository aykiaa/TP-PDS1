#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Rua
{
    int x;
    int y;
    int pavimentado;

};

struct Restaurante
{
    int x;
    int y;
    char nome[40];
    char custo[10]; 
    int velocidade;
};

struct Casa
{
    int x;
    int y;
};

bool is_adjacente(Rua rua1, Rua rua2) //determinar se duas ruas sao adjacentes ou nao, comparando suas coordernadas
{
    if( (rua1.x == rua2.x + 1) && (rua1.y == rua2.y + 1)) return true;
    else if ((rua1.x == rua2.x + 1) && (rua1.y == rua2.y)) return true;
    else if ((rua1.x == rua2.x) && (rua1.y == rua2.y + 1)) return true;
    else return false;

}

int main(){
    // Ler os arquivos ruas.txt e restaurantes.txt
    FILE* f_ruas = fopen("ruas.txt", "r+t");
    FILE* f_restaurantes = fopen("restaurantes.txt", "r+t");

    if (f_ruas == NULL) 
    {
        printf("Erro ao abrir o arquivo Ruas.\n");
        return 1;
    }
    
    if (f_restaurantes == NULL)
    {
        printf("Erro ao abrir o arquivo Ruas.\n");
        return 1;
    }

    Rua ruas_cidade[900];
    Restaurante restaurantes_cidade[24];
    int cont_ruas = 0;
    int cont_rest = 0; 
    Rua ruas_pavimentadas[450];
    int cont_pavimentadas = 0;
    
    // Contabilizando as ruas
    while(!feof(f_ruas))
    {
        fscanf(f_ruas, "%d %d %d", &ruas_cidade[cont_ruas].x, &ruas_cidade[cont_ruas].y, &ruas_cidade[cont_ruas].pavimentado);
        cont_ruas++;
    }
    
    //Contabilizando os restaurantes
    while (!feof(f_restaurantes))
    {
        fscanf(f_restaurantes, "%d %d %s %s %d", &restaurantes_cidade[cont_rest].x, &restaurantes_cidade[cont_rest].y, &restaurantes_cidade[cont_rest].nome, &restaurantes_cidade[cont_rest].custo, &restaurantes_cidade[cont_rest].velocidade);
        cont_rest++;
    }
    
    
    // Separo as ruas pavimentadas em outro array a partir do array geral de ruas 
    for (int i = 0; i < cont_ruas; i++)
    {
        if (ruas_cidade[i].pavimentado == 1)
        {
            ruas_pavimentadas[cont_pavimentadas] = ruas_cidade[i];
            cont_pavimentadas++;
        }
    }
    
    for (int i = 0; i < cont_pavimentadas; i++)
    {
        printf("%d %d %d\n", ruas_pavimentadas[i].x, ruas_pavimentadas[i].y, ruas_pavimentadas[i].pavimentado);
    }
    

    printf("Ruas: %d\n", cont_ruas);
    printf("Ruas pav: %d\n", cont_pavimentadas);


    /*Casa casa;
    printf("Digite as coordernadas de sua casa:\n");
    scanf("X: %d\n", &casa.x);
    scanf("Y: %d\n", &casa.y);*/




    
    fclose(f_ruas);
    fclose(f_restaurantes);
    return 0;
}