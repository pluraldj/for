# DEPENDENCIES
# Libraries that are required to be installed on the system
# - Boost (random and serialization)
#   	Install with "sudo apt-get install libboost-all-dev" (or similar command 
#   	depending on Linux flavor), alternatively install only libboost-random-dev 
#   	and libbost-serialization-dev
# - XercesC (XML parsing)
#		Install with "sudo apt-get install libxerces-c-dev"
# Libraries included with source:
# - libnoise, noiseutils. These are built also.

CXX = g++

# repository root
REPO_ROOT = ../..

# Source root dir
SRC_ROOT = $(REPO_ROOT)/src

# Dependencies root dir
DEPS_ROOT = $(REPO_ROOT)/deps

# Dir where binary ends up
BIN_DIR = $(REPO_ROOT)/bin

# object files
OBJS = Action.o Ai.o Ammo.o AmmoParser.o Armor.o ArmorParser.o AStarSearcher.o BottomWindow.o Character.o Colors.o Combat.o ConsumableParser.o Container.o Creature.o CreatureParser.o DungeonArea.o Dungeon.o DungeonSpec.o DungeonTile.o Entity.o FactionParser.o Game.o Gui.o InventoryWindow.o Item.o ItemParser.o Location.o main.o Perk.o PerkParser.o RightMenuWindow.o Savefile.o Skills.o Special.o SpecialWindow.o StatsWindow.o Tile.o TileSet.o TileSetParser.o TopBarWindow.o Trait.o TraitParser.o Utils.o Visibility.o Weapon.o WeaponParser.o Window.o World.o WorldSpec.o WorldTile.o WorldWindow.o XmlParser.o 

LIBNOISE_SRC_DIR = $(DEPS_ROOT)/libnoisesrc-1.0.0/noise/src
LIBNOISE_SRCS = $(LIBNOISE_SRC_DIR)/noisegen.cpp $(LIBNOISE_SRC_DIR)/latlon.cpp $(LIBNOISE_SRC_DIR)/model/plane.cpp $(LIBNOISE_SRC_DIR)/model/sphere.cpp $(LIBNOISE_SRC_DIR)/model/cylinder.cpp $(LIBNOISE_SRC_DIR)/module/modulebase.cpp $(LIBNOISE_SRC_DIR)/module/perlin.cpp

LIBNOISE_OBJS = modulebase.o perlin.o cylinder.o plane.o sphere.o latlon.o noisegen.o 

# Compiler and linker flags
CFLAGS = -g -Wall -std=c++11 -D LINUX
LFLAGS = 

# Link against libraries
LIBS = -lm -lmenu -lncursesw -lxerces-c -lboost_random -lboost_serialization

# Target name
TARGET = for

# Additional includes
INCLUDES = -I$(SRC_ROOT) -I$(DEPS_ROOT)/noiseutils -I$(DEPS_ROOT)/libnoiseheaders-1.0.0/include -I$(DEPS_ROOT)/xerces-c-3.1.1/src

.PHONY: clean

all: $(TARGET)
	cp $(TARGET) $(BIN_DIR)

$(TARGET): $(OBJS) libnoise
	$(CXX) $(OBJS) $(LIBNOISE_OBJS) noiseutils.o -o $(TARGET) $(LFLAGS) $(LIBS) 

%.o: $(SRC_ROOT)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

noiseutils.o: $(DEPS_ROOT)/noiseutils/noiseutils.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

libnoise: $(LIBNOISE_SRCS)
	$(CXX) -c $(CFLAGS) $^

clean:
	rm -f *.o $(TARGET)   
