#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>



//Alexia Jucalea --> Articolul Masaj

struct Masaj {

	float pret;
	char* denumire;
	int nrUleiuri;
	int* codUleiuri;

};

struct Masaj initializareMasaj(const char* denumire, float pret, int nrUleiuri, int* codUleiuri)
{
	struct Masaj m1;
	m1.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(m1.denumire, denumire);
	m1.pret = pret;
	m1.nrUleiuri = nrUleiuri;
	m1.codUleiuri = (int*)malloc(m1.nrUleiuri * sizeof(int));
	for (int i = 0; i < nrUleiuri; i++)
	{
		m1.codUleiuri[i] = codUleiuri[i];
	}
	return m1;
}


//calculeaza ceva pentru obiect
//sa se afiseze pretul mediu per ulei (pret masaj/nr uleiuri)
float pretMediuUleiuri(struct Masaj m)
{
	return m.pret / (float)m.nrUleiuri;
}

//modofica un camp al obiectului
void modificaPret(struct Masaj* m, float discount)
{
	if (discount > 0)
	{
		m->pret = m->pret * (1 - discount / 100.0);
		printf("\nNoul pret este: %5.2f", m->pret);
	}
}



void afiseazaMasaj(struct Masaj m)
{

	if (m.denumire != NULL)
		printf("Nume: %s\n", m.denumire);
	printf("Pret: %5.2f \n", m.pret);
	printf("Nr uleiuri: %2d\n", m.nrUleiuri);
	printf("Uleiuri: ");
	for (int i = 0; i < m.nrUleiuri; i++)
	{

		printf("%4d ", m.codUleiuri[i]);
	}
	printf("\n");
}


//afiseaza vector
void afiseazaVector(struct Masaj* masaje, int nrMasaje)
{
	for (int i = 0; i < nrMasaje; i++)
	{
		printf("\n");
		afiseazaMasaj(masaje[i]);
	}
}

//copiaza Nelemente
struct Masaj* copiazaNElemente(struct Masaj* masaje, int nrMasaje, int nrElementeCopiate) {
	if (nrElementeCopiate <= nrMasaje && nrElementeCopiate > 0)
	{
		struct Masaj* copy = (struct Masaj*)malloc(sizeof(struct Masaj) * nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++)
		{
			copy[i] = initializareMasaj(masaje[i].denumire, masaje[i].pret, masaje[i].nrUleiuri, masaje[i].codUleiuri);
		}
		return copy;
	}
	else return NULL;
}

struct Masaj* conditieNrMasaje(int nrMasaje, struct Masaj* masaje, int* dimNoua, int pragUleiuriNecesare) {
	*dimNoua = 0;
	for (int i = 0; i < nrMasaje; i++)
	{
		if (masaje[i].nrUleiuri >= pragUleiuriNecesare) (*dimNoua)++;
	}
	struct Masaj* vectorNou = (struct Masaj*)malloc(sizeof(struct Masaj) * (*dimNoua));
	int k = 0;
	for (int i = 0; i < nrMasaje; i++)
	{
		if (masaje[i].nrUleiuri >= pragUleiuriNecesare) {
			vectorNou[k] = initializareMasaj(masaje[i].denumire, masaje[i].pret, masaje[i].nrUleiuri, masaje[i].codUleiuri);
			k++;
		}
	}
	/*struct Masaj* vectorNou = NULL;
	int nr = 0;

	for (int i = 0; i < nrMasaje; i++) {
		if (masaje[i].nrUleiuri > 3) {
			nr++;
			vectorNou = realloc(vectorNou, nr * sizeof(struct Masaj));
			if (vectorNou == NULL) {
				printf("Eroare la realocarea memoriei.\n");
			}
			vectorNou[nr - 1] = masaje[i];
		}
	}*/

	return vectorNou;
}

//deazlocare vector 
void dezalocareVectorMasaje(struct Masaj** masaje, int* nrMasaje) {
	//de ce am trimis nr masaje prin adresa la seminar?
	for (int i = 0; i < *nrMasaje; i++)
	{
		free((*masaje)[i].denumire);
		free((*masaje)[i].codUleiuri);
	}
	free(*masaje);
	*nrMasaje = 0;
	*masaje = NULL;
}
//get obiect by conditie
struct Masaj getMasajByPrice(struct Masaj* masaje, int nrMasaje, float pret)
{
	for (int i = 0; i < nrMasaje; i++)
	{
		if (masaje[i].pret == pret) return initializareMasaj(masaje[i].denumire, masaje[i].pret, masaje[i].nrUleiuri, masaje[i].codUleiuri);
	}
	//returnam masaj default
	return initializareMasaj("-", 0.0, 0, NULL);
}

