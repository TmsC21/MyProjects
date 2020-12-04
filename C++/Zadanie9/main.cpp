/*
Meno a priezvisko: Tomas Cupela

POKYNY:
(1)  Subor premenujte na Priezvisko_Meno_ID_zadanie09.cpp (pouzite vase udaje bez diakritiky).
(2)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(3)  Cela implementacia musi byt v tomto jednom subore.
(4)  Odovzdajte len tento (spravne premenovany) zdrojovy subor.
(5)  Program musi byt kompilovatelny.
(6)  Globalne a staticke premenne su zakazane.
(7)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(8)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo struktury.
     V prvych osmich prikladoch mozete pouzit iterativnu alebo rekurzivnu implementaciu. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
     V pripade implementacie rekurziou, moze byt hlavna cast implemetovana v pridanej rekurzivnej funkcii. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
(9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo struktur).
     Testovaci kod ale nebude hodnoteny.
(10) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <exception>
#include <set>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol binarneho vyhladavacieho stromu
struct Node {
    int value;     // hodnota uzla
    Node *smaller; // uzol 'smaller' a jeho nasledovnici maju hodnotu mensiu ako 'value'
    Node *greater; // uzol 'greater' a jeho nasledovnici maju hodnotu vacsiu ako 'value

    explicit Node(int value = 0, Node *smaller = nullptr, Node *greater = nullptr)
            : value(value)
            , smaller(smaller)
            , greater(greater)
    {
    }
};

// Binarny vyhladavaci strom
struct BinarySearchTree {
    Node *root; // koren stromu

    explicit BinarySearchTree(Node *root = nullptr)
            : root(root)
    {
    }
};

// Vynimka oznacujuca, ze uzol so zadanou hodnotou v strome neexistuje
class ValueNotExistsException : public std::exception {
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati najmensiu hodnotu v strome.
    V pripade neexistencie tejto hodnoty vyhodi vynimku.

    VSTUPNY PARAMETER:
        [in] tree - strom, v ktorom funkcia hlada minimum

    NAVRATOVA HODNOTA:
        najmensia hodnota v strome

    VYNIMKA:
        ValueNotExistsException - ak je strom prazdny
*/

