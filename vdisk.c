#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "vdisk.h" 
#include "tiposdato.h"

#define SECXTRACK 17
#define SUPERFICIES 160

int currentcyl[4]={0,0,0,0};
int currentsec[4]={0,0,0,0};

extern struct SECBOOT secboot;

int secboot_en_memoria = 0;
int blocksmap_en_memoria = 0;
int blocksmap[13600];
int mapa_bits_bloques;

int nodesmap_en_memoria = 0;
int nodesmap[512];
int mapa_bits_nodos_i;

int area_nodos;
int area_archivos;

int vdwritesector(int drive, int head, int cylinder, int sector, int nsecs, char *buffer)
{
    char filename[20];
    int fp;
    int timecyl,timesec;
    int sl,offset;
    sprintf(filename,"disco%c.vd",(char) drive+'0');
    fp=open(filename,O_WRONLY);
    if(fp==-1)
        return(-1);

    // Valida parámetros
    if(drive<0 || drive>3)
        return(-1);

    if(head<0 || head>=HEADS)
        return(-1);

    if(cylinder<0 || cylinder>=CYLINDERS)
        return(-1);

    if(sector<1 || sector>SECTORS)
        return(-1);

    if(sector+nsecs-1>SECTORS)
        return(-1);

    // Hace el retardo
    timesec=sector-currentsec[drive];
    if(timesec<0)
        timesec+=SECTORS;
    usleep(timesec*1000);
    currentsec[drive]=sector;

    timecyl=abs(currentcyl[drive]-cylinder);
    usleep(timecyl*1000);    
    currentcyl[drive]=cylinder;

    // Calcula la posición en el archivo
    sl=cylinder*SECTORS*HEADS+head*SECTORS+(sector-1);
    offset=sl*512;
    lseek(fp,offset,SEEK_SET);
    write(fp,buffer,512*nsecs);
    close(fp);
    return(nsecs);
}

int vdreadsector(int drive, int head, int cylinder, int sector, int nsecs, char *buffer)
{
    char filename[20];
    int fp;
    int timecyl,timesec;
    int sl,offset;
    sprintf(filename,"disco%c.vd",(char) drive+'0');
    fp=open(filename,O_RDONLY);
    if(fp==-1)
        return(-1);
                                                                                
    // Valida parámetros
    if(drive<0 || drive>3)
        return(-1);
                                                                                
    if(head<0 || head>=HEADS)
        return(-1);
                                                                                
    if(cylinder<0 || cylinder>=CYLINDERS)
        return(-1);
                                                                                
    if(sector<1 || sector>SECTORS)
        return(-1);
                                                                                
    if(sector+nsecs-1>SECTORS)
        return(-1);
                                                                                
    // Hace el retardo
    timesec=sector-currentsec[drive];
    if(timesec<0)
        timesec+=SECTORS;
    usleep(timesec*1000);
    currentsec[drive]=sector;
                                                                                
    timecyl=abs(currentcyl[drive]-cylinder);
    usleep(timecyl*1000);
    currentcyl[drive]=cylinder;
                                                                                
    // Calcula la posición en el archivo
    sl=cylinder*SECTORS*HEADS+head*SECTORS+(sector-1);
    offset=sl*512;
    lseek(fp,offset,SEEK_SET);
    read(fp,buffer,512*nsecs);
    close(fp);
    return(nsecs);
}

int vdwriteseclog(int sec_log, char *buffer)
{
    int drive = 0; 
    int head = (sec_log/SECXTRACK)%SUPERFICIES; 
    int cylinder = (sec_log/(SECXTRACK*SUPERFICIES)); 
    int sector = (sec_log%SECXTRACK)+1; 
    int nsecs = 1;

    char filename[20];
    int fp;
    int timecyl,timesec;
    int sl,offset;
    sprintf(filename,"disco%c.vd",(char) drive+'0');
    fp=open(filename,O_WRONLY);
    if(fp==-1)
        return(-1);

    // Valida parámetros
    if(drive<0 || drive>3)
        return(-1);

    if(head<0 || head>=HEADS)
        return(-1);

    if(cylinder<0 || cylinder>=CYLINDERS)
        return(-1);

    if(sector<1 || sector>SECTORS)
        return(-1);

    if(sector+nsecs-1>SECTORS)
        return(-1);

    // Hace el retardo
    timesec=sector-currentsec[drive];
    if(timesec<0)
        timesec+=SECTORS;
    usleep(timesec*1000);
    currentsec[drive]=sector;

    timecyl=abs(currentcyl[drive]-cylinder);
    usleep(timecyl*1000);    
    currentcyl[drive]=cylinder;

    // Calcula la posición en el archivo
    sl=cylinder*SECTORS*HEADS+head*SECTORS+(sector-1);
    offset=sl*512;
    lseek(fp,offset,SEEK_SET);
    write(fp,buffer,512*nsecs);
    close(fp);
    return(nsecs);
}

