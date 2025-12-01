#include "MotorEletrico.hpp"

MotorEletrico::MotorEletrico(const std::string& tag, double vidaUtil, double tempRef, 
                             double torqueRef, double vibRef, double eficRef)
    : Maquina(tag, vidaUtil, tempRef, torqueRef, vibRef, eficRef) {}

double MotorEletrico::processarLeitura(double temp, double torque, double vib, double efic) {
    double minutos = 1.0;
    
    // Regra Específica: Motores sofrem mais com torque
    if (torque > _torqueRef * 1.10) {
        minutos += 10.0; // Penalidade alta
        _anomaliasDetectadas.push_back("PERIGO (Motor): Torque excessivo!");
        _precisaManutencao = true;
    }

    minutos += Maquina::processarLeitura(temp, torque, vib, efic);
    return minutos;
}

std::string MotorEletrico::getTipo() const {
    return "Motor Eletrico";
}