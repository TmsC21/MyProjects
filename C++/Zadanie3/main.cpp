/*
Meno a priezvisko: Tomas Cupela

POKYNY:
(1)  Subor premenujte na Priezvisko_Meno_ID_zadanie03.cpp (pouzite vase udaje bez diakritiky).
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
#include <cstring>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node* next; // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
    Node* first; // smernik na prvy uzol zoznamu
};
Node *novyNode(const int val){
	Node *newnode = new Node;
	newnode->data = val;
	newnode->next = nullptr;
	return newnode;
}
void appendNode(List* list, const int val) {
    Node *novy = novyNode(val);
	if(!list->first){
		list->first = novy;
	}
	else{
		Node *tmp = list->first;
		while(tmp->next){
			tmp = tmp->next;
		}
		tmp->next = novy;
	}
}
List* createListFromArray(const int* data, const size_t n) {
	List *list = new List;
	list->first = nullptr;
	if(n == 0){
		return list;
	}
	else if(n < 0){
		return nullptr;
	}
	else{		
		for(size_t x = 0 ; x < n ; x++){
			appendNode(list,data[x]);
		}
		return list;
	}
	return nullptr; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}
void printList(List *list){
	Node *tmp = list->first;
	while(tmp){
		cout << tmp->data << " ";
		tmp = tmp->next;
	}
	cout << endl;
}
//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Usporiada pole 'data' od najvacsieho prvku po najmensi prvok.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'length' moze mat lubovolnu hodnotu
        'data' ukazuje na platne pole

    PRIKLADY:
        {1,3,2} -> {3, 2, 1}
        {1} -> {1}
        {} -> {}
*/
void insertionSort(int *data, const size_t length) {
	int val = 0,hole = 0;
	for(size_t x = 1; x < length ;x++){
		val = data[x];
		hole = x;
		while(hole>0 && data[hole-1]<val){
			data[hole] = data[hole-1];
			hole--;
		}
		data[hole] = val;
	}
	for(size_t x = 0; x < length ;x++){
		cout << data[x] << " ";
	}
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Usporiada textove retazce v poli 'data' od najvacsieho prvku po najmensi (lexikograficky).
    Preusporiadajte smerniky v poli.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada.
                Pole obsahuje smerniky na textove retazce.
                Kazdy textovy retazec je ukonceny '\0'.
                Posledny smernik ma hodnotu 'nullptr'. Podla toho urcite pocet prvkov pola (pocet textovych retazcov).

    VSTUPNE PODMIENKY:
        'data' obsahuje minimalne jeden smernik.
        Posledny smernik ma hodnotu 'nullptr'.

    PRIKLADY:
        {"Juraj", "Peter", "Andrej", nullptr} -> {"Peter", "Juraj", "Andrej", nullptr}
        {"Juraj", "Anabela", "Peter", "Andrej", nullptr} -> {"Peter", "Juraj", "Andrej", "Anabela", nullptr}
        {"Andrej", nullptr} -> {"Andrej", nullptr}
        {nullptr} -> {nullptr}

    POZNAMKY:
        Pri testovani mozete jednoducho pole vytvorit nasledovnym sposobom:
        const char *mena[] = {"Juraj", "Peter", "Andrej", nullptr};

        Na porovnanie obsahu textovych retazcov vyuzite prislusnu funkciu zo standardnej kniznice.
*/
void insertionSort(const char *data[]) {
	int x=0,hole=0;
	const char *val;
	while(data[x]!=nullptr){
		val = data[x];
		hole = x;
		while(hole>0 && (strcmp(data[hole-1],val)<0)){
			data[hole] = data[hole-1];
			hole--;
		}
		data[hole] = val;
		x++;
	}
	x= 0;
	while(data[x]!=nullptr){
		cout << data[x] << " ";
		x++;
	}
}
	
//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Usporiada zretazeny zoznam 'list' od najvacsieho prvku po najmensi.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] list - zretazeny zoznam, ktory funkcia usporiada

    VSTUPNE PODMIENKY:
        'list' obsahuje lubovolny pocet uzlov (moze byt prazdny)
        'list' nie je 'nullptr'

    PRIKLADY:
        vstup: 2->1->3, vystup: 3->2->1
        vstup: prazdny zoznam, vystup: prazdny zoznam
*/
void insertionSort(List * list) {
	Node* head = list->first;
	Node* tmp = list->first;
	Node* tmp_next = list->first->next;
	while(tmp_next){
		tmp = head;
		while(tmp != tmp_next){
			if(tmp->data < tmp_next->data){
				int temp = tmp_next->data;
				tmp_next->data = tmp->data;
				tmp->data = temp;
			}
			else{
				tmp = tmp->next;
			}
		}
		tmp_next = tmp_next->next;
	}
	printList(list);
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vykona algoritmus merge (cast algoritmu merge sort), ktory ma linearnu vypoctovu zlozitost.
    Kombinuje dve susedne, usporiadane casti v poli 'input', do jednej usporiadanej casti v poli 'output'.
    Usporiadanie je od najvacsieho prvku po najmensi prvok!

    PARAMETRE:
        [out] output - vystupne pole, ktoreho cast output[low]...output[high-1] bude po vykonani funkcie usporiadana
        [in]  input  - vstupne pole, ktoreho casti input[low]...input[middle-1] a input[middle]...input[high-1]
                         musia byt pri volani funkcie usporiadane od najvacsieho prvku po najmensi
        [in]  low    - index 1. prvku lavej usporiadanej casti pola 'input'
        [in]  middle - index 1. prvku pravej usporiadanej casti pola 'input'
        [in]  high   - index za poslednym prvkom pravej usporiadanej casti pola 'input'

    VYSTUPNE PODMIENKY:
        Obsah 'input' sa nemeni.
        output[low] ... output[high-1] obsahuje usporiadane prvky z input[low] ... input[high-1], zvysne prvky v 'output' funkcia nemeni
        Prvky s indexami mensimi ako 'low' sa nemenia (ani v jednom poli)
        Prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia (ani v jednom poli)

    PRIKLAD:
        low: 4
        middle: 8
        hight: 12
        input:                         {10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10}
        output pred vykonanim funkcie: {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20}
        output po vykonani funkcie:    {20, 20, 20, 20,  8,  7,  5,  4,  2,  2,  1,  0, 20, 20, 20, 20}
*/
void mergePointers(int *L, int *R,const size_t low,int *output,size_t len_L,size_t len_R){
	size_t i=0 ,j=0,k=0;
	while(i<len_L && j<len_R){
		if(L[i] >= R[j]){
			output[k+low] = L[i];
			i++;
		}
		else{
			output[k+low] = R[j];
			j++;
		}
		k++;
	}
	while(i < len_L){
		output[k+low] = L[i];
		i++;
		k++;
	}
	while(j < len_R){
		output[k+low] = R[j];
		j++;
		k++;
	}
}
void merge(int* output, const int* input, const size_t low, const size_t middle, const size_t high)
{
	size_t len_input_A = middle-low;
	size_t len_input_B = high-middle;
	size_t y = 0,z = 0;
	int* Array_A = new int[len_input_A];
	int* Array_B = new int[len_input_B];
    for(size_t x=low; x<high; x++){
		if(x < middle){
			*(Array_A+y) = *(input+x);
			y++;
		}
		else{
			*(Array_B+z) = *(input+x);
			z++;
		}
	}
	mergePointers(Array_A,Array_B,low,output,len_input_A,len_input_B);
	for(size_t x=0;x<low+high;x++){
		cout << output[x] << " ";
	}
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Usporiada prvky v poli 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus merge sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        {1,3,2} -> {3, 2, 1}
        {1} -> {1}
        {} -> {}

    POZNAMKA:
        Pri implementacii top-down bude vhodne vytvorit a zavolat rekurzivnu funkciu.
*/
void mergeArrays(int*L ,int*R, int*A,size_t len_L,size_t len_R){
	size_t i=0 ,j=0,k=0;
	while(i<len_L && j<len_R){
		if(L[i] >= R[j]){
			A[k] = L[i];
			i++;
		}
		else{
			A[k] = R[j];
			j++;
		}
		k++;
	}
	while(i < len_L){
		A[k] = L[i];
		i++;
		k++;
	}
	while(j < len_R){
		A[k] = R[j];
		j++;
		k++;
	}
}
void mergeSort(int *data, const size_t length) {
    if(length<2){
		return;
	}
	else{
		size_t mid = length/2;
		int* left = new int[mid];
		int* right = new int[length-mid];
		for(size_t i = 0 ; i < mid; i++){
			left[i] = data[i];
		}
		for(size_t i = mid;i < length; i++){
			right[i-mid] = data[i]; 
		}
		mergeSort(left,mid);
		mergeSort(right,length-mid);
		mergeArrays(left,right,data,mid,length-mid);
	}
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main() {
	int data[] = {30,40,50,10,20};
	size_t val = sizeof(data)/sizeof(int);
	int data2[] = {1,2,5,4,10};
	size_t val2 = sizeof(data2)/sizeof(int);
	List *list = new List;
	list->first = nullptr;
	list = createListFromArray(data,val);
	insertionSort(data,val);
	const char *data_str[] = {"Juraj", "Anabela", "Peter", "Andrej", nullptr};
	cout << endl;
	insertionSort(data_str);
	cout << endl;
	insertionSort(list);
	
	int low=4,
        middle=8,
        hight=12;
		
	int input[] = {10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10,10};
	int output[] ={20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,20};
	merge(output,input,low,middle,hight);
	cout << endl;
	mergeSort(data2,val2);
	for(size_t i=0; i<val2; i++){
		cout << data2[i]<< ". ";
	}
    return 0;
}
