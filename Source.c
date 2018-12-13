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
	char kategoria[51];
	char znacka[51];
	char predajca[101];
	int cena;
	int rok_vyroby;
	char stav_vozidla[201];
	struct zaznamy *next;
} Zaznam;

//funkcia nacita udaje zo suboru
Zaznam * funkcia_n(int *p_pocet_zaznamov, Zaznam *head, Zaznam *current) {
	//kontrola ci uz bol list vytvoreny, ak nie nacita zo suboru, ak ano, uvolni sa
	if (head == NULL) {
		char c;
		int i;
		//otvaranie a kontrola uspesneho otvorenia
		FILE *file_read1 = fopen("auta.txt", "r");
		if (!file_read1) {
			printf("Zaznamy neboli nacitane\n");
		}

		//zistenie poctu zaznamov a vypis
		while ((c = getc(file_read1)) != EOF) {
			if (c == '$') {
				(*p_pocet_zaznamov)++;
			}
		}
		printf("Nacitalo sa %d zaznamov\n", *p_pocet_zaznamov);
		fclose(file_read1);
		FILE *file_read2 = fopen("auta.txt", "r");
		if (!file_read2) {
			printf("Zaznamy neboli nacitane\n");
		}
		
		//postupne naplnenie structov
		Zaznam *temp = NULL;
		for (i = 0; i < *p_pocet_zaznamov + 1; i++) {
			current = (Zaznam *)malloc(sizeof(Zaznam));        //vytvorenie izolovaneho structu
			getc(file_read2);
			getc(file_read2);
			fgets(&current->kategoria, 50, file_read2);
			strtok(current->kategoria, "\n");
			fgets(&current->znacka, 50, file_read2);
			strtok(current->znacka, "\n");
			fgets(&current->predajca, 100, file_read2);
			strtok(current->predajca, "\n");
			fscanf(file_read2, "%d", &current->cena);
			getc(file_read2);
			fscanf(file_read2, "%d", &current->rok_vyroby);
			getc(file_read2);
			fgets(&current->stav_vozidla, 200, file_read2);
			strtok(current->stav_vozidla, "\n");

			current->next = NULL;

			if (head == NULL) {									
				head = current;									
			}													
			else {
				temp = head;
				while (temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = current;
			}
		}

		fclose(file_read2);
		return head;
	}
	else {
		Zaznam* temp;

		while (head != NULL) {
			temp = head;
			head = head->next;
			free(temp);
		}
		return head;
	}
}

//vypis poloziek
int funkcia_v(int *p_pocet_zaznamov, Zaznam *head) {
	int poradie_zaznam = 1;
	Zaznam *temp = head;
	if (temp != NULL) {
		while (temp->next != NULL) {
			printf("%d.\n", poradie_zaznam);
			printf("kategoria: %s\n", temp->kategoria);
			printf("znacka: %s\n", temp->znacka);
			printf("predajca: %s\n", temp->predajca);
			printf("cena: %d\n", temp->cena);
			printf("rok_vyroby: %d\n", temp->rok_vyroby);
			printf("stav_vozidla: %s\n", temp->stav_vozidla);
			poradie_zaznam++;
			temp = temp->next;
		}
	}
	return 0;
}

//pridava zaznam na zadanu poziciu
Zaznam * funkcia_p(int *p_pocet_zaznamov, Zaznam *head) {
	//nacitanie a kontrola ci je pozicia kladne cislo
	int pozicia, pocet_prvkov=0;
	scanf("%d", &pozicia);
	if (pozicia < 1) {
		return head;
	}
 
	char *added_kategoria;
	char *added_znacka;
	char *addeda_predajca;
	int added_cena;
	int added_rok_vyroby;
	char *added_stav_vozidla;

	//priadnie na zaciatok
	if (pozicia == 1) {
		//vytvorenie docasnej struktury a vlozenie udajov
		Zaznam *docasny = (Zaznam *)malloc(sizeof(Zaznam));
		*docasny->kategoria = scanf("%[^\n]\n", &added_kategoria);
		*docasny->znacka = scanf("%[^\n]\n", &added_znacka);
		*docasny->predajca = scanf("%[^\n]\n", &addeda_predajca);
		docasny->cena = scanf("%d", &added_cena);
		docasny->rok_vyroby = scanf("%d", &added_rok_vyroby);
		*docasny->stav_vozidla = scanf("%[^\n]\n", &added_stav_vozidla);

		//ulozenie docasneho na zaciatok spajaneho zoznamu
		docasny->next = head;
		head = docasny;
	}

	//pridanie na n-tu poziciu
	if (pozicia > 1) {
		while (1) {
			Zaznam *temp = head;
			if (temp != NULL) {
				while (temp->next != NULL) {
					pocet_prvkov++;	//pocet prvkov v zozname
					// ked najde spravnu poziciu
					if (pocet_prvkov == pozicia) {
						//vytvorenie docasnej struktury a vlozenie udajov
						Zaznam *docasny = (Zaznam *)malloc(sizeof(Zaznam));
						*docasny->kategoria = scanf("%[^\n]\n", &added_kategoria);
						*docasny->znacka = scanf("%[^\n]\n", &added_znacka);
						*docasny->predajca = scanf("%[^\n]\n", &addeda_predajca);
						docasny->cena = scanf("%d", &added_cena);
						docasny->rok_vyroby = scanf("%d", &added_rok_vyroby);
						*docasny->stav_vozidla = scanf("%[^\n]\n", &added_stav_vozidla);

						docasny->next = temp->next;
						temp->next = docasny;
					}

					//ked je cislo pozicie vacsie ako pocet prvkov v zozname, pridava novz prvok na koniec
					if (pocet_prvkov < pozicia) {
						//vytvorenie docasnej struktury a vlozenie udajov
						Zaznam *docasny = (Zaznam *)malloc(sizeof(Zaznam));
						*docasny->kategoria = scanf("%[^\n]\n", &added_kategoria);
						*docasny->znacka = scanf("%[^\n]\n", &added_znacka);
						*docasny->predajca = scanf("%[^\n]\n", &addeda_predajca);
						docasny->cena = scanf("%d", &added_cena);
						docasny->rok_vyroby = scanf("%d", &added_rok_vyroby);
						*docasny->stav_vozidla = scanf("%[^\n]\n", &added_stav_vozidla);

						//najdenie posledneho
						Zaznam *last = (Zaznam *)malloc(sizeof(Zaznam));
						while (last->next != NULL) {
							last = last->next;
						}
						//pridanie na posledne miesto;
						last->next = docasny;
					}
					temp = temp->next;
				}
			}
		}
	}


	return head;
}



//odstranuje podla znacky
Zaznam * funkcia_z(int *p_pocet_zaznamov, Zaznam *head) {
	int j = 0, pocet_vymazani = 0;
	char zadana_znacka[50];
	char upper_zadana_znacka[50];
	scanf("%s", &zadana_znacka);

	//zmena znakov zadanej znacky na velke pre nasledne porovnanie
	while (zadana_znacka[j - 1]) {
		upper_zadana_znacka[j] = toupper(zadana_znacka[j]);
		j++;
	}

	//ulozenie head, zmena znacky v head na velke pismena na porovnanie
	Zaznam * temp = head, *previous = NULL;
	while (temp->next != NULL) {
		int k = 0, vymazat = 0;
		char upper_temp_znacka[50];
		while (temp->znacka[k - 1]) {
			upper_temp_znacka[k] = toupper(temp->znacka[k]);
			k++;
		}
		//podmienka na vymazanie
		if (strstr(upper_temp_znacka, upper_zadana_znacka) != NULL) {
			pocet_vymazani++;
			if (temp == head) {
				head = head->next;
				free(temp);
			}
			
			previous = temp;
			temp = temp->next;
			previous->next = temp->next;
			free(temp); 
		}
		memset(upper_temp_znacka, 0, sizeof(upper_temp_znacka));
		temp = temp->next;
	}
	printf("Vymazalo sa %d zaznamov\n", pocet_vymazani);
	return head;
}

//vypise auta podla nazvu a ceny
int funkcia_h(int *p_pocet_zaznamov, Zaznam *head) {
	//nacita udaje
	char zadana_znacka[50];
	char upper_zadana_znacka[50];
	int zadana_cena, poradie = 1, j = 0;
	scanf("%s", zadana_znacka);
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
				printf("%d.\n", poradie);
				printf("kategoria: %s\n", temp->kategoria);
				printf("znacka: %s\n", temp->znacka);
				printf("predajca: %s\n", temp->predajca);
				printf("cena: %d\n", temp->cena);
				printf("rok_vyroby: %d\n", temp->rok_vyroby);
				printf("stav_vozidla: %s\n", temp->stav_vozidla);
				poradie++;
			}
			temp = temp->next;
		}
		if (poradie == 1)
			printf("V ponuke nie su pozadovane auta.\n");
	}
	return 0;
}

