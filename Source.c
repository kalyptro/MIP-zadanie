#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct zaznamy{
	char kategoria[50];
	char znak[50];
	char predajca[50];
	int cena;
	int rok_vyroby;
	char stav_vozidla[200];
	struct zaznamy *next;
} ZAZNAM;

int main() {


	return 0;
}