Character.o: Character.cpp Character.h Entity.h Object.h Level.h gba.h
Entity.o: Entity.cpp Entity.h Object.h Level.h
Level.o: Level.cpp Level.h Object.h gba.h
Object.o: Object.cpp Object.h
SpikeRow.o: SpikeRow.cpp SpikeRow.h Object.h
font.o: font.cpp font.h
gba.o: gba.cpp gba.h
main.o: main.cpp gba.h font.h sprite.h background.h Object.h Entity.h \
 Level.h Character.h