int vdreadseclog(int sec_log, char *buffer)
{
    int drive = 0; 
    int head = (sec_log/SECXTRACK)%SUPERFICIES; 
    int cylinder = (sec_log/(SECXTRACK*SUPERFICIES)); 
    int sector = (sec_log%SECXTRACK)+1; 
    int nsecs = 1;    

    char filename[20];
    int fp;
    int timecyl,timesec;
    int sl,offset;
    sprintf(filename,"disco%c.vd",(char) drive+'0');
    fp=open(filename,O_RDONLY);
    if(fp==-1)
        return(-1);
                                                                                
    // Valida parámetros
    if(drive<0 || drive>3)
        return(-1);
                                                                                
    if(head<0 || head>=HEADS)
        return(-1);
                                                                                
    if(cylinder<0 || cylinder>=CYLINDERS)
        return(-1);
                                                                                
    if(sector<1 || sector>SECTORS)
        return(-1);
                                                                                
    if(sector+nsecs-1>SECTORS)
        return(-1);
                                                                                
    // Hace el retardo
    timesec=sector-currentsec[drive];
    if(timesec<0)
        timesec+=SECTORS;
    usleep(timesec*1000);
    currentsec[drive]=sector;
                                                                                
    timecyl=abs(currentcyl[drive]-cylinder);
    usleep(timecyl*1000);
    currentcyl[drive]=cylinder;
                                                                                
    // Calcula la posición en el archivo
    sl=cylinder*SECTORS*HEADS+head*SECTORS+(sector-1);
    offset=sl*512;
    lseek(fp,offset,SEEK_SET);
    read(fp,buffer,512*nsecs);
    close(fp);
    return(nsecs);
}
            
int assignblock(int block)
{
	int offset = block/8;
	int shift = block%8;
	int result;
	int i;
	int sector;

	if(!secboot_en_memoria)
	{
		result = vdreadsector(0,0,0,1,1, (char *) &secboot);
		secboot_en_memoria = 1;
	}
	
	mapa_bits_bloques = secboot.sec_res + secboot.sec_mapa_bits_nodos_i;

	if(!blocksmap_en_memoria)
	{
		for(i=0;i<secboot.sec_mapa_bits_bloques;i++)
			result = vdreadseclog(mapa_bits_bloques+i, blocksmap+i*512);
		blocksmap_en_memoria = 1;
	}

	blocksmap[offset]|=(1<<shift);

	sector = (offset/512)*512;
	vdwriteseclog(mapa_bits_bloques+sector, blocksmap+sector*512);

	return(1);
} 

int unassignblock(int block)
{
	int offset = block/8;
	int shift = block%8;
	int result;
	int i;
	int sector;

	if(!secboot_en_memoria)
	{
		result = vdreadsector(0,0,0,1,1, (char *) &secboot);
		secboot_en_memoria = 1;
	}
	
	mapa_bits_bloques = secboot.sec_res + secboot.sec_mapa_bits_nodos_i;

	if(!blocksmap_en_memoria)
	{
		for(i=0;i<secboot.sec_mapa_bits_bloques;i++)
			result = vdreadseclog(mapa_bits_bloques+i, blocksmap+i*512);
		blocksmap_en_memoria = 1;
	}

	blocksmap[offset]&=(char) ~(1<<shift);

	sector = (offset/512)*512;
	vdwriteseclog(mapa_bits_bloques+sector, blocksmap+sector*512);

	return(1);
} 

int isblockfree (int block)
{
	int offset = block/8;
	int shift = block%8;
	int result;
	int i;

	if(!secboot_en_memoria)
	{
		result = vdreadsector(0,0,0,1,1, (char *) &secboot);
		secboot_en_memoria = 1;
	}
	
	mapa_bits_bloques = secboot.sec_res + secboot.sec_mapa_bits_nodos_i;

	if(!blocksmap_en_memoria)
	{
		for(i=0;i<secboot.sec_mapa_bits_bloques;i++)
			result = vdreadseclog(mapa_bits_bloques+i, blocksmap+i*512);
		blocksmap_en_memoria = 1;
	}

	if(blocksmap[offset] & (1<<shift))
		return (0);
	else
		return(1);
}
	
int nextfreeblock()
{
	int i,j;
	int result;

	if(!secboot_en_memoria)
	{
		result = vdreadsector(0,0,0,1,1, (char *) &secboot);
		secboot_en_memoria = 1;
	}
	
	mapa_bits_bloques = secboot.sec_res + secboot.sec_mapa_bits_nodos_i;

	if(!blocksmap_en_memoria)
	{
		for(i=0;i<secboot.sec_mapa_bits_bloques;i++)
			result = vdreadseclog(mapa_bits_bloques+i, blocksmap+i*512);
		blocksmap_en_memoria = 1;
	}

	i=0;
	while(blocksmap[i]==0xFF && 1<secboot.sec_mapa_bits_bloques*512)
		i++;

	if(i<secboot.sec_mapa_bits_bloques*512)
	{
		j=0;
		while(blocksmap[i] & (1<<j) && j<8)
			j++;

		return (i*8+j);
	}
	else
		return (-1);
}
//--------------------------------------Nodos---------------------------------------

