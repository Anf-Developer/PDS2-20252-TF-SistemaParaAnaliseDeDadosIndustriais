#ifndef MAQUINA_HPP
#define MAQUINA_HPP

#include <string>
#include <vector>

/**
 * @brief Classe Base que representa uma máquina industrial.
 */
class Maquina {
protected:
    std::string _tag;
    double _vidaUtilReferenciaHoras;
    double _vidaUtilRestanteHoras;
    
    // Parâmetros ideais
    double _temperaturaRef;
    double _torqueRef;
    double _vibracaoRef;
    double _eficienciaRef;

    // Status: false = Operando, true = Precisa Manutenção
    bool _precisaManutencao; 

    std::vector<std::string> _anomaliasDetectadas;

public:
    Maquina(const std::string& tag, double vidaUtil, double tempRef, 
            double torqueRef, double vibRef, double eficRef);

    virtual ~Maquina();

    /**
     * @brief Processa leitura e aplica regras de desgaste.
     * @return Minutos de vida útil consumidos.
     */
    virtual double processarLeitura(double temp, double torque, double vib, double efic);

    void atualizarVidaUtil(double minutosConsumidos);
    
    /**
     * @brief Define se a máquina precisa de manutenção.
     */
    void setPrecisaManutencao(bool status);
    bool getPrecisaManutencao() const;

    // Getters
    std::string getTag() const;
    virtual std::string getTipo() const; // Para saber se é Motor ou Genérica
    double getVidaUtilRestanteHoras() const;
    double getVidaUtilReferenciaHoras() const;
    double getTempRef() const;
    double getTorqueRef() const;
    double getVibracaoRef() const;
    double getEficienciaRef() const;
    const std::vector<std::string>& getAnomalias() const;
};

#endif // MAQUINA_HPP