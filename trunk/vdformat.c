#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vdisk.h"
#include "tiposdato.h"

struct SECBOOT secboot;
 
int main()
{

//secboot.nombre_disco = "disco123";
secboot.sec_superbloque = 1;
secboot.sec_mapa_bits_nodos_i = 1;
secboot.sec_mapa_bits_bloques = 4;
secboot.sec_tabla_nodos_i = 512;
secboot.sec_logicos_totales = 54400;
secboot.sec_x_bloque = 4;
secboot.heads = 20;
secboot.cyls = 160;
secboot.secfis = 17;
//secboot.codigoboot = ;

printf("%d", sizeof(struct SECBOOT));

vdwritesector(0,0,0,1,1,(char *) &secboot);


}
