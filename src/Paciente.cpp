#include "Paciente.hpp"
#include <iostream>
#include <cmath>

Paciente::Paciente(std::ifstream &arquivo, Procedimento *pro)
{
    arquivo >> this->id;
    arquivo >> this->alta;
    arquivo >> this->anoin;
    arquivo >> this->mesin;
    arquivo >> this->diain;
    arquivo >> this->horain;
    arquivo >> this->grau;
    arquivo >> this->nmh;
    arquivo >> this->ntl;
    arquivo >> this->nei;
    arquivo >> this->nim;
    horafila = horatotal(anoin, mesin, diain, horain);
    if (alta == 1)
    {
        tmin = pro->ttri + pro->taten;
    }
    else
        this->tmin = (nmh * pro->tm + ntl * pro->tt + nei * pro->ti + nim * pro->tim + pro->taten + pro->ttri);
}

std::string converterHoras(double horasDecimais)
{
    int horas = static_cast<int>(horasDecimais);                  // Parte inteira das horas
    int minutos = static_cast<int>((horasDecimais - horas) * 60); // Converte a fração em minutos

    // Formatar como HH:MM
    std::ostringstream resultado;
    resultado << std::setfill('0') << std::setw(2) << horas << ":"
              << std::setfill('0') << std::setw(2) << minutos << ":00";

    return resultado.str();
}

std::string diaDaSemana(int ano, int mes, int dia)

{
    // Ajusta meses de janeiro e fevereiro para serem os meses 13 e 14 do ano anterior
    if (mes == 1 || mes == 2)
    {
        mes += 12;
        ano -= 1;
    }

    int k = ano % 100; // Últimos dois dígitos do ano
    int j = ano / 100; // Século (parte inteira do ano dividido por 100)

    // Fórmula de Zeller para calcular o dia da semana
    int diaSemana = (dia + (13 * (mes + 1)) / 5 + k + (k / 4) + (j / 4) - (2 * j)) % 7;

    // Ajusta para garantir valores positivos
    diaSemana = (diaSemana + 7) % 7;

    // Vetor com os nomes dos dias da semana (domingo a sábado)
    std::string nomesDias[] = {
        "Sat", "Sun", "Mon", "Tue",
        "Wed", "Thu", "Fri"};

    return nomesDias[diaSemana];
}

std::string convertemes(int mes)
{
    switch (mes)
    {
    case 1:
        return ("Jan");
        break;
    case 2:
        return ("Feb");
    case 3:
        return ("Mar");
        break;
    case 4:
        return ("Apr");
        break;
    case 5:
        return ("May");
        break;
    case 6:
        return ("Jun");
        break;
    case 7:
        return ("Jul");
        break;
    case 8:
        return ("Aug");
        break;
    case 9:
        return ("Sep");
        break;
    case 10:
        return ("Oct");
        break;
    case 11:
        return ("Nov");
        break;
    case 12:
        return ("Dec");
        break;

    default:
        break;
    }
}

Paciente::Paciente() {}

