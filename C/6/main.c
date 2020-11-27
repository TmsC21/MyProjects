#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define MAX_LEN 1000
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void cislo_vstup(int argc, char **argv){
	int cisla[argc],n=0;
	for(int i=2;i<argc;i++){
		cisla[i-2]=atoi(argv[i]);
	}
	qsort(cisla,argc-2,sizeof(int),cmpfunc);
	
	for(int i=0;i<argc-2;i++){
		n=cisla[i];
		if(n==cisla[i+1]){
			printf("ERR03");
			exit(-1);
		}
		if(cisla[i]!=i+1){
			printf("ERR03");
			exit(-1);
		}
	}
}

char *uprav_text(char *text){
	char *finish_pole=(char*)malloc(strlen(text)*sizeof(char));
	int len_max=strlen(text),d=0;
	char znaky[32]={'\0'};
	
	for(int i=33;i<127;i++){
		if((i>64 && i<91) || (i>96 && i<123) || (i>47 && i<58)){
			continue;
		}
		else{
			znaky[d]=i+'\0';
			d++;
		}
	}
	d=0;
	for(int i=0;i<len_max;i++){
			switch(text[i]){
				case '1':
				finish_pole=(char*)realloc(finish_pole,5+strlen(finish_pole)*sizeof(char));
					finish_pole[d]='J';
					d++;
					finish_pole[d]='E';
					d++;
					finish_pole[d]='D';
					d++;
					finish_pole[d]='N';
					d++;
					finish_pole[d]='A';
					d++;
				break;
				case '2':
				finish_pole=(char*)realloc(finish_pole,3+strlen(finish_pole)*sizeof(char));
					finish_pole[d]='D';
					d++;
					finish_pole[d]='V';
					d++;
					finish_pole[d]='A';
					d++;
				break;
				case '3':
				finish_pole=(char*)realloc(finish_pole,3+strlen(finish_pole)*sizeof(char));
					finish_pole[d]='T';
					d++;
					finish_pole[d]='R';
					d++;
					finish_pole[d]='I';
					d++;
				break;
				case '4':
				finish_pole=(char*)realloc(finish_pole,5+strlen(finish_pole)*sizeof(char));
					finish_pole[d]='S';
					d++;
					finish_pole[d]='T';
					d++;
					finish_pole[d]='Y';
					d++;
					finish_pole[d]='R';
					d++;
					finish_pole[d]='I';
					d++;
				break;
				case '5':
				finish_pole=(char*)realloc(finish_pole,3+strlen(finish_pole)*sizeof(char));
					finish_pole[d]='P';
					d++;
					finish_pole[d]='A';
					d++;
					finish_pole[d]='T';
					d++;
				break;
				case '6':
				finish_pole=(char*)realloc(finish_pole,4+strlen(finish_pole)*sizeof(char));
					finish_pole[d]='S';
					d++;
					finish_pole[d]='E';
					d++;
					finish_pole[d]='S';
					d++;
					finish_pole[d]='T';
					d++;
				break;
				case '7':
				finish_pole=(char*)realloc(finish_pole,5+strlen(finish_pole)*sizeof(char));
					finish_pole[d]='S';
					d++;
					finish_pole[d]='E';
					d++;
					finish_pole[d]='D';
					d++;
					finish_pole[d]='E';
					d++;
					finish_pole[d]='M';
					d++;
				break;
				case '8':
				finish_pole=(char*)realloc(finish_pole,4+strlen(finish_pole)*sizeof(char));
					finish_pole[d]='O';
					d++;
					finish_pole[d]='S';
					d++;
					finish_pole[d]='E';
					d++;
					finish_pole[d]='M';
					d++;
				break;
				case '9':
				finish_pole=(char*)realloc(finish_pole,5+strlen(finish_pole)*sizeof(char));
					finish_pole[d]='D';
					d++;
					finish_pole[d]='E';
					d++;
					finish_pole[d]='V';
					d++;
					finish_pole[d]='A';
					d++;
					finish_pole[d]='T';
					d++;
				break;
				case '0':
				finish_pole=(char*)realloc(finish_pole,4+strlen(finish_pole)*sizeof(char));
					finish_pole[d]='N';
					d++;
					finish_pole[d]='U';
					d++;
					finish_pole[d]='L';
					d++;
					finish_pole[d]='A';
					d++;
				break;
				default:
					finish_pole[d]=text[i];
					d++;
				}
		}
	finish_pole[d]='\0';
	d=1;
	len_max=strlen(finish_pole);
	int del=9999999;
	int poc=0;
	
	for(int i=0;i<len_max;i++){
		for(int y=0; y<32; y++){
			if(finish_pole[i]==znaky[y]){
				poc++;
			}
		}
	}
	
	char *pole=(char*)malloc(1+(len_max-poc)*sizeof(char));
	for(int i=0;i<len_max;i++){
			for(int y=0; y<32; y++){
				if(finish_pole[i]==znaky[y]){
					del=i;
				}
			}
		if(del!=i){
			pole[d-1]=finish_pole[i];
			d++;
		}
	}
	pole[d-1]='\0';

	for(int i=0;i<strlen(pole);i++){
		pole[i]=toupper(pole[i]);
	}
	if(strlen(pole)>1000){
		printf("ERR05");
		exit(-1);
	}
	free(finish_pole);
	return pole;
}

