//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO - Nível Novato
// ========================================================================
// Desafio nível novato(Construção de territorios)
//
// Criar um sistema de entrada de dados, com inputs para cadastrar
// "territorios", esses territorio devem ter os campos organizados em 
// uma struct (nome, dominado por, tropas), depois de realizar a coleta de dados
// eles devem ser armazenados em um array de structs. O sistema devee exibir os itens do array
// quando atingir o limite de 5 cadastros no array.
// ========================================================================

#include <stdio.h>
#include <stdlib.h>  // Adicionada a letra 'd' aqui!
#include <string.h>

#define MAX_TERRITORIOS 5
#define MAX_STRINGS 100

typedef struct 
{
    char nome[MAX_STRINGS];
    char dominadoPor[MAX_STRINGS];
    int tropas;
} Territorio;

Territorio array_territorios[MAX_TERRITORIOS];

// essa função serve para que em uma passada seguinte do do/while não haja leitura 
// inesperade de caracteres especiais como \n(pular linha)
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void coletando_dados(void){

    int contagem = 0;

    char nome[MAX_STRINGS];
     char dominadorPor[MAX_STRINGS];
      int tropas;

    do {
        printf("\n================================================\n");
        printf("Preencha os campos e cadastre o terreno %d:\n", contagem + 1);
        
        printf("Qual nome do terreno?\n");
        scanf(" %[^\n]", nome); //" %[^\n]" permite strings com espaços
        
        printf("Quem domina o terreno (escolha uma \n cor)?\n");
        scanf(" %[^\n]",dominadorPor);
        
        printf("Qual o número de tropas?\n");
        scanf("%d", &tropas); //%d e o &para coleta de números inteiros
            limpar_buffer();

        // passando os dados para o array de structs
        strcpy(array_territorios[contagem].nome, nome);
        strcpy(array_territorios[contagem].dominadoPor, dominadorPor);
        array_territorios[contagem].tropas = tropas;

        contagem ++;
    } while (contagem < MAX_TERRITORIOS);
    // quando contagem atingir 4 cadastro encerra(0,1,2,3,4)
        printf("\n >>> Cadastros finalizados! <<<\n");
    
} 

int main (void){
    coletando_dados();

    printf(">>> Os dados coletados foram: <<<");
    // for vai rodar o array e apresentar os dados cadastrados
    for(int i =0 ;i < MAX_TERRITORIOS; i++){
        printf("=== Terreno %d === \n", i);
        printf("Nome %s \n", array_territorios[i].nome);
        printf("Dominador por: %s \n", array_territorios[i].dominadoPor);
        printf("Quantidade d tropas: %d \n", array_territorios[i].tropas);
        printf("---------- \n");
    }
    printf("===================");
    return 0;
}

      



