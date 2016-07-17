
extern void dummy ( unsigned int );

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

void notmain ( void )
{
    unsigned int ra;

    for(ra=0x30;ra<=0x37;ra++) punch(ra);
    dummy(ra);
    drain_tto();
    return;
}