char *sprac_vstupu(int argc, char **argv,char text[]){
	char str[1500];
	char c=32+'\0';
	int x=0,y=0,o=1;
	int kon;
	fgets(str,sizeof(str),stdin);
	
	for(int i=0;i<1500;i++){
		if(str[i]==c && str[i+1]==c){
			kon=i+1;
		}
	}
	for(int i=0;i<kon;i++){
		if(str[i]==c){
			x++;
		}
	}
	for(int i=0;i<kon;i++){
		if(str[i]==c){
			y++;
		}
		if(y<x){
			if(str[i]==c){
				continue;
			}
			else{											//				text: Vitamin D ochrani proti Covid-19.
				text=(char*)realloc(text,sizeof(char)*o);
				text[o-1]=str[i];
				o++;
			}
		}
	}
	text[o-1]='\0';
	char *pole;
	pole=uprav_text(text);
	free(text);
	return pole;
}

int* text_vstup(int argc, char **argv,int Text[]){
	char abeceda[53]={'\0'};
	char znaky[42]={'\0'};
	int x,o=0,u=0;
	int text[strlen(argv[2])];
	int pole[strlen(argv[2])];
	if(argc>3){
		printf("ERR02");
		exit(-1);
	}
	for(x=0; x<26; x++){
		abeceda[x]=x+'A';
	}
	for(int i=x; i<52 ;i++){
		abeceda[i]=(i-26)+'a';
	}
	
	for(int i=33;i<127;i++){
		if((i>64 && i<91) || (i>96 && i<123)){
			continue;
		}
		else{
			znaky[o]=i+'\0';
			o++;
		}
	}
	o=0;
	
	for(int i=0;i<strlen(argv[2]);i++){
		for(int y=0; y<42; y++){
			if(argv[2][i]==znaky[y]){
				printf("ERR02");
				exit(-1);
			}
		}
	}
	
	for(int i=0;i<strlen(argv[2]);i++){
		text[i]=argv[2][i];
	}
	for(int y=0 ;y<52 ;y++){
		for(int i=0 ;i<strlen(argv[2]) ;i++){
			if(text[i]==abeceda[y]){
				o++;
					if(o==1){
					pole[u]=text[i];
					u++;
				}
			}
		}
		o=0;
	}
	
	int k=1;
	for(int y=0 ;y<u ;y++){
		for(int i=0 ;i<strlen(argv[2]) ;i++){
			if(pole[y]==text[i]){
				Text[i]=k;
				k++;
			}
		}
	}
	return Text;
}

int* spracovanie_prep(int argc, char **argv,int *kluc_text, int prep[],int vst[]){
	int cislo=0,len=0,max_str_len=0;
	prep[0]=0;
	prep[1]=0;
	vst[0]=0;
	vst[1]=0;
	
	
	if(strcmp(argv[1],"-e")==0){
		prep[0]=1;	
	}
	else if(strcmp(argv[1],"-d")==0){
		prep[1]=1;
			
	}
	else if(strlen(argv[1])>2){
			printf("ERR01");
			exit(-1);
	}
	else{
		printf("ERR01");
		exit(-1);
	}
	
		for(int i=2; i<argc ;i++){
		len=strlen(argv[i]);
		max_str_len+=len;
			for(int y=0; y<len; y++){
				if(isdigit(argv[i][y])!=0){
					cislo++;
				}
			}
		}
	
	if(cislo==max_str_len){
		vst[0]=1;
		cislo_vstup(argc,argv);
	}
	else if(cislo!=max_str_len){
		vst[1]=1;
		kluc_text=text_vstup(argc,argv,kluc_text);
	}
	return kluc_text;
}

