#include <getopt.h>
#include <limits.h>
#include <sys/wait.h>

#include <pthread.h>
#include <syslog.h>
#include <fcntl.h>

#include "common.h"

void atender_cliente(int connfd);
void crearInformacion(const char *buffers, char *info);


void print_help(char *command)
{
	printf("Servidor simple de ejecución remota de comandos.\n");
	printf("uso:\n %s [-d] <puerto>\n", command);
	printf(" %s -h\n", command);
	printf("Opciones:\n");
	printf(" -h\t\t\tAyuda, muestra este mensaje\n");
	printf(" -d\t\t\tModo daemon\n");
	printf(" -j\t\t\tEspecifica el numero de worker threads");
}

/**
 * Función que crea argv separando una cadena de caracteres en
 * "tokens" delimitados por la cadena de caracteres delim.
 *
 * @param linea Cadena de caracteres a separar en tokens.
 * @param delim Cadena de caracteres a usar como delimitador.
 *
 * @return Puntero a argv en el heap, es necesario liberar esto después de uso.
 *	Retorna NULL si linea está vacía.
 */
char **parse_comando(char *linea, char *delim)
{ 
	char *token;
	char *linea_copy;
	int i, num_tokens = 0;
	char **argv = NULL;
	char *saveptr = NULL;

	linea_copy = (char *) malloc(strlen(linea) + 1);
	strcpy(linea_copy, linea);

	/* Obtiene un conteo del número de argumentos */
	token = strtok_r(linea_copy, delim, &saveptr);
	/* recorre todos los tokens */
	while( token != NULL ) {
		token = strtok_r(NULL, delim, &saveptr);
		num_tokens++;
	}
	free(linea_copy);

	/* Crea argv en el heap, extrae y copia los argumentos */
	if(num_tokens > 0){

		/* Crea el arreglo argv */
		argv = (char **) malloc((num_tokens + 1) * sizeof(char **));

		/* obtiene el primer token */
		token = strtok_r(linea, delim, &saveptr);
		/* recorre todos los tokens */
		for(i = 0; i < num_tokens; i++){
			argv[i] = (char *) malloc(strlen(token)+1);
			strcpy(argv[i], token);
			token = strtok_r(NULL, delim, &saveptr);
		}
		argv[i] = NULL;
	}

	return argv;
}

/**
 * Recibe SIGINT, termina ejecución
 */
void salir(int signal){
	printf("BYE\n");
	exit(0);
}

void *thread(void *vargp);
void *threadTaxi (void *vargp);
void *threadClientes (void *vargp);


bool dflag = false; //Opción -d, El programa es Daemon
bool jflag = false; 
void daemonize(char *nombre_programa)
{
	printf("Entrando modo daemon...\n");

	int fd0, fd1, fd2;
	pid_t pid;
	
	if ((pid = fork()) < 0){
		fprintf(stderr, "No es posible hacer un fork, error %s\n", strerror(errno));
		exit(1);
	}else if (pid != 0)
		exit(0);

	setsid();

	//Cerrar solamente stdout, stdin y stderr
	close(0);
	close(1);
	close(2);

	//se deben abrir otra vez, por que se podría abrir un archivo al stdout, stdin o stderr
	//y los printf van a enviar a ese archivo
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(fd0);
	fd2 = dup(fd0);

	//Abrir un log para este daemon en el sistema syslog
	openlog(nombre_programa, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d",
		fd0, fd1, fd2);
		exit(1);
	}
}

sbuf_t sbuf;

int main(int argc, char **argv)
{
	int opt, index;
	int NTHREADS = 10;
	//Sockets
	int listenfd;
	unsigned int clientlen;
	//Direcciones y puertos
	struct sockaddr_in clientaddr;
	char *port;

	while ((opt = getopt (argc, argv, "hdj")) != -1){
		switch(opt)
		{
			case 'h':
				print_help(argv[0]);
				return 0;
			case 'd':
				dflag = true;
				break;
			case 'j':
				jflag = true;
				break;	
			default:
				fprintf(stderr, "uso: %s [-d] <puerto>\n", argv[0]);
				fprintf(stderr, "	 %s -h\n", argv[0]);
				return 1;
		}
	}

	/* Recorre argumentos que no son opción */
	for (index = optind; index < argc; index++){
		port = argv[index];
		}
		printf("Grilla de %s x %s, espera de %s turnos antes de aumentar prioridad , %s segundos entre cada movimiento en la grilla , %s es la distancia maxima a un cliente para ser atendido por un taxi, %s clientes VIP, %s clientos NOVIP , %s taxis \n ",argv[1],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]);

		printf("numero de taxis : %d" , atoi(argv[7]));

		int totalclientes= atoi(argv[5]) + atoi(argv[6]);

	  	printf(" \n numero de clientes: %d \n",totalclientes);

		pthread_t ptTaxis;
		pthread_t ptClientes;

		int x=0;
		for (x = 0; x < atoi(argv[7]); x++){
			pthread_create(&ptTaxis, NULL, threadTaxi, NULL);
		}
		int y=0;
		for (y = 0; y < totalclientes; y++){
			pthread_create(&ptClientes, NULL, threadClientes, NULL);
		}



	if(argv == NULL){
		fprintf(stderr, "uso: %s [-d] <puerto>\n", argv[0]);
		fprintf(stderr, "	 %s -h\n", argv[0]);
		return 1;
	}

	//Valida el puerto
	int port_n = atoi(port);
	if(port_n <= 0 || port_n > USHRT_MAX){
		fprintf(stderr, "Puerto: %s invalido. Ingrese un número entre 1 y %d.\n", port, USHRT_MAX);
		return 1;
	}

	//Registra funcion para señal SIGINT (Ctrl-C)
	signal(SIGINT, salir);

	//Abre un socket de escucha en port
	sbuf_init(&sbuf,NTHREADS);
	listenfd = open_listenfd(port);

	if(listenfd < 0)
		connection_error(listenfd);


	if(dflag)
		daemonize(argv[0]);

	int connfd;
	pthread_t tid;


	if(jflag)
		NTHREADS=atoi(argv[index-2]);
	int i=0;
	for (i = 0; i < NTHREADS; i++)
		pthread_create(&tid, NULL, thread, NULL);

	while (1) {
		clientlen=sizeof(clientaddr);
		connfd= accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		sbuf_insert(&sbuf, connfd);
	}
}

/*
 * thread - En un nuevo hilo atiende al cliente. 
 */
void *thread(void *vargp){
	
	pthread_detach(pthread_self());
	while (1)
	{
		int connfd = sbuf_remove(&sbuf);
		atender_cliente(connfd);
		close(connfd);
	
	}
}

void* threadTaxi( void * vargp){
		
			printf("\n hilo taxi corriendo \n");
			return NULL;

}

void* threadClientes( void * vargp){
			printf("\n hilo cliente corriendo \n");
			return NULL;

}


void atender_cliente(int connfd)
{
	int n;
	char buf[MAXLINE] = {0};
	


	//Comunicación con cliente es delimitada con '\0'
	while(1){

		
     
		n = read(connfd, buf, MAXLINE);
	
		if(n <= 0)
			return;
		printf("Recibido: %s", buf);
		//Detecta "CHAO" y se desconecta del cliente
		if(strcmp(buf, "CHAO\n") == 0){
			write(connfd, "BYE\n", 5);
			return;
		}

		write(connfd, "Comunicandome con el server \n", 30);

		

		memset(buf, 0, MAXLINE); //Encera el buffer
	}
}
