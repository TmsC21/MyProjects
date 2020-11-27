typedef struct TIME{
	int rok;
	int mesiac;
	int den;
}timestamp;
typedef struct IMP_DATA{
	int IMEI;
	double GPS_LAT;
	double GPS_LON;
	timestamp datum;
}imp_data;


typedef void (*pfunkcia)(imp_data*,char**,int,char*);

#define poc_param 1
