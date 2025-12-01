#include "Maquina.hpp"

Maquina::Maquina(const std::string& tag, double vidaUtil, double tempRef, 
                 double torqueRef, double vibRef, double eficRef)
    : _tag(tag), _vidaUtilReferenciaHoras(vidaUtil), _vidaUtilRestanteHoras(vidaUtil),
      _temperaturaRef(tempRef), _torqueRef(torqueRef), 
      _vibracaoRef(vibRef), _eficienciaRef(eficRef), _precisaManutencao(false) {
}

Maquina::~Maquina() {}

double Maquina::processarLeitura(double temp, double torque, double vib, double efic) {
    double minutos = 1.0;
    //Regra Base: Temperatura maior que 15% do limite
    if (temp > _temperaturaRef * 1.15) {
        minutos += 2.0;
        _anomaliasDetectadas.push_back("ALERTA: Temperatura alta (Generico)");
        _precisaManutencao = true; //  manutenção automática
    }
    return minutos;
}

void Maquina::atualizarVidaUtil(double minutosConsumidos) {
    _vidaUtilRestanteHoras -= (minutosConsumidos / 60.0);
    if (_vidaUtilRestanteHoras < 0) _vidaUtilRestanteHoras = 0;
}

void Maquina::setPrecisaManutencao(bool status) {
    _precisaManutencao = status;
}

bool Maquina::getPrecisaManutencao() const {
    return _precisaManutencao;
}

std::string Maquina::getTag() const { return _tag; }
std::string Maquina::getTipo() const { return "Generica"; }
double Maquina::getVidaUtilRestanteHoras() const { return _vidaUtilRestanteHoras; }
double Maquina::getVidaUtilReferenciaHoras() const { return _vidaUtilReferenciaHoras; }
double Maquina::getTempRef() const { return _temperaturaRef; }
double Maquina::getTorqueRef() const { return _torqueRef; }
double Maquina::getVibracaoRef() const { return _vibracaoRef; }
double Maquina::getEficienciaRef() const { return _eficienciaRef; }
const std::vector<std::string>& Maquina::getAnomalias() const { return _anomaliasDetectadas; }