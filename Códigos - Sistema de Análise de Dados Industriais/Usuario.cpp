#include "Usuario.hpp"

Usuario::Usuario(const std::string& login, const std::string& senha, const std::string& tipo)
    : _login(login), _senha(senha), _tipo(tipo) {}

Usuario::~Usuario() {}

bool Usuario::autenticar(const std::string& senhaInput) const {
    return _senha == senhaInput;
}

std::string Usuario::getLogin() const { return _login; }
std::string Usuario::getTipo() const { return _tipo; }

// Implementação padrão da base: Ninguém pode nada (Segurança por padrão)
bool Usuario::podeCadastrarMaquinas() const { return false; }
bool Usuario::podeAutorizarManutencao() const { return false; }