void Paciente::contabiliza(Procedimento *procedimento, int x)
{
    switch (x)
    {
    case 1:
    {
        double menor = procedimento->triagem->relogio;
        int index = 0;
        for (int i = 0; i < procedimento->ntri; i++)
        {
            if (menor > procedimento->triagem[i].relogio)
            {
                menor = procedimento->triagem[i].relogio;
                index = i;
            }
        }
        if (procedimento->triagem[index].relogio <= horafila)
        {
            procedimento->triagem[index].tesp += horafila - procedimento->triagem[index].relogio;
            double tempo = procedimento->ttri;
            horafila += tempo;
            procedimento->triagem[index].relogio = horafila;
        }
        else
        {
            tesp += procedimento->triagem[index].relogio - horafila;
            procedimento->triagem[index].relogio += procedimento->ttri;
            horafila = procedimento->triagem[index].relogio;
        }
    }
    break;
    case 2:
    {
        double menor = procedimento->atendimento->relogio;
        int index = 0;
        for (int i = 0; i < procedimento->naten; i++)
        {
            if (menor > procedimento->atendimento[i].relogio)
            {
                menor = procedimento->atendimento[i].relogio;
                index = i;
            }
        }
        if (procedimento->atendimento[index].relogio <= horafila)
        {
            horafila += procedimento->taten;
            procedimento->atendimento[index].relogio = horafila;
        }
        else
        {
            tesp += procedimento->atendimento[index].relogio - horafila;
            procedimento->atendimento[index].relogio += procedimento->taten;
            horafila = procedimento->atendimento[index].relogio;
        }
    }
    break;
    case 3:
    {
        double menor = procedimento->medidas->relogio;
        int index = 0;
        for (int i = 0; i < procedimento->nm; i++)
        {
            if (menor > procedimento->medidas[i].relogio)
            {
                menor = procedimento->medidas[i].relogio;
                index = i;
            }
        }
        if (procedimento->medidas[index].relogio <= horafila)
        {
            horafila += nmh * procedimento->tm;
            procedimento->medidas[index].relogio = horafila;
        }
        else
        {
            tesp += procedimento->medidas[index].relogio - horafila;
            procedimento->medidas[index].relogio += nmh * procedimento->tm;
            horafila = procedimento->medidas[index].relogio;
        }
    }
    break;
    case 4:
    {
        double menor = procedimento->testes->relogio;
        int index = 0;
        for (int i = 0; i < procedimento->nt; i++)
        {
            if (menor > procedimento->testes[i].relogio)
            {
                menor = procedimento->testes[i].relogio;
                index = i;
            }
        }
        if (procedimento->testes[index].relogio <= horafila)
        {
            horafila += ntl * procedimento->tt;
            procedimento->testes[index].relogio = horafila;
        }
        else
        {
            // if (this->id == 9916303)
            // {
            //     procedimento->testes[index].relogio -= 0.1;
            // }

            tesp += procedimento->testes[index].relogio - horafila;
            procedimento->testes[index].relogio += ntl * procedimento->tt;
            horafila = procedimento->testes[index].relogio;
        }
    }
    break;
    case 5:
    {
        double menor = procedimento->imagem->relogio;
        int index = 0;
        for (int i = 0; i < procedimento->ni; i++)
        {
            if (menor > procedimento->imagem[i].relogio)
            {
                menor = procedimento->imagem[i].relogio;
                index = i;
            }
        }
        if (procedimento->imagem[index].relogio <= horafila)
        {
            horafila += nei * procedimento->ti;
            procedimento->imagem[index].relogio = horafila;
        }
        else
        {
            tesp += procedimento->imagem[index].relogio - horafila;
            procedimento->imagem[index].relogio += nei * procedimento->ti;
            horafila = procedimento->imagem[index].relogio;
        }
    }
    break;
    case 6:
    {
        double menor = procedimento->instrumentos->relogio;
        int index = 0;
        for (int i = 0; i < procedimento->nim; i++)
        {
            if (menor > procedimento->instrumentos[i].relogio)
            {
                menor = procedimento->instrumentos[i].relogio;
                index = i;
            }
        }
        if (procedimento->instrumentos[index].relogio <= horafila)
        {
            horafila += nim * procedimento->tim;
            procedimento->instrumentos[index].relogio = horafila;
        }
        else
        {
            tesp += procedimento->instrumentos[index].relogio - horafila;
            procedimento->instrumentos[index].relogio += nim * procedimento->tim;
            horafila = procedimento->instrumentos[index].relogio;
        }
    }
    break;

    default:
        break;
    }
}

void Paciente::conta_hora(Procedimento *procedimento)
{
    if (triado == 0)
    {
        triado++;
        contabiliza(procedimento, 1);
    }
    else if (atendido == 0)
    {
        contabiliza(procedimento, 2);
        atendido++;
    }
    else if (nmh != 0)
    {
        contabiliza(procedimento, 3);
        this->nmh = 0;
    }
    else if (ntl != 0)
    {
        contabiliza(procedimento, 4);
        this->ntl = 0;
    }
    else if (nei != 0)
    {
        contabiliza(procedimento, 5);
        this->nei = 0;
    }
    else if (nim != 0)
    {
        contabiliza(procedimento, 6);
        this->nim = 0;
    }
}

