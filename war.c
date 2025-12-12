// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_NOME 50
#define MAX_COR 20
#define MAX_TERRITORIOS 5

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct {
    char nome[MAX_NOME];
    char cor_Exercito[MAX_COR];
    int numero_Tropas;
} Territorio;

// 
Territorio *territorios = NULL;
int totalTerritorios = 0;

// --- Declarar Funções ---
//Funçao Limpar buffer de entrada
void limparBufferEntrada();
// Função Menu Principal
void MenuPrincipal();
//Função Cadastrar Territorios
void CadastrarTerritorio();
//Função Listar Territorios
void ListarTerritorios();
//Função Exibir Mapa
void exibirMapa();
//Função SimularAtaque
void simularAtaque(int origem, int destino);
// Função Fase de ataque
void faseDeAtaque();

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {

    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    setlocale(LC_ALL, "Portuguese");
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    srand(time(NULL));
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
     printf("Alocando memória para %d territórios...\n", MAX_TERRITORIOS);
     territorios = (Territorio *)calloc(MAX_TERRITORIOS, sizeof(Territorio));
     if (territorios == NULL) {
        printf("ERRO: Falha ao alocar memória!\n");
        printf("O sistema não tem memória disponível.\n");
        return 1;
     }
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    


    while (1)
    {
     MenuPrincipal();
    }
    
    
     // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// ---------------- Implementação das Funções ----------------

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.
void MenuPrincipal() {
    int opcao;

    printf("Menu Principal\n");
    printf("1. Jogar\n");
    printf("2. Listar Territórios\n");
    printf("3. Cadastrar Territórios\n");
    printf("4. Exibir estado atual do mapa\n");
    printf("5. Sair\n");
    scanf("%d", &opcao);
    limparBufferEntrada();

    switch (opcao)
    {
    case 1:
        faseDeAtaque();
        break;
    
    case 2:
        ListarTerritorios();
        break;

    case 3:
        while (totalTerritorios<MAX_TERRITORIOS)
        {
        CadastrarTerritorio();
        }

        break;

    case 4:
        exibirMapa();
        break;

    case 5:
        printf("\nEncerrando o jogo...\n");
        if (territorios != NULL) {
        free(territorios);
        territorios = NULL;
        printf("Memoria liberada com sucesso!\n");
    }
        exit(0);
        break;

    default:
        printf("Opção inválida !\n");
        break;
    }
}

// Função CadastrarTerritorio()
void CadastrarTerritorio(){

    printf("Cadastro de Territorio !\n");
    if (totalTerritorios < MAX_TERRITORIOS)
    {
        printf("Digite o nome do território :\n");
        fgets(territorios[totalTerritorios].nome, MAX_NOME, stdin);
        territorios[totalTerritorios].nome[strcspn(territorios[totalTerritorios].nome, "\n")] = '\0';


        printf("Digite a cor do exército :\n");
        fgets(territorios[totalTerritorios].cor_Exercito, MAX_COR, stdin);
        territorios[totalTerritorios].cor_Exercito[strcspn(territorios[totalTerritorios].cor_Exercito, "\n")] = '\0';



        printf("Digite a quantidade de tropas :\n");
        scanf("%d", &territorios[totalTerritorios].numero_Tropas);
        limparBufferEntrada();

        totalTerritorios++;
        printf("\nTerritório cadastrado! (%d/%d)\n", totalTerritorios, MAX_TERRITORIOS);
    } else {
        printf("Territórios cadastrados\n");
    }
}

// Função Listar Territórios
void ListarTerritorios() {
    if (totalTerritorios == 0) {
    printf("Nenhum território cadastrado ainda.\n");
    printf("Use a opção 3 para cadastrar territórios.\n");
    return;
    }
    printf("\nLista de Territórios!\n");
    for (int i = 0; i < totalTerritorios; i++)
    { 
        printf("==== Territorio(%d) ====\n", totalTerritorios);
        printf("Nome do território : %s ", territorios[i].nome);
        printf("Cor do exército : %s ", territorios[i].cor_Exercito);
        printf("Tropas : %d \n", territorios[i].numero_Tropas);
        printf("=========================\n");
        printf("\n");
    }
    
}

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
void exibirMapa() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                 MAPA DO MUNDO - JOGO WAR                   ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    if (totalTerritorios == 0) {
        printf(" Cadastre territórios usando a opção 3 do menu.\n\n");
        return;
    }
    
    printf("\n");
    
    for (int i = 0; i < totalTerritorios; i++) {
        printf("┌─────────────────────────────────────────────────────────┐\n");
        printf("│ TERRITÓRIO #%-2d                                        │\n", i + 1);
        printf("├─────────────────────────────────────────────────────────┤\n");
        printf("│  Nome:       %-40s │\n", territorios[i].nome);
        printf("│  Exército:   %-40s │\n", territorios[i].cor_Exercito);
        printf("│  Tropas:     %-40d │\n", territorios[i].numero_Tropas);
        printf("└─────────────────────────────────────────────────────────┘\n");
        
        if (i < totalTerritorios - 1) {
            printf("             \n\n");
        }
    }
        printf("\n");
        printf("═══════════════════════════════════════════════════════════\n");
        printf("Territórios Cadastrados: %d/%d\n", totalTerritorios, MAX_TERRITORIOS);
    
        // Estatísticas adicionais
        int totalTropas = 0;
        for (int i = 0; i < totalTerritorios; i++) {
        totalTropas += territorios[i].numero_Tropas;
    }
    printf(" Total de tropas no mapa: %d\n", totalTropas);
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("\n");
}

// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.
// faseDeAtaque()
void faseDeAtaque() {
    char continuar;
    
    do {
        printf("\nFASE DE ATAQUE\n");
        printf("--------------------------------------\n\n");

        exibirMapa();

        int origem, destino;
        
        printf("\nEscolha o territorio de ORIGEM (atacante) [1-%d]: ", totalTerritorios);
        scanf("%d", &origem);
        limparBufferEntrada();

        if (origem < 1 || origem > totalTerritorios) {
            printf("Territorio invalido! Deve ser entre 1 e %d.\n", totalTerritorios);
            continue;
        }

        printf("Escolha o territorio de DESTINO (defensor) [1-%d]: ", totalTerritorios);
        scanf("%d", &destino);
        limparBufferEntrada();

        if (destino < 1 || destino > totalTerritorios) {
            printf("Territorio invalido! Deve ser entre 1 e %d.\n", totalTerritorios);
            continue;
        }

        simularAtaque(origem - 1, destino - 1);
        
        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
        limparBufferEntrada();
        
    } while (continuar == 's' || continuar == 'S');
    
    printf("\nVoltando ao menu principal...\n");
}

// Função para rolar um dado
int rolarDado() {
    return 1 + rand() % 6;
}
// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.
void simularAtaque(int origem, int destino) {
    printf("\nSIMULANDO COMBATE - TURNO\n");
    printf("--------------------------------------\n\n");

    if (origem == destino) {
        printf("Nao pode atacar o proprio territorio!\n");
        return;
    }

    if (territorios[origem].numero_Tropas < 1) {
        printf("Territorio nao tem tropas para atacar!\n");
        return;
    }

    if (strcmp(territorios[origem].cor_Exercito, territorios[destino].cor_Exercito) == 0) {
        printf("Nao pode atacar territorio do mesmo exercito!\n");
        return;
    }

    printf("SITUACAO ANTES DA BATALHA:\n");
    printf("Atacante: %s (%s) - %d tropas\n",
           territorios[origem].nome,
           territorios[origem].cor_Exercito,
           territorios[origem].numero_Tropas);
    printf("\n");
    
    printf("Defensor: %s (%s) - %d tropas\n\n",
           territorios[destino].nome,
           territorios[destino].cor_Exercito,
           territorios[destino].numero_Tropas);
    printf("\n");

    printf("Pressione ENTER para rolar os dados...");
    getchar();

    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();

    printf("\nAtacante rolou: %d\n", dadoAtacante);
    printf("Defensor rolou: %d\n", dadoDefensor);
    
    printf("\nPressione ENTER para ver o resultado...");
    getchar();

    printf("\n");
    
    if (dadoAtacante > dadoDefensor) {
        printf("ATACANTE VENCEU!\n\n");
        territorios[destino].numero_Tropas--;
        printf("%s perdeu 1 tropa! (%d restantes)\n",
               territorios[destino].nome,
               territorios[destino].numero_Tropas);
        
        if (territorios[destino].numero_Tropas == 0) {
            printf("\nTERRITORIO CONQUISTADO!\n");
            printf("%s conquistou %s!\n\n",
                   territorios[origem].cor_Exercito,
                   territorios[destino].nome);
            
            printf("Pressione ENTER para transferir tropas...");
            getchar();
            
            strcpy(territorios[destino].cor_Exercito, territorios[origem].cor_Exercito);
            territorios[destino].numero_Tropas = 1;
            territorios[origem].numero_Tropas--;
            printf("\n1 tropa transferida.\n");
            printf("%s agora pertence a %s\n", 
                   territorios[destino].nome,
                   territorios[destino].cor_Exercito);
        }
    }
    else if (dadoDefensor > dadoAtacante) {
        printf("DEFENSOR VENCEU!\n\n");
        territorios[origem].numero_Tropas--;
        printf("%s perdeu 1 tropa! (%d restantes)\n",
               territorios[origem].nome,
               territorios[origem].numero_Tropas);
        
        if (territorios[origem].numero_Tropas == 0) {
            printf("\nATACANTE PERDEU O TERRITORIO!\n");
            printf("%s perdeu %s para %s!\n\n",
                   territorios[origem].cor_Exercito,
                   territorios[origem].nome,
                   territorios[destino].cor_Exercito);
            
            printf("Pressione ENTER para contra-ataque...");
            getchar();
            
            strcpy(territorios[origem].cor_Exercito, territorios[destino].cor_Exercito);
            territorios[origem].numero_Tropas = 1;
            territorios[destino].numero_Tropas--;
            printf("\n1 tropa do defensor ocupou o territorio.\n");
            printf("%s agora pertence a %s\n",
                   territorios[origem].nome,
                   territorios[origem].cor_Exercito);
        }
    }
    else {
        printf("EMPATE! (favorece o atacante)\n\n");
        territorios[destino].numero_Tropas--;
        printf("%s perdeu 1 tropa! (%d restantes)\n",
               territorios[destino].nome,
               territorios[destino].numero_Tropas);
        
        if (territorios[destino].numero_Tropas == 0) {
            printf("\nTERRITORIO CONQUISTADO!\n");
            printf("%s conquistou %s!\n\n",
                   territorios[origem].cor_Exercito,
                   territorios[destino].nome);
            
            printf("Pressione ENTER para transferir tropas...");
            getchar();
            
            strcpy(territorios[destino].cor_Exercito, territorios[origem].cor_Exercito);
            territorios[destino].numero_Tropas = 1;
            territorios[origem].numero_Tropas--;
            printf("\n1 tropa transferida.\n");
            printf("%s agora pertence a %s\n",
                   territorios[destino].nome,
                   territorios[destino].cor_Exercito);
        }
    }

    printf("\nSITUAÇÃO FINAL:\n");
    printf("%s (%s): %d tropas\n",
           territorios[origem].nome,
           territorios[origem].cor_Exercito,
           territorios[origem].numero_Tropas);
    printf("%s (%s): %d tropas\n",
           territorios[destino].nome,
           territorios[destino].cor_Exercito,
           territorios[destino].numero_Tropas);
    
    printf("\nPressione ENTER para continuar...");
    getchar();
    printf("--------------------------------------\n");
}
// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}