#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // praca so znakmi
#include <string.h> // praca s retazcami
#include <unistd.h> // funkcia getopt()
#define pocet_funkcii 10
void ToUpper(char pole_stringov[], int pocet_stringov){
	printf("ToUpper\n");
	for(int i=0; i<=pocet_stringov; i++){
		pole_stringov[i]=toupper(pole_stringov[i]);
	}
}
void ToLower(char pole_stringov[], int pocet_stringov){
	printf("ToLower\n");
	for(int i=0; i<=pocet_stringov; i++){
		pole_stringov[i]=tolower(pole_stringov[i]);
	}
}
void IsAlpha(char pole_stringov[], int pocet_stringov){
	
}

typedef void (*pFunkcie_bez_PARAM)(char*, int);
typedef void (*pFunkcie_s_PARAM)(char, int, int);
int dostatopt(int argc, char *argv[],pFunkcie_bez_PARAM prepinace_bez_PARAM[]){
	int opt,i=0;
		while((opt=getopt(argc,argv,"ula"))!=-1){
			switch(opt){
				case 'u':
					prepinace_bez_PARAM[i]=ToUpper;
					printf("1.u\n");
					i++;
					break;
				case 'l':
					prepinace_bez_PARAM[i]=ToLower;
					printf("1.l\n");
					i++;
					break;
				case 'a':
					prepinace_bez_PARAM[i]=IsAlpha;
					printf("1\n");
					i++;
					break;
				default:
					printf("err\n");
			}
		}
		return i;
}

void run_text_processor(int argc, char *argv[],int i,pFunkcie_bez_PARAM prepinace_bez_PARAM[]) {
	char str[81];
	int len=0;
	
   gets(str);
   len=strlen(str);
   for(int x=0; x<i; x++){
	   printf("pocet parametrov: %i\n",x);
	   prepinace_bez_PARAM[x](str,len);
   }
   for(int z=0; z<len; z++){
	   printf("%c",str[z]);
   }
}
 
int main(int argc, char *argv[]) {

	int i;
	pFunkcie_bez_PARAM prepinace_bez_PARAM[pocet_funkcii];
	i=dostatopt(argc, argv, prepinace_bez_PARAM);
    run_text_processor(argc, argv, i, prepinace_bez_PARAM);
    return 0;
	
}
