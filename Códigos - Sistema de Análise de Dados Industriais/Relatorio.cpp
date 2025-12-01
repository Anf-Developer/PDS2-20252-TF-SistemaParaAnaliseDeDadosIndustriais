#include "Relatorio.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

void Relatorio::gerarRelatorioDetalhado(const Maquina& maquina) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n--- Relatorio Detalhado: " << maquina.getTag() << " (" << maquina.getTipo() << ") ---\n";
    
    double perc = (maquina.getVidaUtilRestanteHoras() / maquina.getVidaUtilReferenciaHoras()) * 100.0;
    std::cout << "Vida Util: " << maquina.getVidaUtilRestanteHoras() << " h (" << perc << "%)\n";
    std::cout << "Status: " << (maquina.getPrecisaManutencao() ? "PRECISA MANUTENCAO" : "Operacional") << "\n";
    
    std::cout << "Anomalias:\n";
    for (const auto& a : maquina.getAnomalias()) {
        std::cout << " - " << a << "\n";
    }
}

void Relatorio::gerarSumarioSistema(const std::map<std::string, Maquina*>& maquinas) {
    std::ofstream arquivo("relatorio.txt");
    std::cout << "\n--- Sumario Geral ---\n";
    
    for (const auto& par : maquinas) {
        Maquina* m = par.second;
        std::string status = m->getPrecisaManutencao() ? "[MANUTENCAO]" : "[OK]";
        
        std::cout << m->getTag() << " \t| " << m->getTipo() << " \t| " << status << "\n";
        if (arquivo.is_open()) {
            arquivo << m->getTag() << "," << m->getVidaUtilRestanteHoras() << "," << status << "\n";
        }
    }
    std::cout << "(Arquivo relatorio.txt gerado)\n";
}