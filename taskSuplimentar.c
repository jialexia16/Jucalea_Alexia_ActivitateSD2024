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



void afiseazaMasaj(struct Masaj* m)
{

	if (m->denumire != NULL)
		printf("Nume: %s\n", m->denumire);
	printf("Pret: %5.2f \n", m->pret);
	printf("Nr uleiuri: %2d\n", m->nrUleiuri);
	printf("Uleiuri: ");
	for (int i = 0; i < m->nrUleiuri; i++)
	{

		printf("%4d ", m->codUleiuri[i]);
	}
	printf("\n");
}

//Creati in functia main un vector alocat dinamic cu cel putin 5 obiecte de tipul structurii voastre.
// functie care va creea un nou vector în care va copia dintr-un vector primit ca parametru obiectele care indeplinesc o anumita conditie
// functie care muta intr-un nou vector obiectele care indeplinesc o alta conditie fata de cerinta precedenta
//Realizati o functie care concateneaza doi vectori.
//Realizati o functie care afiseaza un vector cu obiecte.

struct Masaj* conditieNrMasaje(int nrMasaje, struct Masaj* masaje) {
	struct Masaj* vectorNou = NULL;
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
	}

	return vectorNou;
}




void main()
{
	int* coduri = malloc(sizeof(int) * 3);
	coduri[0] = 100;
	coduri[1] = 101;
	coduri[2] = 102;
	struct Masaj m1 = initializareMasaj("MASAJ1", 100.0, 3, coduri);
	afiseazaMasaj(&m1);
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
	struct Masaj* masaje = malloc(sizeof(struct Masaj) * 5);
	masaje[0] = m1;
	masaje[1] = initializareMasaj("MASAJ3", 300, 4, coduri2);
	masaje[2] = initializareMasaj("MASAJ3", 300, 4, coduri2);
	masaje[3] = initializareMasaj("MASAJ4", 400, 4, coduri2);
	masaje[4] = initializareMasaj("MASAJ5", 500, 3, coduri3);


	//functie creare vector care sa preia masajaele cu nrUleiuri mai mari decat 3
	printf("\n ------------------------CONDITIE--------------------\n");
	struct Masaj* masajeConditie = malloc(sizeof(conditieNrMasaje(5, masaje)));
	masajeConditie = conditieNrMasaje(5, masaje);
	for (int i = 0; i < 2; i++)
	{
		afiseazaMasaj(&masajeConditie[i]);
	}
	free(coduri2);
	free(coduri3);
}