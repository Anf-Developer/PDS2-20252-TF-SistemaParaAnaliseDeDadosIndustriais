#ifndef TIPOS_USUARIOS_HPP
#define TIPOS_USUARIOS_HPP

#include "Usuario.hpp"


class Operador : public Usuario {
public:
    Operador(std::string login, std::string senha) 
        : Usuario(login, senha, "Operador") {}
};


class Supervisor : public Usuario {
public:
    Supervisor(std::string login, std::string senha) 
        : Usuario(login, senha, "Supervisor") {}

    bool podeCadastrarMaquinas() const override {
        return true;
    }
};


class Gestor : public Usuario {
public:
    Gestor(std::string login, std::string senha) 
        : Usuario(login, senha, "Gestor") {}

    bool podeAutorizarManutencao() const override {
        return true;
    }
    
    bool podeCadastrarMaquinas() const override {
        return true; 
    }
};

#endif 