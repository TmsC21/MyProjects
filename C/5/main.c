#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
typedef struct _Turnus{
	int **pole;
	int R;
	int S;
}turnus;
char *to_decimal(int *pole[],int R,int S,char pole_decimal[]){
	int result=0,d=0;
	char c=0x00;
	for(int i=0; i<R; i++){
		for(int y=S-1; 0<=y; y--){
			if(pole[i][y]==1){
				result+=pow(2,d);
			}
			d++;
		}
		pole_decimal[i]=result^c;
		result=0;
		d=0;
	}
	return pole_decimal;
}

int** to_binary(char hex[],int **pole_binar,int len){
	for(int i=0;i<len;i++){
		for(int x =0 ;x<=7; x++){
			pole_binar[i][x]=(hex[i] >> x) & 0x01;
		}
	}
	return pole_binar;
}
	
int je_cislo(char *argv){
	int x = *argv+'0';
	if(strcmp(argv,"0")==0){
		return 1;
	}
	else if(isalpha(x)==0){
		return 0;
	}
	return 1;
}

int chyba(int argc,char **argv,int optind){
	int index;
	for (index = optind; index < argc; index++){
		if(atoi(argv[index])<0){
			return 1;
		}
	}
	return 0;
}

void write_binary_file(int T,int R, int S,turnus *next_pole,char **str){
	FILE *f;
	f=fopen(str[1],"wb");
	if(f==NULL){
		exit(-1);
	}
	char *pole = (char*) calloc(R,sizeof(char));
	pole=to_decimal(next_pole[T].pole,R,S,pole);
	fwrite(pole,sizeof(char),R,f);
	fclose(f);
	free(pole);
}

int** read_binary_file(char **str,int argc,int R, int S,int *pole_rs[]){
	FILE * fp;
    char *buffer=NULL;
	int len;
    fp = fopen(str[0], "rb");
	
    if (fp == NULL) {
		exit(-1);
    }
	fseek(fp,0,SEEK_END);
	len=ftell(fp);
	fseek(fp,0,SEEK_SET);
	buffer=(char*)calloc(len,sizeof(char));
	
	
	int **pole_binar=(int**) calloc(len,sizeof(int*));
	for (int i = 0;i < len;i++) {
		pole_binar[i] = (int*) calloc(8,sizeof(int));
	}
	fread(buffer, len*sizeof(char), 1, fp);
	
	pole_binar=to_binary(buffer,pole_binar,len);
	
	pole_rs=pole_binar;
	
    fclose(fp);
	return pole_rs;
}

int** read_text_file(char **str,int argc,int R, int S,int *pole_rs[]){
	FILE *f;
	f=fopen(str[0],"r+");
	char c;
	char *cislo=&c;
	int r=0,s=0,x=0;
	while((c=getc(f))!=EOF){
		if(isdigit(c)==0){
			continue;
		}
		else{
			if(r<=R){
				if(s==S){
					r++;
					s=0;
					pole_rs[r][s]=atoi(cislo);
					s++;
				}
				else{
					pole_rs[r][s]=atoi(cislo);
					s++;
				}
				x++;
				if(x==R*S){
					break;
				}
			}
		}
	}
	fclose(f);
	return pole_rs;
}

void write_text_file(int T,int R, int S,turnus *next_pole,char **str,int x){
	FILE *f;
	f=fopen(str[1],"w+");
	if(f==NULL){
		exit(-1);
	}
	if(x==1){
		for(int y=0;y<=T;y++){
			for(int i=0; i<R; i++){
				for(int x=0; x<S; x++){
					if(next_pole[y].pole[i][x]==1){
						fprintf(f,"1");
					}
					else{
						fprintf(f,"0");
					}
				}
				fprintf(f,"\n");
			}
			fprintf(f,"\n");
		}
	}
	else{
		for(int i=0; i<R; i++){
			for(int y=0; y<S; y++){
				if(next_pole[T].pole[i][y]==1){
					fprintf(f,"*");
				}
				else{
					fprintf(f," ");
				}
			}
			fprintf(f,"\n");
		}
	}
	fclose(f);
}

