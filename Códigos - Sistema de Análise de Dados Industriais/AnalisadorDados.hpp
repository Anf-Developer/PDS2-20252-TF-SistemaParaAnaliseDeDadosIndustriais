
#ifndef ANALISADOR_DADOS_HPP
#define ANALISADOR_DADOS_HPP

#include <string>
#include <map>
#include "Maquina.hpp"

class AnalisadorDados {
public:
    AnalisadorDados();
    void processarArquivo(const std::string& filename, std::map<std::string, Maquina*>& maquinas);
};

#endif 