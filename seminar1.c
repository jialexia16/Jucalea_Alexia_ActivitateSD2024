#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

struct Cofetarie {
	char* nume;
	int nrAngajati;
	float* salarii;
};

void afiseazaCofetarie(struct Cofetarie* c)
{
	if (c->nume != NULL)
	{
		printf("Nume: %s\n", c->nume);
	}
	printf("Nr angajati: %d\n", c->nrAngajati);
	printf("Salarii: ");
	if (c->nrAngajati != NULL) {
		for (int i = 0; i < c->nrAngajati; i++)
		{
			printf("%5.2f, ", c->salarii[i]);
		}
	}

	printf("\n");
}


struct Cofetarie initializareCofetarie(const char* nume, int nrAngajati, const float* salarii)
{
	struct Cofetarie c;
	c.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrAngajati = nrAngajati;
	c.salarii = (float*)malloc(c.nrAngajati * sizeof(float));
	for (int i = 0; i < c.nrAngajati; i++)
	{
		c.salarii[i] = salarii[i];
	}
	return c;
}

void stergeCofetarie(struct Cofetarie c)
{
	if (c.nume != NULL)
	{
		free(c.nume);
	}

	if (c.salarii != NULL)
	{
		free(c.salarii);
	}
}

//int main()
//{
//	/*struct Cofetarie c1;
//	float* v = malloc(sizeof(float) * 2);
//	initializareCofetarie("Dulce",3,)
//	afiseazaCofetarie(c1);*/
//	float* v = malloc(sizeof(float) * 2);
//	v[0] = 4567;
//	v[1] = 3456;
//	struct Cofetarie c2 = initializareCofetarie("Mara", 2, v);
//	afiseazaCofetarie(&c2);
//	free(v);
//	/*free(c2.nume);
//	free(c2.salarii);*/
//	stergeCofetarie(c2);
//	afiseazaCofetarie(&c2);
//
//	/*free(c1.nume);
//	free(c1.salarii);*/
//	return 0;
//}