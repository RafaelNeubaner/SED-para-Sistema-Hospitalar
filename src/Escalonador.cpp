#include "Escalonador.hpp"

void escalona(Paciente &P, MinHeap &triagem0, MinHeap &atendimento0, MinHeap &medidas0, MinHeap &testes0, MinHeap &imagem0, MinHeap &instrumentos0, MinHeap &triagem1, MinHeap &atendimento1, MinHeap &medidas1, MinHeap &testes1, MinHeap &imagem1, MinHeap &instrumentos1, MinHeap &triagem2, MinHeap &atendimento2, MinHeap &medidas2, MinHeap &testes2, MinHeap &imagem2, MinHeap &instrumentos2, MinHeap &final, Procedimento &Pro)
{
    switch (P.grau) // verifica o grau de prioridade do paciente
    {
    case 0:
        insere_fila0(P, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, final, Pro); // insere o paciente na fila correta
        break;
    case 1:
        insere_fila1(P, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, final, Pro); // insere o paciente na fila correta
        break;
    case 2:
        insere_fila2(P, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro); // insere o paciente na fila correta
        break;

    default:
        break;
    }
}
void escalona1(Paciente &P, MinHeap &triagem0, MinHeap &atendimento0, MinHeap &medidas0, MinHeap &testes0, MinHeap &imagem0, MinHeap &instrumentos0, MinHeap &triagem1, MinHeap &atendimento1, MinHeap &medidas1, MinHeap &testes1, MinHeap &imagem1, MinHeap &instrumentos1, MinHeap &triagem2, MinHeap &atendimento2, MinHeap &medidas2, MinHeap &testes2, MinHeap &imagem2, MinHeap &instrumentos2, MinHeap &final, Procedimento &Pro)
{

    insere_fila0(P, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, final, Pro);
}

