#ifndef PROCEDIMENTO_HPP
#define PROCEDIMENTO_HPP
#include <fstream>

class Sala
{

public:
    double relogio;
    double tesp;
    Sala();
    ~Sala();
};

class Procedimento
{
private:
    /* data */
public:
    double ttri; //tempo de triagem
    double taten; //tempo de atendimento
    double tm; //tempo de medidas
    double tt; //tempo de testes
    double ti; //tempo de exames de imagem
    double tim; //tempo de intrumentos e medicamentos
    double tmin; //tempo minimo que o paciente ficara no hopital
    int ntri; //numero de salas para triagem
    int naten; //numero de salas para atendimento
    int nm; //numero de salas para medidas
    int nt; //numero de salas para testes
    int ni; //numero de saas para exames de magem
    int nim; //numero de salas para instrumentos
    Sala *triagem;// vetor de salas para triagem
    Sala *atendimento;// vetor de salas para atendimento
    Sala *medidas;// vetor de salas para medidas
    Sala *testes;// vetor de salas para testes
    Sala *imagem;// vetor de salas para exames de imagem
    Sala *instrumentos;// vetor de salas para instrumentos
    Procedimento(std::ifstream &arquivo);//construtor do tad procedimento que utiliza um arquivo como parametro para preencher as informações
    ~Procedimento();
};
#endif