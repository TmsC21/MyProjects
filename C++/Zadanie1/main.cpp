/*
Meno a priezvisko: Cupela Tomas

POKYNY:
(1)  Subor premenujte na Priezvisko_Meno_ID_zadanie01.cpp (pouzite vase udaje bez diakritiky).
(2)  Implementujte funkcie tak, aby splnovali popis pri ich deklaraciach.
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
#include <cmath>
#include <cstring>
#include <cctype>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Bod v rovine
struct Point {
    int x; // x-ova suradnica
    int y; // y-ova suradnica
};

// Usecka v rovine
struct Line {
    Point start; // zaciatocny bod
    Point end;   // koncovy bod
};

// Student
struct Student {
    char *name; // meno studenta
    int year;   // rocnik studia
};

// Uspesnost vykonania funkcie
enum class Result {
    SUCCESS, // funkcia vykonana uspesne
    FAILURE  // chyba pri vykonavani funkcie
};

// Matematicka funkcia
enum class Operation {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE
};

// Vstup pre matematicky vypocet funkcie s dvoma parametrami
struct CalculationInput {
    int operand1; // prvy parameter
    int operand2; // druhy parameter
    Operation operation; // funkcia
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vytlaci obsah pola na standardny vystup.
    V implementacii musi byt pouzity 'std::cout'.

    Format tlace:
    - prvky pola (cisla) su oddelene jednou medzerou
    - pred prvym prvkom je gulata otvaracia zatvorka (medzi zatvorkou a cislom nesmie byt medzera)
    - za poslednym prvkom je gulata zatvaracia zatvorka (medzi cislom a zatvorkou nesmie byt medzera)

    PARAMETRE:
        [in] data   - pole cisiel
        [in] length - dlzka pola 'data'

    VSTUPNE PODMIENKY:
        'length' moze mat lubovolnu hodnotu
        'data' ukazuje na platne pole

    PRIKLADY:
        prazdne pole: ()
        jednoprvkove pole: (10)
        2 prvkove pole:    (10 20)
        10 prvkove pole:   (8 -5 100000 2 1 2 4 5 -20 345)
*/
void printArray(const int *data, size_t length) {
	if(length == 0){
		cout << "prazdne pole: ()" << endl;
	}else if(length == 1){
		cout << "jednoprvkove pole: (" << data[length-1] << ")" << endl; 
	}else{
		cout << length << " prvkove pole: ("; 
		for(size_t x = 0; x < length ;x++){
			if(x == length-1){
				cout << data[x];
			}else{
				cout << data[x] << " ";
			}
		}
		cout << ")" << endl;
	}
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Zo standardneho vstupu nacita dve cele cisla (typu 'int') a vrati ich sucet.
    V implementacii musi byt pouzity 'std::cin'.

    NAVRATOVA HODNOTA:
        sucet cisiel nacitanych zo standardneho vstupu

    VSTUPNE PODMIENKY:
        Textovy vstup zadany na standardny vstup programu obsahuje dve cele cisla, ktore mozno reprezetovat typom 'int'.
        Nemusite osetrovat moznost chybnych udajov zadanych na standardny vstup.

    PRIKLADY:
        Ak je na standardny vstup zadany text "10 20\n" (bez uvodzoviek), tak funkcia vrati 30.
        Ak je na standardny vstup zadany text " 10 \n 20 \n" (bez uvodzoviek), tak funkcia vrati 30.
*/
int sumOfTwoNumbersFromConsole(){
    int sucet = 0;
	int a = 0, b = 0;
	
	cin >> a;
	cin >> b;
	
	sucet = a + b;
    return sucet; 
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vrati 'true' ak 'text' obsahuje velke pismeno, inak vrati 'false'.

    PARAMETER:
        [in] text - textovy retazec ukonceny '\0'

    NAVRATOVA HODNOTA:
        'true'  - ak 'text' obsahuje aspon jedno velke pismeno
        'false' - ak 'text' neobsahuje ani jedno velke pismeno (plati aj pre prazdny retazec)

    POZNAMKA:
        Pri implementacii pouzite funkciu 'std::isupper'.
*/
bool containsUpperCase(const char *text) {
	char c;
	int x = 0;
    while(text[x]){
		c = text[x];
		if(isupper(c)){
			return true;
		}
		x++;
	}
    return false; 
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vrati 'true' ak 'data' obsahuje stupajucu postupnost, inak vrati 'false'.

    PARAMETRE:
        [in] data   - pole hodnot
        [in] length - pocet prvkov pola 'data'

    NAVRATOVA HODNOTA:
        'true' - ak 'data' obsahuje stupajucu postupnost hodnot, alebo pocet prvkov pola je mensi ako 2
        'false' - v opacnom pripade

    PRIKLADY:
        data = {10, 11, 15, 20} => vysledok je 'true'
        data = {10, 15, 15, 20} => vysledok je 'false'
        data = {10, 11, 15, 12} => vysledok je 'false'
        data = {10}             => vysledok je 'true'
        data = {}               => vysledok je 'true'
*/
bool isAscending(const int *data, size_t length) {
	
	size_t pocet = 0;
	if(length == 1){
		return true;
	}
	else if(length == 0){
		return true;
	}
	else{
		int predosle_cislo = data[0];
		
		for(size_t x = 1; x < length; ++x){
			if(data[x] > predosle_cislo){
				pocet++;
				predosle_cislo = data[x];
			}
		}
		if(pocet == length-1){
			return true;
		}
	}
	
    return false; 
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Posunie hodnoty pola 'data' o 1 miesto vyssie. Hodnotu posledneho prvku presunie na zaciatok.

    PARAMETRE:
        [in,out] data - pole hodnot, ktore bude preusporiadane
        [in] length   - pocet prvkov pola 'data'

    PRIKLADY:
        {10, 20, 30, 40, 50} => {50, 10, 20, 30, 40}
        {10} => {10}
        {} => {}
*/
void shiftUp(int *data, size_t length) {
	int cislo = data[0];
	int buduc_cislo;
    for(size_t x = 0; x < length ;++x){
		if(x != length-1){
			buduc_cislo = data[x+1];
			data[x+1] = cislo;
			cislo = buduc_cislo;
		}
		else{
			data[0] = cislo;
		}
	}
	for(size_t x = 0; x < length ;++x){
		cout << data[x] << " ";
	}
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Preusporiada pole 'data' tak, ze jeho prvky budu v opacnom poradi.

    PARAMETRE:
        [in, out] data - pole hodnot, ktore bude preusporiadane
        [in] lenght    - pocet prvkov pola 'data'

    PRIKLADY:
        {10, 20, 30, 40, 50} => {50, 40, 30, 20, 10}
        {10, 20, 30, 40} => {40, 30, 20, 10}
        {10} => {10}
        {} => {}
*/
void reverse(int * data, size_t length) {
    int cislo;
    for(size_t x = 0; x < length/2 ;++x){
		cislo = data[x];
		data[x] = data[(length-1)-x];
		data[(length-1)-x] = cislo;
	}
	for(size_t x = 0; x < length ;++x){
		cout << data[x] << " ";
	}
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vrati dlzku usecky 'line'

    PARAMETER:
        [in] line - usecka

    NAVRATOVA HODNOTA:
        dlzka usecky 'line'

    PRIKLAD:
        line:
            start:
                x = 10
                y = 20
            end:
                x = 100
                y = 50
        return 94.868329805
*/
double length(const Line * line) {
	double A = pow(line->end.x - line->start.x , 2);
	double B = pow(line->end.y - line->start.y , 2);
    return sqrt(A + B); 
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vrati dlzku usecky 'line'

    PARAMETER:
        [in] line - usecka

    NAVRATOVA HODNOTA:
        dlzka usecky 'line'

    PRIKLAD:
        line:
            start:
                x = 10
                y = 20
            end:
                x = 100
                y = 50
        return 94.868329805
*/
double length(const Line & line) {
    double A = pow(line.end.x - line.start.x , 2);
	double B = pow(line.end.y - line.start.y , 2);
    return sqrt(A + B); 
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vytvori noveho studenta s menom 'name' a rocnikom studia 'year'.
    Vrati smernik na vytvoreneho studenta.

    PARAMETRE:
        [in] name - meno studenta (textovy retazec ukonceny '\0')
        [in] year - rocnik v ktorom student studuje

    NAVRATOVA HODNOTA:
        vytvoreny student
*/
Student * createStudent(const char *name, int year) {
	Student *student = new Student;
	student->name = new char[strlen(name)+1];
	strcpy(student->name,name);
	student->year = year;
    return student; 
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Vypocita celociselny matematicky vypocet zadany parametrom 'input'.
    Vysledok ulozi do 'output'.

    PARAMETRE:
        [in] input   - vstupne udaje pre matematicky vypocet
        [out] output - vystupna hodnota vypoctu (v pripade moznosti vypoctu)

    NAVRATOVA HODNOTA:
        Result::SUCCESS - ak je mozne vypocitat vyslednu hodnotu
        Result::FAILURE - ak nie je mozne vypocitat vyslednu hodnotu (v pripade delenia nulou)

    VYSTUPNE PODMIENKY:
        - Vysledok vypoctu je celociselny.
        - Ak je mozne vykonat vypocet, tak sa vysledok ulozi do 'output' a funkcia vrati 'Result::SUCCESS',
          inak (v pripade delenia nulou) sa hodnota 'output' nemeni a funkcia vrati 'Result::FAILURE'.
*/
Result calculate(int *output, const CalculationInput * input) {
	switch(input->operation){
		case Operation ::PLUS:
			*output = input->operand1 + input->operand2;
		break;
		case Operation ::MINUS:
			*output = input->operand1 - input->operand2;
		break;
		case Operation ::DIVIDE:
			if(input->operand2 == 0){
				return Result::FAILURE;
			}else{
				*output = input->operand1 / input->operand2;
			}
		break;
		case Operation ::MULTIPLY:
			*output = input->operand1 * input->operand2;
		break;
	}
    return Result::SUCCESS;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main(int argc, char** argv) {
	
	int arr[] = {10,15,10,-5,40,50,0,10,44,-25};
	size_t x = sizeof(arr)/sizeof(int);
    printArray(arr,x);
	
	cout << sumOfTwoNumbersFromConsole() << endl;
	
	
	const char* txt = "Hello";
	if(containsUpperCase(txt)){
		cout << "True" << endl;
	}
	else{
		cout << "False" << endl;
	}
	
	if(isAscending(arr,x)){
		cout << "True" << endl;
	}
	else{
		cout << "False" << endl;
	}
	
	
	shiftUp(arr,x);
	cout << endl;
	reverse(arr,x);
	cout << endl;
	 
	Line *usecka = new Line;
	usecka->start.x = 10;
	usecka->start.y = 20;
	  
	usecka->end.x = 100;
	usecka->end.y = 50;
	  
	cout << length(usecka) << endl;;
	delete usecka;
	
	Line usecka_ref;
	usecka_ref.start.x = 10;
	usecka_ref.start.y = 20;
	  
	usecka_ref.end.x = 100;
	usecka_ref.end.y = 50;
	
	cout << length(&usecka_ref) << endl;
	
	char str[] = "Marcin";
	int yer = 10;
	Student *st;
	st = createStudent(str,yer);
	cout << st->name << " " << st->year << endl;
	delete st;
	
	int *out = new int;
	CalculationInput *in = new CalculationInput;
	in->operand1 = 40;
	in->operand2 = 20;
	in->operation = Operation::DIVIDE;
	calculate(out,in);
	cout << *out << endl;
	in->operation = Operation::MINUS;
	calculate(out,in);
	cout << *out << endl;
	in->operation = Operation::MULTIPLY;
	calculate(out,in);
	cout << *out << endl;
	in->operation = Operation::PLUS;
	calculate(out,in);
	cout << *out << endl;
	delete out;
	delete in;
}