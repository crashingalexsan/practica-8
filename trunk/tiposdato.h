struct SECBOOT {
	char jump[4];
	char nombre_disco[8];
	unsigned char sec_superbloque;
	unsigned char sec_mapa_bits_nodos_i;
	unsigned char sec_mapa_bits_bloques;
	unsigned short sec_tabla_nodos_i;
	unsigned short sec_logicos_totales;
	unsigned char sec_x_bloque;
	unsigned char heads;
	unsigned char cyls;
	unsigned char secfis;
	unsigned char codigoboot[487];
};

struct INODE {

char name[22];
unsigned short uid;
unsigned short gid;
unsigned short perm;
unsigned int fechahoracreacion;
unsigned int fechahoramodif;
unsigned int tam;
unsigned short aptdir[10];
unsigned short indirect;
unsigned short indirectdoble;
};

struct DATE
{
unsigned short sec;
unsigned short min;
unsigned short hour;
unsigned short day;
unsigned short month;
unsigned short year;
};
