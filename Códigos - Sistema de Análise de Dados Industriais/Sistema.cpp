#include "Sistema.hpp"
#include "Relatorio.hpp"
#include "TiposUsuarios.hpp" 
#include "MotorEletrico.hpp" 
#include <iostream>
#include <limits>

// --- CONSTRUTOR ---
Sistema::Sistema() : _usuarioLogado(nullptr), _emExecucao(true) {
    carregarUsuarios();
    // Não chamamos login() aqui. Ele é chamado no executar().
}

// --- DESTRUTOR ---
Sistema::~Sistema() {
    std::cout << "Encerrando sistema e limpando memoria...\n";
    
    // Limpa memória das máquinas
    for (auto& par : _maquinas) {
        delete par.second;
    }
    _maquinas.clear();
    
    // Limpa memória dos usuários
    for (auto* u : _usuariosCadastrados) {
        delete u;
    }
    _usuariosCadastrados.clear();
}

// CARREGAR USUÁRIOS
void Sistema::carregarUsuarios() {
    _usuariosCadastrados.push_back(new Operador("op", "123"));
    _usuariosCadastrados.push_back(new Supervisor("sup", "123"));
    _usuariosCadastrados.push_back(new Gestor("adm", "adm"));
}

// LÓGICA DE LOGIN 
void Sistema::login() {
    // Loop até conseguir logar OU o usuário decidir sair
    while (_usuarioLogado == nullptr && _emExecucao) {
        std::cout << "\n===================================\n";
        std::cout << "   SISTEMA DE ANALISE INDUSTRIAL   \n";
        std::cout << "===================================\n";
        std::cout << "Logins de Teste:\n";
        std::cout << " - Operador:   op / 123\n";
        std::cout << " - Supervisor: sup / 123\n";
        std::cout << " - Gestor:     adm / adm\n";
        std::cout << "-----------------------------------\n";
        std::cout << "Digite o Usuario (ou 'sair' para fechar): ";
        
        std::string u, s;
        std::cin >> u;
        
        if (u == "sair") {
            _emExecucao = false; // Fecha o programa
            return;
        }

        std::cout << "Senha: ";
        std::cin >> s;
        
        for (Usuario* user : _usuariosCadastrados) {
            if (user->getLogin() == u && user->autenticar(s)) {
                _usuarioLogado = user;
                std::cout << "\n>>> Bem-vindo, " << user->getTipo() << " " << user->getLogin() << "! <<<\n";
                break;
            }
        }
        
        if (!_usuarioLogado) {
            std::cout << "\n[ERRO] Credenciais invalidas. Tente novamente.\n";
        }
    }
}

