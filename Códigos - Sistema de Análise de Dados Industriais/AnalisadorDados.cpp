#include "AnalisadorDados.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

AnalisadorDados::AnalisadorDados() {}

void AnalisadorDados::processarArquivo(const std::string& filename,
                                       std::map<std::string, Maquina*>& maquinas) {
    std::ifstream arquivo(filename);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o arquivo: " + filename);
    }

    std::string linha;
    int linhaNum = 0;

    while (std::getline(arquivo, linha)) {
        linhaNum++;
        std::stringstream ss(linha);
        std::string tag, tempStr, torqueStr, vibStr, eficStr;
        
        if (std::getline(ss, tag, ',') && std::getline(ss, tempStr, ',') &&
            std::getline(ss, torqueStr, ',') && std::getline(ss, vibStr, ',') &&
            std::getline(ss, eficStr)) {
            
            try {
                double temp = std::stod(tempStr);
                double torque = std::stod(torqueStr);
                double vib = std::stod(vibStr);
                double efic = std::stod(eficStr);

                auto it = maquinas.find(tag);
                if (it != maquinas.end()) {
                    double minutos = it->second->processarLeitura(temp, torque, vib, efic);
                    it->second->atualizarVidaUtil(minutos);
                } else {
                    std::cerr << "Aviso: TAG " << tag << " nao encontrada (Linha " << linhaNum << ")\n";
                }
            } catch (...) {
                std::cerr << "Aviso: Dados invalidos na linha " << linhaNum << "\n";
            }
        }
    }
    arquivo.close();
}