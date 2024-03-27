#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>


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
		printf("\n\nNume: %s\n", m.denumire);
	printf("Pret: %5.2f \n", m.pret);
	printf("Nr uleiuri: %2d\n", m.nrUleiuri);
	printf("Uleiuri: ");
	for (int i = 0; i < m.nrUleiuri; i++)
	{

		printf("%4d ", m.codUleiuri[i]);
	}
	printf("\n");
}

void afiseazaMasajPeOLinie(struct Masaj m)
{

	if (m.denumire != NULL)
		printf("\nNume: %s", m.denumire);
	printf("  Pret: %5.2f", m.pret);
	printf("  Nr uleiuri: %2d", m.nrUleiuri);
	printf("  Uleiuri: ");
	for (int i = 0; i < m.nrUleiuri; i++)
	{

		printf("%4d ", m.codUleiuri[i]);
	}
	//printf("\n");
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
		fprintf(fp, "%s,%.2f,%d", masaj.denumire, masaj.pret, masaj.nrUleiuri);
		for (int i = 0; i < masaj.nrUleiuri; i++)
		{
			fprintf(fp, ",%2d", masaj.codUleiuri[i]);
		}
		fprintf(fp, "\n");
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
		printf("\nAm scris in fisier!\n");
		for (int i = 0; i < nrMasaje; i++)
		{
			scrieMasajInFisier(file, masaje[i]);
			scrieMasajInFisier(file, masaje[i]);
			//am apelat de 2 ori ca eu am vector de 5 elemente si ati spus sa fie 10 obiecte in fisier 
		}
	}
	fclose(fp);
}

struct Masaj* adaugaVector(struct Masaj* masaje, struct Masaj m, int* nrMasaje)
{
	struct Masaj* aux = (struct Masaj*)malloc(sizeof(struct Masaj) * ((*nrMasaje) + 1));
	if (aux == NULL)
	{
		printf("Eroare la alocarea memoriei!");
		return NULL;
	}
	for (int i = 0; i < (*nrMasaje); i++)
	{
		aux[i] = masaje[i];
	}
	aux[(*nrMasaje)] = m;
	(*nrMasaje)++;
	if (masaje != NULL)
	{
		free(masaje);
	}
	return aux;
}

//Scrieti intr - un program C functia care sa citeasca obiectele din fisier si sa le salveze intr - un vector.
struct Masaj* citesteMasaje(char* file, int* nrMasaje)
{
	FILE* f = fopen(file, "r");
	char linie[100];
	struct Masaj* masaje = NULL;
	//struct Masaj* masaje = (struct Masaj*)malloc(sizeof(struct Masaj) * 10);
	*nrMasaje = 0;
	char del[] = ",\n";
	while (fgets(linie, sizeof(linie), f) != NULL)
	{
		struct Masaj m;
		char* token = strtok(linie, del);
		m.denumire = malloc(strlen(token) + 1);
		strcpy(m.denumire, token);
		token = strtok(NULL, del);
		m.pret = atof(token);
		token = strtok(NULL, del);
		m.nrUleiuri = atoi(token);
		m.codUleiuri = malloc(sizeof(int) * m.nrUleiuri);
		for (int i = 0; i < m.nrUleiuri; i++)
		{
			token = strtok(NULL, del);
			m.codUleiuri[i] = atoi(token);
		}
		masaje = adaugaVector(masaje, m, nrMasaje);
		//masaje[*nrMasaje] = m;
		//(*nrMasaje)++;
	}
	fclose(f);
	return masaje;
}


//Creati o functie care sa copieze (deep copy) elementele din vector intr o matrice alocata dinamic
struct Masaj** copiazaElementeMatrice(struct Masaj* masaje, int nrMasaje, int nrLinii, int* nrColoane)
{
	struct Masaj** matrice = (struct Masaj**)malloc(sizeof(struct Masaj*) * nrLinii);
	for (int i = 0; i < nrLinii; i++)
	{
		nrColoane[i] = 0;
		matrice[i] = NULL;
	}

	for (int i = 0; i < nrMasaje; i++)
	{
		matrice[masaje[i].nrUleiuri - 3] = adaugaVector(matrice[masaje[i].nrUleiuri - 3], masaje[i], &(nrColoane[masaje[i].nrUleiuri - 3]));
	}
	return matrice;
}
//Scrieti o functie care muta liniile din matrice, astfel incat acestea sa fie sortate
//  dupa numarul de elemente de pe linie.


//Scrieti o functie care sa afiseze elementele dintr  o matrice.
void afiseazaMatrice(struct Masaj** matrice, int nrLinii, int* nrColoane)
{
	for (int i = 0; i < nrLinii; i++)
	{
		printf("\nLinia %d", i + 1);
		printf("\nColoane: %d", nrColoane[i]);
		for (int j = 0; j < nrColoane[i]; j++)
		{
			afiseazaMasajPeOLinie(matrice[i][j]);
			printf("\n");

		}
		printf("\n\n");
	}
}


