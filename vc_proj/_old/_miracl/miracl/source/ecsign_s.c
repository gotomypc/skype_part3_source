/*
 *   Elliptic Curve Digital Signature Algorithm (ECDSA)
 *
 *
 *   This program asks for the name of a <file>, computes its message digest,
 *   signs it, and outputs the signature to a file <file>.ecs. It is assumed 
 *   that curve parameters are available from a file common.ecs, as well as 
 *   the private key of the signer previously generated by the ecsgen program
 *
 *   The curve is y^2=x^3+Ax+B mod p
 *
 *   The file common.ecs is presumed to exist, and to contain the domain
 *   information {p,A,B,q,x,y}, where A and B are curve parameters, (x,y) are
 *   a point of order q, p is the prime modulus, and q is the order of the 
 *   point (x,y). In fact normally q is the prime number of points counted
 *   on the curve. 
 *
 *   This program is written for static mode.
 *   For a 160-bit modulus p, MR_STATIC could be defined as 5 in mirdef.h
 *   for a 32-bit processor, or 10 for a 16-bit processor.
 *   The system parameters can be found in the file common.ecs
 *   Assumes MR_GENERIC_MT is defined in mirdef.h
 *
 *
 *   Copyright (c) 1997-2005 Shamus Software Ltd.
 */

#include <stdio.h>
#include "miracl.h"
#include <stdlib.h>
#include <string.h>

void strip(char *name)
{ /* strip off filename extension */
    int i;
    for (i=0;name[i]!='\0';i++)
    {
        if (name[i]!='.') continue;
        name[i]='\0';
        break;
    }
}

static void hashing(miracl *mip,FILE *fp,big hash)
{ /* compute hash function */
    char h[20];
    int len,ch;
    sha sh;
    shs_init(&sh);
    while ((ch=fgetc(fp))!=EOF) shs_process(&sh,ch);
    shs_hash(&sh,h);
    len=(MIRACL*MR_STATIC)/8;
    if (len>20) len=20;
    bytes_to_big(mip,len,h,hash);
}

int main()
{
    FILE *fp;
    char ifname[50],ofname[50];
    big a,b,p,q,x,y,d,r,s,k,hash;
    epoint *g;
    long seed;
    int bits;
    miracl instance;
    miracl *mip=&instance;
    char mem[MR_BIG_RESERVE(11)];            /* reserve space on the stack for 11 bigs */
    char mem1[MR_ECP_RESERVE(1)];            /* and one elliptic curve points         */
    memset(mem,0,MR_BIG_RESERVE(11));
    memset(mem1,0,MR_ECP_RESERVE(1));
 

/* get public data */

#ifndef MR_EDWARDS	
    fp=fopen("common.ecs","rt");
    if (fp==NULL)
    {
        printf("file common.ecs does not exist\n");
        return 0;
    }
    fscanf(fp,"%d\n",&bits); 
#else
    fp=fopen("edwards.ecs","rt");
    if (fp==NULL)
    {
        printf("file edwards.ecs does not exist\n");
        return 0;
    }
    fscanf(fp,"%d\n",&bits); 
#endif


    mirsys(mip,bits/4,16);   /* Use Hex internally */

    a=mirvar_mem(mip,mem,0);
    b=mirvar_mem(mip,mem,1);
    p=mirvar_mem(mip,mem,2);
    q=mirvar_mem(mip,mem,3);
    x=mirvar_mem(mip,mem,4);
    y=mirvar_mem(mip,mem,5);
    d=mirvar_mem(mip,mem,6);
    r=mirvar_mem(mip,mem,7);
    s=mirvar_mem(mip,mem,8);
    k=mirvar_mem(mip,mem,9);
    hash=mirvar_mem(mip,mem,10);

    innum(mip,p,fp);     /* modulus        */
    innum(mip,a,fp);     /* curve parameters */
    innum(mip,b,fp);     
    innum(mip,q,fp);     /* order of (x,y) */
    innum(mip,x,fp);     /* (x,y) point on curve of order q */
    innum(mip,y,fp);
    fclose(fp);

/* randomise */
    printf("Enter 9 digit random number seed  = ");
    scanf("%ld",&seed);
    getchar();
    irand(mip,seed);

    ecurve_init(mip,a,b,p,MR_PROJECTIVE);  /* initialise curve */
    g=epoint_init_mem(mip,mem1,0);
    epoint_set(mip,x,y,0,g); /* initialise point of order q */

/* calculate r - this can be done offline, 
   and hence amortized to almost nothing   */
    bigrand(mip,q,k);
    ecurve_mult(mip,k,g,g);      /* see ebrick.c for method to speed this up */
    epoint_get(mip,g,r,r);
    divide(mip,r,q,q);

/* get private key of signer */
    fp=fopen("private.ecs","rt");
    if (fp==NULL)
    {
        printf("file private.ecs does not exist\n");
        return 0;
    }
    innum(mip,d,fp);
    fclose(fp);

/* calculate message digest */
    printf("file to be signed = ");
    gets(ifname);
    strcpy(ofname,ifname);
    strip(ofname);
    strcat(ofname,".ecs");
    if ((fp=fopen(ifname,"rb"))==NULL)
    {
        printf("Unable to open file %s\n",ifname);
        return 0;
    }

    hashing(mip,fp,hash);
    fclose(fp);
/* calculate s */
    xgcd(mip,k,q,k,k,k);

    mad(mip,d,r,hash,q,q,s);
    mad(mip,s,k,k,q,q,s);
    fp=fopen(ofname,"wt");
    otnum(mip,r,fp);
    otnum(mip,s,fp);
    fclose(fp);

    memset(mem,0,MR_BIG_RESERVE(11));
    memset(mem1,0,MR_ECP_RESERVE(1));
 
    return 0;
}