int nextfreenode()
{
	int i,j;
	int result;

	if(!secboot_en_memoria)
	{
		result = vdreadsector(0,0,0,1,1, (char *) &secboot);
		secboot_en_memoria = 1;
	}
	
	mapa_bits_nodos_i = secboot.sec_res;

	if(!nodesmap_en_memoria)
	{
		for(i=0;i<secboot.sec_mapa_bits_nodos_i;i++)
			result = vdreadseclog(mapa_bits_nodos_i+i, nodesmap+i*512);
		nodesmap_en_memoria = 1;
	}

	i=0;
	while(nodesmap[i]==0xFF && 1<secboot.sec_mapa_bits_nodos_i*512)
		i++;

	if(i<secboot.sec_mapa_bits_nodos_i*512)
	{
		j=0;
		while(nodesmap[i] & (1<<j) && j<8)
			j++;

		return (i*8+j);
	}
	else
		return (-1);
}

int assignnode(int block)
{
	int offset = block/8;
	int shift = block%8;
	int result;
	int i;
	int sector;

	if(!secboot_en_memoria)
	{
		result = vdreadsector(0,0,0,1,1, (char *) &secboot);
		secboot_en_memoria = 1;
	}
	
	mapa_bits_nodos_i = secboot.sec_res + 1 ;

	if(!nodesmap_en_memoria)
	{
		for(i=0;i<secboot.sec_mapa_bits_nodos_i;i++)
			result = vdreadseclog(mapa_bits_bloques+i, nodesmap+i*512);
		nodesmap_en_memoria = 1;
	}

	nodesmap[offset]|=(1<<shift);

	sector = (offset/512)*512;
	vdwriteseclog(mapa_bits_nodos_i+sector, nodesmap+sector*512);

	return(1);
} 

int isnodefree (int block)
{
	int offset = block/8;
	int shift = block%8;
	int result;
	int i;

	if(!secboot_en_memoria)
	{
		result = vdreadsector(0,0,0,1,1, (char *) &secboot);
		secboot_en_memoria = 1;
	}
	
	mapa_bits_nodos_i = secboot.sec_res;

	if(!nodesmap_en_memoria)
	{
		for(i=0;i<secboot.sec_mapa_bits_nodos_i;i++)
			result = vdreadseclog(mapa_bits_nodos_i+i, nodesmap+i*512);
		nodesmap_en_memoria = 1;
	}

	if(nodesmap[offset] & (1<<shift))
		return (0);
	else
		return(1);
}

////////////////////------------------------------------------////////////////////////////


/////---------------------------Areas de disco----------------/////////////////////////
int getmapabitsnodos()
{
mapa_bits_nodos_i = secboot.sec_res;
return mapa_bits_nodos_i;
}

int getmapabitsdatos()
{
mapa_bits_bloques = secboot.sec_res + secboot.sec_mapa_bits_nodos_i;
return mapa_bits_bloques;
}

int getareanodos()
{
area_nodos = secboot.sec_res + secboot.sec_mapa_bits_nodos_i + mapa_bits_bloques;
return area_nodos;
}

int getareaarchivos()
{
area_archivos = secboot.sec_res + secboot.sec_mapa_bits_nodos_i + mapa_bits_bloques + area_nodos;
return area_archivos;
}

/////////////////////////////////////////////////////////////////

unsigned int datetoint(struct DATE date)
{
unsigned int val=0;

  val=date.year-1970;
  val<<=4;
  val|=date.month;
  val<<=5;
  val|=date.day;
  val<<=5;
  val|=date.hour;
  val<<=6;
  val|=date.min;
  val<<=6;
  val|date.sec;
  
  return(val);
}

int inttodate(struct DATE *date,unsigned int val)
{
  date->sec=val&0x3F;
  val>>=6;
  date->min=val&0x3F;
  val>>=6;
  date->hour=val&0x1F;
  val>>=5;
  date->day=val&0x1F;
  val>>=5;
  date->month=val&0x0F;
  val>>=4;
  date->year=(val&0x3F) + 1970;
  return(1);
}

int bloqueasector(int bloque)
{
int sector[4]; 
sector[0] = (518 + (bloque-1)*4);
sector[1] = (519 + (bloque-1)*4);
sector[2] = (520 + (bloque-1)*4);  
sector[3] = (521 + (bloque-1)*4);
return(sector);
}