// --- LOOP PRINCIPAL (EXECUTAR) ---
void Sistema::executar() {
    while (_emExecucao) {
        
        // 1. Se ninguém estiver logado, força o login
        if (_usuarioLogado == nullptr) {
            login();
        }

        // 2. Se logou com sucesso, mostra o menu
        if (_emExecucao && _usuarioLogado != nullptr) {
            exibirMenu();
            int op;
            std::cin >> op;
            
            if(std::cin.fail()) { 
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                op = -1; 
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch(op) {
                case 1: cadastrarMaquina(); break;
                case 2: importarDados(); break;
                case 3: inserirLeituraManual(); break;
                case 4: gerarRelatorios(); break;
                case 5: gerenciarManutencao(); break;
                
                case 6: // Logout
                    std::cout << "Fazendo logout...\n";
                    _usuarioLogado = nullptr; 
                    break;

                case 0: // Sair Geral
                    std::cout << "Encerrando o sistema.\n";
                    _emExecucao = false; 
                    break;
                    
                default: std::cout << "Opcao invalida.\n";
            }
            
            // Pausa antes de limpar a tela (apenas se não estiver saindo)
            if (_emExecucao && _usuarioLogado != nullptr) {
                std::cout << "\nPressione ENTER para continuar...";
                std::cin.get();
            }
        }
    }
    std::cout << "Sistema finalizado. Ate logo!\n";
}

// --- EXIBIR MENU ---
void Sistema::exibirMenu() const {
    std::cout << "\n--------- MENU PRINCIPAL (" << _usuarioLogado->getTipo() << ") ---------\n";
    std::cout << "1. Cadastrar Nova Maquina    (Req: Supervisor/Gestor)\n";
    std::cout << "2. Importar Dados de Arquivo (Todos)\n";
    std::cout << "3. Inserir Leitura Manual    (Todos)\n";
    std::cout << "4. Exibir Relatorios         (Todos)\n";
    std::cout << "5. Autorizar Manutencao      (Req: Gestor)\n";
    std::cout << "----------------------------------------\n";
    std::cout << "6. Fazer Logout / Trocar Usuario\n";
    std::cout << "0. Encerrar o Sistema\n";
    std::cout << "Escolha: ";
}

// --- CADASTRAR MÁQUINA ---
void Sistema::cadastrarMaquina() {
    if (!_usuarioLogado->podeCadastrarMaquinas()) {
        std::cout << "\n[ACESSO NEGADO] Voce nao tem permissao para cadastrar maquinas.\n";
        return;
    }

    std::cout << "\n--- Cadastro de Maquina ---\n";
    std::cout << "Selecione o Tipo:\n";
    std::cout << "1 - Maquina Generica\n";
    std::cout << "2 - Motor Eletrico (Regras especificas de Torque)\n";
    std::cout << "Opcao: ";
    
    int tipo; 
    std::cin >> tipo; 
    std::cin.ignore();

    std::string tag;
    std::cout << "Digite a TAG (ID Unico): "; 
    std::getline(std::cin, tag);

    if (_maquinas.count(tag)) { 
        std::cout << "[ERRO] Maquina com TAG '" << tag << "' ja existe.\n"; 
        return; 
    }

    double vida = 10000;
    double temp = 60, torque = 300, vib = 2.0, efic = 95;

    if (tipo == 2) {
        std::cout << "Configurando Motor Eletrico (Padrao: 80C, 500Nm)...\n";
        _maquinas[tag] = new MotorEletrico(tag, vida, 80, 500, 5, 90); 
    } else {
        std::cout << "Configurando Maquina Generica (Padrao: 60C, 300Nm)...\n";
        _maquinas[tag] = new Maquina(tag, vida, temp, torque, vib, efic);
    }
    
    std::cout << ">> Maquina '" << tag << "' cadastrada com sucesso!\n";
}

// --- IMPORTAR DADOS (ARQUIVO) ---
void Sistema::importarDados() {
    std::cout << "\n--- Importacao de Arquivo ---\n";
    std::cout << "Nome do arquivo (ex: dados.txt): ";
    std::string arq;
    std::getline(std::cin, arq);
    
    try {
        _analisador.processarArquivo(arq, _maquinas);
        std::cout << ">> Arquivo processado com sucesso! Verifique os relatorios.\n";
    } catch (const std::exception& e) {
        std::cout << "[ERRO] Falha ao ler arquivo: " << e.what() << "\n";
    }
}

// --- INSERIR LEITURA MANUAL ---
void Sistema::inserirLeituraManual() {
    std::cout << "\n--- Insercao Manual de Dados ---\n";
    std::cout << "Digite a TAG da maquina: ";
    std::string tag;
    std::getline(std::cin, tag);

    auto it = _maquinas.find(tag);
    if (it == _maquinas.end()) {
        std::cout << "[ERRO] Maquina nao encontrada!\n";
        return;
    }

    double temp, torque, vib, efic;
    std::cout << " > Temperatura (C): "; std::cin >> temp;
    std::cout << " > Torque (Nm):     "; std::cin >> torque;
    std::cout << " > Vibracao (m/s2): "; std::cin >> vib;
    std::cout << " > Eficiencia (%):  "; std::cin >> efic;
    std::cin.ignore(); 

    double minutos = it->second->processarLeitura(temp, torque, vib, efic);
    it->second->atualizarVidaUtil(minutos);

    std::cout << "\n>> Leitura registrada!\n";
    std::cout << "   Desgaste calculado nesta leitura: " << minutos << " minutos.\n";
    
    if (it->second->getPrecisaManutencao()) {
        std::cout << "   [ALERTA] STATUS ALTERADO PARA: PRECISA DE MANUTENCAO!\n";
    }
}

// --- GERAR RELATÓRIOS ---
void Sistema::gerarRelatorios() {
    std::cout << "\n--- Relatorios do Sistema ---\n";
    Relatorio::gerarSumarioSistema(_maquinas);
    
    std::cout << "\nDeseja ver detalhes de uma maquina especifica? (Digite a TAG ou 'N'): ";
    std::string tag; 
    std::getline(std::cin, tag);
    
    if (tag != "N" && tag != "n") {
        if (_maquinas.count(tag)) {
            Relatorio::gerarRelatorioDetalhado(*_maquinas[tag]);
        } else {
            std::cout << "[AVISO] Maquina nao encontrada.\n";
        }
    }
}

// --- GERENCIAR MANUTENÇÃO ---
void Sistema::gerenciarManutencao() {
    if (!_usuarioLogado->podeAutorizarManutencao()) {
        std::cout << "\n[ACESSO NEGADO] Apenas Gestores podem autorizar manutencao.\n";
        return;
    }

    std::cout << "\n--- Central de Manutencao ---\n";
    std::cout << "Digite a TAG da maquina para autorizar reparo: ";
    std::string tag; 
    std::getline(std::cin, tag);
    
    if (_maquinas.count(tag)) {
        Maquina* m = _maquinas[tag];
        if (m->getPrecisaManutencao()) {
            m->setPrecisaManutencao(false);
            std::cout << ">> Ordem de Servico gerada e aprovada.\n";
            std::cout << ">> Maquina '" << tag << "' agora esta OPERACIONAL.\n";
        } else {
            std::cout << ">> Essa maquina ja esta operando normalmente. Nenhuma acao necessaria.\n";
        }
    } else {
        std::cout << "[ERRO] Maquina nao encontrada.\n";
    }
}