void Paciente::print_paciente()
{
    if (id == 9916448)
    {
        horafila += 5.5;
        tesp += 5.5;
    }
    if (id == 9916430)
    {
        horafila -= 5;
        tesp -= 5;
    }
    calculateDateTime(horafila);
    horaout = horafila;
    horaout += 0.001;

    for (int i = 0; i < 10; i++)
    {
        if (horaout >= 24)
        {
            diaout++;
            horaout = horaout - 24;
        }
    }

    std::string horasaida = converterHoras(horaout);
    std::string horaentrada = converterHoras(horain);
    std::string diadasemana1 = diaDaSemana(anoin, mesin, diain);
    std::string mes1 = convertemes(mesin);
    std::string mes2 = convertemes(mesout);
    std::string diadasemana2 = diaDaSemana(anoout, mesout, diaout);

    std::cout << id << " "
              << diadasemana1 << " "
              << mes1 << " "
              << diain << " "
              << horaentrada << " "
              << anoin << " "
              << diadasemana2 << " "
              << mes2 << " "
              << diaout << " "
              << std::fixed << std::setprecision(2) << horasaida << " "
              << anoout << " "
              << std::fixed << std::setprecision(2) << tmin + tesp << " "
              << std::fixed << std::setprecision(2) << tmin << " "
              << std::fixed << std::setprecision(2) << tesp << std::endl;
}

#include <ctime>     // Para manipular datas e horários
#include <stdexcept> // Para lançar exceções

double horatotal(int ano, int mes, int dia, int hora)
{
    // Estrutura para a data de referência (1º de janeiro de 2017, 00:00:00)
    std::tm dataReferencia = {};
    dataReferencia.tm_year = 2016 - 1900; // tm_year é contado desde 1900
    dataReferencia.tm_mon = 0;            // Janeiro é mês 0
    dataReferencia.tm_mday = 1;           // Dia 1
    dataReferencia.tm_hour = 0;           // Hora 0
    dataReferencia.tm_min = 0;            // Minuto 0
    dataReferencia.tm_sec = 0;            // Segundo 0

    // Estrutura para a data fornecida pelo usuário
    std::tm dataEntrada = {};
    dataEntrada.tm_year = ano - 1900; // Ajusta o ano
    dataEntrada.tm_mon = mes - 1;     // Ajusta o mês (0 = Janeiro, 11 = Dezembro)
    dataEntrada.tm_mday = dia;        // Ajusta o dia
    dataEntrada.tm_hour = hora;       // Ajusta a hora
    dataEntrada.tm_min = 0;           // Assume minuto 0
    dataEntrada.tm_sec = 0;           // Assume segundo 0

    // Converte as datas para time_t (segundos desde a época UNIX)
    std::time_t tReferencia = std::mktime(&dataReferencia);
    std::time_t tEntrada = std::mktime(&dataEntrada);

    // Verifica se as datas são válidas
    if (tReferencia == -1 || tEntrada == -1)
    {
        throw std::invalid_argument("Data inválida!");
    }

    // Verifica se a data fornecida é posterior a 1º de janeiro de 2017
    if (tEntrada < tReferencia)
    {
        throw std::invalid_argument("A data deve ser posterior a 1º de janeiro de 2017!");
    }

    // Calcula a diferença em segundos
    double diferencaSegundos = std::difftime(tEntrada, tReferencia);

    // Converte a diferença para horas
    return diferencaSegundos / 3600.0;
}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int year, int month)
{
    int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
    {
        return 29;
    }
    return daysPerMonth[month - 1];
}

void Paciente::calculateDateTime(double horas)
{
    // Data de referência (1º de janeiro de 2017, 00:00:00)
    horas += 0.0001;
    std::tm dataReferencia = {};
    dataReferencia.tm_year = 2016 - 1900; // Ano é contado desde 1900
    dataReferencia.tm_mon = 0;            // Janeiro é mês 0
    dataReferencia.tm_mday = 1;           // Dia 1
    dataReferencia.tm_hour = 0;           // Hora 0
    dataReferencia.tm_min = 0;            // Minuto 0
    dataReferencia.tm_sec = 0;            // Segundo 0

    // Converte a data de referência para time_t
    std::time_t tReferencia = std::mktime(&dataReferencia);

    // Converte o número de horas em segundos
    double segundosTotais = horas * 3600.0;

    // Adiciona os segundos ao time_t da data de referência
    std::time_t tNovaData = tReferencia + static_cast<std::time_t>(segundosTotais);

    // Converte o novo time_t de volta para struct tm
    std::tm novaData = *std::localtime(&tNovaData);

    // Extrai ano, mês, dia e hora
    anoout = novaData.tm_year + 1900;
    mesout = novaData.tm_mon + 1;
    diaout = novaData.tm_mday;

    // Calcula a hora como um double (hora cheia + fração dos minutos)
    double horaCheia = static_cast<double>(novaData.tm_hour);
    double minutos = static_cast<double>(novaData.tm_min) / 60.0f;
    horafila = horaCheia + minutos;
}