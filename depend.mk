Character.o: Character.cpp Character.h Entity.h Object.h gba.h Level.h
Entity.o: Entity.cpp Level.h Object.h Entity.h Character.h gba.h
Level.o: Level.cpp Level.h Object.h Entity.h Character.h gba.h
Object.o: Object.cpp Object.h
font.o: font.cpp font.h
gba.o: gba.cpp gba.h
main.o: main.cpp gba.h font.h sprite.h background.h Object.h Entity.h \
 Character.h Level.h
