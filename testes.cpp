#include <iostream>
#include <ctime>     // Para manipular datas e horários
#include <stdexcept> // Para lançar exceções

float calcularHorasDesde2017(int ano, int mes, int dia, int hora)
{
    // Estrutura para a data de referência (1º de janeiro de 2017, 00:00:00)
    std::tm dataReferencia = {};
    dataReferencia.tm_year = 2017 - 1900; // tm_year é contado desde 1900
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

int main()
{
    int ano, mes, dia, hora;

    try
    {
        // Solicita ao usuário a data e hora
        std::cout << "Digite o ano (deve ser após 2017): ";
        std::cin >> ano;
        std::cout << "Digite o mês (1-12): ";
        std::cin >> mes;
        std::cout << "Digite o dia (1-31): ";
        std::cin >> dia;
        std::cout << "Digite a hora (0-23): ";
        std::cin >> hora;

        // Calcula as horas desde 1º de janeiro de 2017
        float horas = calcularHorasDesde2017(ano, mes, dia, hora);
        std::cout << "Total de horas desde 1º de janeiro de 2017: " << horas << " horas" << std::endl;
    }
    catch (const std::exception &e)
    {
        // Exibe a mensagem de erro
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}