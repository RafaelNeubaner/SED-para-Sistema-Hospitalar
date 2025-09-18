#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP
#include <ctime>
#include <stdexcept>
#include "Fila.hpp"
#include "Paciente.hpp"

void escalona(Paciente &P, MinHeap &triagem, MinHeap &atendimento, MinHeap &medidas, MinHeap &testes, MinHeap &imagem, MinHeap &instrumentos, MinHeap &triagem1, MinHeap &atendimento1, MinHeap &medidas1, MinHeap &testes1, MinHeap &imagem1, MinHeap &instrumentos1, MinHeap &triagem2, MinHeap &atendimento2, MinHeap &medidas2, MinHeap &testes2, MinHeap &imagem2, MinHeap &instrumentos2, MinHeap &final, Procedimento &Pro);
void escalona1(Paciente &P, MinHeap &triagem, MinHeap &atendimento, MinHeap &medidas, MinHeap &testes, MinHeap &imagem, MinHeap &instrumentos, MinHeap &triagem1, MinHeap &atendimento1, MinHeap &medidas1, MinHeap &testes1, MinHeap &imagem1, MinHeap &instrumentos1, MinHeap &triagem2, MinHeap &atendimento2, MinHeap &medidas2, MinHeap &testes2, MinHeap &imagem2, MinHeap &instrumentos2, MinHeap &final, Procedimento &Pro);
void insere_fila0(Paciente &P, MinHeap &triagem, MinHeap &atendimento, MinHeap &medidas, MinHeap &testes, MinHeap &imagem, MinHeap &instrumentos, MinHeap &final, Procedimento &Pro);
void insere_fila1(Paciente &P, MinHeap &triagem, MinHeap &atendimento, MinHeap &medidas, MinHeap &testes, MinHeap &imagem, MinHeap &instrumentos, MinHeap &final, Procedimento &Pro);
void insere_fila2(Paciente &P, MinHeap &triagem, MinHeap &atendimento, MinHeap &medidas, MinHeap &testes, MinHeap &imagem, MinHeap &instrumentos, MinHeap &final, Procedimento &Pro);
void reescalona(Paciente &P, MinHeap &triagem, MinHeap &atendimento, MinHeap &medidas, MinHeap &testes, MinHeap &imagem, MinHeap &instrumentos, MinHeap &triagem1, MinHeap &atendimento1, MinHeap &medidas1, MinHeap &testes1, MinHeap &imagem1, MinHeap &instrumentos1, MinHeap &triagem2, MinHeap &atendimento2, MinHeap &medidas2, MinHeap &testes2, MinHeap &imagem2, MinHeap &instrumentos2, MinHeap &final, Procedimento &Pro);

#endif
