#include "Procedimento.hpp"

Sala::Sala()
{
    relogio = 0.0;
}

Sala::~Sala()
{
}

Procedimento::Procedimento(std::ifstream &arquivo) //construtor do tad procedimento que utiliza um arquivo como parametro para preencher as informações 
{
    arquivo >> this->ttri;
    arquivo >> this->ntri;

    arquivo >> this->taten;
    arquivo >> this->naten;

    arquivo >> this->tm;
    arquivo >> this->nm;

    arquivo >> this->tt;
    arquivo >> this->nt;

    arquivo >> this->ti;
    arquivo >> this->ni;

    arquivo >> this->tim;
    arquivo >> this->nim;
    triagem = new Sala[ntri];   
    atendimento = new Sala[naten];
    medidas = new Sala[nm];
    testes = new Sala[nt];
    imagem = new Sala[ni];
    instrumentos = new Sala[nim];
}

Procedimento::~Procedimento() //destrutor do tad procedimento
{
    delete[] triagem;
    delete[] atendimento;
    delete[] medidas;
    delete[] testes;
    delete[] imagem;
    delete[] instrumentos;
}
