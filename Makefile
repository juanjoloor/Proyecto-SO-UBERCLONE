DEPS = common.h
CFLAGS = -Wall -c

.PHONY: all debug sanitize clean
all: server client taxi clienteVIP clienteNVIP

server: server.o common.o $(DEPS)
	gcc -o $@ server.o common.o $(DFLAGS) -lpthread -lm

client: client.o common.o $(DEPS)
	gcc -o $@ client.o common.o $(DFLAGS) -lpthread

taxi: taxi.o 
	gcc -o $@ taxi.o -lm

clienteVIP: clienteVIP.o 
	gcc -o $@ clienteVIP.o	

clienteNVIP: clienteNVIP.o 
	gcc -o $@ clienteNVIP.o	

%.o: %.c $(DEPS)
	gcc $(CFLAGS) $< $(DFLAGS)

# Compila usando la opción -g para facilitar la depuración con gdb.
debug: DFLAGS = -g
debug: clean all

# Compila habilitando la herramienta AddressSanitizer para
# facilitar la depuración en tiempo de ejecución.
sanitize: DFLAGS = -fsanitize=address,undefined
sanitize: clean all

clean:
	rm -rf server client taxi clienteVIP clienteNVIP *.o
