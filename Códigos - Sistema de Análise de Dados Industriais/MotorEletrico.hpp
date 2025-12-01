#ifndef MOTOR_ELETRICO_HPP
#define MOTOR_ELETRICO_HPP

#include "Maquina.hpp"


class MotorEletrico : public Maquina {
public:
    MotorEletrico(const std::string& tag, double vidaUtil, double tempRef, 
                  double torqueRef, double vibRef, double eficRef);

    double processarLeitura(double temp, double torque, double vib, double efic) override;
    std::string getTipo() const override;
};

#endif 