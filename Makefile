CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC_DIR = src
IMPL_DIR = $(SRC_DIR)/impl
HEADER_DIR = $(SRC_DIR)/header

SOURCES = $(SRC_DIR)/main.cpp \
          $(IMPL_DIR)/barra.cpp \
          $(IMPL_DIR)/bola.cpp \
          $(IMPL_DIR)/blocos.cpp \
          $(IMPL_DIR)/cores.cpp \
          $(IMPL_DIR)/estado.cpp \
          $(IMPL_DIR)/fases.cpp \
          $(IMPL_DIR)/graficos.cpp \
          $(IMPL_DIR)/itens.cpp \
          $(IMPL_DIR)/jogador.cpp \
          $(IMPL_DIR)/jogo.cpp \
          $(IMPL_DIR)/menu.cpp \
          $(IMPL_DIR)/particulas.cpp \
          $(IMPL_DIR)/ranking.cpp \
          $(IMPL_DIR)/sons.cpp \
          $(IMPL_DIR)/utils.cpp

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = arkanoid

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