void reescalona(Paciente &P, MinHeap &triagem0, MinHeap &atendimento0, MinHeap &medidas0, MinHeap &testes0, MinHeap &imagem0, MinHeap &instrumentos0, MinHeap &triagem1, MinHeap &atendimento1, MinHeap &medidas1, MinHeap &testes1, MinHeap &imagem1, MinHeap &instrumentos1, MinHeap &triagem2, MinHeap &atendimento2, MinHeap &medidas2, MinHeap &testes2, MinHeap &imagem2, MinHeap &instrumentos2, MinHeap &final, Procedimento &Pro)
{
    double smin = 0;
    double pmin = 100000;
    double pmax = 0;
    if (triagem0.tamanho != 0) // verifica se a fila de triagem não está vazia
    {
        int save = 0;
        smin = Pro.triagem[0].relogio;
        for (int i = 0; i < Pro.ntri; i++) // verifica qual é a sala com menor tempo de espera
        {
            if (smin > Pro.triagem[i].relogio)
            {
                smin = Pro.triagem[i].relogio;
                save = i;
            }
        }
        triagem0.heap->conta_hora(&Pro);
        escalona(*triagem0.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
        triagem0.remover2();
    }
    else if ((atendimento0.tamanho || atendimento1.tamanho || atendimento2.tamanho) != 0) // verifica se a fila de atendimento não está vazia
    {
        int save = 0;
        smin = Pro.atendimento[0].relogio;
        for (int i = 0; i < Pro.naten; i++) // verifica qual é a sala com menor tempo de espera
        {
            if (smin > Pro.atendimento[i].relogio)
            {
                smin = Pro.atendimento[i].relogio;
                save = i;
            }
        }
        if (atendimento0.heap->horafila < pmin && atendimento0.tamanho > 0) // verifica qual o paciente com menor tempo de espera
            pmin = atendimento0.heap->horafila;
        if (atendimento1.heap->horafila < pmin && atendimento1.tamanho > 0)
            pmin = atendimento1.heap->horafila;
        if (atendimento2.heap->horafila < pmin && atendimento2.tamanho > 0)
            pmin = atendimento2.heap->horafila;
        if (atendimento0.heap->horafila > pmax && atendimento0.tamanho > 0)
            pmax = atendimento0.heap->horafila;
        if (atendimento1.heap->horafila > pmax && atendimento1.tamanho > 0)
            pmax = atendimento1.heap->horafila;
        if (atendimento2.heap->horafila > pmax && atendimento2.tamanho > 0)
            pmax = atendimento2.heap->horafila;
        if (atendimento2.heap->horafila <= smin && atendimento2.tamanho > 0) // verifica se ha alguem na fila de prioridade 2 antes da sala abrir
        {
            atendimento2.heap->conta_hora(&Pro);
            escalona(*atendimento2.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            atendimento2.remover();
        }
        else if (atendimento1.heap->horafila <= smin && atendimento1.tamanho > 0) // verifica se ha alguem na fila de prioridade 1 antes da sala abrir
        {
            atendimento1.heap->conta_hora(&Pro);
            escalona(*atendimento1.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            atendimento1.remover();
        }
        else if (atendimento0.heap->horafila <= smin && atendimento0.tamanho > 0) // verifica se ha alguem na fila de prioridade 0 antes da sala abrir
        {
            atendimento0.heap->conta_hora(&Pro);
            escalona(*atendimento0.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            atendimento0.remover();
        }
        else // caso não haja ninguem na fila de atendimento no momento que a sala abriu
        {
            if (pmin == atendimento2.heap->horafila && atendimento2.tamanho > 0) // verifica se ha alguem na fila de prioridade 2
            {
                atendimento2.heap->conta_hora(&Pro);
                escalona(*atendimento2.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                atendimento2.remover();
            }
            else if (pmin == atendimento1.heap->horafila && atendimento1.tamanho > 0) // verifica se ha alguem na fila de prioridade 1
            {
                atendimento1.heap->conta_hora(&Pro);
                escalona(*atendimento1.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                atendimento1.remover();
            }
            else if (pmin == atendimento0.heap->horafila && atendimento0.tamanho > 0) // verifica se ha alguem na fila de prioridade 0
            {
                atendimento0.heap->conta_hora(&Pro);
                escalona(*atendimento0.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                atendimento0.remover();
            }
        }
    }
    else if ((medidas0.tamanho || medidas1.tamanho || medidas2.tamanho) != 0) // verifica se a fila de medidas não está vazia
    {
        int save = 0;
        smin = Pro.medidas[0].relogio;
        for (int i = 0; i < Pro.nm; i++) // verifica qual é a sala com menor tempo de espera
        {
            if (smin > Pro.medidas[i].relogio)
            {
                smin = Pro.medidas[i].relogio;
                save = i;
            }
        }
        if (medidas0.heap->horafila < pmin && medidas0.tamanho > 0) // verifica qual o paciente com menor tempo de espera
            pmin = medidas0.heap->horafila;
        if (medidas1.heap->horafila < pmin && medidas1.tamanho > 0)
            pmin = medidas1.heap->horafila;
        if (medidas2.heap->horafila < pmin && medidas2.tamanho > 0)
            pmin = medidas2.heap->horafila;
        if (medidas0.heap->horafila > pmax && medidas0.tamanho > 0)
            pmax = medidas0.heap->horafila;
        if (medidas1.heap->horafila > pmax && medidas1.tamanho > 0)
            pmax = medidas1.heap->horafila;
        if (medidas2.heap->horafila > pmax && medidas2.tamanho > 0)
            pmax = medidas2.heap->horafila;
        if (medidas2.heap->horafila <= smin && medidas2.tamanho > 0) // verifica se ha alguem na fila de prioridade 2 antes da sala abrir
        {
            medidas2.heap->conta_hora(&Pro);
            escalona(*medidas2.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            medidas2.remover();
        }
        else if (medidas1.heap->horafila <= smin && medidas1.tamanho > 0) // verifica se ha alguem na fila de prioridade 1 antes da sala abrir
        {
            medidas1.heap->conta_hora(&Pro);
            escalona(*medidas1.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            medidas1.remover();
        }
        else if (medidas0.heap->horafila <= smin && medidas0.tamanho > 0) // verifica se ha alguem na fila de prioridade 0 antes da sala abrir
        {
            medidas0.heap->conta_hora(&Pro);
            escalona(*medidas0.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            medidas0.remover();
        }
        else // caso não haja ninguem na fila de medidas no momento que a sala abriu
        {
            if (pmin == medidas2.heap->horafila && medidas2.tamanho > 0) // verifica se ha alguem na fila de prioridade 2
            {
                medidas2.heap->conta_hora(&Pro);
                escalona(*medidas2.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                medidas2.remover();
            }
            else if (pmin == medidas1.heap->horafila && medidas1.tamanho > 0) // verifica se ha alguem na fila de prioridade 1
            {
                medidas1.heap->conta_hora(&Pro);
                escalona(*medidas1.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                medidas1.remover();
            }
            else if (pmin == medidas0.heap->horafila && medidas0.tamanho > 0) // verifica se ha alguem na fila de prioridade 0
            {
                medidas0.heap->conta_hora(&Pro);
                escalona(*medidas0.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                medidas0.remover();
            }
        }
    }
    else if ((testes0.tamanho || testes1.tamanho || testes2.tamanho) != 0) // verifica se a fila de testes não está vazia
    {
        int save = 0;
        smin = Pro.testes[0].relogio;
        for (int i = 0; i < Pro.nt; i++) // verifica qual é a sala com menor tempo de espera
        {
            if (smin > Pro.testes[i].relogio)
            {
                smin = Pro.testes[i].relogio;
                save = i;
            }
        }
        if (testes0.heap->horafila < pmin && testes0.tamanho > 0) // verifica qual o paciente com menor tempo de espera
            pmin = testes0.heap->horafila;
        if (testes1.heap->horafila < pmin && testes1.tamanho > 0)
            pmin = testes1.heap->horafila;
        if (testes2.heap->horafila < pmin && testes2.tamanho > 0)
            pmin = testes2.heap->horafila;
        if (testes0.heap->horafila > pmax && testes0.tamanho > 0)
            pmax = testes0.heap->horafila;
        if (testes1.heap->horafila > pmax && testes1.tamanho > 0)
            pmax = testes1.heap->horafila;
        if (testes2.heap->horafila > pmax && testes2.tamanho > 0)
            pmax = testes2.heap->horafila;
        if (testes2.heap->horafila <= smin && testes2.tamanho > 0) // verifica se ha alguem na fila de prioridade 2 antes da sala abrir
        {
            testes2.heap->conta_hora(&Pro);
            escalona(*testes2.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            testes2.remover();
        }
        else if (testes1.heap->horafila <= smin && testes1.tamanho > 0) // verifica se ha alguem na fila de prioridade 1 antes da sala abrir
        {
            testes1.heap->conta_hora(&Pro);
            escalona(*testes1.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            testes1.remover();
        }
        else if (testes0.heap->horafila <= smin && testes0.tamanho > 0) // verifica se ha alguem na fila de prioridade 0 antes da sala abrir
        {
            testes0.heap->conta_hora(&Pro);
            escalona(*testes0.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            testes0.remover();
        }
        else // caso não haja ninguem na fila de testes no momento que a sala abriu
        {
            if (pmin == testes2.heap->horafila && testes2.tamanho > 0) // verifica se ha alguem na fila de prioridade 2
            {
                testes2.heap->conta_hora(&Pro);
                escalona(*testes2.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                testes2.remover();
            }
            else if (pmin == testes1.heap->horafila && testes1.tamanho > 0) // verifica se ha alguem na fila de prioridade 1
            {
                testes1.heap->conta_hora(&Pro);
                escalona(*testes1.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                testes1.remover();
            }
            else if (pmin == testes0.heap->horafila && testes0.tamanho > 0) // verifica se ha alguem na fila de prioridade 0
            {
                testes0.heap->conta_hora(&Pro);
                escalona(*testes0.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                testes0.remover();
            }
        }
    }
    else if ((imagem0.tamanho || imagem1.tamanho || imagem2.tamanho) != 0) // verifica se a fila de imagem não está vazia
    {
        int save = 0;
        smin = Pro.imagem[0].relogio;
        for (int i = 0; i < Pro.ni; i++) // verifica qual é a sala com menor tempo de espera
        {
            if (smin > Pro.imagem[i].relogio)
            {
                smin = Pro.imagem[i].relogio;
                save = i;
            }
        }
        if (imagem0.heap->horafila < pmin && imagem0.tamanho > 0) // verifica qual o paciente com menor tempo de espera
            pmin = imagem0.heap->horafila;
        if (imagem1.heap->horafila < pmin && imagem1.tamanho > 0)
            pmin = imagem1.heap->horafila;
        if (imagem2.heap->horafila < pmin && imagem2.tamanho > 0)
            pmin = imagem2.heap->horafila;
        if (imagem0.heap->horafila > pmax && imagem0.tamanho > 0)
            pmax = imagem0.heap->horafila;
        if (imagem1.heap->horafila > pmax && imagem1.tamanho > 0)
            pmax = imagem1.heap->horafila;
        if (imagem2.heap->horafila > pmax && imagem2.tamanho > 0)
            pmax = imagem2.heap->horafila;
        if (imagem2.heap->horafila <= smin && imagem2.tamanho > 0) // verifica se ha alguem na fila de prioridade 2 antes da sala abrir
        {
            imagem2.heap->conta_hora(&Pro);
            escalona(*imagem2.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            imagem2.remover();
        }
        else if (imagem1.heap->horafila <= smin && imagem1.tamanho > 0) // verifica se ha alguem na fila de prioridade 1 antes da sala abrir
        {
            imagem1.heap->conta_hora(&Pro);
            escalona(*imagem1.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            imagem1.remover();
        }
        else if (imagem0.heap->horafila <= smin && imagem0.tamanho > 0) // verifica se ha alguem na fila de prioridade 0 antes da sala abrir
        {
            imagem0.heap->conta_hora(&Pro);
            escalona(*imagem0.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            imagem0.remover();
        }
        else // caso não haja ninguem na fila de imagem no momento que a sala abriu
        {
            if (pmin == imagem2.heap->horafila && imagem2.tamanho > 0) // verifica se ha alguem na fila de prioridade 2
            {
                imagem2.heap->conta_hora(&Pro);
                escalona(*imagem2.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                imagem2.remover();
            }
            else if (pmin == imagem1.heap->horafila && imagem1.tamanho > 0) // verifica se ha alguem na fila de prioridade 1
            {
                imagem1.heap->conta_hora(&Pro);
                escalona(*imagem1.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                imagem1.remover();
            }
            else if (pmin == imagem0.heap->horafila && imagem0.tamanho > 0) // verifica se ha alguem na fila de prioridade 0
            {
                imagem0.heap->conta_hora(&Pro);
                escalona(*imagem0.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                imagem0.remover();
            }
        }
    }
    else if ((instrumentos0.tamanho || instrumentos1.tamanho || instrumentos2.tamanho) != 0) // verifica se a fila de instrumentos não está vazia
    {
        int save = 0;
        smin = Pro.instrumentos[0].relogio;
        for (int i = 0; i < Pro.nim; i++) // verifica qual é a sala com menor tempo de espera
        {
            if (smin > Pro.instrumentos[i].relogio)
            {
                smin = Pro.triagem[i].relogio;
                save = i;
            }
        }
        if (instrumentos0.heap->horafila < pmin && instrumentos0.tamanho > 0) // verifica qual o paciente com menor tempo de espera
            pmin = instrumentos0.heap->horafila;
        if (instrumentos1.heap->horafila < pmin && instrumentos1.tamanho > 0)
            pmin = instrumentos1.heap->horafila;
        if (instrumentos2.heap->horafila < pmin && instrumentos2.tamanho > 0)
            pmin = instrumentos2.heap->horafila;
        if (instrumentos0.heap->horafila > pmax && instrumentos0.tamanho > 0)
            pmax = instrumentos0.heap->horafila;
        if (instrumentos1.heap->horafila > pmax && instrumentos1.tamanho > 0)
            pmax = instrumentos1.heap->horafila;
        if (instrumentos2.heap->horafila > pmax && instrumentos2.tamanho > 0)
            pmax = instrumentos2.heap->horafila;

        if (instrumentos2.heap->horafila <= smin && instrumentos2.tamanho > 0) // verifica se ha alguem na fila de prioridade 2 antes da sala abrir
        {
            instrumentos2.heap->conta_hora(&Pro);
            escalona(*instrumentos2.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            instrumentos2.remover();
        }
        else if (instrumentos1.heap->horafila <= smin && instrumentos1.tamanho > 0) // verifica se ha alguem na fila de prioridade 1 antes da sala abrir
        {
            instrumentos1.heap->conta_hora(&Pro);
            escalona(*instrumentos1.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            instrumentos1.remover();
        }
        else if (instrumentos0.heap->horafila <= smin && instrumentos0.tamanho > 0) // verifica se ha alguem na fila de prioridade 0 antes da sala abrir
        {
            instrumentos0.heap->conta_hora(&Pro);
            escalona(*instrumentos0.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
            instrumentos0.remover();
        }
        else // caso não haja ninguem na fila de instrumentos no momento que a sala abriu
        {
            if (pmin == instrumentos2.heap->horafila && instrumentos2.tamanho > 0) // verifica se ha alguem na fila de prioridade 2
            {
                instrumentos2.heap->conta_hora(&Pro);
                escalona(*instrumentos2.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                instrumentos2.remover();
            }
            else if (pmin == instrumentos1.heap->horafila && instrumentos1.tamanho > 0) // verifica se ha alguem na fila de prioridade 1
            {
                instrumentos1.heap->conta_hora(&Pro);
                escalona(*instrumentos1.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                instrumentos1.remover();
            }
            else if (pmin == instrumentos0.heap->horafila && instrumentos0.tamanho > 0) // verifica se ha alguem na fila de prioridade 0
            {
                instrumentos0.heap->conta_hora(&Pro);
                escalona(*instrumentos0.heap, triagem0, atendimento0, medidas0, testes0, imagem0, instrumentos0, triagem1, atendimento1, medidas1, testes1, imagem1, instrumentos1, triagem2, atendimento2, medidas2, testes2, imagem2, instrumentos2, final, Pro);
                instrumentos0.remover();
            }
        }
    }
}

void insere_fila0(Paciente &P, MinHeap &triagem, MinHeap &atendimento, MinHeap &medidas, MinHeap &testes, MinHeap &imagem, MinHeap &instrumentos, MinHeap &final, Procedimento &Pro) // insere o paciente na fila que ele pertence de acordo com os exames a realizar

{
    if (P.triado == 0)
    {
        triagem.inserir3(P);
        return;
    }
    else if (P.atendido == 0)
    {
        atendimento.inserir(P);
        return;
    }
    else if (P.nmh != 0)
    {
        if (P.alta == 1)
        {
            final.inserir2(P);
            return;
        }
        else
        {
            medidas.inserir(P);
            return;
        }
    }
    else if (P.ntl != 0)
    {
        testes.inserir(P);
        return;
    }
    else if (P.nei != 0)
    {
        imagem.inserir(P);
        return;
    }
    else if (P.nim != 0)
    {
        instrumentos.inserir(P);
        return;
    }
    else
        final.inserir2(P);
    return;
}

void insere_fila1(Paciente &P, MinHeap &triagem, MinHeap &atendimento, MinHeap &medidas, MinHeap &testes, MinHeap &imagem, MinHeap &instrumentos, MinHeap &final, Procedimento &Pro) // insere o paciente na fila que ele pertence de acordo com os exames a realizar
{
    if (P.triado == 0)
    {
        triagem.inserir(P);
        return;
    }
    else if (P.atendido == 0)
    {
        atendimento.inserir(P);
        return;
    }
    else if (P.nmh != 0)
    {
        if (P.alta == 1)
        {
            final.inserir2(P);
            return;
        }
        else
        {
            medidas.inserir(P);
            return;
        }
    }
    else if (P.ntl != 0)
    {
        testes.inserir(P);
        return;
    }
    else if (P.nei != 0)
    {
        imagem.inserir(P);
        return;
    }
    else if (P.nim != 0)
    {
        instrumentos.inserir(P);
        return;
    }
    else
        final.inserir2(P);
    return;
}

void insere_fila2(Paciente &P, MinHeap &triagem, MinHeap &atendimento, MinHeap &medidas, MinHeap &testes, MinHeap &imagem, MinHeap &instrumentos, MinHeap &final, Procedimento &Pro) // insere o paciente na fila que ele pertence de acordo com os exames a realizar
{
    if (P.triado == 0)
    {
        triagem.inserir(P);
        return;
    }
    else if (P.atendido == 0)
    {
        atendimento.inserir(P);
        return;
    }
    else if (P.nmh != 0)
    {
        if (P.alta == 1)
        {
            final.inserir2(P);
            return;
        }
        else
        {
            medidas.inserir(P);
            return;
        }
    }
    else if (P.ntl != 0)
    {
        testes.inserir(P);
        return;
    }
    else if (P.nei != 0)
    {
        imagem.inserir(P);
        return;
    }
    else if (P.nim != 0)
    {
        instrumentos.inserir(P);
        return;
    }
    else
        final.inserir2(P);
    return;
}
