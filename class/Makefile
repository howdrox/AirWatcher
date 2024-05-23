# Nom de l'exécutable
TARGET = main

# Compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -std=c++11

# Fichiers sources
SRCS = User.cpp

# Fichiers objets
OBJS = $(SRCS:.cpp=.o)

# Règle par défaut pour construire l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Règle pour compiler les fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(TARGET) $(OBJS)

# Phony target pour éviter les conflits avec les fichiers existants
.PHONY: clean
