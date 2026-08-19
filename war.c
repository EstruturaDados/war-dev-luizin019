// Desafio nível MESTRE 
// Com alocação dinâmica e modularização m funções diversas
// A ideia do jogo é cadastrar territorios(nome, cor, quantidade de tropas),
// com alocação de memoria sendo a quantide de equipes a escolha livre
// resumo das novas matrias a ser usada
// Script modularizado em funções destintas
// Agora como mais uma função adicional para missão para um territorio
// A missão vai ser escolher um territorio jogar 3 dados,
//  a quantidade somada dos resultados/ pela quantidade de territorios existentes no sistema arrdondando resultado para baixo,
//  será acresido na quantidade de tropas daquele territorio
// tambem tera opção de jogar sorte que tambem roda os 3 dados, e cada um dos territorio tera suas tropas aumentadas
// de acordo com um rsultado de um dado(aleatorio)

//* ponteiro dee endereço de memoria de algum item 
//& aponta para valor contido em um determinado endereço

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
int calcular_valor_tropas(int soma_dados, int total_territorios);
void missao_adicionar_tropas(Territorio* territorios, int total);
void missao_sorte(Territorio* territorios, int total);
int jogar_tres_dados();
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

// como as duas novas funções usarão sorteio de tres dados
int jogar_tres_dados() {
    int dado1 = jogar_dados();
    int dado2 = jogar_dados();
    int dado3 = jogar_dados();

    int soma = dado1 + dado2 + dado3;

    printf("Os três dados jogados foram: %d + %d + %d = %d\n", dado1, dado2, dado3, soma);

    return soma;
}

int calcular_valor_tropas(int soma_dados, int total_territorios) {
    if (total_territorios == 0) {
        return 0;
    }
// double deixa o decimal com apenas duas casas depois da virgula
    double valor_bruto = (double)soma_dados / total_territorios;
// floor errdonda para o inteiro abaixo
    int valor_final = (int)floor(valor_bruto);

    printf("Resultado: %d / %d = %.2f → Arredondado para: %d\n", 
           soma_dados, total_territorios, valor_bruto, valor_final);

    return valor_final;
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

        printf("%s rolou dado, resultado: %d\n", territorios[indexA].nome, dadoA);
        printf("%s rolou dado, resultado: %d\n", territorios[indexD].nome, dadoD);
    
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

void missao_adicionar_tropas(Territorio* territorios, int total) {
    if (total == 0) {
        printf("\nNenhum território cadastrado ainda!\n");
        return;
    }

    printf("\n=== MISSAO: ADICIONAR TROPAS(aleatórias)===\n");

    exibe_territorios(territorios, total);
    
    int escolha;
    printf("\nEscolha o território para receber as novas tropas (1-%d): ", total);
    scanf("%d", &escolha);
    limpar_buffer();
    
    if (escolha < 1 || escolha > total) {
        printf("Opção inválida, esse território é possivelmente inexistente!\n");
        return;
    }

    int index = escolha - 1;
    
    printf("\nTerritório escolhido: %s\n", territorios[index].nome);
    printf("Tropas atuais: %d\n", territorios[index].qtdTropas);
    
    printf("\nJogando 3 dados...\n");
    int soma_dados = jogar_tres_dados();
 
    int valor_adicionado = calcular_valor_tropas(soma_dados, total);
    
    territorios[index].qtdTropas += valor_adicionado;
    
    printf("\n%s recebeu +%d novas tropas!\n", territorios[index].nome, valor_adicionado);
    printf("Tropas atualizadas para: %d\n", territorios[index].qtdTropas);
}

void missao_sorte(Territorio* territorios, int total) {
    if (total == 0) {
        printf("\nNenhum território cadastrado ainda!\n");
        return;
    }

    printf("\n=== MISSAO: A SORTE ESTÁ LANÇADA ===\n");
    printf("ATENÇÃO: Todas as tropas serão ZERADAS e redistribuídas!\n");
    
    printf("\nSituação atual de cada território:\n");
    exibe_territorios(territorios, total);
// aqui o malloc cria um array temporario para guardar os valores 
    int* novos_valores = (int*) malloc(total * sizeof(int));
    
    if (novos_valores == NULL) {
        printf("Erro ao alocar memória temporária!\n");
        return;
    }
    printf("\nCalculando os novos valoresde cada território...\n");
// o for roda o total de terrenos cadastrados ecalcular novo valor de tropa de cada  
    for (int i = 0; i < total; i++) {
        printf("\n--- %s ---\n", territorios[i].nome);
        
        int soma_dados = jogar_tres_dados();
        int novo_valor = calcular_valor_tropas(soma_dados, total);
        
        novos_valores[i] = novo_valor;
        
        printf("Novo valor calculado: %d tropas\n", novo_valor);
    }
    printf("\nZerando todas as tropas...\n");
    for (int i = 0; i < total; i++) {
        territorios[i].qtdTropas = 0;
    }
    printf("\nDistribuido os novos valores...\n");
    for (int i = 0; i < total; i++) {
        territorios[i].qtdTropas = novos_valores[i];
        printf("%s agora tem %d tropas\n", 
               territorios[i].nome, 
               territorios[i].qtdTropas);
    }
// free apenas para array temporario da função 
    free(novos_valores);
    novos_valores = NULL;
    
    printf("\n--- SITUAÇÃO FINAL: ---\n");
    exibe_territorios(territorios, total);
    
    printf("\nMissão 'A Sorte Está Lançada' concluída!\n");
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
        printf("4 - Ganhar tropas (aleatórias)\n");
        printf("5 - A sorte esta lançada\n");
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
            case 4: 
                missao_adicionar_tropas(territorios, total);
                break;

            case 5:         
                missao_sorte(territorios, total);
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
// 1ºmissão "adicionar tropas", a regra vai ser selecionar um território cadastrado no 
// array e jogar 3 dado o resultado desse dados, 
// a soma dos resultados desse 3 dados dividido pela quantidade de territórios cadastrados
// no sistema sera adicionada as tropas daquele território escolhido antes, caso de valor quebrado, sera arredondado para baixo e atualizado no array as tropas daquele territorio
// 2ºmissão "A sorte esta lançada", consiste em jogar 3 dados para cada um dos territorios
// existents no sistema, para cada territorio, sera somado (a soma do valor resultante daqueles
// 3 dados jogados na vez dele, tambem dividindo pelo total de equipes cadastradas no 
// sistema e arredondado para baixo em caso de numero não inteiros), e em vez de somar as 
// tropas daqueles territorio vamos zerar as tropas d todas nssa missão e cada um vai ter 
// a sorte de ganhar novos valores de tropas de acordo com o sorteio dos tres dados deles 
// de acordo com regra de resultado estabelecida (soma 3 dados/quantidade de territorios)
// arredondo para o nº inteiro anterior