//Obiectele pe care le cititi dintr-un fisier le salvati intr-o lista simplu inlantuita.
//struct Nod{
//	struct Masaj m;
//	struct Nod* nexAt;
//}Nod;
//
//void salvareLista(struct Nod** p)
//
//{
//	struct Nod* u = NULL;
//	int n;
//	struct Masaj* masaje = citesteMasaje("date.txt", &n);
//	printf("\n\nnt masaje citite %d:", n);
//	for (int i = 0; i < n; i++)
//	{
//		adaugaInLista(masaje[i], p, &u);
//	}
//}
//
//void adaugaInLista(struct Masaj m, struct Nod**p, struct Nod*u) 
//{
//	struct Nod* c = malloc(sizeof(struct Nod));
//	c->m = m;
//	c->next = NULL;
//	if (p == NULL)
//	{
//		p = c;
//	}
//	else { u->next = c; }
//	u = c;
//}
//
//void afiseazaLista(struct Nod *p) {
//	struct Nod* c;
//	c = p;
//	while (c)
//	{
//		afiseazaMasaj(c->m);
//		c = c->next;
//	}
//	printf("\n");
//}


struct elem {
	struct Masaj m;
	struct elem* urm;
};

struct Lista {
	struct elem* prim;
	struct elem* ultim;
};

//creare element nou
struct elem* nou(struct Masaj m, struct elem* urm)
{
	struct elem* e = (struct elem*)malloc(sizeof(struct elem));
	if (!e)
	{
		printf("\nMemorie insuficenta.");
		exit(1);
	}
	e->m = m;
	e->urm = urm;
	return e;
}

//adauga element in lista
//struct elem* adaugaInceput(struct Lista* lista, struct Masaj m)
//{
//	struct elem* e = nou(m, lista->prim);
//	lista->prim = e;
//	if (!lista->ultim)
//	{
//		lista->ultim = e;
//	}
//}
//
//struct elem* adaugaSfarsit(struct Lista* lista, struct Masaj m)
//{
//	struct elem* e = nou(m, NULL);
//	if (!lista->ultim)
//	{
//		lista->ultim = lista->prim = e;
//	}
//	else {
//		lista->ultim->urm = e;
//		lista->ultim = e;
//	}
//}
//
//struct elem* preiaElementeInLista(struct Lista* lista, struct Masaj* masaje, int nrMasaje)
//{
//	for (int i = 0; i < nrMasaje; i++)
//	{
//		adaugaInceput(lista, masaje[i]);
//	}
//	return lista->prim;
//}
//
//void afiseazaLista(struct Lista* lista)
//{
//	struct elem* p;
//	for (p = lista->prim; p; p = p->urm)
//	{
//		afiseazaMasaj(p->m);
//	}
//}

// varianta de lista simplu inlantuita
typedef struct Nod Nod;
struct Nod {
	struct Masaj masaj;
	Nod* next;
};

void inserareInceput(struct Masaj m, Nod** lista)
{
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->masaj = m;
	nod->next = (*lista);
	*lista = nod;
}

void insereazaSfarsit(struct Masaj m, Nod** lista)
{
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->masaj = m;
	nod->next = NULL;

	if (*lista == NULL)
	{
		*lista = nod;
	}
	else
	{
		Nod* n = *lista;
		while (n->next != NULL)
		{
			n = n->next;
		}
		n->next = nod;
	}
}

struct Nod* preiaElementeInLista(struct Nod* lista, struct Masaj* masaje, int nrMasaje)
{
	for (int i = 0; i < nrMasaje; i++)
	{
		inserareInceput(masaje[i], &lista);
	}
	return lista;
}

void afiseazaLista(Nod* lista)
{
	while (lista != NULL)
	{
		afiseazaMasajPeOLinie(lista->masaj);
		lista = lista->next;
	}
}


//stergere lista
void stergereLista(Nod** lista)
{
	while (*lista != NULL)
	{
		free((*lista)->masaj.denumire);
		free((*lista)->masaj.codUleiuri);
		Nod* aux = (*lista)->next;
		free(*lista);
		*lista = aux;
	}
}

