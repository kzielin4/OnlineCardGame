/**
 * Autor: Mateusz Skolimowski
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
#include <time.h>

struct client_t
{
    int socket;
    pthread_mutex_t* mutex;
    char nick[50];
    int trybGracza;
    std::vector<karta> kartyGracza;
};

enum numerKarty numeryKart(int i);
enum typKarty typyKart(int j);
std::vector<karta> stworzVectorWszystkichKart();
std::vector<struct client_t*> rozlosujKarty(std::vector<struct client_t*> clientList,std::vector<karta> wszystkieKarty);
void wypiszKartyGraczy(std::vector<struct client_t*> clientList);

int game(std::vector<struct client_t*> clientList, int iloscGraczy)
{
	std::vector<karta> wszystkieKarty = stworzVectorWszystkichKart();
	clientList = rozlosujKarty(clientList,wszystkieKarty);
	wypiszKartyGraczy(clientList);
	while(1)
	{
        	for(int i=0;i<clientList.size();++i)
			write(clientList[i]->socket, "Rozpoczynamy gre\n",18 );
		sleep(1);
		for(int i=0;i<clientList.size();++i)
			write(clientList[i]->socket, "TEST\n",5 );
		sleep(1);
	}
}
enum typKarty typyKart(int j)
{
	switch (j)
	{
		case 0:
			return PIK;
		case 1:
			return TREFL;
		case 2:
			return KARO;
		case 3:
			return KIER;
	}
}

enum numerKarty numeryKart(int i)
{
	switch (i)
	{
		case 0:
			return DZIEWIATKA;
		case 1:
			return DZIESIATKA;
		case 2:
			return WALET;
		case 3:
			return DAMA;
		case 4:
			return KROL;
		case 5:
			return AS;
	}
}

std::vector<karta> stworzVectorWszystkichKart()
{
	std::vector<karta> v;
	for(int i = 0 ; i < 6 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
		{
			v.push_back(karta(typyKart(j),numeryKart(i)));
		}
	}
	return v;
}

std::vector<struct client_t*> rozlosujKarty(std::vector<struct client_t*> clientList,std::vector<karta> wszystkieKarty)
{
	srand(time(NULL));
	for(int i = 0 ; 0 < wszystkieKarty.size(); i++)
	{
		if (i%clientList.size() == 0)
			i = 0;
		int losowa = rand() % wszystkieKarty.size();
		clientList.at(i)->kartyGracza.push_back(karta(wszystkieKarty.at(losowa).getTyp(),wszystkieKarty.at(losowa).getNumer()));
		std::vector<karta>::iterator it;
		it = wszystkieKarty.begin();
		it += losowa;
		wszystkieKarty.erase(it);
	}
	return clientList;
}

void wypiszKartyGraczy(std::vector<struct client_t*> clientList)
{
	for(int i = 0 ; i < clientList.size() ; i++)
	{
		printf("karty gracza : %s\n",clientList[i]->nick);
		for(int j = 0 ; j < clientList[i]->kartyGracza.size(); j++)
		{
			printf("typ : %d , numer : %d\n",clientList[i]->kartyGracza[j].getTyp(),clientList[i]->kartyGracza[j].getNumer());
		}
	}
}
