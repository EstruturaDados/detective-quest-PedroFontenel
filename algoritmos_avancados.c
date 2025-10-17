#include <stdio.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 26 // Uma entrada para cada letra do alfabeto

// 🌳 Estrutura da árvore binária de salas
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// 🔍 Estrutura da árvore de busca binária (BST) para pistas
typedef struct Pista {
    char nome[50];
    struct Pista *esquerda;
    struct Pista *direita;
} Pista;

// 🕵️ Estrutura da tabela hash para suspeitos
typedef struct Suspeito {
    char pista[50];
    char nome[50];
    struct Suspeito *prox;
} Suspeito;

Suspeito *tabelaHash[TAM_HASH] = {NULL};

// 🔧 Funções auxiliares
int hash(char *str) {
    return (str[0] - 'a') % TAM_HASH;
}

// 🌳 Criação da árvore de salas
Sala* criarSala(char *nome, Sala *esq, Sala *dir) {
    Sala *nova = malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = esq;
    nova->direita = dir;
    return nova;
}

// 🔍 Inserção na BST de pistas
Pista* inserirPista(Pista *raiz, char *nome) {
    if (!raiz) {
        Pista *nova = malloc(sizeof(Pista));
        strcpy(nova->nome, nome);
        nova->esquerda = nova->direita = NULL;
        return nova;
    }
    if (strcmp(nome, raiz->nome) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, nome);
    else if (strcmp(nome, raiz->nome) > 0)
        raiz->direita = inserirPista(raiz->direita, nome);
    return raiz;
}

// 🔍 Exibição em ordem alfabética
void emOrdem(Pista *raiz) {
    if (raiz) {
        emOrdem(raiz->esquerda);
        printf("- %s\n", raiz->nome);
        emOrdem(raiz->direita);
    }
}

// 🕵️ Inserção na tabela hash
void inserirNaHash(char *pista, char *suspeito) {
    int h = hash(pista);
    Suspeito *novo = malloc(sizeof(Suspeito));
    strcpy(novo->pista, pista);
    strcpy(novo->nome, suspeito);
    novo->prox = tabelaHash[h];
    tabelaHash[h] = novo;
}

// 🕵️ Exibir pistas e suspeitos
void exibirHash() {
    printf("\n🔍 Pistas e Suspeitos:\n");
    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito *atual = tabelaHash[i];
        while (atual) {
            printf("Pista: %s → Suspeito: %s\n", atual->pista, atual->nome);
            atual = atual->prox;
        }
    }
}

// 🕵️ Determinar suspeito mais citado
void suspeitoMaisCitado() {
    char nomes[100][50];
    int contadores[100] = {0};
    int total = 0;

    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito *atual = tabelaHash[i];
        while (atual) {
            int encontrado = 0;
            for (int j = 0; j < total; j++) {
                if (strcmp(nomes[j], atual->nome) == 0) {
                    contadores[j]++;
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                strcpy(nomes[total], atual->nome);
                contadores[total++] = 1;
            }
            atual = atual->prox;
        }
    }

    int max = 0, idx = 0;
    for (int i = 0; i < total; i++) {
        if (contadores[i] > max) {
            max = contadores[i];
            idx = i;
        }
    }

    printf("\n🏆 Suspeito mais citado: %s (%d pistas)\n", nomes[idx], max);
}

// 🎮 Exploração da mansão
void explorarSalas(Sala *atual, Pista **raizPistas) {
    char opcao;
    while (atual) {
        printf("\n📍 Você está na sala: %s\n", atual->nome);

        // Nível Aventureiro: encontrar pistas
        if (strcmp(atual->nome, "Biblioteca") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Livro Rasgado");
            inserirNaHash("Livro Rasgado", "Sr. Moreira");
        } else if (strcmp(atual->nome, "Cozinha") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Faca Suja");
            inserirNaHash("Faca Suja", "Dona Clara");
        }

        printf("Escolha: [e] esquerda, [d] direita, [s] sair: ");
        scanf(" %c", &opcao);

        if (opcao == 'e')
            atual = atual->esquerda;
        else if (opcao == 'd')
            atual = atual->direita;
        else
            break;
    }
}

int main() {
    // 🌳 Criar árvore de salas
    Sala *sala1 = criarSala("Biblioteca", NULL, NULL);
    Sala *sala2 = criarSala("Cozinha", NULL, NULL);
    Sala *sala3 = criarSala("Hall", sala1, sala2);

    // 🔍 Árvore de pistas
    Pista *raizPistas = NULL;

    // 🎮 Iniciar exploração
    explorarSalas(sala3, &raizPistas);

    // 🔍 Mostrar pistas encontradas
    printf("\n📜 Pistas encontradas:\n");
    emOrdem(raizPistas);

    // 🕵️ Mostrar suspeitos
    exibirHash();

    // 🕵️ Mostrar suspeito mais citado
    suspeitoMaisCitado();

    return 0;
}

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

