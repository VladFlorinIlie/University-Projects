#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie *TP;

typedef struct celula
{
    TP fiu;
    struct celula *urm;
} TCelula, *TLista, **AL;

typedef struct trie
{
    TLista fii;
    char simb;
    char finalCuv;
} TTrie, *TP, **TA;

TP creare(char simb)
{
    TP nod = (TP) malloc(sizeof(TTrie));
    if(!nod)
        return NULL;
    nod->finalCuv = 0;
    nod->fii = NULL;
    nod->simb = simb;

    return nod;
}

TLista alocareCeulua(TP fiu)
{
    TLista l = (TLista) malloc(sizeof(TCelula));
    if(!l)
        return NULL;

    l->fiu = fiu;
    l->urm = NULL;

    return l;
}

void adauga(TP nod, char *cuv, int niv)
{
    AL p = &(nod->fii);
    if(strlen(cuv) == niv) //cuv se termina in nodul curent
    {
        nod->finalCuv = 1;
        return;
    }
    for(; *p != NULL; p = &((*p)->urm))
        if((*p)->fiu->simb == cuv[niv])
        {
            adauga((*p)->fiu, cuv, niv + 1);
            return;
        }
        else if((*p)->fiu->simb > cuv[niv])
            break;

    TP fiu = creare(cuv[niv]);
    if(!fiu)
        return;
    TLista aux = alocareCeulua(fiu);
    if(!aux)
    {
        free(fiu);
        return;
    }
    aux->urm = *p;
    *p = aux;
    adauga((*p)->fiu, cuv, niv + 1);

}

void sterge(TP *nod, char *cuv, int niv)
{
    if(strlen(cuv) == niv) //cuv se termina in nodul curent
    {
        (*nod)->finalCuv = 0;
        if((*nod)->fii == NULL)
        {
            free(*nod);
            *nod = NULL;
        }
        return;
    }
    AL p = &((*nod)->fii);
    for(; *p != NULL; p = &((*p)->urm))
        if((*p)->fiu->simb == cuv[niv])
        {
            sterge(&((*p)->fiu), cuv, niv + 1);
            break;
        }
        else if((*p)->fiu->simb > cuv[niv])
            return;
    if(*p == NULL)
        return;
    if((*p)->fiu == NULL) //daca fiul este sters, sterge si celula din lista
    {
        TLista l;
        l = *p;
        *p = (*p)->urm;
        free(l);
    }
    if((*nod)->fii == NULL && (*nod)->finalCuv == 0)
    {
        free(*nod);
        *nod = NULL;
    }
}

int find(TP nod, char *cuv, int niv)
{
    if(strlen(cuv) == niv)
    {
        if(nod->finalCuv == 1)
            return 1;
        else
            return 0;
    }
    TLista p = nod->fii;
    for(; p != NULL; p = p->urm)
        if(p->fiu->simb == cuv[niv])
            return find(p->fiu, cuv, niv + 1);
        else if(p->fiu->simb > cuv[niv])
            break;
    return 0;
}

void longPrefix(TP nod, char *cuv, int niv, int *lg, FILE *out)
{
    if(strlen(cuv) == niv)
         return;
    TLista p = nod->fii;
    for(; p != NULL; p = p->urm)
        if(p->fiu->simb == cuv[niv])
        {
            fprintf(out, "%c", cuv[niv]);
            *lg = *lg + 1;
            longPrefix(p->fiu, cuv, niv + 1, lg, out);
        }
        else if(p->fiu->simb > cuv[niv])
            return;
}

char *allPrefix(TP nod, char *prefix, char *cuv, int niv, int *ok, FILE *out)
{
    TLista p = nod->fii;
    for(; p != NULL; p = p->urm)
        if(strlen(prefix) > niv && p->fiu->simb == prefix[niv])
        {
            cuv = realloc(cuv, (niv + 2) * sizeof(char));
            if(!cuv)
                return NULL;
            cuv[niv] = prefix[niv];
            cuv[niv + 1] = '\0';
            if(strlen(prefix) == niv + 1 && p->fiu->finalCuv == 1)
            {//cand exista prefixul in trie
                fprintf(out, "%s ", cuv);
                *ok = 0;
            }
            cuv = allPrefix(p->fiu, prefix, cuv, niv + 1, ok, out);
        }
        else if(strlen(prefix) <= niv)
        {
            cuv = realloc(cuv, (niv + 2) * sizeof(char));
            if(!cuv)
                return NULL;
            cuv[niv] = p->fiu->simb;
            cuv[niv + 1] = '\0';
            if(p->fiu->finalCuv == 1)
            {
                fprintf(out, "%s ", cuv);
                *ok = 0;
            }
            cuv = allPrefix(p->fiu, prefix, cuv, niv + 1, ok, out);
        }
    return cuv;
}

