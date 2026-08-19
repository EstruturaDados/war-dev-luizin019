//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO - Nível Aventureito
// ========================================================================
// Desafio nível novato(Construção de territorios)
//
// Desafio nível aventureiro 
// Com alocação dinâmica e modularização m funções diversas
// A ideia do jogo é cadastrar territorios(nome, cor, quantidade de tropas),
// com alocação de memoria sendo a quantide de equipes a escolha livre
// resumo das novas matrias a ser usada
// ========================================================================


//* ponteiro dee endereço de memoria de algum item 
//& aponta para valor contido em um determinado endereço
//free() ao final da aplicacação deve libeerar a memória usada

//calloc reserva o espaço na memoria mas antes zera os valores contido nesse espço
// ponteiro = calloc(quantidade, sizeof(Tipo));

//realoc reajusta de tamanho um espaço ja reseervado anteriormente
// ponteiro = realloc(ponteiro, novo_tamanho_total * sizeof(Tipo));

//malloc reserva espaço na memoria mas pode vir com valor alocados anteriormente 
// ponteiro = malloc(quantidade * sizeof(Tipo));


#include <time.h> 
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

#define TAMANHO_INICIAL 2
#define MAX_STRING 100

typedef struct 
{
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int qtdTropas;
}Territorio;



// prototipação das funções a serem utilizadas
// * é o ponteiro que aponta para Territorio (enderço na memória)
Territorio* cadastro_territorio(int* total);
void exibe_territorios(Territorio* territorios, int total);
void batalha(Territorio* territorios, int total);
int jogar_dados();
void limpar_buffer();
void liberar_memoria(Territorio** territorios);
// **ponteiro para ponteiro, aqui é usado dois ** pois o ponteiro vai ficar com valor zerado, mas na função main
// esse valor precisa ficar com null para não "quebrar a função" e ficar com ponteiro fantasma


// essa função de limpeza é usada pois em c, quando digita ENTER, fica com \n teclado, e essa função "limpa" essa sujeira isso
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// usa a função de números randomicos, e deixa eles restritos de 1 a 6(numeros de dados reias)
int jogar_dados(){
    return (rand() %6 +1);
}

Territorio* cadastro_territorio(int* total){
    int capacidade = TAMANHO_INICIAL;//2 inicialmente dpois pode almentar com forma é cadastrados mais territorios no array

    Territorio* territorios = (Territorio*) malloc(capacidade *sizeof(Territorio));
//o uso do malloc aqui basicamente serve para reservar 1 espço de memoria com capacidade para armazenar 2 Territorios  
//  depois com if valida se tem o espaço necessário na para reserva  
    if(territorios == NULL){
        printf("ERRO: sem memória para reeserva!");
        exit(1);
    }

    printf("\n --- Cadastro de Territórios --- \n");
    printf("Digite 'sair' para encerrar o sistema \n");

  char entrada[10];

    do{

        if(total >= capacidade){
            capacidade *= 2;
// aumenta o alocameento caso total passe a ser maior que a espaço reservado com malloc anterior
            Territorio* temp = (Territorio*) realloc(territorios, capacidade *sizeof(Territorio));

        if(temp == NULL){
            printf("ERRO: Falha ao realocar memória!\n");
            free(territorios);
            exit(1);
        }
//como houve mudanças de realocamento, agora deve atualizado o territorios
        territorios = temp;
        printf("\nMemória expandida para %d territorios\n", capacidade);
    }

         printf("\n--- Território %d ---\n", *total + 1);
        
        printf("Nome do território (ou 'sair' para encerrar): ");
        scanf(" %[^\n]", territorios[*total].nome);
            limpar_buffer();

        // Verifica se o usuário quer sair
        if (strcmp(territorios[*total].nome, "sair") == 0) {
            printf("\n--- Cadastros finalizados! ---\n");
            break;
        }

        printf("Cor do território: ");
        scanf(" %[^\n]", territorios[*total].cor);
            limpar_buffer();

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[*total].qtdTropas);
            limpar_buffer();

        (*total)++; 
   
    } while(1);

// ajusta alocamento do array territorios que pode estar posições sobrando depois da expanção
       if (*total < capacidade) {
        Territorio* temp = (Territorio*) realloc(territorios, (*total) * sizeof(Territorio));
        if (temp != NULL) {
            territorios = temp;
        }
    }

    return territorios;
}

