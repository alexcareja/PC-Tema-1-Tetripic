#include <stdio.h>

//declararea functiilor ce urmeaza a fi folosite
void print_map(unsigned long long );
int verif_harta(unsigned long long *);
int coliziune(unsigned long long,
              unsigned long long);
void miscareStanga(int,
                   unsigned long long *,
                   unsigned long long *,
                   unsigned long long *);
void miscareDreapta(int,
                   unsigned long long *,
                   unsigned long long *,
                   unsigned long long *);

int zero(unsigned long long);

int main()
{
    //Declararea variabilelor
    //harta - este variabila in care memoram toate stagiile hartii
    //i,k - contori
    //tabloul transf memoreaza cele 8 transformari aferente fiecarei piese
    unsigned long long harta, piesa, piesaTEMP;
    int mutari, i, k, transf[8], completedLines=0;
    float scor;

    //Citirea de la tastatura
    scanf("%llu", &harta);
    print_map(harta);
    scanf("%d",&mutari);
    for(i = 0, scor = 0;i < mutari;i++)
    {
        scanf("%llu",&piesa);
        for(k  =0;k < 8;k++)
        {
            scanf("%d",&transf[k]);
        }
        //piesa parcurge harta incepand cu linia 7;
        for(k = 7;k >= 0;k--)
        {
            piesaTEMP = piesa << (8 * k);
            //Daca are loc o coliziune, impiedicam piesa din a cobori,
            //iar dacarespectiva coliziune a avut loc pe cea mai
            //de sus linie, atunci jocul ia sfarsit
            if(piesaTEMP & harta)
            {
                //daca piesa nu intra pe prima linie (cea mai de sus)
                //jocul va lua sfarsit
                if(7 == k)
                {
                    scor = sqrt(zero(harta)) + pow(1.25, completedLines);
                    printf("GAME OVER!\nScore:%0.2f",scor);
                    return 0;
                }
                else
                {
                    //piesa urca inapoi pe nivelul anterior
                    piesaTEMP <<= 8;
                    break;
                }
            }
            //Daca nu are loc o coliziune, atunci piesa ramane
            //la nivel si are loc miscarea ei stanga/dreapta
            else
            {
                if(transf[7-k] < 0)
                {
                    miscareStanga(transf[7-k], &piesa, &piesaTEMP, &harta);
                }
                else
                {
                    miscareDreapta(transf[7-k], &piesa, &piesaTEMP, &harta);
                }
            }
            print_map(harta | piesaTEMP);
        }
        harta |= piesaTEMP;
        completedLines += verif_harta(&harta);
    }
    scor = sqrt(zero(harta)) + pow(1.25, completedLines);
    print_map(harta);
    printf("GAME OVER!\nScore:%0.2f",scor);
    return 0;
}

//functia print_map afiseaza harta
void print_map(unsigned long long harta)
{
	int i;
	for(i = 63;i >= 0;i--)
	{
		if((harta >> i) & 1)
        {
            printf("#");
        }
        else
        {
            printf(".");
        }
		if(0 == i%8)
        {
            printf("\n");
        }
	}
	printf("\n");
}

//Functia verif_harta va verifica daca vreo linie este
//completa si va elimina lniile complete daca este cazul
//De asemenea, functia foloseste ca parametru un pointer
//catre adresa variabilei harta, declarata in main
//Functia returneaza numarul de linii complete pe care le-a eliminat
int verif_harta(unsigned long long *h)
{
    int i,ok,lines=0;
    //Daca ok<8 => linia nu trebuie eliminata
    //Daca ok=8 => linia trebuie eliminata
    //Parcurgem harta
	for(i = 63,ok = 0;i >= 0;i--)
	{
        if((*h >> i) & 1)
        {
            //Daca bitul este egal cu 1, ok creste
            ok++;
            //Verificam daca ok a ajuns la 8,
            //adica toti bitii de pe linie sunt 1
            if(8 == ok)
            {
                //Eliminam linia plina si reinitializam ok
                if(i)
                {
                    *h=((*h >> (i+8)) << (i)) | ((*h << (64-i)) >> (64-i));
                    lines++;
                }
                //else, cazul banal in care linia de eliminat este
                //linia finala, caz in care shiftam la dreapta cu 8 biti
                else
                {
                    *h >>= 8;
                    lines++;
                }
                ok = 0;
            print_map(*h);
            }
        }
        //Altfel, trecem la urmatoarea linie si reinitializam ok
        else
        {
            i -= i % 8;
            ok = 0;
        }
	}
	return lines;
}

int coliziune(unsigned long long piesa,
              unsigned long long harta)
{
    if(harta & piesa)
    {
        return 1;
    }
 return 0;
}

void miscareStanga(int miscari,
                   unsigned long long *piesa,
                   unsigned long long *piesaTEMP,
                   unsigned long long *harta)
{
    int i;
    for(i = 0;i > miscari; i--)
    {
        if(1 == ((*piesa >> 7) % 2) || 1 == ((*piesa >> 15) % 2))
        {
            return;
        }
        if(coliziune(*piesaTEMP << 1, *harta))
        {
            return;
        }
        else
        {
            *piesa <<= 1;
            *piesaTEMP <<= 1;
        }
    }
}

void miscareDreapta(int miscari,
                   unsigned long long *piesa,
                   unsigned long long *piesaTEMP,
                   unsigned long long *harta)
{
    int i;
    for(i = 0;i < miscari; i++)
    {
        if(*piesa % 2 || (*piesa>>8) % 2)
        {
            return;
        }
        if(coliziune(*piesaTEMP >> 1, *harta))
        {
            return;
        }
        else
        {
            *piesa >>= 1;
            *piesaTEMP >>= 1;
        }
    }
}

//functia int zero va numara si va returna numarul de zerouri de pe harta
int zero(unsigned long long h)
{
    int i,nr=64;
    for(i = 0;i < 64;i++)
    {
        if((h >> i) & 1)
        {
            nr--;
        }
    }
    return nr;
}