void mLength(TP nod, char *prefix, int niv, int *suma, int *nr)
{
    TLista p = nod->fii;
    for(; p != NULL; p = p->urm)
        if(strlen(prefix) > niv && p->fiu->simb == prefix[niv])
        {
            if(strlen(prefix) == niv + 1 && p->fiu->finalCuv == 1)
            {
                *suma = *suma + niv + 1;
                *nr = *nr + 1;
            }
            mLength(p->fiu, prefix, niv + 1, suma, nr);
        }
        else if(strlen(prefix) <= niv)
        {
            if(p->fiu->finalCuv == 1)
            {
                *suma = *suma + niv + 1;
                *nr = *nr + 1;
            }
            mLength(p->fiu, prefix, niv + 1, suma, nr);
        }
}

void freeAll(TP nod)
{
    TLista p = nod->fii, l;
    for(; p != NULL; )
    {
        freeAll(p->fiu);
        l = p;
        p = p->urm;
        free(l);
    }
    free(nod);
}

void citire(char **op, char **cuv, FILE *in)
{
    int lg = 0;
    char c;
    while(1)
    {
        c = getc(in);
		if(c == '\r') //pentru CR
			c = getc(in);
        if(c == ' ' || c == '\n')
            break;
        *op = realloc(*op, lg + 2);
        if(*op == NULL)
            return;
        (*op)[lg] = c;
        (*op)[lg + 1] = '\0';
        lg++;
    }
	if(*cuv != NULL)
    {
        free(*cuv);
        *cuv = NULL;
    }
    if(c == ' ')
    {
        lg = 0;
        while(1)
        {
            c = getc(in);
			if(c == '\r')
				c = getc(in);
            if(c == '\n' || c == EOF)
                break;
            *cuv = realloc(*cuv, lg + 2);
            if(*cuv == NULL)
                return;
            (*cuv)[lg] = c;
            (*cuv)[lg + 1] = '\0';
            lg++;
        }
    }
}

int main(int argc, char **argv)
{
    char *op = NULL, *cuv = NULL, *cuvv = NULL, ch;
    int i, n, lg, suma, nr, ok;
    TP rad = NULL;
	
	if(argc != 3)
		return -3;

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    if(!in || !out)
        return -1;

    fscanf(in, "%d%c", &n, &ch); //citeste n si terminatorul de linie
	if(ch == '\r')// pentru carriage return
		fscanf(in, "%c", &ch);

    for(i = 0; i < n; i++)
    {
        citire(&op, &cuv, in);
        if(!rad)
            rad = creare(' ');

        if(strcmp(op, "add") == 0)
            adauga(rad, cuv, 0);
        else if(strcmp(op, "remove") == 0)
            sterge(&rad, cuv, 0);
        else if(strcmp(op, "find") == 0)
        {
            int fnd;
            fnd = find(rad, cuv, 0);
            if(fnd)
                fprintf(out, "True\n");
            else
                fprintf(out, "False\n");
        }
        else if(strcmp(op, "find_longest_prefix") == 0)
        {
            lg = 0;
            longPrefix(rad, cuv, 0, &lg, out);
            if(lg == 0)
                fprintf(out, "None");
            fprintf(out, "\n");
        }
        else if(strcmp(op, "find_all_with_prefix") == 0)
        {
            ok = 1;
            if(!cuv)
                cuvv = allPrefix(rad, "", cuvv, 0, &ok, out);
            else
                cuvv = allPrefix(rad, cuv, cuvv, 0, &ok, out);
            if(ok == 1)
                fprintf(out, "None");
            fprintf(out, "\n");
        }
        else if(strcmp(op, "mean_length") == 0)
        {
            suma = nr = 0;
            if(!cuv)
                mLength(rad, "", 0, &suma, &nr);
            else
                mLength(rad, cuv, 0, &suma, &nr);
            if(nr != 0)
                fprintf(out, "%.3f\n", (float)suma / nr);
            else
                fprintf(out, "0\n");
        }
    }
    fclose(in);
    fclose(out);

    free(op);
    if(cuvv)
        free(cuvv);
    if(cuv)
        free(cuv);
    if(rad)
        freeAll(rad);

    return 0;
}
