#include "Escalonador.hpp"
#include "Fila.hpp"
#include "Paciente.hpp"
#include "Procedimento.hpp"
#include <iostream>

int main(int agrc, char **argv)
{
    std::ifstream arquivo("arquivo.csv"); // abre o arquivo
    if (!arquivo.is_open())         // verifica se o arquivo foi aberto
    {
        std::cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO" << std::endl;
    }
    int npacientes;
    Procedimento *p = new Procedimento(arquivo); // cria um procedimento
    arquivo >> npacientes;
    MinHeap pacientes(npacientes);    // cria um vetor de pacientes
    MinHeap fila0triagem(npacientes); // cria as filas dos procedimentos
    MinHeap fila0atendimento(npacientes);
    MinHeap fila1atendimento(npacientes);
    MinHeap fila2atendimento(npacientes);
    MinHeap fila0medidas(npacientes);
    MinHeap fila1medidas(npacientes);
    MinHeap fila2medidas(npacientes);
    MinHeap fila0testes(npacientes);
    MinHeap fila1testes(npacientes);
    MinHeap fila2testes(npacientes);
    MinHeap fila0imagem(npacientes);
    MinHeap fila1imagem(npacientes);
    MinHeap fila2imagem(npacientes);
    MinHeap fila0instrumentos(npacientes);
    MinHeap fila1instrumentos(npacientes);
    MinHeap fila2instrumentos(npacientes);
    MinHeap final(npacientes);

    for (int i = 0; i < npacientes; i++) // inicializa os pacientes
    {
        Paciente *pa = new Paciente(arquivo, p);
        pacientes.inserir3(*pa);
        delete pa;
    }
    for (int i = 0; i < npacientes; i++) // escalona os pacientes na fila de triagem
    {
        Paciente pa = pacientes.remover3();
        escalona1(pa, fila0triagem, fila0atendimento, fila0medidas, fila0testes, fila0imagem, fila0instrumentos, fila0triagem, fila1atendimento, fila1medidas, fila1testes, fila1imagem, fila1instrumentos, fila0triagem, fila2atendimento, fila2medidas, fila2testes, fila2imagem, fila2instrumentos, final, *p);
    }
    // for (int i = 0; i < npacientes; i++)
    // {
    //     fila0triagem.remover().print_paciente();
    // }
    for (int j = 0; j < 6; j++) // reescalona os pacientes nas filas de acordo com o procedimento que eles deverão realizar
    {
        int max;
        switch (j)
        {
        case 0:
            max = fila0triagem.tamanho;
            goto command;
        case 1:
            max = fila0atendimento.tamanho + fila1atendimento.tamanho + fila2atendimento.tamanho;
            goto command;
            ;
        case 2:
            max = fila0medidas.tamanho + fila1medidas.tamanho + fila2medidas.tamanho;
            goto command;
            ;
        case 3:
            max = fila0testes.tamanho + fila1testes.tamanho + fila2testes.tamanho;
            goto command;
            ;
        case 4:
            max = fila0imagem.tamanho + fila1imagem.tamanho + fila2imagem.tamanho;
            goto command;
            ;
        case 5:
            max = fila0instrumentos.tamanho + fila1instrumentos.tamanho + fila2instrumentos.tamanho;
            goto command;

        default:
            goto command;
        }
    command:
        for (int i = 0; i < max; i++)
        {
            reescalona(pacientes.heap[i], fila0triagem, fila0atendimento, fila0medidas, fila0testes, fila0imagem, fila0instrumentos, fila0triagem, fila1atendimento, fila1medidas, fila1testes, fila1imagem, fila1instrumentos, fila0triagem, fila2atendimento, fila2medidas, fila2testes, fila2imagem, fila2instrumentos, final, *p);
        }
    }
    for (int i = 0; i < npacientes; i++) // imprime os pacientes ordenandos por id
    {
        final.remover2().print_paciente();
    }
}