int min(const BinarySearchTree *tree) {
	Node *tmp = tree->root;
	int minimum;
	if(tmp == nullptr){
		throw ValueNotExistsException();
	}
	while(tmp != nullptr){
		minimum = tmp->value;
		tmp = tmp->smaller;
	}
    return minimum;
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati hlbku uzla s hodnotou 'value' v strome 'tree'.
    Hlbka korena je 0.
    Ak hladany uzol v strome nie je, tak funkcia vyhodi vynimku.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Hlbka uzla s hodnotou 'value'.

    VYNIMKA:
        ValueNotExistsException - ak sa uzol s hodnotou 'value' v strome nenachdza
*/

size_t search_hlbka(Node *root, int key, size_t hlbka,bool &yes) 
{ 
	
    if (root == NULL || root->value == key){
		yes= true;
		if(root == NULL){
			yes = false;
		}
		return hlbka; 
	}
    if (root->value < key){
		hlbka++;
		return search_hlbka(root->greater, key,hlbka,yes); 
	} 
	hlbka++;
    return search_hlbka(root->smaller, key,hlbka,yes); 
}
unsigned depth(const BinarySearchTree *tree, int value) {
    size_t hlbka = 0;
	bool yes = false;
	hlbka = search_hlbka(tree->root,value,hlbka,yes);
	if(yes == false){
		throw ValueNotExistsException();
	}
    return hlbka; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot uzlov, ktore musi prejst pri hladani uzla s hodnotou 'value'.
    Prva hodnota vystupneho zoznamu je hodnota korena, druha hodnota zoznamu je lavy alebo pravy nasledovnik korena, atd.
    Poslednou hodnotou vo vystupnom zozname je hodnota uzla, na ktorom sa hladanie zastavilo.
    Ak 'tree' obsahuje uzol s hodnotou 'value', tak poslednou hodnotou vystupeho zoznamu je 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol s hodnotou 'value'
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Zoznam hodnot uzlov, ktorych hodnoty musela funkcia pri hladani porovnavat.
        Poradie hodnot vo vystupnom zozname musi zodpovedat poradiu prechadzania uzlov stromu.

    PRIKLADY:
        V prikladoch predpokladajme strom:
                  40
                 /  \
               20    50
              /  \    \
            10   30    60

        1. priklad
            value: 30 -> vystup: (40, 20, 30)
        2. priklad
            value: 45
            vystup: (40, 50)
*/
void print_list(list<int> list){
	for(auto i : list){
		cout << i << " ";
	}
	cout << endl;
}
void search_list(Node *root, int key, list<int> &list) 
{ 
	if(root == nullptr){
		return; 
	}
    if ( root->value == key){
		list.push_back(root->value);
		return; 
	}
	
    if (root->value < key){
		if(root->greater!=nullptr){
			search_list(root->greater, key,list);
		}
		list.push_back(root->value);
		return;
	}
		
	if(root->smaller!=nullptr){
		search_list(root->smaller, key,list); 
	}
	list.push_back(root->value);
	return;
}

list<int> path(const BinarySearchTree *tree, int value) noexcept {
    list<int> list;
	search_list(tree->root,value,list);
	list.reverse();
	print_list(list);
    return list; 
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu.

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho pocet uzlov funkcia zistuje

    NAVRATOVA HODNOTA:
        pocet uzlov stromu
*/
size_t search_size(Node *root, size_t sajz) 
{ 
    if (root == nullptr){
		return sajz; 
	}
    if (root->greater != nullptr){
		sajz++;
		sajz = search_size(root->greater,sajz); 
	} 
	if(root->smaller != nullptr){
		sajz++;
		sajz = search_size(root->smaller,sajz);
	}
	 return sajz;
}
size_t count(const BinarySearchTree *tree) noexcept {
	size_t sajz = 0;
	if(tree->root == nullptr){
		return sajz;
	}
	sajz++;
    sajz = search_size(tree->root,sajz);
    return sajz; 
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot vsetkych uzlov v strome 'tree'.
    Zoznam musi byt usporiadany od najmensieho prvku po najvacsi.

    Usporiadanie dosiahnite vhodnou postupnostou prechadzania uzlov stromu!

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho hodnoty funkcia vrati

    NAVRATOVA HODNOTA:
        hodnoty uzlov, v poradi od najmensej po najvacsiu
*/
void inOrderAll(Node* root,list<int> &list) 
{ 
	if (root == nullptr) return; 
    if (root != NULL) 
    { 
        inOrderAll(root->smaller,list); 
        list.push_back(root->value);
        inOrderAll(root->greater,list); 
    } 
} 
list<int> all(const BinarySearchTree *tree) noexcept {
    list<int> list;
	inOrderAll(tree->root,list);
    return list; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu 'tree', ktorych hodnota je vacsie ako 'value'

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia pocita pocet uzlov splnajich podmienku
        [in] value - hodnota, podla ktorej sa vyberaju uzly

    NAVRATOVA HODNOTA:
        pocet uzlov s hodnotou vacsou ako 'value'
*/
void search_greater(Node *root, int key, size_t &pocet) 
{ 
	if(root == nullptr){
		return;
	}
	if(root->value > key){
		cout << root->value << " ";
		pocet++;
	}
    if (root->greater != nullptr){
		search_greater(root->greater,key,pocet); 
	} 
	if(root->smaller != nullptr){
		search_greater(root->smaller,key,pocet);
	}
	return;
}
size_t countGreater(const BinarySearchTree *tree, int value) noexcept {
    size_t pocet = 0;
	if(tree->root == nullptr){
		return pocet;
	}
	search_greater(tree->root,value,pocet);
	cout << endl;
    return pocet; 
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani vsetky uzly stromu a dealokuje ich.

    Na dealokaciu pouzite operator 'delete'!

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho uzly funkcia odstrani

    VYSTUPNE PODMIENKY:
        vsetky uzly su dealokovane
        'tree->root' je nulovy smernik
*/
void deleteTree(Node* node)  
{  
    if (node == NULL) return;  

    deleteTree(node->smaller);  
    deleteTree(node->greater);   
    delete node; 
}  
void clear(BinarySearchTree *tree) noexcept {
    deleteTree(tree->root);
	tree->root = nullptr;
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia hlada hodnotu 'value' vo vektore 'data'.
    Vrati pocet prvkov v 'data', ktore pri hladni porovnala s 'value'.
    Vektor 'data' obsahuje usporiadane hodnoty.
    Casova narocnost algoritmu je O(n log(n)).

    PARAMETRE:
        'data' - hodnoty usporiadane od najmensieho prvku po najvacsi
        'value' - hodnota hladana v 'data'

    NAVRATOVA HODNOTA:
        Pocet prvkov 'data', ktore funkcia pri hladani porovnala s 'value'.
        (bez ohladu na to, ci 'data' obsahuje hodnotu 'value').

    VSTUPNA PODMIENKA:
        Hodnoty v 'data' su usporiadane od najmensieho prvku po najvacsi.

    PRIKLADY:
        data = (100, 102, 104, 106, 108, 110, 112), value = 106 -> vystup: 1
        data = (100, 102, 104, 106, 108, 110, 112), value = 110 -> vystup: 2
        data = (100, 102, 104, 106, 108, 110, 112), value = 108 -> vystup: 3
        data = (100, 102, 104, 106, 108, 110), value = 104 -> vystup: 1 alebo 3
        data = (100, 102, 104, 106, 108, 110), value = 107 -> vystup: 3
        data = (100), value = 100 -> vystup: 1
        data = (200), value = 200 -> vystup: 1
        data = (), value = 100 -> vystup: 0
*/
int binarySearch(const vector<int> arr, int l, int r, int x,size_t &pocet) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
		pocet++;
        if (arr[mid] == x) {
			return mid; 
		}
        if (arr[mid] > x) {
			return binarySearch(arr, l, mid - 1, x,pocet);
		}
        return binarySearch(arr, mid + 1, r, x,pocet); 
    } 
  
    return -1; 
} 
unsigned contains(const vector<int> & data, int value) noexcept {
	size_t pocet = 0;
    int result = binarySearch(data, 0, data.size()-1,value,pocet);
    return pocet;
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati histogram slov v 'data' (zisti, kolko krat sa ktore slovo nachadza v 'data')

    PARAMETER:
        'data' - vektor slov

    NAVRATOVA HODNOTA:
        histogram slov (pre kazde slovo z 'data' obsahuje pocet jeho vyskytov)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Histogram obsahuje iba slova, ktore sa v 'data' nachadzaju

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> 3, "lietadlo" -> 1, "luk" -> 2, "okno" -> 1}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> 1, "" -> 1}

        vstup: data = ()
        vystup: {}
*/

map<string, size_t> histogram(const vector<string> & data) noexcept {
	map<string, size_t> mymap;
	if(data.empty()){
		return mymap;
	}
	for(auto i: data){
		mymap[i] = 0;
	}
	map<string, size_t>::key_compare mycomp = mymap.key_comp();
	string highest = mymap.rbegin()->first;     
	map<string, size_t>::iterator it = mymap.begin();
	for(auto i: data){
		do {
			if(i == it->first){
				it->second++;
			}
	  } while ( mycomp((*it++).first, highest) );
	  it = mymap.begin();
	}
	do {
    cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );
    return mymap; 
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati index slov v 'data' (pre kazde slovo mnozinu indexov jeho vyskytu).

    PARAMETER:
        data - vektor slov

    NAVRATOVA HODNOTA:
        index slov (pre kazde slovo z 'data' obsahuje indexy, na ktorych sa slovo v 'data' nachadza)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Index obsahuje zoznamy vyskytov len pre slova, ktore sa nachadzaju v 'data'

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> {0, 3, 4}, "lietadlo" -> {1}, "luk" -> {2, 6}, "okno" -> {5}}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> {0}, "" -> {1}}

        vstup: data = ()
        vystup: {}
*/

map<string, set<size_t>> index(const vector<string> & data) noexcept {
	map<string, set<size_t>> mymap;
	if(data.empty()){
		return mymap;
	}
	size_t k=0;
	for(auto i: data){
		mymap[i].insert(k);
		k++;
	}
    return mymap; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury
void inOrder(Node* root) 
{ 
	
    if (root != NULL) 
    { 
        inOrder(root->smaller); 
        cout << root->value <<". "; 
        inOrder(root->greater); 
    } 
} 
Node* newNode(int value ) 
{ 
    Node* node = (Node*)malloc(sizeof(Node)); 
    node->value  = value; 
    node->smaller = node->greater = NULL; 
    return (node); 
} 
Node* insertLevelOrder(int arr[], Node* root, 
                       int i, int n) 
{ 
    // Base case for recursion 
    if (i < n) 
    { 
        Node* temp = newNode(arr[i]); 
        root = temp; 
  
        // insert left child 
        root->smaller = insertLevelOrder(arr, 
                   root->smaller, 2 * i + 1, n); 
  
        // insert right child 
        root->greater = insertLevelOrder(arr, 
                  root->greater, 2 * i + 2, n); 
    } 
    return root; 
} 
int main() {
	
	
	int arr[] = {40,20,50,10,30,45,60,5,11}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
    Node* root = insertLevelOrder(arr, root, 0, n);
	BinarySearchTree *bs = new BinarySearchTree;
	bs->root = root;
	//path(bs,4);
	//cout << count(bs) << endl;
	//all(bs);
	//cout << countGreater(bs,4)<< endl;
	//clear(bs);
	//vector<string> data = {"pocitac", "lietadlo", "luk", "pocitac", "pocitac", "okno", "luk"};
	//histogram(data);
	//index(data);
	const vector<int> data ={107};
	cout << contains(data,107) << endl;
    return 0;
}

