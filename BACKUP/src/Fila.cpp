#include "Fila.hpp"

// Construtor do MinHeap
MinHeap::MinHeap(){}
MinHeap::MinHeap(int capacidade)
    : capacidade(capacidade), tamanho(0)
{
    heap = new Paciente[capacidade]; // Alocação dinâmica do array
}

// Destrutor do MinHeap
MinHeap::~MinHeap()
{
    delete[] heap; // Libera a memória alocada dinamicamente
}

// Função para obter o índice do pai
int MinHeap::pai(int i)
{
    return (i - 1) / 2;
}

// Função para obter o índice do filho à esquerda
int MinHeap::filhoEsquerdo(int i)
{
    return 2 * i + 1;
}

// Função para obter o índice do filho à direita
int MinHeap::filhoDireito(int i)
{
    return 2 * i + 2;
}

// Função para trocar dois elementos no heap
void MinHeap::troca(int i, int j)
{
    Paciente temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

// Função para organizar o heap para cima (up-heap)
void MinHeap::subir(int i)
{
    while (i > 0 && comparar(heap[i], heap[pai(i)]))
    {
        troca(i, pai(i));
        i = pai(i);
    }
}
void MinHeap::subir2(int i)
{
    while (i > 0 && comparar2(heap[i], heap[pai(i)]))
    {
        troca(i, pai(i));
        i = pai(i);
    }
}
void MinHeap::subir3(int i)
{
    while (i > 0 && comparar3(heap[i], heap[pai(i)]))
    {
        troca(i, pai(i));
        i = pai(i);
    }
}

// Função para organizar o heap para baixo (down-heap)
void MinHeap::descer(int i)
{
    int menor = i;
    int esquerdo = filhoEsquerdo(i);
    int direito = filhoDireito(i);

    // Verifica o filho à esquerda
    if (esquerdo < tamanho && comparar(heap[esquerdo], heap[menor]))
    {
        menor = esquerdo;
    }

    // Verifica o filho à direita
    if (direito < tamanho && comparar(heap[direito], heap[menor]))
    {
        menor = direito;
    }

    // Se o menor elemento não for o pai, troca e continua descendo
    if (menor != i)
    {
        troca(i, menor);
        descer(menor);
    }
}
void MinHeap::descer2(int i)
{
    int menor = i;
    int esquerdo = filhoEsquerdo(i);
    int direito = filhoDireito(i);

    // Verifica o filho à esquerda
    if (esquerdo < tamanho && comparar2(heap[esquerdo], heap[menor]))
    {
        menor = esquerdo;
    }

    // Verifica o filho à direita
    if (direito < tamanho && comparar2(heap[direito], heap[menor]))
    {
        menor = direito;
    }

    // Se o menor elemento não for o pai, troca e continua descendo
    if (menor != i)
    {
        troca(i, menor);
        descer2(menor);
    }
}

void MinHeap::descer3(int i)
{
    int menor = i;
    int esquerdo = filhoEsquerdo(i);
    int direito = filhoDireito(i);

    // Verifica o filho à esquerda
    if (esquerdo < tamanho && comparar3(heap[esquerdo], heap[menor]))
    {
        menor = esquerdo;
    }

    // Verifica o filho à direita
    if (direito < tamanho && comparar3(heap[direito], heap[menor]))
    {
        menor = direito;
    }

    // Se o menor elemento não for o pai, troca e continua descendo
    if (menor != i)
    {
        troca(i, menor);
        descer3(menor);
    }
}

// Função para comparar dois pacientes (baseado em hora de chegada)
bool MinHeap::comparar(const Paciente &a, const Paciente &b)
{
    if (a.anoin != b.anoin)
        return a.anoin < b.anoin;
    if (a.mesin != b.mesin)
        return a.mesin < b.mesin;
    if (a.diain != b.diain)
        return a.diain < b.diain;
    if (a.horafila != b.horafila)
        return a.horafila < b.horafila;
    return a.id < b.id;
}

bool MinHeap::comparar2(const Paciente &p1, const Paciente &p2)
{
    return p1.id < p2.id; // Menor id tem preferência
}

bool MinHeap::comparar3(const Paciente &a, const Paciente &b)
{
    if (a.anoin != b.anoin)
        return a.anoin < b.anoin;
    if (a.mesin != b.mesin)
        return a.mesin < b.mesin;
    if (a.diain != b.diain)
        return a.diain < b.diain;
    if (a.horafila != b.horafila)
        return a.horafila < b.horafila;
    return a.id < b.id;
}

// Função para redimensionar o heap
void MinHeap::redimensionar()
{
    int novaCapacidade = (capacidade * (3 / 2)); // aumenta a capacidade
    Paciente *novoHeap = new Paciente[novaCapacidade];

    for (int i = 0; i < tamanho; i++)
    {
        novoHeap[i] = heap[i];
    }

    heap = novoHeap;
    delete[] heap; // Libera a memória antiga
    capacidade = novaCapacidade;
}

// Função para inserir um paciente no heap
void MinHeap::inserir( Paciente p)
{
    if (tamanho >= capacidade)
    {
        redimensionar(); // Redimensiona o heap se necessário
    }
    heap[tamanho] = p;
    subir(tamanho);
    tamanho++;
}

void MinHeap::inserir2(Paciente p)
{
    if (tamanho >= capacidade)
    {
        redimensionar(); // Redimensiona o heap se necessário
    }
    heap[tamanho] = p;
    subir2(tamanho);
    tamanho++;
}

void MinHeap::inserir3(Paciente p)
{
    if (tamanho >= capacidade)
    {
        redimensionar(); // Redimensiona o heap se necessário
    }
    heap[tamanho] = p;
    subir3(tamanho);
    tamanho++;
}

// Função para remover o paciente com maior prioridade
Paciente MinHeap::remover()
{

    Paciente raiz = heap[0];
    heap[0] = heap[tamanho - 1];
    tamanho--;
    descer(0);
    return raiz;
}
Paciente MinHeap::remover2()
{

    Paciente raiz = heap[0];
    heap[0] = heap[tamanho - 1];
    tamanho--;
    descer2(0);
    return raiz;
}

Paciente MinHeap::remover3()
{

    Paciente raiz = heap[0];
    heap[0] = heap[tamanho - 1];
    tamanho--;
    descer3(0);
    return raiz;
}

// Função para verificar se o heap está vazio
bool MinHeap::vazio() const
{
    return tamanho == 0;
}
