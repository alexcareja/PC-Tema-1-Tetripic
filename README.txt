=========================README=========================

************************TetriBit************************

Pentru implementarea jocului am creat cateva functii:

---> Functia pint_map este creata doar pentru afisarea 
	 hartii si transmite ca parametru harta

---> Functia verif_harta returneaza numarul de linii 
	 completate eliminate si transmite ca parametru
	 un pointer care retine adresa hartii cu scopul 
	 de a o modifica daca trebuie eliminate linii
	 
---> Functia coliziune este folosita in miscarea piesei
	 stanga respectiv dreapta, si aceasta returneaza 0
	 daca piesa se poate misca cu o unitate in stanga,
	 respectiv dreapta, si 1 daca ar avea loc o suprapunere
	 
---> Functiile miscareStanga si miscareDreapta primesc ca 
	 parametrii miscarea pe care trebuie sa o efectueze 
	 piesa, si 3 pointeri care retin adresele a 3 varibile
	 (piesa, piesaTEMP si harta) cu scopul de a le modifica
	 valorile. Miscarea in stanga/dreapta se face bit cu bit
	 pana cand are loc o coliziune cu marginea sau cu alte 
	 piese de pe harta.
	 
---> Functia zero returneaza numarul de zerouri de pe harta
	 dupa finalizarea jocului, si rolul ei revine in calcu-
	 larea scorului
	 

In main are loc citirea datelor jocului si desfasurarea lui.


Informatii despre variabilele din main:

---> harta = valoarea hartii

---> piesa = valoarea piesei

---> piesaTEMP este o valiabila in care se retine valoarea
	 piesei shiftata la stanga cu un anumit numar de biti
	 (multiplu de 8) pentru a avea pozitia in timp real 
	 a piesei in harta.
	
---> mutari = numarul de mutari

---> i,k = contori

---> transf[] = un vector in care retinem cele 8 transformari
	 aferente fiecarei piese
	 
---> mutari = numarul de piese care se vor citirea

---> scor 

---> completedLines = numarul de linii complete elimiate

O data ce se citeste o piesa si cele 8 tranformari ale ei, 
imediat incepe parcurgerea hartii de catre aceasta. In cazul
unei coliziuni fatale pe prima linie (cea mai de sus) a hartii
jocul ia sfarsit si se calculeaza scorul. Inainte de fiecare 
coborare a piesei pe urmatoarea linie se verifica daca este 
posibila aceasta miscare printr-un test. Dupa ce ultima piesa 
citita a parcurs harta (pana la un punct unde are loc o coliziune
sau pana pe ultima linie) se va citi urmatoarea piesa (daca este
cazul), iar in final se calculeaza si se afiseaza scorul dupa
formula data.