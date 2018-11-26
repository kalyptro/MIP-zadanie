//Samuel Rosolanka - Projekt 2 PrPr

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//vytvorenie struct
typedef struct zaznamy{
	char kategoria[50];
	char znak[50];
	char predajca[50];
	int cena;
	int rok_vyroby;
	char stav_vozidla[200];
	struct zaznamy *next;
} ZAZNAM;

ZAZNAM *funkcia_n(int *p_pocet_zaznamov, ZAZNAM *head, ZAZNAM *current) {
	printf("som n\n");
	char c;
	//ZAZNAM *temp = NULL;
	//otvaranie a kontrola uspesneho otvorenia
	FILE *fr = fopen("C:\\Users\\samue\\OneDrive\\Desktop\\Projekt 2 PrPr\\Projekt 2\\Projekt 2\\auta.txt", "r");
	if (!fr) {
		printf("Zaznamt neboli nacitane\n");
	}
	
	//zistenie poctu zaznamov a vypis
	while ((c = getc(fr)) != EOF) {
		if (c == '$') {
			(*p_pocet_zaznamov)++;
		}
	}
	printf("Nacitalo sa %d zaznamov\n", *p_pocet_zaznamov);

	//postupne naplnenie structov
	ZAZNAM *temp;
	for (int i = 0; i < *p_pocet_zaznamov; i++) {

		current = (ZAZNAM *)malloc(sizeof(ZAZNAM));        //vytvorenie izolovaneho structu
		//getc(fr);
		//getc(fr);
		//fgets(&(current->kategoria), 51, fr);
		strcpy(current->kategoria, "wuhu");

		current->next = NULL;

		if (head == NULL) {									//prepojenie s predchadzajucimi alebo
			head = current;									//ak je prazdny, tak vztvorenie prveho
		}
		else {
			temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = current;

		}
		

		/*fgets();
		strtok(, "\n");
		fscanf(fr, "%s", pole_zaznamov[i].pohlavie);
		fscanf(fr, "%s", pole_zaznamov[i].rok);
		fscanf(fr, "%s", pole_zaznamov[i].spz);
		fscanf(fr, "%s", pole_zaznamov[i].priestupok);
		fscanf(fr, "%s", pole_zaznamov[i].pokuta);
		fscanf(fr, "%s", pole_zaznamov[i].datum);
		//getc(fr);
		//getc(fr);*/

	}
	//current->next = NULL;
	temp = head;
	while (temp->next != NULL) {
		printf("kategoria: %s\n", temp->kategoria);
		temp = temp->next;
	}
	

	/*for (current = head; current; current = current->next) {
		printf("znacka: %s\n", current->kategoria);
	}*/

	fclose(fr);
	return head;
}

void funkcia_v(int *p_pocet_zaznamov) {
	printf("som v\n");
}

void funkcia_p(int *p_pocet_zaznamov) {
	printf("som p\n");
}

void funkcia_z(int *p_pocet_zaznamov) {
	printf("som z\n");
}

void funkcia_h(int *p_pocet_zaznamov) {
	printf("som h\n");
}

void funkcia_a(int *p_pocet_zaznamov) {
	printf("som a\n");
}

void funkcia_k() {
	printf("som k\n");
}

int main() {
	ZAZNAM *head, *current;
	head = current = NULL;  
	char funkcia;
	int pocet_zaznamov = 0;
	int *p_pocet_zaznamov = &pocet_zaznamov;

	while(1) {
		scanf("%c", &funkcia);
		if (funkcia == 'n')
			head = funkcia_n(&pocet_zaznamov, &head, &current);
		else if (funkcia == 'v')
			funkcia_v(&pocet_zaznamov);
		else if (funkcia == 'p')
			funkcia_p(&pocet_zaznamov);
		else if (funkcia == 'z')
			funkcia_z(&pocet_zaznamov);
		else if (funkcia == 'h')
			funkcia_h(&pocet_zaznamov);
		else if (funkcia == 'a')
			funkcia_a(&pocet_zaznamov);
		else if (funkcia == 'k') {
			funkcia_k();
			break;
		}
	}



	return 0;
}