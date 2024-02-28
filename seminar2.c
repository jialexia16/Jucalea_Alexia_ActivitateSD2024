#include <stdio.h>
#include <malloc.h>

struct Farmacie {
	int id;
	char* nume;
	float suprafata;
};


struct Farmacie initializareFarmacie(int id, char* nume, float suprafata)
{
	struct Farmacie f;
	f.id = id;
	f.nume = (char*)malloc(sizeof(char*) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.suprafata = suprafata;
	return f;
}

void afiseazaFarmacie(struct Farmacie f)
{
	printf("%d. %s are o suprafata de %5.2f \n", f.id, f.nume, f.suprafata);
}

void afiseazaVector(struct Farmacie* farmacii, int nrFarmacii)
{

	//printf("%5.2f", (float)sizeof(farmacii));
	for (int i = 0; i < nrFarmacii; i++)
	{
		afiseazaFarmacie(farmacii[i]);
	}
}

struct Farmacie* copieazaNElemente(struct Farmacie* vector, int nrFarmacii, int nrObjCopiat)
{
	if (nrObjCopiat <= nrFarmacii && nrObjCopiat > 0)
	{
		struct Farmacie* copiat = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrObjCopiat);
		for (int i = 0; i < nrObjCopiat; i++)
		{
			copiat[i] = initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);

		}
		return copiat;
	}
	else {
		return NULL;
	}
}


struct Farmacie* copiazaFarmaciiMici(struct Farmacie* farmacii, int nrFarmacii, float pragSuprafata, int* dimNoua) {
	*dimNoua = 0;
	for (int i = 0; i < nrFarmacii; i++)
	{
		if (farmacii[i].suprafata < pragSuprafata) (*dimNoua)++;
	}

	struct Farmacie* vector = (struct Farmacie*)malloc(sizeof(struct Farmacie) * (*dimNoua));
	int k = 0;
	for (int i = 0; i < nrFarmacii; i++)
	{
		if (farmacii[i].suprafata < pragSuprafata) {
			vector[k++] = initializareFarmacie(farmacii[i].id, farmacii[i].nume, farmacii[i].suprafata);
		}
	}
	return vector;
}


void dezalocareVectorFarmacii(struct Farmacie** vector, int* nrFarmacii)
{
	for (int i = 0; i < *nrFarmacii; i++)
	{
		free((*vector)[i].nume);
	}
	free(*vector);
	*nrFarmacii = 0;
	*vector = NULL;
}


struct Farmacie getFarmacieByID(struct Farmacie* vector, int nrFarmacii, int ID)
{
	for (int i = 0; i < nrFarmacii; i++)
	{
		if (vector[i].id == ID) return initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
	}

	//returnam farmacie default
	return initializareFarmacie(0, "N/A", 0);
}



int main() {
	//int v[40];
	int nrFarmacii = 4;
	struct Farmacie* farmacii = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrFarmacii);
	for (int i = 0; i < nrFarmacii; i++)
	{
		farmacii[i] = initializareFarmacie(i + 1, "Farmacie", 30 * i + 10);
	}

	afiseazaVector(farmacii, nrFarmacii);
	int nrFarmaciiCopiate = 2;
	printf("\n\n");
	struct Farmacie* farmaciiCopiate = copieazaNElemente(farmacii, nrFarmacii, nrFarmaciiCopiate);
	afiseazaVector(farmaciiCopiate, nrFarmaciiCopiate);
	printf("\n\n");
	int nrFarmaciiMici = 0;

	farmacii[3].suprafata = 20;
	struct Farmacie* farmaciiMici = copiazaFarmaciiMici(farmacii, nrFarmacii, 50, &nrFarmaciiMici);
	afiseazaVector(farmaciiMici, nrFarmaciiMici);
	printf("\n----------------------\n");
	struct Farmacie f = getFarmacieByID(farmacii, nrFarmacii, 7);
	afiseazaFarmacie(f);
	printf("\n----------------------\n");
	free(f.nume);

	dezalocareVectorFarmacii(&farmacii, &nrFarmacii);
	dezalocareVectorFarmacii(&farmaciiCopiate, &nrFarmaciiCopiate);
	dezalocareVectorFarmacii(&farmaciiMici, &nrFarmaciiMici);
}