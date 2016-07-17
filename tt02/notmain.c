
#define TKS (*((volatile unsigned int *)0177560))
#define TKB (*((volatile unsigned int *)0177562))
#define TPS (*((volatile unsigned int *)0177564))
#define TPB (*((volatile unsigned int *)0177566))

static void punch ( unsigned int x )
{
    while((TPS&0x80)==0) continue;
    TPB=x;
}

static void drain_tto ( void )
{
    while((TPS&0x80)==0) continue;
}

static unsigned int keyboard ( void )
{
    unsigned int data;

    while((TKS&0x80)==0) continue;
    data=TKB;
    TKS|=1;
    return(data);
}

void notmain ( void )
{
    unsigned int ra;

    TKS|=1;
    for(ra=0x30;ra<=0x37;ra++) punch(ra);
    punch(0x0D);
    punch(0x0A);
    while(1)
    {
        ra=keyboard();
        if(ra==0x1B) break;
        if(ra==0x0D) punch(0x0A);
        punch(ra);
    }
    drain_tto();
    return;
}
