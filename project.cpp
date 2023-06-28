#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


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
    char nome[50];
    char custo[10];
    int velocidade;
    float tempo_de_entrega;
};

struct Casa
{
    int x;
    int y;
    int custo; //1 CARO 2 BARATO
};

struct Esquina
{
    int x;
    int y;
    int distancia;
};

bool is_adjacente(Rua rua1, Rua rua2) //determinar se duas ruas sao adjacentes ou nao, comparando suas coordernadas
{
    if( (rua1.x == rua2.x + 1) && (rua1.y == rua2.y)) return true;
    else if ((rua1.x == rua2.x) && (rua1.y == rua2.y + 1)) return true;
    else if ((rua1.x == rua2.x - 1) && (rua1.y == rua2.y)) return true;
    else if ((rua1.x == rua2.x) && (rua1.y == rua2.y - 1)) return true;
    else return false;

}
int calcular_distancia(Casa casa, Restaurante restaurante, Rua *ruas_pavimentadas, int num_ruas_pavimentadas)
{

    Esquina fila[897];
    int inicio_fila = 0; //primeiro elemento da fila para ser consultado
    int final_fila = 0; //coloca na ultima posicao 
    bool visitado[39][23]= {false}; //crio uma matriz para guardar se uma esquina ja foi vista ou nao, alem disso 39x23 porque essa eh a ultima rua/esquina 

    Esquina esquina_inicial; //Ponto de inicio da pesquisa do caminho a partir da casa do usuario
    esquina_inicial.x = casa.x;
    esquina_inicial.y = casa.y;
    esquina_inicial.distancia = 0;

    fila[final_fila] = esquina_inicial; //primeira esquina entra na fila para ser verificada
    final_fila++;
    visitado[casa.x][casa.y]= true; // crio uma matriz para guardar se uma esquina ja foi vista ou nao

    while (inicio_fila != final_fila) // enquanto a fila for tendo elementos diferentes, ela continua rodando
    {
        Esquina atual = fila[inicio_fila];
        inicio_fila++;

        if (atual.x == restaurante.x && atual.y == restaurante.y) //quando chegar no resturante retorna a distancia 
        {
            return atual.distancia;
        }

        Esquina esq_cima;
        esq_cima.x = atual.x;
        esq_cima.y = atual.y - 1;
        esq_cima.distancia = atual.distancia + 1;

        Esquina esq_baixo;
        esq_baixo.x = atual.x;
        esq_baixo.y = atual.y + 1;
        esq_baixo.distancia = atual.distancia + 1;
        
        Esquina esq_direita;
        esq_direita.x = atual.x + 1;
        esq_direita.y = atual.y;
        esq_direita.distancia = atual.distancia + 1;

        Esquina esq_esquerda;
        esq_esquerda.x = atual.x - 1;
        esq_esquerda.y = atual.y;
        esq_esquerda.distancia = atual.distancia + 1;




        Esquina vizinhos[4] = {esq_direita, esq_esquerda, esq_cima, esq_baixo};

        for (int i = 0; i < 4; i++) // testo os vizinhos, para ver se sao validos dentro da matriz
        {
            Esquina vizinho = vizinhos[i];

            if (vizinho.x >= 0 && vizinho.x < 40 && vizinho.y >= 0 && vizinho.y < 24 && !visitado[vizinho.x][vizinho.y])
            {
                bool caminho_valido = false; //crio uma variavel para verificar se o caminho for pavimentado e dentro dos limites

                for (int j = 0; j < num_ruas_pavimentadas; j++) //verifico se eh uma rua pavimentada
                {
                    if (vizinho.x == ruas_pavimentadas[j].x && vizinho.y == ruas_pavimentadas[j].y)
                    {
                        caminho_valido = true; //valido o caminho
                        break; // e saio do for
                    }
                }

                if (caminho_valido)
                {
                    fila[final_fila] = vizinho; //adiciono o vizinho verificado na fila para pesquisa
                    final_fila++;
                    visitado[vizinho.x][vizinho.y]= true; //indico que a coodernada ja foi visitada
                }
            }
        }
    }
}


float calcular_tempo_entrega(int distancia, int velocidade)
{
    float tempo = distancia / velocidade;
    return tempo;

}


int main()
{
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
        printf("Erro ao abrir o arquivo Restaurantes.\n");
        return 1;
    }

    Rua ruas_cidade[900];
    Restaurante restaurantes_cidade[24];
    int cont_ruas = 0;
    int cont_rest = 0; 
    int cont_rest_caro = 0;
    int cont_rest_barato = 0;
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
        if (restaurantes_cidade[cont_rest].custo == "Caro")
        {
            cont_rest_caro++;
        }
        else cont_rest_barato++;
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
    for (int i = 0; i < cont_rest-1; i++)
    {
        printf("%d %d %s %s %d\n", restaurantes_cidade[i].x, restaurantes_cidade[i].y, restaurantes_cidade[i].nome, restaurantes_cidade[i].custo, restaurantes_cidade[i].velocidade);
    }





    printf("Ruas: %d\n", cont_ruas);
    printf("Ruas pav: %d\n", cont_pavimentadas);

    Casa casa_user;
    printf("Digite as coordernadas de sua casa: \n");
    printf("X:\n"); scanf("%d", &casa_user.x);
    printf("Y:\n"); scanf("%d", &casa_user.y);
    printf("Qual sua preferencia de custo?\n[1]Caro \n[2]Barato\n"); scanf("%d", &casa_user.custo); // 1 para CARO; 2 para BARATO
    
    //Verifica se a casa do usuario esta em uma rua pavimentada
    for (int i = 0; i < cont_ruas; i++)
    {
        if (ruas_cidade[i].x == casa_user.x && ruas_cidade[i].y == casa_user.y && ruas_cidade[i].pavimentado == 0)
        {
            printf("Sua casa nao esta em uma area pavimentada\n");
            break;
        }
    }
    
    //printf("Distancias da sua casa aos restaurantes:\n");
    
    for (int i = 0; i < cont_rest-1; i++)
    {
        int distancia = calcular_distancia(casa_user, restaurantes_cidade[i], ruas_pavimentadas, cont_pavimentadas);
        restaurantes_cidade[i].tempo_de_entrega = distancia/restaurantes_cidade[i].velocidade;
    }
    

    switch (casa_user.custo) //Mostra as opcoes de restaurantes a partir da preferencia (caro ou barato) do usuario
    {
    case 1:
        for (int i = 0; i < cont_rest; i++)
        {
            if(stricmp(restaurantes_cidade[i].custo, "Caro") == 0) //comparo as strings, para printar somente restaurantes CAROS
            {
                printf("%s -> Tempo de entrega: %.2f\n", restaurantes_cidade[i].nome, restaurantes_cidade[i].tempo_de_entrega);
            }
        }
        break;
    case 2:
        for (int i = 0; i < cont_rest; i++)
        {
            if (strcmp(restaurantes_cidade[i].custo, "Barato") == 0)
            {
                printf("%s: Tempo de entrega: %.2f\n", restaurantes_cidade[i].nome, restaurantes_cidade[i].tempo_de_entrega);
            }
        }
        break;
    }
    
    
    
    
    /*for (int i = 0; i < cont_rest-1; i++)
    {
        int distancia = calcular_distancia(casa_user, restaurantes_cidade[i], ruas_pavimentadas, cont_pavimentadas);
        printf("A distancia da sua casa ate o restaurante %s eh %d zambs.\n", restaurantes_cidade[i].nome, distancia);
    }*/



    


    
    fclose(f_ruas);
    fclose(f_restaurantes);
    return 0;
}