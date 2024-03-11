#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Masina
{
	int id;
	char* producator;
	int nrUsi;
	float pret;
};


struct Masina initializareMasina(int id, char* producator, int nrUsi, float pret)
{
	struct Masina m;
	m.id = id;
	m.producator = malloc(strlen(producator) + 1);
	strcpy(m.producator, producator);
	m.pret = pret;
	return m;
}


struct Masina* adaugareVector(struct Masina* masini, struct Masina m, int* nrMasini)
{

	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < (*nrMasini); i++)
	{
		//aux[i] = initializareMasina(masini[i].id, masini[i].producator, masini[i].nrUsi, masini[i].pret);
		aux[i] = masini[i];
	}
	aux[*nrMasini] = m;
	(*nrMasini)++;
	if (masini != NULL)
	{
		free(masini);
	}
	return aux;

}

struct Masina* citesteMasini(const char* file, int* nrMasini)
{
	FILE* f = fopen(file, "r");
	char linie[100];
	char del[] = ",\n";
	struct Masina* masini = NULL;
	*nrMasini = 0;
	while (fgets(linie, 100, f) != NULL)
	{
		struct Masina m;
		char* token = strtok(linie, del);
		m.id = atoi(token);
		token = strtok(NULL, del);
		m.producator = malloc(strlen(token) + 1);
		strcpy(m.producator, token);
		token = strtok(NULL, del);
		m.nrUsi = atoi(token);
		token = strtok(NULL, del);
		m.pret = atoi(token);
		masini = adaugareVector(masini, m, nrMasini);
	}
	return masini;
}

void afisareMasina(struct Masina m)
{
	printf("ID: %2d\n", m.id);
	printf("Producator: %-10s\n", m.producator);
	printf("Nr usi: %2d\n", m.nrUsi);
	printf("Pret: %5.2f\n", m.pret);
}

void afisareVector(struct Masina* masini, int nrMasini)
{
	for (int i = 0; i < nrMasini; i++)
	{
		printf("\n");
		afisareMasina(masini[i]);
	}
}

void main() {
	int nrMasini = 0;
	struct Masina* masini = citesteMasini("masini.txt", &nrMasini);
	afisareVector(masini, nrMasini);
}
