#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
#include <map>
#include <vector>
#include "Maquina.hpp"
#include "Usuario.hpp"
#include "AnalisadorDados.hpp"

/**
 * @brief Classe principal que gerencia o fluxo da aplicação.
 * @details Controla login, menus, cadastro e processamento de dados.
 */
class Sistema {
private:
    // Armazena ponteiros polimórficos para Máquinas
    std::map<std::string, Maquina*> _maquinas;
    
    // Armazena ponteiros polimórficos para Usuários
    std::vector<Usuario*> _usuariosCadastrados;
    
    // Ponteiro para quem está logado no momento 
    Usuario* _usuarioLogado;
    
    AnalisadorDados _analisador;
    bool _emExecucao;

    // Métodos Internos 
    void carregarUsuarios();
    void login();
    void exibirMenu() const;
    
    // Funcionalidades do Menu
    void cadastrarMaquina();
    void importarDados();
    void inserirLeituraManual(); //Nova funcionalidade adicionada
    void gerarRelatorios();
    void gerenciarManutencao();

public:
    Sistema();
    ~Sistema();
    void executar();
};

#endif