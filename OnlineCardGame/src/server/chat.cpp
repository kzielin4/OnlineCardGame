/**
 * Autor: Mateusz Skolimowski
 * 
 * W tym pliku beda znajdowac sie wszystkie funkcje ktore sluza do obslugi chatu od strony serwera.
 * 
 */
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "karta.h"
#include <iostream>
#include <time.h>
#include <cstring>
#include <pthread.h>
#include <string>
#include "game.h"
//#include <boost/thread/thread.hpp>

struct client_t
{
    int socket;
    pthread_mutex_t* mutex;
    char nick[50];
    int trybGracza;
    std::vector<karta> kartyGracza;
};


/*glowna funkcja obslugujaca chat*/
void chat(std::vector<struct client_t*> chatList,int numer)
{
	for(int i = 0 ; i < chatList.size() ; i++)
	{
		printf("[w%d]chatlist[%d].sock = %d\n",numer,i,chatList[i]->socket);
	}
}
