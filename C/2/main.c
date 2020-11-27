#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define V 100
#define v 6
int pravdepodobnost(int podmienky[],int pocet){
	int r=rand()%101;
	if(r<=podmienky[pocet]){
		return 1;
	}
	else{
		return 0;
	}
}
void nakres(int Pole[]){
		for(int i=0; i<V-1;i++){
			if(Pole[i]==1){
				printf("*");
			}
			else{
				printf(" ");
			}	
		}
	printf("\n");
}
void uplatnenie_pravidla(int Pole[],int podmienky[],int poc_podmienok,int opakovanie){
	int x=poc_podmienok/2,pocet=0,z=poc_podmienok/2,y=0,p=0,o=0; 
	int new_pole[V];
	nakres(Pole);
	for(p=0; p<opakovanie; p++){
		for(int i=0; i<V-1; i++){
			if(poc_podmienok==1){
				if(Pole[i]==1){
					pocet++;
				}
				new_pole[i]=pravdepodobnost(podmienky,pocet);
				pocet=0;
			}
			else if(x!=0){
				for(y=x; y<=poc_podmienok; y++){
					if(Pole[x]==1){
						pocet++;
					}
					if(x!=0){
						x=x-1;
					}
				}
				new_pole[i]=pravdepodobnost(podmienky,pocet);
				pocet=0;
			}
			else if(x==0 || o==0){
				for(y=i; y<=poc_podmienok+i; y++){
					if(Pole[y-z]==1){
						pocet+=1;
					}
				}
				new_pole[i]=pravdepodobnost(podmienky,pocet);
				pocet=0;
				if(i==i-z){
					o=z;
				}
			}
			else if(o!=0){
				for(y=i; y<=V-o-1; y++){
					if(Pole[y]==1){
						pocet++;
					}
					if(o!=0){
						o=o-1;
					}
				}
				new_pole[i]=pravdepodobnost(podmienky,pocet);
				pocet=0;
			}
		}
		
		printf("\n");
		for(int i=0; i<V-1;i++){
			Pole[i]=new_pole[i];
		}
		nakres(Pole);
	}
	
}
int podmien(int podmienky[]){
	int poc_podmienok=0,podmienka=0;
	
	printf("Zadaj pocet podmienok ");
	scanf("%d",&poc_podmienok);
	
	for(int i=0;i<poc_podmienok;i++){
		printf("Zadaj podmienku ");
		scanf("%d",&podmienka);
		podmienky[i]=podmienka;
	}
	return poc_podmienok-1;
}
void Calcul(){
	int Pole[V],podmienky[v],poc_podmienok,opakovanie;
	for(int i=0; i<V-1;i++){
		Pole[i]=rand()%2;
	}
	printf("Zadaj pocet opakovani ");
	scanf("%d",&opakovanie);
	
	poc_podmienok=podmien(podmienky);
	uplatnenie_pravidla(Pole,podmienky,poc_podmienok,opakovanie);
}
int main(int argc, char **argv)
{
	srand(time(0));
	Calcul();
}

