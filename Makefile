# $@ = nom cible
# $< = nom premiere dépendance
# $^ = liste des dépendances
# $? = liste des dépendances plus récentes que la cible (? pas capté)
# $* = nom du fichier dans extension

# --------------------------------------------- VARIABLES -------------------------------------------


CXX=g++
COMPILE_FLAGS= -std=c++14 -m64 -g -Wall -I include
LINK_FLAGS= -lSDL2main -lSDL2 -lSDL2_image
SRC=src
OBJ=obj

#tous les fichiers .c dans le dossier src:
SRCS=$(wildcard $(SRC)/*.cpp)

#remplace les occurences d'un src/fichier.c par un obj/fichier.o, pour tous les fichiers du dossier src
# => Dans le dossier obj, fichiers ayant le même nom que les fichiers du dossier src, mais avec l'extension .o
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS)) 


# --------------------------------------------- BINARIES -------------------------------------------


DEBUG_BIN=bin/debug/main
debug:$(DEBUG_BIN) #on veut créer l'éxécutable bin/debug/main

RELEASE_BIN=bin/release/main
release: COMPILE_FLAGS= -std=c++14 -m64 -O2 -Wall -I include
release: $(RELEASE_BIN) #on veut créer l'éxécutable bin/release/main


# --------------------------------------------- COMMANDS -------------------------------------------


#	~2e COMMANDE: 
#Création de l'éxécutable BIN à partir de OBJS: fichiers.o de ./obj, ayant les mêmes noms que les fichiers.c de ./src (linking)

$(DEBUG_BIN): $(OBJS) 
	$(CXX) $(OBJ)/*.o -o $@ $(LINK_FLAGS)

$(RELEASE_BIN): $(OBJS)
	$(CXX)  $(OBJ)/*.o -o $@ -s $(LINK_FLAGS)
#equivaut à: g++ obj/fichier1.o obj/fichier2.o obj/fichier3.o -o bin/.../main


#	~1ere COMMANDE: 
#Création des fichiers objets à partir des fichiers.c du dossier ./src (compiling)
$(OBJ)/%.o: $(SRC)/%.cpp 
	$(CXX) -c $< $(COMPILE_FLAGS) -o $@ 	
#equivaut à: g++ -c src/fichier1.cpp src/fichier2.cpp src/fichier3.cpp -o obj/fichier1.o obj/fichier2.o obj/fichier3.o


#	~Nettoyage:
clean:
	rm $(OBJ)/*.o

