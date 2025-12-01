#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <iostream>


class Usuario {
protected:
    std::string _login;
    std::string _senha;
    std::string _tipo; // Ex: "Operador", "Gestor"

public:
    
    Usuario(const std::string& login, const std::string& senha, const std::string& tipo);

    virtual ~Usuario();

   
    bool autenticar(const std::string& senhaInput) const;

    std::string getLogin() const;
    std::string getTipo() const;

    // Métodos Virtuais de Permissão (Polimorfismo)

   
    virtual bool podeCadastrarMaquinas() const;

    virtual bool podeAutorizarManutencao() const;
};

#endif 