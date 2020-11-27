#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "header.h"
int* vyp_datum(char *datum){
	char ddatum[11]={'\0'};
	int i=0;
	for(int i=0;i<strlen(datum);i++){
		ddatum[i]=datum[i];
	}
	int *data=(int*)malloc(3*sizeof(int));
	char *token;
	token=strtok(ddatum, "-");
   while( token != NULL ) {
		if(i==0){
			data[i]=atoi(token);
			token = strtok(NULL, "-");
			i++;
		}
		if(i==1){
			data[i]=atoi(token);
			token = strtok(NULL, "-");
			i++;
		}
		if(i==2){
			data[i]=atoi(token);
			token = strtok(NULL, "-");
			i++;
		}
   }
   return data;
}
int zistit_out(int argc,char **argv, char *out){
	for(int i=0;i<argc;i++){
		if(strcmp(argv[i],out)==0){
			return 1;
		}
	}
	return 0;
}
int koniec(int argc, char **argv){
	int d=0;
	for(int x=0; x<argc;x++){
		if(strcmp(argv[x],"-i")!=0){
			d++;
		}
		if(strcmp(argv[1],"-i")!=0 && d==argc){
			return 0;
		}
	}
	return 1;
}
imp_data *nacitaj_subor(int argc, char **argv,imp_data *pole_dat,char *subor){
	FILE *f;
	int len=0;
	
	if(koniec(argc,argv)==0){
		printf("koniec");
		exit(-1);
	}
	f=fopen(subor,"r");
	if(f==NULL){
		exit(-1);
	}
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	len=len/38;
	rewind(f);
	pole_dat=(imp_data*)malloc(len*sizeof(imp_data));
	
	if(pole_dat==NULL){
		printf("Nejde to\n");
	}
	int i=0;
	while(fscanf(f,"%d-%d-%d %d %lf %lf",
				&pole_dat[i].datum.rok,
				&pole_dat[i].datum.mesiac,
				&pole_dat[i].datum.den,
				&pole_dat[i].IMEI,
				&pole_dat[i].GPS_LAT,
				&pole_dat[i].GPS_LON
                 )!=EOF){
        i++;
    }
	fclose(f);
	return pole_dat;
}
int sizes(char **argv,char *subor){
	int len;
	FILE *f;
	f=fopen(subor,"r");
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	len=len/38;
	rewind(f);
	fclose(f);
	return len;
}
int cmpfunc (const void * pa, const void * pb) {
	imp_data a = * ((imp_data*) pa); 
	imp_data b = * ((imp_data*) pb);
	int den1,den2;
	den1=a.datum.den+a.datum.mesiac*31+a.datum.rok*365;
	den2=b.datum.den+b.datum.mesiac*31+b.datum.rok*365;
     return den2 - den1;
}
double haversine(double lat1, double lon1, 
                        double lat2, double lon2) 
    { 
        double dLat = (lat2 - lat1) * 
                      M_PI / 180.0; 
        double dLon = (lon2 - lon1) *  
                      M_PI / 180.0; 
  
        lat1 = (lat1) * M_PI / 180.0; 
        lat2 = (lat2) * M_PI / 180.0; 
   
        double a = pow(sin(dLat / 2), 2) +  
                   pow(sin(dLon / 2), 2) *  
                   cos(lat1) * cos(lat2); 
        double rad = 6371; 
        double c = 2 * asin(sqrt(a)); 
        return rad * c *1000; 
}
void param_bez(imp_data *pole_dat,char **argv,int argc,char *subor){
	printf("bez\n");
	int len=sizes(argv,subor);
	FILE *fp;
	qsort(pole_dat,len,sizeof(imp_data),cmpfunc);
	char *out="out";
	if(zistit_out(argc,argv,out)==1){
		fp = fopen ("output.txt", "w+");
		if(fp==NULL){
			printf("error\n");
		}
		for(int x=0; x<len;x++){
		fprintf(fp,"%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
			,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
		}
		fclose(fp);
	}
	else{
		for(int x=0; x<len;x++){
		printf("%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
			,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
		}
	}
	
}	
void param_u(imp_data *pole_dat,char **argv,int argc,char *subor){
	printf("u\n");
	int imei;
	int len=sizes(argv,subor);
	char *out="out";
	FILE *fp;
	if(zistit_out(argc,argv,out)==1){
		imei=atoi(argv[5]);
		fp = fopen ("output.txt", "w+");
		if(fp==NULL){
			printf("error\n");
		}
		for(int x=0; x<len;x++){
			if(pole_dat[x].IMEI==imei){
				fprintf(fp,"%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
				,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
			}
		}
		fclose(fp);
	}
	else{
		imei=atoi(argv[4]);
		for(int x=0; x<len;x++){
			if(pole_dat[x].IMEI==imei){
				printf("%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
				,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
			}
		}
	}
}
void param_l(imp_data *pole_dat,char **argv,int argc,char *subor){
	printf("l\n");
	int len=sizes(argv,subor);
	double lon,lat,distance;
	char *out="out";
	FILE *fp;
	if(zistit_out(argc,argv,out)==1){
		fp = fopen ("output.txt", "w+");
		if(fp==NULL){
			printf("error\n");
		}
		lat=atof(argv[5]);
		lon=atof(argv[6]);
		distance=atof(argv[7]);
		for(int x=0; x<len;x++){
			if(haversine(lat,lon,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON)<=distance){
				fprintf(fp,"%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
				,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
			}
		}
		fclose(fp);
	}
	else{
		lat=atof(argv[4]);
		lon=atof(argv[5]);
		distance=atof(argv[6]);
		for(int x=0; x<len;x++){
			if(haversine(lat,lon,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON)<=distance){
				printf("%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
				,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
			}
		}
	}
}
void param_t(imp_data *pole_dat,char **argv,int argc,char *subor){
	printf("t\n");
	int len=sizes(argv,subor);
	char *out="out";
	char *start,*end;
	FILE *fp;
	if(zistit_out(argc,argv,out)==1){
		fp = fopen ("output.txt", "w+");
		if(fp==NULL){
			printf("error\n");
		}
		 
		start=argv[5];
		 end=argv[6];
		 
		 int *int_start,*int_end;
		 int_start=vyp_datum(start);
		 int_end=vyp_datum(end);
		 
		for(int x=0; x<len; x++){
			if(int_start[0]==int_end[0]){
				if(int_start[0]==pole_dat[x].datum.rok){
					if(int_start[1]<= pole_dat[x].datum.mesiac && int_end[1]>=pole_dat[x].datum.mesiac){
						if(int_start[2]<= pole_dat[x].datum.den && int_end[2]>=pole_dat[x].datum.den){
							fprintf(fp,"%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
							,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
						}
					}
				}
			}
			else{
				if(int_start[0]==pole_dat[x].datum.rok){
					if(int_start[1]<= pole_dat[x].datum.mesiac){
						if(int_start[2]<= pole_dat[x].datum.den){
							fprintf(fp,"%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
							,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
							
						}
					}
				}
				if(int_end[0]==pole_dat[x].datum.rok){
					if(int_end[1]>=pole_dat[x].datum.mesiac){
						if(int_end[2]>=pole_dat[x].datum.den){
							fprintf(fp,"%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
							,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
						}
					}
				}
			}
		}
		fclose(fp);
	}
	else{
		 start=argv[4];
		 end=argv[5];
		 
		 int *int_start,*int_end;
		 int_start=vyp_datum(start);
		 int_end=vyp_datum(end);
		 
		for(int x=0; x<len; x++){
			if(int_start[0]==int_end[0]){
				if(int_start[0]==pole_dat[x].datum.rok){
					if(int_start[1]<= pole_dat[x].datum.mesiac && int_end[1]>=pole_dat[x].datum.mesiac){
						if(int_start[2]<= pole_dat[x].datum.den && int_end[2]>=pole_dat[x].datum.den){
							printf("%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
							,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
						}
					}
				}
			}
			else{
				if(int_start[0]==pole_dat[x].datum.rok){
					if(int_start[1]<= pole_dat[x].datum.mesiac){
						if(int_start[2]<= pole_dat[x].datum.den){
							printf("%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
							,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
							
						}
					}
				}
				if(int_end[0]==pole_dat[x].datum.rok){
					if(int_end[1]>=pole_dat[x].datum.mesiac){
						if(int_end[2]>=pole_dat[x].datum.den){
							printf("%d-%d-%d %d %.5lf %.5lf\n",pole_dat[x].datum.rok,pole_dat[x].datum.mesiac,pole_dat[x].datum.den,pole_dat[x].IMEI
							,pole_dat[x].GPS_LAT,pole_dat[x].GPS_LON);
						}
					}
				}
			}
		}
	}
}
void param_s(imp_data *pole_dat,char **argv,int argc,char *subor){
	printf("s\n");
}

char* spracuj_parametre(int argc, char **argv,char *subor,imp_data *pole_dat,pfunkcia *fun){
	int opt,st=0;
	while((opt=getopt(argc,argv,"i:ults"))!=-1){
		switch(opt){
			case 'i':
				subor=optarg;
				if(st==0){
					fun[0]=param_bez;
				}
				break;
			case 'u':
				st++;
				fun[0]=param_u;
				break;
			case 'l':
				st++;
				fun[0]=param_l;
				break;
			case 't':
				st++;
				fun[0]=param_t;
				break;
			case 's':
				st++;
				fun[0]=param_s;
				break;
			default:
				break;
		}
	}
	return subor;
}
void zapisovanie(pfunkcia pole[poc_param],imp_data *pole_dat,char **argv,int argc,char *subor){
	pole[0](pole_dat,argv,argc,subor);
}


int main(int argc, char **argv)
{
	char *subor=NULL;
	imp_data *pole_dat=NULL;
	pfunkcia pole[poc_param];
	subor=spracuj_parametre(argc,argv,subor,pole_dat,pole);
	pole_dat=nacitaj_subor(argc,argv,pole_dat,subor);
	zapisovanie(pole,pole_dat,argv,argc,subor);
}
