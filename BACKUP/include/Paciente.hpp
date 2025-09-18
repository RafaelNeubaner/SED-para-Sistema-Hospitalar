#ifndef PACIENTE_HPP
#define PACIENTE_HPP
#include "Procedimento.hpp"
#include <chrono>
#include <iostream>
#include <iomanip>

class Paciente
{
private:
public:
    int triado = 0; // 0 se não foi triado, 1 se foi triado
    int atendido = 0;// 0 se não foi atendido, 1 se foi atendido
    int id; //identificador do paciente 
    int alta; // 0 se não recebeu alta, 1 se recebeu alta
    int anoin; // ano de entrada
    int mesin; // mês de entrada
    int diain; // dia de entrada
    float horain;// hora de entrada
    int grau;// grau de prioridade
    int nmh;//numero de exames de medidas
    int ntl;//numero de exames de testes
    int nei;//numero de exames de imagem
    int nim;//numero de exames de instrumentos
    float tmin;//tempo minimo que o paciente ficara no hospital
    float tat;//tempo de atendimento
    float tesp;//tempo de espera
    int mesout;//mes de saida
    int diaout;//dia de saida
    float horaout;//hora de saida
    int anoout;//ano de saida
    float horafila;//  hora de entrada na fila

    Paciente(std::ifstream &arquivo, Procedimento *pro);//construtor do tad paciente que utiliza um arquivo como parametro para preencher as informações
    Paciente();
    void contabiliza(Procedimento *procedimento, int x);//função que contabiliza o tempo de espera do paciente
    void print_paciente();//função que imprime as informações do paciente
    void conta_hora(Procedimento *Pro);//função que conta o tempo de espera do paciente
    std::string convertedia();//função que converte o dia da semana
    void calculateDateTime(int totalHours); // função que calcula a data e hora de saida do paciente
};

std::string converterHoras(float horasDecimais);//função que converte as horas decimais em horas normais

std::string convertemes(int mes);//função que converte o mês em string

std::string diaDaSemana(int ano, int mes, int dia);//função que obtem o dia da semana

float horatotal(int ano, int mes, int dia, int hora); // função que calcula o tempo total em horas

void calculateDateTime(int totalHours);//função que calcula a data e hora de saida do paciente

#endif