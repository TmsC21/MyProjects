/*
Meno a priezvisko: Tomas Cupela

POKYNY:
(1)  Subor premenujte na Priezvisko_Meno_ID_zadanie04.cpp (pouzite vase udaje bez diakritiky).
(2)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(3)  Cela implementacia musi byt v tomto jednom subore.
(4)  Odovzdajte len tento (spravne premenovany) zdrojovy subor.
(5)  Program musi byt kompilovatelny.
(6)  Globalne a staticke premenne su zakazane.
(7)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie hotovych pomocnych funkcii, ani implementacie zadanych datovych typov.
(8)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo struktury.
(9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo struktur).
     Testovaci kod ale nebude hodnoteny.
(10) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Hmotnost produktu a obalu. Hmotnost zabaleneho produktu je suctom obidvoch poloziek
struct Weight {
    int product; // hmotnost produktu
    int packing; // hmotnost balenia
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data'.
    Pouzije algoritmus bubble sort.
    Poradie usporiadania je od najvacsieho prvku po najmensi.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNA PODMIENKA:
        ak 'length' > 0, tak 'data' ukazuje na platne pole

    PRIKLADY:
        {1,3,2} -> {3, 2, 1}
        {} -> {}
*/
void bubble(int *data, const size_t length){
	int swap;
    for(size_t i=0; i<length-1 ;i++){
		if(data[i] < data[i+1]){
			swap = data[i+1];
			data[i+1] = data[i];
			data[i] = swap;
		}
	}
}
void bubbleSort(int *data, const size_t length) {
	for(size_t i=0; i<length ;i++){
		bubble(data,length);
	}
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' podla celkovej hmotnosti zabaleneho tovaru, t.j. podla suctu poloziek ('product' a 'packing').
    Pouzije algoritmus bubble sort.
    Poradie usporiadania je od najvacsieho prvku po najmensi (od najtazsieho zabaleneho tovaru po najlahsi zabaleny tovar).

    Podmienka porovnania struktur:
    Pri porovnavani prvkov funkcia scita hodnoty 'product' a 'packing' oboch porovnavanych struktur.
    Struktury s vacsim suctom poloziek budu po usporiadani pred strukturami s mensim suctom poloziek.

    Vzajomne usporiadanie struktur s rovnakym suctom poloziek:
    Pri bodovom hodnoteni nezalezi na vzajomnom usporiadani struktur s rovnakym suctom poloziek (aj ked hodnoty poloziek mozu byt rozne).
    Lepsie je vsak implementovat stabilne triedenie (struktury s rovnakym suctom poloziek nemenia vzajomne usporiadanie).

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNA PODMIENKA:
        ak 'length' > 0, tak 'data' ukazuje na platne pole

    PRIKLADY:
        {{10, 1}, {20, 2}, {5,2}} -> {{20, 2}, {10, 1},{5,2}} pretoze 20+2=22, 10+1=11, 5+2=7 a 22 > 11 > 7
        {} -> {}

    POZNAMKA:
        Priklady jednoducheho vytvorenia pola v testovacom kode:
        Weight baliky[] = {{10, 1}, {20, 2}, {5,2}};
        Weight baliky[] = {{.product = 10, .packing = 1}, {.product = 20, .packing = 2}, {.product = 5, .packing = 2}};
*/

void bubbleSort(Weight *data, const size_t length) {
	int suc1,suc2;
	Weight swap;
    for(size_t x=0 ;x < length;x++){
		for(size_t y=0 ;y < length-1;y++){
			suc1 = data[y].packing + data[y].product;
			suc2 = data[y+1].packing + data[y+1].product;
			if(suc1 < suc2){
				swap = data[y];
				data[y] = data[y+1];
				data[y+1] = swap;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vyberie pivota a vrati jeho index.
    Pivota vyberie ako median prvkov:
      - data[low]
      - data[(high+low)/2]
      - data[high-1]

    PARAMETRE:
        [in] data - pole, v ktoreho casti s indexami 'low' ... 'high'-1, funkcia vybera pivot
        [in] low  - index prveho prvku casti pola, v ktorej funkcia hlada pivot
        [in] high - index za poslednym prvkom casti pola, v ktorej funkcia hlada pivot

    NAVRATOVA HODNOTA:
        index pivota

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole
        'low' < 'high'

    PRIKLADY:
        data: {10, 20, 2000, 30, 1000, 40, 5000, 50, 60, 70}, low: 2, high: 7 -> return 2
        data: {10, 20, 1000, 30, 2000, 40, 5000, 50, 60, 70}, low: 2, high: 7 -> return 4
        data: {10, 20, 5000, 30, 1000, 40, 2000, 50, 60, 70}, low: 2, high: 7 -> return 6

        data: {10, 20, 1000, 30, 40, 2000, 50, 5000, 60, 70}, low: 2, high: 8 -> return 5

        data: {10, 20, 1000, 2000, 30, 40, 50},               low: 2, high: 4 -> return 3
        data: {10, 20, 2000, 1000, 30, 40, 50},               low: 2, high: 4 -> return 3

        data: {10, 20, 1000, 30, 40},                         low: 2, high: 3 -> return 2
*/
size_t getPivotIndex(const int *data, const size_t low, const size_t high)
{
	int new_data[]{data[low],data[(high+low)/2],data[high-1]};
	int median;
	for(int x = 0; x < 3; x++){
		for(int y = 0; y < 2; y++){
			if(new_data[y] < new_data[y+1]){
				median = new_data[y];
				new_data[y] = new_data[y+1];
				new_data[y+1] = median;
			}
		}
	}
	median = new_data[1];
	for(size_t x = low; x < high ; x++){
		if(median == data[x]){
			return x;
		}
	}
    return 0; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona partition (cast algoritmu quick sort) a vrati novy index pivota.
    Pouzije styl algoritmu Lomuto.
    Poradie usporiadania:
        Najprv (vlavo) budu prvky vacsie alebo rovne ako pivot,
        potom pivot,
        potom (vpravo) prvky mensie ako pivot.

    PARAMETRE:
        [in, out] data - pole, v ktoreho casti 'low' ... 'high'-1 bude vykonane partition
        [in] pivot     - index pivota (pred partition)
        [in] low       - index prveho prvku casti pola, v ktorej bude vykonany partition
        [in] high      - index za poslednym prvkom casti pola, v ktorej bude vykonany partition

    NAVRATOVA HODNOTA:
        Index pivota po vykonani partition.

    VSTUPNE PODMIENKY:
        'low' <= 'pivot' < 'high'
        (index pivota moze byt lubobolny v rozsahu 'low'...'high'-1, napriklad v pripade nahodneho vyberu pivota)
        'data' ukazuje na platne pole

    PRIKLADY:
        1. priklad:
            vstup:  data: {10, 20, 30, 40, 50, 60, 70, 80, 90}, pivot: 5, low: 2, high: 7
            vystup: data: {10, 20, 70, 60, 50, 30, 40, 80, 90}, return 3

        2. priklad:
            vstup:  data: {10, 20, 30, 40, 50, 60, 70, 50, 80, 90}, pivot: 4, low: 2, high: 8
            vystup: data: {10, 20, 50, 60, 70, 50, 30, 40, 80, 90}, return 5
*/
void swap_pointer(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
size_t partition(int *data, const size_t pivot, const size_t low, const size_t high)
{
	swap_pointer(&data[pivot], &data[high - 1]);
    size_t index = low;
    for(size_t i = low; i<high-1;i++){
        if(data[i] >= data[high-1]){
            swap_pointer(&data[i], &data[index++]);
        }
    }
	swap_pointer(&data[high-1],&data[index]);
    return index;
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada cast pola 'data' (s indexami 'low' ... 'high'-1).
    Pouzije algoritmus quick sort, styl Lomuto.
    Poradie usporiadania je od najvacsieho prvku po najmensi.

    PARAMETRE:
        [in, out] data - pole, ktoreho cast funkcia usporiada
        [in] low       - index prveho prvkou casti pola, ktoru funkcia usporiada
        [in] high      - index za posledny prvok casti pola, ktoru funkcia usporiada

    VSTUPNA PODMIENKA:
        ak 'low' < 'high', tak 'data' ukazuje na platne pole

    PRIKLAD:
        data: {1, 2, 3, 4, 5, 6, 7, 8, 9}, low: 2, high: 7 -> data: {1, 2, 7, 6, 5, 4, 3, 8, 9}
*/
size_t getPivot(const int *pole, const size_t low, const size_t high) {
    size_t middle_index = (low + high) / 2;
    int left = pole[low];
    int middle = pole[middle_index];
    int right = pole[high - 1];

    if ((left <= middle && left >= right) || (left >= middle && left <= right)) {
        return low;
    }
    if ((right <= middle && right >= left) || (right >= middle && right <= left)){
        return high - 1;
    }
    return middle_index;

}
size_t partitionn(int *pole, const size_t pivot_index, const size_t low, const size_t high){
    swap_pointer(&pole[pivot_index], &pole[high - 1]);
    size_t insert_index = low;
    size_t compare_index = low;
    while (compare_index < high) {
        if (pole[compare_index] >= pole[high - 1]) {
            swap_pointer(&pole[insert_index], &pole[compare_index]);
            insert_index++;
        }
        compare_index++;
    }
    return insert_index - 1;
}
void quickSort(int *pole, const size_t low, const size_t high)
{
    if (low + 1 >= high) {
        return;
    }
    size_t pivot_index = getPivot(pole, low, high);
    pivot_index = partitionn(pole, pivot_index, low, high);
    quickSort(pole, low, pivot_index);
    quickSort(pole, pivot_index + 1, high);
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main() {

	int lowq = 2, highq = 7;
	int data_qsort[]={1, 2, 3, 4, 5, 6, 7, 8, 9};
	quickSort(data_qsort,lowq,highq);
	for(int x=0;x<9;x++){
		cout << data_qsort[x] << " ";
	}
    return 0;
}