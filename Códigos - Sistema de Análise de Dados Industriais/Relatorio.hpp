#ifndef RELATORIO_HPP
#define RELATORIO_HPP

#include "Maquina.hpp"
#include <map>
#include <string>

class Relatorio {
public:
    static void gerarRelatorioDetalhado(const Maquina& maquina);
    static void gerarSumarioSistema(const std::map<std::string, Maquina*>& maquinas);
};

#endif // RELATORIO_HPP