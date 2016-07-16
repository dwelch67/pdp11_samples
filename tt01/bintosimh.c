
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char data[0x8000];
unsigned char header[6];

FILE *fpin;
FILE *fpout;

int main ( int argc, char *argv[] )
{
    unsigned int ra;

    unsigned int len;
    unsigned int sum;

    if(argc<3)
    {
        printf("bintosim input output\n");
        return(1);
    }
    fpin=fopen(argv[1],"rb");
    if(fpin==NULL)
    {
        printf("Error opening file [%s]\n",argv[1]);
        return(1);
    }
    len=fread(data,1,sizeof(data),fpin);
    fclose(fpin);
    printf("%u bytes read\n",len);

    fpout=fopen(argv[2],"wb");
    if(fpout==NULL)
    {
        printf("Error creating file [%s]\n",argv[2]);
        return(1);
    }
    header[0]=0x01;
    header[1]=0x00; //??
    ra=len+6;
    header[2]=(ra>>0)&0xFF;
    header[3]=(ra>>8)&0xFF;
    header[4]=0x00;
    header[5]=0x00;

    sum=0;
    for(ra=0;ra<6;ra++) sum+=header[ra];
    fwrite(header,1,6,fpout);
    fwrite(data,1,len,fpout);
    for(ra=0;ra<len;ra++) sum+=data[ra];
    sum=0x100-sum;

    fwrite(&sum,1,1,fpout);


    header[0]=0x01;
    header[1]=0x01; //??
    header[2]=6;
    header[3]=0;
    header[4]=0x00;
    header[5]=0x00;
    fwrite(header,1,6,fpout);


        //001             ---
        //xxx              |
        //lo_count         |
        //hi_count         |
        //lo_origin        > count bytes
        //hi_origin        |
        //data byte        |
        //:                |
        //data byte       ---
        //checksum



    fclose(fpout);

    return(0);
}

