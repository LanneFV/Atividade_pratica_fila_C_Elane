#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int prox_id = 1;

// Macros de Validação
#define VALIDAR_FILA(fila) \
    if ((fila) == NULL) { \
        fprintf(stderr, "ERRO: Fila NULL. Operacao abortada.\n"); \
        return; \
    }

#define VALIDAR_FILA_INT(fila) \
    if ((fila) == NULL) { \
        fprintf(stderr, "ERRO: Fila NULL. Operacao abortada.\n"); \
        return -1; \
    }

#define VALIDAR_PONTEIRO(ptr) \
    if ((ptr) == NULL) { \
        fprintf(stderr, "ERRO: Ponteiro NULL detectado.\n"); \
        return -1; \
    }

/* ============================================================
   REMOVIDO → Função inválida que quebrava o arquivo
============================================================ */
// void validar_id(paciente paciente) {}

/* ============================================================
   Resetar ID
============================================================ */
void resetar_id() {
    prox_id = 1;
}

/* ============================================================
   Criar fila
============================================================ */
Fila *criar_fila() {
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    if (!fila) {
        fprintf(stderr, "Erro ao alocar fila.\n");
        exit(1);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

/* ============================================================
   Criar paciente
============================================================ */
paciente adicionar_paciente(const char *nome) {
    paciente p;
    p.id = prox_id++;
    snprintf(p.nome, sizeof(p.nome), "%s", nome);
    return p;
}

/* ============================================================
   Lista vazia
============================================================ */
int lista_vazia(Fila *fila) {
    return (!fila || fila->inicio == NULL);
}

/* ============================================================
   Lista cheia (agora implementada)
============================================================ */
int lista_cheia(Fila *fila) {
    VALIDAR_FILA_INT(fila);
    return fila->tamanho >= MAX_PACIENTES_POR_FILA;
}

/* ============================================================
   Liberar fila (AGORA RETORNA INT)
============================================================ */
int liberar_fila(Fila *fila) {
    VALIDAR_FILA_INT(fila);

    if (fila->inicio == NULL) {
        free(fila);
        return 0;
    }

    int count = 0;
    Elemento *atual = fila->inicio;
    Elemento *prox;

    do {
        prox = atual->prox;
        free(atual);
        atual = prox;
        count++;
    } while (atual != fila->inicio);

    free(fila);
    return count;
}

/* ============================================================
   Enfileirar
============================================================ */
int enfileirar(Fila *fila, paciente dados) {
    VALIDAR_FILA_INT(fila);

    if (lista_cheia(fila)) {
        fprintf(stderr, "ERRO: Fila cheia.\n");
        return FILA_CHEIA;
    }

    Elemento *novo = malloc(sizeof(Elemento));
    if (!novo) {
        fprintf(stderr, "Erro malloc.\n");
        return -1;
    }

    novo->dados = dados;

    if (fila->inicio == NULL) {
        novo->prox = novo;
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        novo->prox = fila->inicio;
        fila->fim->prox = novo;
        fila->fim = novo;
    }

    fila->tamanho++;
    return 0;
}

/* ============================================================
   Desenfileirar (CORRIGIDO)
============================================================ */
int desenfileirar(Fila *fila, paciente *dados) {
    VALIDAR_FILA_INT(fila);
    VALIDAR_PONTEIRO(dados);

    if (lista_vazia(fila))
        return FILA_VAZIA;

    Elemento *temp = fila->inicio;

    *dados = temp->dados;  // CORRETO

    if (fila->inicio == fila->fim) {
        fila->inicio = NULL;
        fila->fim = NULL;
    } else {
        fila->inicio = temp->prox;
        fila->fim->prox = fila->inicio;
    }

    free(temp);
    fila->tamanho--;
    return 0;
}

/* ============================================================
   Tamanho
============================================================ */
int tamanho_fila(Fila *fila) {
    return fila ? fila->tamanho : 0;
}

/* ============================================================
   Impressões
============================================================ */
void print_paciente(paciente paciente) {
    printf("ID: %d, Nome: %s\n", paciente.id, paciente.nome);
}

void imprimir_fila(Fila *fila) {
    if (lista_vazia(fila)) {
        printf("Fila vazia.\n");
        return;
    }

    Elemento *atual = fila->inicio;
    printf("--- Conteudo da Fila (Tamanho %d) ---\n", fila->tamanho);

    do {
        print_paciente(atual->dados);
        atual = atual->prox;
    } while (atual != fila->inicio);

    printf("-------------------------------------\n");
}

/* ============================================================
   Limpar buffer
============================================================ */
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ============================================================
   Pegar ID
============================================================ */
int pegar_id(paciente paciente) {
    printf("ID: %d\n", paciente.id);
    return paciente.id;
}

/* ============================================================
   Atendimento
============================================================ */
void atender_proximo_paciente(Fila *f1, Fila *f2, Fila *f3) {
    if (!f1 || !f2 || !f3) {
        fprintf(stderr, "ERRO: Filas NULL.\n");
        return;
    }

    paciente pac;
    int r = -1;

    if (!lista_vazia(f3)) r = desenfileirar(f3, &pac);
    else if (!lista_vazia(f2)) r = desenfileirar(f2, &pac);
    else if (!lista_vazia(f1)) r = desenfileirar(f1, &pac);
    else {
        printf("Todas as filas vazias.\n");
        return;
    }

    if (r == 0) {
        printf("Paciente atendido:\n");
        print_paciente(pac);
    }
}

/* ============================================================
   Liberar todas
============================================================ */
int liberar_todas_filas(Fila *f1, Fila *f2, Fila *f3) {
    int total = 0;

    if (f1) total += liberar_fila(f1);
    if (f2) total += liberar_fila(f2);
    if (f3) total += liberar_fila(f3);

    printf("Total liberado: %d elementos.\n", total);
    return total;
}

/* ============================================================
   Relatorio
============================================================ */
int Gerar_relatorio(Fila *f1, Fila *f2, Fila *f3, paciente paciente) {
    if (!f1 || !f2 || !f3) return -1;

    printf("Gerando relatório do paciente:\n");
    print_paciente(paciente);

    return 0;
}