//aktualizuje cenu vozidla podla znacky a roku vyroby
int funkcia_a(int *p_pocet_zaznamov, Zaznam *head) {
	//nacitavanie udajov
	char zadana_znacka[50];
	char upper_zadana_znacka[50];
	int zadany_rok, j = 0, pocet_aktualizovanych = 0;
	scanf("%s", &zadana_znacka);
	scanf("%d", &zadany_rok);

	//zmena pismen na velke pre nasledne porovnanie
	while (zadana_znacka[j - 1]) {
		upper_zadana_znacka[j] = toupper(zadana_znacka[j]);
		j++;
	}

	//aktualizacia ceny
	Zaznam *temp = head;
	if (temp != NULL) {
		while (temp->next != NULL) {
			if ((zadany_rok == temp->rok_vyroby) && (strcasecmp(upper_zadana_znacka, temp->znacka) == 0)) {
				pocet_aktualizovanych++;
				temp->cena -= 100;

				if (temp->cena < 0)
					temp->cena == 0;
			}
			temp = temp->next;
		}
	}
	printf("Aktualizovalo sa %d zaznamov\n", pocet_aktualizovanych);
	return 1;
}

//uvolnenie celeho zoznamu
void funkcia_k(Zaznam *head) {
	Zaznam* temp;

	while (head != NULL){
		temp = head;
		head = head->next;
		free(temp);
	}
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
			funkcia_p(&pocet_zaznamov, head);
		else if (funkcia == 'z')
			funkcia_z(&pocet_zaznamov, head);
		else if (funkcia == 'h')
			funkcia_h(&pocet_zaznamov, head);
		else if (funkcia == 'a')
			funkcia_a(&pocet_zaznamov, head);
		else if (funkcia == 'k') {
			funkcia_k(head);
			break;
		}
	}
	return 0;
}
