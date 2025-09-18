#ifndef FILA_HPP
#define FILA_HPP
#include "Paciente.hpp"

class MinHeap
{
public:
    Paciente *heap; // Ponteiro para o array de pacientes no heap de memória
    int capacidade; // Capacidade máxima do heap
    int tamanho;    // Número atual de elementos no heap

    // Funções auxiliares
    int pai(int i);
    int filhoEsquerdo(int i);
    int filhoDireito(int i);
    void troca(int i, int j);
    void subir(int i);//função para subir o paciente na fila
    void subir2(int i);                                   // função para subir o paciente na fila utilizando compsaração 2
    void subir3(int i);                                   // função para subir o paciente na fila utilizando compsaração 2
    void descer(int i);                                   // função para descer o paciente na fila
    void descer2(int i);                                  // função para descer o paciente na fila utilizando comparação 2
    void descer3(int i);                                  // função para descer o paciente na fila utilizando comparação 2
    bool comparar(const Paciente &p1, const Paciente &p2);//função para comparar dois pacientes de acordo com data e hora
    bool comparar2(const Paciente &p1, const Paciente &p2); // função para comparar dois pacientes de acordo com o id
    bool comparar3(const Paciente &p1, const Paciente &p2); // função para comparar dois pacientes de acordo com o id
    void redimensionar();

    // Construtor e destrutor
    MinHeap(int capacidade);
    MinHeap();
    ~MinHeap();

    // Operações principais
    void inserir( Paciente p);//função para inserir um paciente na fila utilizando comparação 1
    void inserir2(Paciente p); // função para inserir um paciente na fila utilizando comparação 2
    void inserir3(Paciente p); // função para inserir um paciente na fila utilizando comparação 2
    Paciente remover();        // função para remover um paciente da fila utilizando comparação 1
    Paciente remover2();       // função para remover um paciente da fila utilizando comparação 2
    Paciente remover3();       // função para remover um paciente da fila utilizando comparação 2
    bool vazio() const;        // função para verificar se a fila está vazia
};

#endif