//1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru. Daca lista are mai putine noduri decat index-ul dat, nu se realizeaza stergerea.
int stergereNodIndex(Nod** lista, int index)
{
	int k = 1;
	Nod* temp, * prev = NULL;

	if (index <= 0) {
		printf("Am vrut sa sterg nod de pe pozitia invalida.\n");
		return -1;
	}

	if (*lista == NULL) {
		printf("Lista este goala.\n");
		return -1;
	}

	if (index == 1)
	{
		temp = *lista;
		*lista = temp->next;
		free(temp);
		return 1;
	}
	else {
		temp = *lista;
		while (temp != NULL && k != index)
		{
			prev = temp;
			temp = temp->next;
			k++;
		}
		if (temp == NULL) {
			printf("Am vrut sa sterg nod de pe pozitia %d care nu exista.\n", index);
			return -1;
		}
		else
		{
			if (temp->next == NULL)
			{
				prev->next = NULL;
				free(temp);
			}
			else
			{
				prev->next = temp->next;
				free(temp);
			}

			return index;
		}
	}
}

//2. Implementati o functie care sa insereze elementele in cadrul listei simplu inlantuite astfel incat acestea a fie sortate crescator dupa un camp la alegerea voastra.
void inserezaCrescatorDupaPret(Nod** lista, struct Masaj m)
{
	Nod* nod = *lista;
	Nod* prev = NULL;
	Nod* nodAdaugat = (Nod*)malloc(sizeof(Nod));
	nodAdaugat->masaj = initializareMasaj(m.denumire, m.pret, m.nrUleiuri, m.codUleiuri);
	nodAdaugat->next = NULL;
	if (*lista == NULL)
	{
		*lista = nodAdaugat;
		return;
	}
	while (nod != NULL && m.pret > nod->masaj.pret)
	{
		prev = nod;
		nod = nod->next;
	}
	if (prev == NULL)
	{
		nodAdaugat->next = *lista;
		*lista = nodAdaugat;
	}
	else {
		prev->next = nodAdaugat;
		nodAdaugat->next = nod;

	}
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

	//scrieMasajInFisier("date.txt", m1);
	//Creati un fisier in care sa aveti minim 10 obiecte de tipul structurii create.Asezarea in fisier a elementelor o faceti la libera alegere.
	scrieVectorMasajeInFisier("date.txt", masaje, nrMasaje);

	printf("\n ------------------------MASAJE FISIER--------------------\n");

	int nrMasajeFisier = 0;
	printf("nr masaje citite: %d", nrMasajeFisier);
	// struct Masaj* masajeFisier = (struct Masaj*)malloc(sizeof(citesteMasaje("data.txt", &nrMasajeFisier)));
	struct Masaj* masajeFisier = citesteMasaje("date.txt", &nrMasajeFisier);
	printf("\n\nnr masaje citite: %d", nrMasajeFisier);
	afiseazaVector(masajeFisier, nrMasajeFisier);

	printf("\n ------------------------MATRICE--------------------\n");
	int nrLinii = 2;
	int* nrColoane = (int*)malloc(sizeof(int) * nrLinii);
	struct Masaj** matrice = (struct Masaj**)malloc(sizeof(struct Masaj*) * nrLinii);
	matrice = copiazaElementeMatrice(masajeFisier, nrMasajeFisier, nrLinii, nrColoane);
	afiseazaMatrice(matrice, nrLinii, nrColoane);


	printf("\n ------------------------LISTA SIMPLU INLANTUITA--------------------\n");
	//struct Lista lista;
	//lista.prim = lista.ultim = NULL;
	//lista.prim=preiaElementeInLista(&lista, masaje, nrMasaje);
	//afiseazaLista(&lista);
	Nod* lista = NULL;
	lista = preiaElementeInLista(lista, masaje, nrMasaje);
	insereazaSfarsit(masaje[0], &lista);
	afiseazaLista(lista);
	//stergereLista(&lista);
	//afiseazaLista(lista);
	printf("\nAm vrut sa sterg nod de pe pozitia %d", stergereNodIndex(&lista, 6));
	afiseazaLista(lista);

	printf("\n ------------------------LISTA SIMPLU INLANTUITA ORDONATA--------------------\n");
	Nod* listaOrdonata = NULL;
	inserezaCrescatorDupaPret(&listaOrdonata, masaje[0]);
	inserezaCrescatorDupaPret(&listaOrdonata, masaje[4]);
	inserezaCrescatorDupaPret(&listaOrdonata, masaje[2]);
	inserezaCrescatorDupaPret(&listaOrdonata, masaje[1]);
	inserezaCrescatorDupaPret(&listaOrdonata, masaje[3]);
	afiseazaLista(listaOrdonata);

	dezalocareVectorMasaje(&masajeFisier, &nrMasajeFisier);
	dezalocareVectorMasaje(&masajeCopiate, &nrMasajeCopiate);
	dezalocareVectorMasaje(&masajeConditie, &nrMasajeScumpe);
	dezalocareVectorMasaje(&masaje, &nrMasaje);
	free(coduri2);
	free(coduri3);
	printf("\n----------------------------------------------------------------");

}
