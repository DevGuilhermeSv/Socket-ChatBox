#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "mensagem.c"

//variavel global de string
char **STRING;
//defique o socket de comunicação
int skt;

void *servidor(void *thread);
int writing();

void *func_CLI(void *thread_CLI)
{
	int num = *(int *)thread_CLI;

	printf("Thread rodando %d \n", num);
	puts("chat disponivel");

	puts("mensagem a disparar");

	if (skt != 1)
	{

		writing();
	}
}
int writing()
{
	for (size_t i = 0; i < 1000; i++)
	{
		
		int _Write = write(skt, STRING[i], 5);
		if (_Write == -1)
		{
			puts("Error ao enviar");
		}
	}
	int _Write = write(skt, "-1", 5);

	puts("Enviado");
	//bzero(buffer_in, sizeof(buffer_in));

	return 0;
}
void *reading(void *threads)
{
	int num = *(int *)threads;
	char buffer_out[1000];
	while (1)
	{
		if ((read(skt, buffer_out, sizeof(buffer_out))) > 0)
		{

			puts(buffer_out);
			return 0;
		}
	}
}

int main(int argc, char const *argv[])
{
	STRING = randon();
	pthread_t thread_CLI, thread_read;
	pthread_t threads_server;

	int id = 1, id2 = 2;
	pthread_create(&threads_server, NULL, servidor, (void *)&id2);
	pthread_join(threads_server, NULL);
	pthread_create(&thread_CLI, NULL, func_CLI, (void *)&id);
	pthread_create(&thread_read, NULL, reading, (void *)&id);

	//pthread_create(&thread_CLI[1],NULL,func_comunicacao,(void*)&id[1]);

	pthread_join(thread_CLI, NULL);
	pthread_join(thread_read, NULL);

	return 0;
}

void *servidor(void *thread)
{
	puts("ok");

	// definindo o socket de comunicação tcp em ipv4
	int socket_com = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_com == -1)
	{
		printf("Erro na criacao do socket \n");
		return 0;
	}
	else
		printf("Sucesso!\n");
	// definição do bind para definição da estrutura de comunicação( portas e ip);
	struct sockaddr_in cliente;
	struct sockaddr_in server;

	cliente.sin_family = AF_INET;
	cliente.sin_addr.s_addr = INADDR_ANY;
	cliente.sin_port = htons(5555);

	while (connect(socket_com, (struct sockaddr *)&cliente, sizeof(cliente)) == -1)
	{
		perror("Erro ao conectar,aguardando servidor");
		sleep(2);
		skt = 1;
	}

	skt = socket_com;

	return 0;
}
