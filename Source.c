//Samuel Rosolanka - Projekt 2 PrPr

//pre funkcnost strcasecmp() vo VisualStudio 2017
#ifdef _MSC_VER 
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//vytvorenie struct
typedef struct zaznamy {
	char kategoria[50];
	char znacka[50];
	char predajca[100];
	int cena;
	int rok_vyroby;
	char stav_vozidla[200];
	struct zaznamy *next;
} Zaznam;


Zaznam *funkcia_n(int *p_pocet_zaznamov, Zaznam *head, Zaznam *current) {
	char c;
	int i;
	//otvaranie a kontrola uspesneho otvorenia
	FILE *fr1 = fopen("auta.txt", "r");
	if (!fr1) {
		printf("Zaznamy neboli nacitane\n");
	}

	//zistenie poctu zaznamov a vypis
	while ((c = getc(fr1)) != EOF) {
		if (c == '$') {
			(*p_pocet_zaznamov)++;
		}
	}
	printf("Nacitalo sa %d zaznamov\n", *p_pocet_zaznamov);
	fclose(fr1);
	FILE *fr2 = fopen("auta.txt", "r");
	if (!fr2) {
		printf("Zaznamy neboli nacitane\n");
	}
	//postupne naplnenie structov

	Zaznam *temp = NULL;
	for (i = 0; i < *p_pocet_zaznamov+1; i++) {
		current = (Zaznam *)malloc(sizeof(Zaznam));        //vytvorenie izolovaneho structu
		getc(fr2);
		getc(fr2);
		fgets(&current->kategoria, 50, fr2);
		strtok(current->kategoria, "\n");
		//fscanf(fr2, "%s", &current->znacka);
		fgets(&current->znacka, 50, fr2);
		strtok(current->znacka, "\n");
		//getc(fr2);
		fgets(&current->predajca, 100, fr2);
		strtok(current->predajca, "\n");
		fscanf(fr2, "%d", &current->cena);
		getc(fr2);
		fscanf(fr2, "%d", &current->rok_vyroby);
		getc(fr2);
		fgets(&current->stav_vozidla, 200, fr2);
		strtok(current->stav_vozidla, "\n");

		current->next = NULL;

		if (head == NULL) {									//prepojenie s predchadzajucimi alebo
			head = current;									//ak je prazdny, tak vztvorenie prveho
		}													//tym prvym je potom current
		else {
			temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = current;
		}
	}

	fclose(fr2);
	return head;
}

//vypis poloziek
void funkcia_v(int *p_pocet_zaznamov, Zaznam *head) {
	int i = 1;
	Zaznam *temp = head;
	if (temp != NULL) {
		while (temp->next != NULL) {
			printf("%d.\n", i);
			printf("kategoria: %s\n", temp->kategoria);
			printf("znacka: %s\n", temp->znacka);
			printf("predajca: %s\n", temp->predajca);
			printf("cena: %d\n", temp->cena);
			printf("rok_vyroby: %d\n", temp->rok_vyroby);
			printf("stav_vozidla: %s\n", temp->stav_vozidla);
			i++;
			temp = temp->next;
		}
	}
}

void funkcia_p(int *p_pocet_zaznamov) {
	printf("som p\n");
}

void funkcia_z(int *p_pocet_zaznamov) {
	printf("som z\n");
}

//vypise auta podla nazvu a ceny
void funkcia_h(int *p_pocet_zaznamov, Zaznam *head) {
	//nacita udaje
	char zadana_znacka[50];
	char upper_zadana_znacka[50];
	int zadana_cena, i = 1, j = 0;
	scanf("%s", &zadana_znacka);
	scanf("%d", &zadana_cena);

	//zmena pismen na velke pre nasledne porovnanie
	while (zadana_znacka[j - 1]) {
		upper_zadana_znacka[j] = toupper(zadana_znacka[j]);
		j++;
	}

	//kontrola podmienok a vypis
	Zaznam *temp = head;
	if (temp != NULL) {
		while (temp->next != NULL) {
			if ((strcasecmp(upper_zadana_znacka, temp->znacka) == 0) && (zadana_cena >= temp->cena)) {
				printf("%d.\n", i);
				printf("kategoria: %s\n", temp->kategoria);
				printf("znacka: %s\n", temp->znacka);
				printf("predajca: %s\n", temp->predajca);
				printf("cena: %d\n", temp->cena);
				printf("rok_vyroby: %d\n", temp->rok_vyroby);
				printf("stav_vozidla: %s\n", temp->stav_vozidla);
				i++;
			}
			temp = temp->next;
		}
		if (i == 1)
			printf("V ponuke nie su pozadovane auta.\n");
	}
}

//aktualizyuje cenu vozidla podla znacky a roku vyroby
void funkcia_a(int *p_pocet_zaznamov, Zaznam *head) {
	//nacitavanie udajov
	char zadana_znacka[50];
	char upper_zadana_znacka[50];
	int zadany_rok, j = 0, i = 0;
	scanf("%s", &zadana_znacka);
	scanf("%d", &zadany_rok);
	printf("zadany rok: %d\n", zadany_rok);

	//zmena pismen na velke pre nasledne porovnanie
	while (zadana_znacka[j - 1]) {
		upper_zadana_znacka[j] = toupper(zadana_znacka[j]);
		j++;
	}

	Zaznam *temp = head;
	if (temp != NULL) {
		while (temp->next != NULL) {
			if ((zadany_rok == temp->rok_vyroby) && (strcasecmp(upper_zadana_znacka, temp->znacka) == 0)) {
				i++;
				temp->cena -= 100;

				if (temp->cena < 0)
					temp->cena == 0;
			}
			temp = temp->next;
		}
	}
	printf("Aktualizovalo sa %d zaznamov\n", i);
}

void funkcia_k() {
	printf("som k\n");
}

int main() {
	Zaznam *head, *current;
	head = current = NULL;
	char funkcia;
	int pocet_zaznamov = 0;
	int *p_pocet_zaznamov = &pocet_zaznamov;


	while (1) {
		scanf("%c", &funkcia);
		if (funkcia == 'n')
			head = funkcia_n(&pocet_zaznamov, head, current);
		else if (funkcia == 'v')
			funkcia_v(&pocet_zaznamov, head);
		else if (funkcia == 'p')
			funkcia_p(&pocet_zaznamov);
		else if (funkcia == 'z')
			funkcia_z(&pocet_zaznamov);
		else if (funkcia == 'h')
			funkcia_h(&pocet_zaznamov, &head);
		else if (funkcia == 'a')
			funkcia_a(&pocet_zaznamov, &head);
		else if (funkcia == 'k') {
			funkcia_k();
			break;
		}
	}
	return 0;
}
