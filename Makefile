# CompilaciOn de los proyectos

# Banderas
CFLAGS = -std=gnu11 -Wall -Wextra -O3

todo: prueba_cajas prueba_easyin

prueba_cajas: prueba_cajas.o boxout.o box_list.o
	$(CC) -o $@ $? $(CFLAGS)

prueba_easyin: prueba_easyin.o easyin.o
	$(CC) -o $@ $? $(CFLAGS)

prueba_cajas.o: prueba_cajas.c
	$(CC) -c -o $@ $? $(CFLAGS)

boxout.o: Biblioteca_Cajas/boxout.c
	$(CC) -c -o $@ $? $(CFLAGS)


box_list.o: Biblioteca_Cajas/box_list.c
	$(CC) -c -o $@ $? $(CFLAGS)

prueba_easyin.o: prueba_easyin.c
	$(CC) -c -o $@ $? $(CFLAGS)

easyin.o: Biblioteca_Entrada/easyin.c
	$(CC) -c -o $@ $? $(CFLAGS)

clear:
	rm *.o prueba_cajas prueba_easyin