void print_pole(int R,int S,int *pole_rs[]){
	for(int i=0; i<R; i++){
		for(int y=0; y<S; y++){
			if(pole_rs[i][y]==1){
				printf("*");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
	}
}

int podmienky(int pocet,int stred){
	if(stred == 1){
		if(pocet == 2 || pocet == 3){
			return 1;
		}
	}
	else if(stred == 0 && pocet == 3){
		return 1;
	}
	return 0;
}

int evolve(turnus jaj,int R,int S){
	int counter=0;
			if(S==0 && jaj.pole[R][jaj.S-1]==1){//<-
				counter++;
			}
			else if(jaj.pole[R][S-1]==1){
				counter++;
			}
			if(S!=jaj.S-1 && jaj.pole[R][S+1]==1){//->
				counter++;
			}
			else if(S==jaj.S-1 && jaj.pole[R][0]==1  ){
				counter++;
			}									//	|
			if(R==jaj.R-1 && jaj.pole[0][S]==1  ){	//	v
				counter++;
			}
			else if(R!=jaj.R-1 && jaj.pole[R+1][S]==1  ){
				counter++;
			}
			if( R!=jaj.R-1 && S!=jaj.S-1 && jaj.pole[R+1][S+1]==1 ){//vpravo dole
				counter++;
			}
			else if(R==jaj.R-1 && S!=jaj.S-1 && jaj.pole[0][S+1]==1  ){
				counter++;
			}
			else if(R==jaj.R-1 && S==jaj.S-1 && jaj.pole[0][0]==1  ){
				counter++;
			}
			else if(R!=jaj.R-1 && S==jaj.S-1 && jaj.pole[R+1][0]==1  ){
				counter++;
			}
			if(R!=jaj.R-1 && S!=0 && jaj.pole[R+1][S-1]==1  ){	//	 /
				counter++;									//	v
				
			}
			else if(R==jaj.R-1 && S!=0 && jaj.pole[0][S-1]==1  ){
				counter++;
			}
			else if(R!=jaj.R-1 && S==0 && jaj.pole[R+1][jaj.S-1]==1  ){
				counter++;
			}
			else if(R==jaj.R-1 && S==0 && jaj.pole[0][jaj.S-1]==1){
				counter++;
			}
			
			if(R==0 && jaj.pole[jaj.R-1][S]==1){//	A
				counter++;					//	|
			}
			else if( R!=0 && jaj.pole[R-1][S]==1){
				counter++;
			}
			if(R!=0 && S!=jaj.S-1 && jaj.pole[R-1][S+1]==1){	//	A
				counter++;									// /
				
			}
			else if(R!=0 && S==jaj.S-1 && jaj.pole[R-1][0]==1   ){
				counter++;
			}
			else if(R==0 && S!=jaj.S-1 && jaj.pole[jaj.R-1][S+1]==1  ){
				counter++;
			}
			else if(R==0 && S==jaj.S-1 && jaj.pole[jaj.R-1][0]==1){
				counter++;
			}
			if(R!=0 && S!=0 && jaj.pole[R-1][S-1]==1  ){	//vlavo hore
				counter++;							
				
			}
			else if(R==0 && S!=0 && jaj.pole[jaj.R-1][S-1]==1){
				counter++;
			}
			else if( R!=0 && S==0 && jaj.pole[R-1][jaj.S-1]==1 ){
				counter++;
			}
			else if(R==0 && S==0 && jaj.pole[jaj.R-1][jaj.S-1]==1  ){
				counter++;
			}
	if(podmienky(counter,jaj.pole[R][S])==1){
		return 1;
	}
	else{
		return 0;
	}
	
}

void next_state(int R,int S,int T,int *pole_rs[],int param_v,char **str,int param_b){
	turnus *next_pole;
	next_pole=(turnus*)malloc((T+2)*sizeof(turnus));
	for(int i=1;i<=T+1;i++){
		next_pole[i].pole= (int**) calloc(R,sizeof(int*));
		for (int p = 0; p < R; p++) {
			next_pole[i].pole[p] = (int*) calloc(S,sizeof(int));
		}
		next_pole[i].R=R;
		next_pole[i].S=S;
	}
	next_pole[0].pole=pole_rs;
	next_pole[0].R=R;
	next_pole[0].S=S;
	for(int y=0;y<T;y++){
		for(int i=0;i<R;i++){
			for(int z=0;z<S;z++){
				if(evolve(next_pole[y],i,z)==1){
					next_pole[y+1].pole[i][z]=1;
				}
				else{
					next_pole[y+1].pole[i][z]=0;
				}
			}
		}
	}
	if(param_v==1){
		for(int y=0;y<=T;y++){
			print_pole(R,S,next_pole[y].pole);
			printf("\n");
		}
		if(param_b==1){
			write_binary_file(T,R,S,next_pole,str);
		}
		else{
			write_text_file(T,R,S,next_pole,str,1);
		}
		
	}
	else{
		print_pole(R,S,next_pole[T].pole);
		if(param_b==1){
			write_binary_file(T,R,S,next_pole,str);
		}
		else{
			write_text_file(T,R,S,next_pole,str,0);
		}
	}
	for(int i=0;i<=T;i++){
		free(next_pole[i].pole);
	}
	free(next_pole);
}

char** spracuj_parametre(int argc, char **argv,int pole[],char **str){
	pole[3]=0;
	pole[4]=0;
	int opt,index,i=0;
	while((opt=getopt(argc,argv,":bv"))!=-1){
		switch(opt){
			case 'v':
				if(chyba(argc,argv,optind)==1){
					exit(-1);
				}
				pole[3]=1;
				break;
			case 'b':
				if(chyba(argc,argv,optind)==1){
					exit(-1);
				}
				pole[4]=1;
			break;
			default:
				if(chyba(argc,argv,optind)==1){
				exit(-1);
				}
			break;
		}
		
	}
	
	int len=0;
	
	for (index = optind; index < argc; index++){
		if(i<3){
			pole[i]=atoi(argv[index]);
		}
		i++;
		if(je_cislo(argv[index])==0 && i<=3){
			exit(-1);
		}
		if(i==4){
			len=strlen(argv[index]);
			str[0]=(char*)malloc(len*sizeof(char));
			str[0]=argv[index];
		}
		if(i==5){
			len=strlen(argv[index]);
			str[1]=(char*)malloc(len*sizeof(char));
			str[1]=argv[index];
		}
	}
	if(i<3){
		exit(-1);
	}
	if((pole[0]<=0) || (pole[1]<=0)){
		exit(-1);
	}
	return str;
}

int main(int argc, char **argv)
{
	int pole_hodnot[5];
	char **str=(char**)malloc(2*sizeof(char*));
	int** pole_rs;
	str=spracuj_parametre(argc,argv,pole_hodnot,str);
	
	int R=pole_hodnot[0],S=pole_hodnot[1],T=pole_hodnot[2],param_v=pole_hodnot[3],param_b=pole_hodnot[4];
	pole_rs = (int**) calloc(R,sizeof(int*));
	
	for (int i = 0;i < R;i++) {
		pole_rs[i] = (int*) calloc(S,sizeof(int));
	}
	if(param_b==1){
		if(S%8!=0){
			while((S%8)!=0){
				S++;
			}
		}
		pole_rs=read_binary_file(str,argc,R,S,pole_rs);
		next_state(R,S,T,pole_rs,param_v,str,param_b);
	}
	else{
		pole_rs=read_text_file(str,argc,R,S,pole_rs);
		next_state(R,S,T,pole_rs,param_v,str,param_b);
	}
	for (int i = 0;i < R;i++) {
		free(pole_rs[i]);
	}
	free(str[0]);
	free(str[1]);
	free(str);
	free(pole_rs);
	return 0;
}
