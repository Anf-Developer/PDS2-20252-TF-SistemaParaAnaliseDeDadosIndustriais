#include "Sistema.hpp"
#include <iostream>

int main() {
    try {
        Sistema sistema;
        sistema.executar();
    } catch (const std::exception& e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}