void sifrovanie(char *text,char **argv,int vst[],int *kluc_text,char **str, int *kluc_cislo,int argc){
		int len_str;
		if(vst[0]==1){
			len_str=argc-2;
		}
		if(vst[1]==1){
			len_str=strlen(argv[2]);
		}
		int len_final_str;
		if(strlen(text)%len_str==0){
			len_final_str=strlen(text)/len_str;
		}
		else{
			len_final_str=strlen(text)/len_str+1;
		}
		
		str=(char**)malloc(len_str*sizeof(char*));
		
		
		for(int i=0;i<len_str;i++){
			str[i]=NULL;
		}
		int d=0;
		char *text_oprava=(char*)malloc(1+strlen(text)*sizeof(char));
		for(int y=0;y<len_str;y++){
			for(int i=0;i<len_final_str;i++){
				if(d>strlen(text)){
					continue;
				}
				else{
					if((i*len_str+y)>=strlen(text)){
						continue;
					}
					else{
						text_oprava[d]=text[i*len_str+y];
						text_oprava[d+1]='\0';
					}
				}
				d++;
			}
		}
		int vypocet=strlen(text_oprava)%len_str;
		int pocet_riadkov=len_final_str;
		int e=0,poce=0;
		for(int y=0;y<len_str;y++){
			if(y==vypocet){
				pocet_riadkov-=1;
			}
			str[y]=(char*)realloc(str[y],1+pocet_riadkov*sizeof(char));
			for(int i=0;i<strlen(text_oprava);i++){
				if(poce<pocet_riadkov){
					str[y][poce]=text_oprava[e];
					str[y][poce+1]='\0';
					e++;
				}
				poce++;
			}
			poce=0;
		}
		free(text_oprava);
		char *konecny_text=(char*)malloc(1+strlen(text)*sizeof(char));
		
		int pocet=0,kek=0;
		
		
		if(vst[1]==1){
			for(int i=0;i<len_str;i++){
				for(int y=0;y<len_str;y++){
					if(kluc_text[y]==i+1){
						pocet++;
						if(pocet==1){
							strcpy(konecny_text,str[kek]);
						}
						else{
							strcat(konecny_text,str[kek]);
						}
					}
					else{
						kek++;
					}
				}
				kek=0;
			}
			
		}
		if(vst[0]==1){
			for(int i=2;i<argc;i++){
				kluc_cislo[i-2]=atoi(argv[i]);
			}
			for(int i=0;i<len_str;i++){
				for(int y=0;y<len_str;y++){
					if(kluc_cislo[y]==i+1){
						pocet++;
						if(pocet==1){
							strcpy(konecny_text,str[kek]);
						}
						else{
							strcat(konecny_text,str[kek]);
						}
					}
					else{
						kek++;
					}
				}
				kek=0;
			}
		}
		
		konecny_text[strlen(text)]='\0';
		for(int i=0;i<strlen(konecny_text);i++){
			if(i%5==0 && i!=0){
				if(i+1==strlen(konecny_text) && strlen(konecny_text)%5==0){
					continue;
				}
				else{
					printf(" ");
				}
			}
			printf("%c",konecny_text[i]);
		}
		printf("\n\n");
		free(text_oprava);
		free(konecny_text);
		for(int i=0;i<len_str;i++){
			free(str[i]);
		}
		free(str);
}

int main(int argc, char **argv)
{
	int prep[2];
	int vst[2];
	int *kluc_text=(int*)calloc((argc-2),sizeof(int));
	char *text=NULL;
	char**str=NULL;
	int kluc_cislo[argc];
	
	kluc_text=spracovanie_prep(argc,argv,kluc_text,prep,vst);
	text=sprac_vstupu(argc,argv,text);
	
	if(prep[0]==1){
		sifrovanie(text,argv,vst,kluc_text,str,kluc_cislo,argc);
	}
	free(kluc_text);
	return 0;
}
