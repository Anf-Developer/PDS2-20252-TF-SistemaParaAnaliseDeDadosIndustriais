CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = sistema

SRCS = main.cpp Sistema.cpp Usuario.cpp Maquina.cpp MotorEletrico.cpp AnalisadorDados.cpp Relatorio.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET).exe relatorio.txt

run: all
	$(TARGET)
