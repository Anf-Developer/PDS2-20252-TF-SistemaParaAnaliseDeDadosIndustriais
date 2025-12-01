CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = sistema

# Lista de arquivos fonte
SRCS = main.cpp Sistema.cpp Usuario.cpp Maquina.cpp MotorEletrico.cpp AnalisadorDados.cpp Relatorio.cpp

# Regra padrão
all: $(TARGET)

# Regra de compilação
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Regra de limpeza
clean:
	rm -f $(TARGET) relatorio.txt

# Regra para rodar
run: all
	./$(TARGET)