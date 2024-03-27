
#include<stdio.h>
#include<malloc.h>

typedef struct Santier Santier; //definim un alias pt struct Santier numit Santier
typedef struct Nod Nod;
struct Santier {
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

struct Nod {
    Santier santier;
    Nod* next;
};

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
    Santier santier;
    santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
    strcpy(santier.numeProiect, numeProiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;

    return santier;
}

Nod* inserareInceput(Santier santier, Nod* lista)
{
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    //shallow copy pt a nu avea un obiect in plus de sters in main
    nod->santier = santier;
    nod->next = lista;
    return nod;
}

void afisareSantier(Santier s) {
    printf("Proiectul %s are %d muncitori ce lucreaza pe o suprafata de %5.2f m^2\n", s.numeProiect, s.nrMuncitori, s.suprafata);
}

void afisareLista(Nod* lista) {
    while (lista != NULL) {
        //procesare
        afisareSantier(lista->santier);
        lista = lista->next;
    }
}

int sumaMuncitori(Nod* lista) {
    int suma = 0;
    while (lista != NULL) {
        suma += lista->santier.nrMuncitori;
        lista = lista->next;
    }
    return suma;
}

void stergereLista(Nod** lista) {
    while ((*lista) != NULL) {
        free((*lista)->santier.numeProiect);
        Nod* aux = (*lista)->next;
        free(*lista);
        (*lista) = aux;
    }
    (*lista) = NULL;

}



float densitateMuncitori(Santier s) {
    if (s.suprafata > 0) {
        return s.nrMuncitori / s.suprafata;
    }
    else return 0;
}



//2. Implementati o functie care sa insereze elementele in cadrul listei simplu inlantuite astfel incat acestea a fie sortate crescator dupa un camp la alegerea voastra.
char* numeSantierDensitateMaxima(Nod* lista) {
    float max = 0;
    char* aux = NULL;
    while (lista != NULL) {
        if (densitateMuncitori(lista->santier) > max)
        {
            max = densitateMuncitori(lista->santier);
            aux = lista->santier.numeProiect;
        }
        lista = lista->next;

    }
    if (aux != NULL) {
        char* numeProiectDensitate = (char*)malloc(strlen(aux) + 1);
        strcpy(numeProiectDensitate, aux);

        return numeProiectDensitate;
    }

    else return NULL;
}

void insereazaCrescatorDupaNrMuncitori(Nod** lista, Santier s)
{
    Nod* nod = *lista;
    Nod* prev = NULL;

    Nod* nodAdaugat = (Nod*)malloc(sizeof(Nod));
    nodAdaugat->santier = initializareSantier(s.numeProiect, s.nrMuncitori, s.suprafata);
    nodAdaugat->next = NULL;

    if (*lista == NULL)
    {
        *lista = nodAdaugat;
        return;
    }

    while (nod != NULL && s.nrMuncitori > nod->santier.nrMuncitori)
    {
        prev = nod;
        nod = nod->next;
    }

    if (prev == NULL)
    {
        nodAdaugat->next = *lista;
        *lista = nodAdaugat;
    }
    else
    {
        prev->next = nodAdaugat;
        nodAdaugat->next = nod;
    }
}

int main() {
    Nod* lista = NULL;
    Santier s1 = initializareSantier("Santier 1", 700, 450);
    Santier s2 = initializareSantier("Santier 2", 3000, 500);
    Santier s3 = initializareSantier("Santier 3", 6700, 300);

    lista = inserareInceput(s1, lista);
    lista = inserareInceput(s2, lista);
    lista = inserareInceput(s3, lista);
    lista = inserareInceput(initializareSantier("Santier 4", 40, 600), lista);
    afisareLista(lista);
    printf("\nNr muncitori total: %d ", sumaMuncitori(lista));

    printf("\nProiectul cu cea mai mare densitate de muncitori este %s", numeSantierDensitateMaxima(lista));

    printf("\n-------------------------------------------------------------------------------------\n");
    Nod* listaCresc = NULL;
    insereazaCrescatorDupaNrMuncitori(&listaCresc, s3);
    insereazaCrescatorDupaNrMuncitori(&listaCresc, s1);
    insereazaCrescatorDupaNrMuncitori(&listaCresc, s2);
    insereazaCrescatorDupaNrMuncitori(&listaCresc, s1);
    afisareLista(listaCresc);

    stergereLista(&lista);
    afisareLista(lista);

}