void exibe_territorios(Territorio* territorios, int total){

   if (total == 0) {
        printf("\nNenhum território cadastrado ainda!\n");
        return;
    }

    printf("\n--- Territorios cadastrados---\n");
     for (int i = 0; i < total; i++) {
        printf("Território: %d \nNome: %s \nCor: %s \nQuantidade de tropas: %d \n", 
               i + 1,
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].qtdTropas);
    }
}

void batalha(Territorio* territorios, int total) {
    if(total < 2){
        printf("Preecisa de dois territórios para que a batalha aconteeça!");
        return;
    }

    int atacante, defencor; 

    printf("\n ---Início das batalhas ----\n");

    while(1) { 
    exibe_territorios(territorios, total);

        printf("Escolha o ATACANTE (1-%d)\n", total);
        scanf("%d", &   atacante);

        printf("Escolha o DEFENSOR (1-%d)\n", total);
        scanf("%d", &defencor);

    if(atacante < 1 || defencor < 1 || atacante > total || defencor > total){
        printf("Números de atacante ou defensor inválidos!\n");
        continue;
    }
    if(atacante == defencor){
        printf("Um território não pode atacar ele mesmo!\n");
        continue;
    }
// como o array começa com indice 0 o jogador escolhei um indice superior ao original do array,
// aqui ajusta para posição original do array
    int indexA = atacante - 1;
    int indexD = defencor - 1;

    if(territorios[indexA].qtdTropas <= 0){
        printf("Território %s já derrotado e sem tropas para a batalha!\n", territorios[indexA].nome);
    }
     if(territorios[indexD].qtdTropas <= 0){
        printf("Território %s já derrotado e sem tropas para a batalha!\n", territorios[indexD].nome);
    }

    printf("\n--- %s (Atacando) VS %s (Defendendo)---\n",
    territorios[indexA].nome, territorios[indexD].nome);

    int dadoA = jogar_dados();
    int dadoD = jogar_dados();

        printf("🎲 %s rolou dado, resultado: %d\n", territorios[indexA].nome, dadoA);
        printf("🎲 %s rolou dado, resultado: %d\n", territorios[indexD].nome, dadoD);
    
     if (dadoA > dadoD) {
            printf("%s VENCEU!\n", territorios[indexA].nome);
                territorios[indexD].qtdTropas--;
            
            if (territorios[indexD].qtdTropas == 0) {
                printf(" %s CONQUISTOU %s!\n", 
                    territorios[indexA].nome, 
                    territorios[indexD].nome);
            }
        } else if (dadoD > dadoA) {
                printf(" %s VENCEU!\n", 
                    territorios[indexD].nome);
            territorios[indexA].qtdTropas--;
            
            if (territorios[indexA].qtdTropas == 0) {
                printf(" %s CONQUISTOU %s!\n", 
                    territorios[indexD].nome, 
                    territorios[indexA].nome);
            }
             } else {
                printf("EMPATE!\n");
            }

// validação se ainda tem territórios para outras batalhas ou se resta apenas o veencedor único
        int ativos = 0;
        for (int i = 0; i < total; i++) {
            if (territorios[i].qtdTropas > 0) ativos++;
        }
        
        if (ativos <= 1) {
            printf("\nJOGO ENCERRADO! Apenas um território sobreviveu!\n");
            break;
             }
        }
    }
void liberar_memoria(Territorio** territorios) {
    if (*territorios != NULL) {
// free para liberar os espaços dee memórias usados pelo sistema
        free(*territorios);     
        *territorios = NULL;    
        printf("Memória liberada!\n");
    }
}
int main() {
    srand(time(NULL));  

Territorio* territorios = NULL;
    int total = 0;
    int opcao; 

      do {
        printf("\n========================================\n");
        printf("         BATALHA DOS TERRITÓRIOS\n");
        printf("========================================\n");
        printf("1 - Cadastrar territórios\n");
        printf("2 - Ver todos os territórios\n");
        printf("3 - Iniciar batalha\n");
        printf("0 - Sair do jogo\n");
        printf("========================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limpar_buffer();

    switch (opcao){
             case 1: 
                if (territorios != NULL) {
                    liberar_memoria(&territorios);
                    total = 0;
                }
                territorios = cadastro_territorio(&total);
                printf("\nTotal de territórios cadastrados: %d\n", total);
                break;

            case 2:
                exibe_territorios(territorios, total);
                break;

            case 3: 
                batalha(territorios, total);
                break;

            case 0:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
                }
      } while (opcao != 0);
    
    liberar_memoria(&territorios);
    
    printf("\n=== FIM DO JOGO ===\n");
    return 0;

}