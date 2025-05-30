#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definição básica do nó para listas encadeadas
typedef struct No {
    int dado;
    struct No *prox;
} No;

/////////////////////////////////////////
// 1. Inserção Básica
void inserir_inicio(No **lista, int val) {
    No *novo = malloc(sizeof(No));
    novo->dado = val;
    novo->prox = *lista;
    *lista = novo;
}

void inserir_fim(No **lista, int val) {
    No *novo = malloc(sizeof(No));
    novo->dado = val;
    novo->prox = NULL;
    if (*lista == NULL) {
        *lista = novo;
        return;
    }
    No *aux = *lista;
    while (aux->prox) aux = aux->prox;
    aux->prox = novo;
}

void teste_insercao() {
    No *lista = NULL;
    inserir_fim(&lista, 10);
    inserir_inicio(&lista, 5);
    printf("Lista apos insercao (esperado 5 10): ");
    for (No *p = lista; p; p = p->prox) printf("%d ", p->dado);
    printf("\n");
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 2. Contagem de Nós
int contar_nos(No *lista) {
    int count = 0;
    while (lista) {
        count++;
        lista = lista->prox;
    }
    return count;
}

void teste_contar_nos() {
    No *lista = NULL;
    inserir_fim(&lista, 1);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 3);
    printf("Numero de nos: %d\n", contar_nos(lista)); // 3
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 3. Busca de Elemento
int buscar_elemento(No *lista, int val) {
    while (lista) {
        if (lista->dado == val) return 1;
        lista = lista->prox;
    }
    return 0;
}

void teste_buscar_elemento() {
    No *lista = NULL;
    inserir_fim(&lista, 10);
    inserir_fim(&lista, 20);
    printf("Busca 10: %d\n", buscar_elemento(lista, 10)); // 1
    printf("Busca 30: %d\n", buscar_elemento(lista, 30)); // 0
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 4. Inserção em Posição Específica
void inserir_posicao(No **lista, int pos, int val) {
    if (pos == 0) {
        inserir_inicio(lista, val);
        return;
    }
    No *aux = *lista;
    int i = 0;
    while (aux && i < pos - 1) {
        aux = aux->prox;
        i++;
    }
    if (!aux) return; // pos invalida
    No *novo = malloc(sizeof(No));
    novo->dado = val;
    novo->prox = aux->prox;
    aux->prox = novo;
}

void teste_inserir_posicao() {
    No *lista = NULL;
    inserir_fim(&lista, 1);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 4);
    inserir_posicao(&lista, 2, 3); // inserir 3 na pos 2
    printf("Lista apos inserir na posicao 2 (esperado 1 2 3 4): ");
    for (No *p = lista; p; p = p->prox) printf("%d ", p->dado);
    printf("\n");
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 5. Remoção por Valor
void remover_valor(No **lista, int val) {
    No *aux = *lista, *prev = NULL;
    while (aux) {
        if (aux->dado == val) {
            if (prev == NULL) {
                *lista = aux->prox;
            } else {
                prev->prox = aux->prox;
            }
            free(aux);
            return;
        }
        prev = aux;
        aux = aux->prox;
    }
}

void teste_remover_valor() {
    No *lista = NULL;
    inserir_fim(&lista, 1);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 3);
    remover_valor(&lista, 2);
    printf("Lista apos remover 2 (esperado 1 3): ");
    for (No *p = lista; p; p = p->prox) printf("%d ", p->dado);
    printf("\n");
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 6. Inversão Iterativa
void inverter_lista(No **lista) {
    No *prev = NULL, *curr = *lista, *next = NULL;
    while (curr) {
        next = curr->prox;
        curr->prox = prev;
        prev = curr;
        curr = next;
    }
    *lista = prev;
}

void teste_inverter_lista() {
    No *lista = NULL;
    for (int i = 1; i <= 3; i++) inserir_fim(&lista, i);
    inverter_lista(&lista);
    printf("Lista invertida (esperado 3 2 1): ");
    for (No *p = lista; p; p = p->prox) printf("%d ", p->dado);
    printf("\n");
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 7. Nó do Meio (ponteiro rápido e lento)
No* encontrar_meio(No *lista) {
    if (!lista) return NULL;
    No *slow = lista;
    No *fast = lista;
    while (fast && fast->prox) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }
    return slow;
}

void teste_encontrar_meio() {
    No *lista = NULL;
    for (int i = 1; i <= 5; i++) inserir_fim(&lista, i);
    No *meio = encontrar_meio(lista);
    printf("No do meio (esperado 3): %d\n", meio->dado);
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 8. Impressão Reversa com Pilha
typedef struct Pilha {
    No *topo;
} Pilha;

void pilha_init(Pilha *p) {
    p->topo = NULL;
}

void pilha_push(Pilha *p, int val) {
    No *novo = malloc(sizeof(No));
    novo->dado = val;
    novo->prox = p->topo;
    p->topo = novo;
}

int pilha_pop(Pilha *p) {
    if (!p->topo) return -1;
    No *aux = p->topo;
    int val = aux->dado;
    p->topo = aux->prox;
    free(aux);
    return val;
}

void pilha_imprimir_reverso(No *lista) {
    Pilha p;
    pilha_init(&p);
    while (lista) {
        pilha_push(&p, lista->dado);
        lista = lista->prox;
    }
    while (p.topo) {
        printf("%d ", pilha_pop(&p));
    }
    printf("\n");
}

void teste_imprimir_reverso() {
    No *lista = NULL;
    for (int i = 1; i <= 5; i++) inserir_fim(&lista, i);
    printf("Impressao reversa (esperado 5 4 3 2 1): ");
    pilha_imprimir_reverso(lista);
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 9. Pilha com Array
typedef struct {
    int arr[100];
    int topo;
} PilhaArray;

void pilha_array_init(PilhaArray *p) {
    p->topo = -1;
}

int pilha_array_push(PilhaArray *p, int val) {
    if (p->topo == 99) return 0;
    p->arr[++p->topo] = val;
    return 1;
}

int pilha_array_pop(PilhaArray *p) {
    if (p->topo == -1) return -1;
    return p->arr[p->topo--];
}

int pilha_array_topo(PilhaArray *p) {
    if (p->topo == -1) return -1;
    return p->arr[p->topo];
}

int pilha_array_esta_vazia(PilhaArray *p) {
    return p->topo == -1;
}

void teste_pilha_array() {
    PilhaArray p;
    pilha_array_init(&p);
    pilha_array_push(&p, 10);
    pilha_array_push(&p, 20);
    printf("Topo da pilha (esperado 20): %d\n", pilha_array_topo(&p));
    pilha_array_pop(&p);
    printf("Topo apos pop (esperado 10): %d\n", pilha_array_topo(&p));
    printf("Esta vazia? %d\n", pilha_array_esta_vazia(&p));
}

/////////////////////////////////////////
// 10. Pilha com Lista Encadeada
typedef struct NoPilha {
    int dado;
    struct NoPilha *prox;
} NoPilha;

typedef struct {
    NoPilha *topo;
} PilhaLista;

void pilha_lista_init(PilhaLista *p) {
    p->topo = NULL;
}

void pilha_lista_push(PilhaLista *p, int val) {
    NoPilha *novo = malloc(sizeof(NoPilha));
    novo->dado = val;
    novo->prox = p->topo;
    p->topo = novo;
}

int pilha_lista_pop(PilhaLista *p) {
    if (!p->topo) return -1;
    NoPilha *aux = p->topo;
    int val = aux->dado;
    p->topo = aux->prox;
    free(aux);
    return val;
}

int pilha_lista_topo(PilhaLista *p) {
    if (!p->topo) return -1;
    return p->topo->dado;
}

int pilha_lista_esta_vazia(PilhaLista *p) {
    return p->topo == NULL;
}

void teste_pilha_lista() {
    PilhaLista p;
    pilha_lista_init(&p);
    pilha_lista_push(&p, 10);
    pilha_lista_push(&p, 20);
    printf("Topo pilha lista (esperado 20): %d\n", pilha_lista_topo(&p));
    pilha_lista_pop(&p);
    printf("Topo apos pop (esperado 10): %d\n", pilha_lista_topo(&p));
    printf("Esta vazia? %d\n", pilha_lista_esta_vazia(&p));
}

/////////////////////////////////////////
// 11. Verificação de Parênteses Balanceados
int verificar_balanceamento(const char *str) {
    char pilha[100];
    int topo = -1;
    for (int i = 0; str[i]; i++) {
        char c = str[i];
        if (c == '(' || c == '{' || c == '[') {
            pilha[++topo] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (topo == -1) return 0;
            char aberto = pilha[topo--];
            if ((c == ')' && aberto != '(') ||
                (c == '}' && aberto != '{') ||
                (c == ']' && aberto != '[')) return 0;
        }
    }
    return topo == -1;
}

void teste_verificar_balanceamento() {
    char str[] = "({[]})";
    printf("Balanceamento de '%s': %d\n", str, verificar_balanceamento(str)); // 1
    char str2[] = "({[})";
    printf("Balanceamento de '%s': %d\n", str2, verificar_balanceamento(str2)); // 0
}

/////////////////////////////////////////
// 12. Inversão de String com Pilha
void inverter_string(char *str) {
    int len = strlen(str);
    char pilha[100];
    int topo = -1;
    for (int i = 0; i < len; i++) pilha[++topo] = str[i];
    for (int i = 0; i < len; i++) str[i] = pilha[topo--];
}

void teste_inverter_string() {
    char s[] = "hello";
    inverter_string(s);
    printf("String invertida (esperado olleh): %s\n", s);
}

/////////////////////////////////////////
// 13. Verificação de Palíndromo com Pilha
int palindromo_pilha(const char *str) {
    int len = strlen(str);
    char pilha[100];
    int topo = -1;
    for (int i = 0; i < len / 2; i++) pilha[++topo] = str[i];
    int inicio = (len % 2 == 0) ? len / 2 : len / 2 + 1;
    for (int i = inicio; i < len; i++) {
        if (topo == -1 || str[i] != pilha[topo--]) return 0;
    }
    return 1;
}

void teste_palindromo_pilha() {
    printf("Palindromo 'radar': %d\n", palindromo_pilha("radar")); // 1
    printf("Palindromo 'hello': %d\n", palindromo_pilha("hello")); // 0
}

/////////////////////////////////////////
// 14. Ordenação de Pilha (usando outra pilha)
void ordenar_pilha(PilhaArray *p) {
    PilhaArray aux;
    pilha_array_init(&aux);
    while (!pilha_array_esta_vazia(p)) {
        int tmp = pilha_array_pop(p);
        while (!pilha_array_esta_vazia(&aux) && pilha_array_topo(&aux) > tmp) {
            pilha_array_push(p, pilha_array_pop(&aux));
        }
        pilha_array_push(&aux, tmp);
    }
    while (!pilha_array_esta_vazia(&aux)) {
        pilha_array_push(p, pilha_array_pop(&aux));
    }
}

void teste_ordenar_pilha() {
    PilhaArray p;
    pilha_array_init(&p);
    pilha_array_push(&p, 30);
    pilha_array_push(&p, 10);
    pilha_array_push(&p, 20);
    ordenar_pilha(&p);
    printf("Pilha ordenada (esperado 10 20 30): ");
    while (!pilha_array_esta_vazia(&p)) {
        printf("%d ", pilha_array_pop(&p));
    }
    printf("\n");
}

/////////////////////////////////////////
// 15. Fila com Array Circular
typedef struct {
    int arr[100];
    int inicio, fim, tamanho;
} FilaCircular;

void fila_circular_init(FilaCircular *f) {
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
}

int fila_circular_enfileirar(FilaCircular *f, int val) {
    if (f->tamanho == 100) return 0;
    f->fim = (f->fim + 1) % 100;
    f->arr[f->fim] = val;
    f->tamanho++;
    return 1;
}

int fila_circular_desenfileirar(FilaCircular *f) {
    if (f->tamanho == 0) return -1;
    int val = f->arr[f->inicio];
    f->inicio = (f->inicio + 1) % 100;
    f->tamanho--;
    return val;
}

int fila_circular_frente(FilaCircular *f) {
    if (f->tamanho == 0) return -1;
    return f->arr[f->inicio];
}

void teste_fila_circular() {
    FilaCircular f;
    fila_circular_init(&f);
    fila_circular_enfileirar(&f, 1);
    fila_circular_enfileirar(&f, 2);
    printf("Frente da fila (esperado 1): %d\n", fila_circular_frente(&f));
    fila_circular_desenfileirar(&f);
    printf("Frente apos desenfileirar (esperado 2): %d\n", fila_circular_frente(&f));
}

/////////////////////////////////////////
// 16. Fila com Lista Encadeada
typedef struct NoFila {
    int dado;
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} FilaLista;

void fila_lista_init(FilaLista *f) {
    f->inicio = f->fim = NULL;
}

void fila_lista_enfileirar(FilaLista *f, int val) {
    NoFila *novo = malloc(sizeof(NoFila));
    novo->dado = val;
    novo->prox = NULL;
    if (!f->fim) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

int fila_lista_desenfileirar(FilaLista *f) {
    if (!f->inicio) return -1;
    int val = f->inicio->dado;
    NoFila *tmp = f->inicio;
    f->inicio = f->inicio->prox;
    if (!f->inicio) f->fim = NULL;
    free(tmp);
    return val;
}

int fila_lista_frente(FilaLista *f) {
    if (!f->inicio) return -1;
    return f->inicio->dado;
}

void teste_fila_lista() {
    FilaLista f;
    fila_lista_init(&f);
    fila_lista_enfileirar(&f, 1);
    fila_lista_enfileirar(&f, 2);
    printf("Frente fila lista (esperado 1): %d\n", fila_lista_frente(&f));
    fila_lista_desenfileirar(&f);
    printf("Frente apos desenfileirar (esperado 2): %d\n", fila_lista_frente(&f));
    // liberar
    while (f.inicio) {
        fila_lista_desenfileirar(&f);
    }
}

/////////////////////////////////////////
// 17. Geração de Números Binários com Fila
void gerar_binarios(int N) {
    FilaLista f;
    fila_lista_init(&f);
    fila_lista_enfileirar(&f, 1);
    for (int i = 0; i < N; i++) {
        int val = fila_lista_desenfileirar(&f);
        printf("%d ", val);
        fila_lista_enfileirar(&f, val * 10);
        fila_lista_enfileirar(&f, val * 10 + 1);
    }
    printf("\n");
    // liberar resto
    while (f.inicio) fila_lista_desenfileirar(&f);
}

void teste_gerar_binarios() {
    printf("Primeiros 3 numeros binarios (esperado 1 10 11): ");
    gerar_binarios(3);
}

/////////////////////////////////////////
// 18. Inversão dos Primeiros K Elementos da Fila usando Pilha
void inverter_primeiros_k(FilaCircular *f, int k) {
    if (k > f->tamanho) return;
    PilhaArray p;
    pilha_array_init(&p);
    for (int i = 0; i < k; i++) {
        pilha_array_push(&p, fila_circular_desenfileirar(f));
    }
    while (!pilha_array_esta_vazia(&p)) {
        fila_circular_enfileirar(f, pilha_array_pop(&p));
    }
    int t = f->tamanho - k;
    for (int i = 0; i < t; i++) {
        fila_circular_enfileirar(f, fila_circular_desenfileirar(f));
    }
}

void teste_inverter_primeiros_k() {
    FilaCircular f;
    fila_circular_init(&f);
    for (int i = 1; i <= 5; i++) fila_circular_enfileirar(&f, i);
    inverter_primeiros_k(&f, 3);
    printf("Fila apos inverter primeiros 3 (esperado 3 2 1 4 5): ");
    while (f.tamanho) {
        printf("%d ", fila_circular_desenfileirar(&f));
    }
    printf("\n");
}

/////////////////////////////////////////
// 19. Detecção de Ciclo (Algoritmo de Floyd)
int detectar_ciclo(No *lista) {
    No *slow = lista, *fast = lista;
    while (fast && fast->prox) {
        slow = slow->prox;
        fast = fast->prox->prox;
        if (slow == fast) return 1;
    }
    return 0;
}

void teste_detectar_ciclo() {
    No *lista = NULL;
    inserir_fim(&lista, 1);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 3);
    // Criar ciclo: último nó aponta para segundo nó
    No *aux = lista;
    while (aux->prox) aux = aux->prox;
    aux->prox = lista->prox; 
    printf("Detectar ciclo (esperado 1): %d\n", detectar_ciclo(lista));
    // Não liberar pois ciclo
}

/////////////////////////////////////////
// 20. União de Listas Ordenadas
No* unir_listas_ordenadas(No *l1, No *l2) {
    No dummy;
    No *tail = &dummy;
    dummy.prox = NULL;
    while (l1 && l2) {
        if (l1->dado < l2->dado) {
            tail->prox = l1;
            l1 = l1->prox;
        } else {
            tail->prox = l2;
            l2 = l2->prox;
        }
        tail = tail->prox;
    }
    tail->prox = (l1) ? l1 : l2;
    return dummy.prox;
}

void teste_unir_listas_ordenadas() {
    No *l1 = NULL;
    No *l2 = NULL;
    inserir_fim(&l1, 1);
    inserir_fim(&l1, 3);
    inserir_fim(&l2, 2);
    inserir_fim(&l2, 4);
    No *unida = unir_listas_ordenadas(l1, l2);
    printf("Lista unida ordenada (esperado 1 2 3 4): ");
    for (No *p = unida; p; p = p->prox) printf("%d ", p->dado);
    printf("\n");
    // liberar
    while (unida) {
        No *tmp = unida;
        unida = unida->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 21. Remoção de Todas as Ocorrências
void remover_todas_ocorrencias(No **lista, int val) {
    while (*lista && (*lista)->dado == val) {
        No *tmp = *lista;
        *lista = (*lista)->prox;
        free(tmp);
    }
    No *aux = *lista;
    while (aux && aux->prox) {
        if (aux->prox->dado == val) {
            No *tmp = aux->prox;
            aux->prox = tmp->prox;
            free(tmp);
        } else {
            aux = aux->prox;
        }
    }
}

void teste_remover_todas_ocorrencias() {
    No *lista = NULL;
    inserir_fim(&lista, 1);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 3);
    remover_todas_ocorrencias(&lista, 2);
    printf("Lista apos remover todas ocorrencias de 2 (esperado 1 3): ");
    for (No *p = lista; p; p = p->prox) printf("%d ", p->dado);
    printf("\n");
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 22. Intersecção de Listas
int get_tamanho(No *lista) {
    int count = 0;
    while (lista) {
        count++;
        lista = lista->prox;
    }
    return count;
}

No* encontrar_intersecao(No *l1, No *l2) {
    int len1 = get_tamanho(l1);
    int len2 = get_tamanho(l2);
    while (len1 > len2) {
        l1 = l1->prox;
        len1--;
    }
    while (len2 > len1) {
        l2 = l2->prox;
        len2--;
    }
    while (l1 && l2) {
        if (l1 == l2) return l1;
        l1 = l1->prox;
        l2 = l2->prox;
    }
    return NULL;
}

void teste_encontrar_intersecao() {
    No *l1 = NULL;
    No *l2 = NULL;
    inserir_fim(&l1, 1);
    inserir_fim(&l1, 2);
    inserir_fim(&l1, 3);
    inserir_fim(&l2, 9);
    // Criar intersecao no no com dado 2
    No *aux1 = l1->prox; // no 2
    No *aux2 = l2;
    while (aux2->prox) aux2 = aux2->prox;
    aux2->prox = aux1;
    No *inter = encontrar_intersecao(l1, l2);
    printf("Intersecao encontrada (esperado 2): %d\n", inter ? inter->dado : -1);
    // liberar (cuidado para não liberar nodes compartilhados duas vezes)
    l2->prox = NULL; // separar as listas para liberar
    while (l1) {
        No *tmp = l1;
        l1 = l1->prox;
        free(tmp);
    }
    while (l2) {
        No *tmp = l2;
        l2 = l2->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 23. Remoção do K-ésimo Nó do Fim
void remover_k_esimo_fim(No **lista, int k) {
    No *fast = *lista;
    No *slow = *lista;
    for (int i = 0; i < k; i++) {
        if (!fast) return;
        fast = fast->prox;
    }
    if (!fast) {
        // remover o primeiro
        No *tmp = *lista;
        *lista = (*lista)->prox;
        free(tmp);
        return;
    }
    while (fast->prox) {
        fast = fast->prox;
        slow = slow->prox;
    }
    No *tmp = slow->prox;
    slow->prox = tmp->prox;
    free(tmp);
}

void teste_remover_k_esimo_fim() {
    No *lista = NULL;
    inserir_fim(&lista, 1);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 3);
    inserir_fim(&lista, 4);
    remover_k_esimo_fim(&lista, 2);
    printf("Lista apos remover 2o do fim (esperado 1 2 4): ");
    for (No *p = lista; p; p = p->prox) printf("%d ", p->dado);
    printf("\n");
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 24. Remoção de Duplicatas de Lista Ordenada
void remover_duplicatas(No *lista) {
    No *atual = lista;
    while (atual && atual->prox) {
        if (atual->dado == atual->prox->dado) {
            No *tmp = atual->prox;
            atual->prox = tmp->prox;
            free(tmp);
        } else {
            atual = atual->prox;
        }
    }
}

void teste_remover_duplicatas() {
    No *lista = NULL;
    inserir_fim(&lista, 1);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 3);
    remover_duplicatas(lista);
    printf("Lista apos remover duplicatas (esperado 1 2 3): ");
    for (No *p = lista; p; p = p->prox) printf("%d ", p->dado);
    printf("\n");
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 25. Encontrar Elemento do Meio da Lista
int elemento_meio(No *lista) {
    No *slow = lista, *fast = lista;
    while (fast && fast->prox) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }
    if (slow) return slow->dado;
    return -1;
}

void teste_elemento_meio() {
    No *lista = NULL;
    inserir_fim(&lista, 1);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 3);
    printf("Elemento do meio (esperado 2): %d\n", elemento_meio(lista));
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// Main para rodar todos os testes
int main() {
    teste_palindromo_pilha();
    teste_ordenar_pilha();
    teste_fila_circular();
    teste_fila_lista();
    teste_gerar_binarios();
    teste_inverter_primeiros_k();
    teste_detectar_ciclo();
    teste_unir_listas_ordenadas();
    teste_remover_todas_ocorrencias();
    teste_encontrar_intersecao();
    teste_remover_k_esimo_fim();
    teste_remover_duplicatas();
    teste_elemento_meio();
    return 0;
}

/////////////////////////////////////////
// 26. Avaliação de Expressão Pós-fixa
// Exemplo: "3 4 + 2 *" = (3+4)*2 = 14
int avaliar_posfixa(const char *expr) {
    PilhaArray pilha;
    pilha_array_init(&pilha);

    int i = 0;
    while (expr[i]) {
        if (expr[i] == ' ') {
            i++;
            continue;
        }
        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            pilha_array_push(&pilha, num);
        } else {
            // operador
            if (pilha.topo < 2) return -1; // erro expressão inválida
            int b = pilha_array_pop(&pilha);
            int a = pilha_array_pop(&pilha);
            switch (expr[i]) {
                case '+': pilha_array_push(&pilha, a + b); break;
                case '-': pilha_array_push(&pilha, a - b); break;
                case '*': pilha_array_push(&pilha, a * b); break;
                case '/': pilha_array_push(&pilha, a / b); break;
                default: return -1; // operador inválido
            }
            i++;
        }
    }
    return pilha_array_pop(&pilha);
}

void teste_avaliar_posfixa() {
    printf("Avaliar posfixa '3 4 + 2 *' (esperado 14): %d\n", avaliar_posfixa("3 4 + 2 *"));
}

/////////////////////////////////////////
// 27. Fila usando Duas Pilhas
typedef struct {
    PilhaArray s1, s2;
} FilaDuplaPilha;

void fila_dupla_pilha_init(FilaDuplaPilha *f) {
    pilha_array_init(&f->s1);
    pilha_array_init(&f->s2);
}

void fila_dupla_pilha_enfileirar(FilaDuplaPilha *f, int val) {
    pilha_array_push(&f->s1, val);
}

int fila_dupla_pilha_desenfileirar(FilaDuplaPilha *f) {
    if (pilha_array_esta_vazia(&f->s2)) {
        while (!pilha_array_esta_vazia(&f->s1)) {
            pilha_array_push(&f->s2, pilha_array_pop(&f->s1));
        }
    }
    if (pilha_array_esta_vazia(&f->s2)) return -1;
    return pilha_array_pop(&f->s2);
}

int fila_dupla_pilha_frente(FilaDuplaPilha *f) {
    if (pilha_array_esta_vazia(&f->s2)) {
        while (!pilha_array_esta_vazia(&f->s1)) {
            pilha_array_push(&f->s2, pilha_array_pop(&f->s1));
        }
    }
    if (pilha_array_esta_vazia(&f->s2)) return -1;
    return pilha_array_topo(&f->s2);
}

void teste_fila_dupla_pilha() {
    FilaDuplaPilha f;
    fila_dupla_pilha_init(&f);
    fila_dupla_pilha_enfileirar(&f, 10);
    fila_dupla_pilha_enfileirar(&f, 20);
    printf("Fila dupla pilha frente (esperado 10): %d\n", fila_dupla_pilha_frente(&f));
    printf("Fila dupla pilha desenfileirar (esperado 10): %d\n", fila_dupla_pilha_desenfileirar(&f));
    printf("Fila dupla pilha desenfileirar (esperado 20): %d\n", fila_dupla_pilha_desenfileirar(&f));
}

/////////////////////////////////////////
// 28. Inversão em Grupos de K Nós
No* inverter_grupos(No *head, int k) {
    if (!head || k == 1) return head;

    No dummy;
    dummy.prox = head;
    No *prev = &dummy;
    No *curr, *nex, *tail;
    int count = 0;

    // Contar o número total de nós
    No *temp = head;
    while (temp) {
        count++;
        temp = temp->prox;
    }

    while (count >= k) {
        curr = prev->prox;
        nex = curr->prox;
        for (int i = 1; i < k; i++) {
            curr->prox = nex->prox;
            nex->prox = prev->prox;
            prev->prox = nex;
            nex = curr->prox;
        }
        prev = curr;
        count -= k;
    }

    return dummy.prox;
}

void teste_inverter_grupos() {
    No *lista = NULL;
    for (int i = 1; i <= 5; i++) inserir_fim(&lista, i);
    lista = inverter_grupos(lista, 2);
    printf("Lista apos inverter grupos de 2 (esperado 2 1 4 3 5): ");
    for (No *p = lista; p; p = p->prox) printf("%d ", p->dado);
    printf("\n");
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 29. Palíndromo com Espaço O(1) (lista ligada)
int eh_palindromo(No *head) {
    if (!head || !head->prox) return 1;

    // Encontrar meio da lista
    No *slow = head, *fast = head;
    while (fast && fast->prox) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }

    // Inverter segunda metade
    No *prev = NULL, *curr = slow, *next;
    while (curr) {
        next = curr->prox;
        curr->prox = prev;
        prev = curr;
        curr = next;
    }

    // Comparar primeira e segunda metade
    No *start = head, *end = prev;
    while (end) {
        if (start->dado != end->dado) return 0;
        start = start->prox;
        end = end->prox;
    }

    // Reverter de volta a segunda metade (opcional para não alterar lista)
    curr = prev;
    prev = NULL;
    while (curr) {
        next = curr->prox;
        curr->prox = prev;
        prev = curr;
        curr = next;
    }

    return 1;
}

void teste_eh_palindromo() {
    No *lista = NULL;
    inserir_fim(&lista, 1);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 3);
    inserir_fim(&lista, 2);
    inserir_fim(&lista, 1);
    printf("Eh palindromo (esperado 1): %d\n", eh_palindromo(lista));
    // liberar
    while (lista) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

/////////////////////////////////////////
// 30. Trapping Rain Water (usando pilha)
int trapping_rain_water(int *heights, int n) {
    PilhaArray pilha;
    pilha_array_init(&pilha);
    int water = 0, i = 0;
    while (i < n) {
        while (!pilha_array_esta_vazia(&pilha) && heights[i] > heights[pilha.arr[pilha.topo - 1]]) {
            int top = pilha_array_pop(&pilha);
            if (pilha_array_esta_vazia(&pilha)) break;
            int distance = i - pilha.arr[pilha.topo - 1] - 1;
            int bounded_height = (heights[i] < heights[pilha.arr[pilha.topo - 1]] ? heights[i] : heights[pilha.arr[pilha.topo - 1]]) - heights[top];
            water += distance * bounded_height;
        }
        pilha_array_push(&pilha, i++);
    }
    return water;
}

void teste_trapping_rain_water() {
    int heights[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int n = sizeof(heights)/sizeof(heights[0]);
    printf("Trapping Rain Water (esperado 6): %d\n", trapping_rain_water(heights, n));
}