//Realizati o functie care concateneaza doi vectori.
//Scrieti intr - un program C functia care sa citeasca obiectele din fisier si sa le salveze intr - un vector.



//Scrieti o functie care va salva un obiect  intr - un fisier text.
void scrieMasajInFisier(char* file, struct Masaj masaj)
{
	FILE* fp = fopen(file, "a");
	if (fp == NULL)
	{
		printf("Eroare deschidere fisier %s", file);
		return -1;
	}
	else {
		fprintf(fp, "\n%-8s %5.2f %3d\n", masaj.denumire, masaj.pret, masaj.nrUleiuri);
		for (int i = 0; i < masaj.nrUleiuri; i++)
		{
			fprintf(fp, "%2d ", masaj.codUleiuri[i]);
		}
	}
	fclose(fp);
}


//Scrieti o functie care va salva un vector de obiecte intr - un fisier text.
void scrieVectorMasajeInFisier(char* file, struct Masaj* masaje, int nrMasaje)
{
	FILE* fp = fopen(file, "w");
	if (fp == NULL)
	{
		printf("Eroare deschidere fisier %s", file);
		return -1;
	}
	else {
		fprintf(fp, "%2d\n", 2 * nrMasaje);
		for (int i = 0; i < nrMasaje; i++)
		{
			scrieMasajInFisier(file, masaje[i]);
			scrieMasajInFisier(file, masaje[i]);
			//am apelat de 2 ori ca eu am vector de 5 elemente si ati spus sa fie 10 obiecte in fisier 
		}
	}
	fclose(fp);
}


void main()
{
	int* coduri = malloc(sizeof(int) * 3);
	coduri[0] = 100;
	coduri[1] = 101;
	coduri[2] = 102;
	struct Masaj m1 = initializareMasaj("MASAJ1", 100.0, 3, coduri);
	afiseazaMasaj(m1);
	printf("Pret mediu uleiuri:  %5.2f ", pretMediuUleiuri(m1));
	modificaPret(&m1, 10);
	free(coduri);
	int* coduri2 = malloc(sizeof(int) * 4);
	coduri2[0] = 200;
	coduri2[1] = 201;
	coduri2[2] = 202;
	coduri2[3] = 203;
	int* coduri3 = malloc(sizeof(int) * 3);
	coduri3[0] = 300;
	coduri3[1] = 301;
	coduri3[2] = 302;

	//vector obiecte de tip Masaj
	int nrMasaje = 5;
	struct Masaj* masaje = (struct Masaj*)malloc(sizeof(struct Masaj) * nrMasaje);
	masaje[0] = m1;
	masaje[1] = initializareMasaj("MASAJ2", 200, 4, coduri2);
	masaje[2] = initializareMasaj("MASAJ3", 300, 4, coduri2);
	masaje[3] = initializareMasaj("MASAJ4", 400, 4, coduri2);
	masaje[4] = initializareMasaj("MASAJ5", 500, 3, coduri3);
	printf("\n ------------------------VECTOR--------------------\n");
	afiseazaVector(masaje, nrMasaje);
	printf("\n ------------------------COPIEAZA N ELEMENTE--------------------\n");
	int nrMasajeCopiate = 2;
	struct Masaj* masajeCopiate = copiazaNElemente(masaje, 5, nrMasajeCopiate);
	afiseazaVector(masajeCopiate, nrMasajeCopiate);

	//functie creare vector care sa preia masajaele cu nrUleiuri mai mari decat 3
	printf("\n ------------------------CONDITIE--------------------\n");
	int nrMasajeScumpe = 0;
	struct Masaj* masajeConditie = conditieNrMasaje(5, masaje, &nrMasajeScumpe, 4);
	afiseazaVector(masajeConditie, nrMasajeScumpe);
	printf("\n ------------------------MASAJ CAUTAT--------------------\n");
	struct Masaj masajCautat = getMasajByPrice(masaje, nrMasaje, 90.0);
	afiseazaMasaj(masajCautat);

	//scrieMasajInFisier("data.txt", m1);
	//Creati un fisier in care sa aveti minim 10 obiecte de tipul structurii create.Asezarea in fisier a elementelor o faceti la libera alegere.
	scrieVectorMasajeInFisier("data.txt", masaje, nrMasaje);

	dezalocareVectorMasaje(&masajeCopiate, &nrMasajeCopiate);
	dezalocareVectorMasaje(&masajeConditie, &nrMasajeScumpe);
	dezalocareVectorMasaje(&masaje, &nrMasaje);
	free(coduri2);
	free(coduri3);
}