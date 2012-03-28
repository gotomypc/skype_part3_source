//
// Util.c
//

#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

#include "rc4/Expand_IV.h"
#include "short_types.h"

extern int main_unpack (u8 *indata, u32 inlen);
extern int encode_to_7bit(char *buf, uint word, int limit);

int show_memory(char *mem, int len, char *text);
unsigned int Calculate_CRC32(char *crc32, int bytes);
int mysub_crc32_from_table_no_call_00853B40(unsigned int *ret_data, unsigned int a2);


int show_memory(char *mem, int len, char *text){
	int zz;
	int i;

	printf("%s\n",text);
	printf("Len: 0x%08X\n",len);

	zz=0;
	for(i=0;i<len;i++){
		printf("%02X ",mem[i] & 0xff);
		zz++;if (zz == 16) { zz=0; printf("\n ");};
	};
	printf("\n");

	return 0;
};



int first_bytes_header(u16 seqnum, char *header, int header_len, char *buf, int buf_len){	
	int len;

	len=encode_to_7bit(header, (buf_len+6)*2, 5);
	if (len==-1){
		return -1;
	};

	seqnum=bswap16(seqnum);
	memcpy(header+len,(char *)&seqnum,2);
	seqnum=bswap16(seqnum);
	len+=2;
	
	header[len]=buf_len+2;
	len++;

	header[len]=0x32;
	len++;

	seqnum--;
	seqnum=bswap16(seqnum);
	memcpy(header+len,(char *)&seqnum,2);
	len+=2;

	return len;

};


int first_bytes_header2(u16 seqnum, char *header, int header_len, char *buf, int buf_len){	
	int len;
	
	len=0;

	header[len]=buf_len+2;
	len++;

	header[len]=0x32;
	len++;

	seqnum=bswap16(seqnum);
	memcpy(header+len,(char *)&seqnum,2);
	len+=2;

	return len;

};

int first_bytes_size(u16 seqnum, char *header, int header_len, char *buf, int buf_len){	
	int len;
	
	len=0;
	len=encode_to_7bit(header, (buf_len+2)*2, 5);

	if (len==-1){
		return -1;
	};

	seqnum=bswap16(seqnum);
	memcpy(header+len,(char *)&seqnum,2);
	len+=2;

	return len;

};


//
// Encode bytes to 7 bit
//
int encode_to_7bit(char *buf, uint word, int limit){
	uint to[10];
	int i;
	int n;
	uint a;


	n=0;
	for(i=0;i<10;i++){
		to[i]=0;
	};


    for (a = word; a > 0x7F; a >>= 7, n++){ 
		
		if (n > 10) {
			//printf("7bit encoding fail\n");
			//exit(1);
			return -1;
		};

        to[n] = (u8) a | 0x80; 
		to[n+1] = (u8) a; 

	};
	to[n]=a;


	if (n > limit) {
		//printf("not enought buffer\n");
		//exit(1);
		return -1;
	};

	for(i=0;i<=n;i++){
		buf[i]=to[i] & 0xff;
	};



    return n+1;
}


/////////////////////////////////////////////////////////////////
//crc32
/////////////////////////////////////////////////////////////////

char CRC_32_Table[]=
"\x00\x00\x00\x00\x96\x30\x07\x77\x2C\x61\x0E\xEE\xBA\x51\x09\x99"
"\x19\xC4\x6D\x07\x8F\xF4\x6A\x70\x35\xA5\x63\xE9\xA3\x95\x64\x9E"
"\x32\x88\xDB\x0E\xA4\xB8\xDC\x79\x1E\xE9\xD5\xE0\x88\xD9\xD2\x97"
"\x2B\x4C\xB6\x09\xBD\x7C\xB1\x7E\x07\x2D\xB8\xE7\x91\x1D\xBF\x90"
"\x64\x10\xB7\x1D\xF2\x20\xB0\x6A\x48\x71\xB9\xF3\xDE\x41\xBE\x84"
"\x7D\xD4\xDA\x1A\xEB\xE4\xDD\x6D\x51\xB5\xD4\xF4\xC7\x85\xD3\x83"
"\x56\x98\x6C\x13\xC0\xA8\x6B\x64\x7A\xF9\x62\xFD\xEC\xC9\x65\x8A"
"\x4F\x5C\x01\x14\xD9\x6C\x06\x63\x63\x3D\x0F\xFA\xF5\x0D\x08\x8D"
"\xC8\x20\x6E\x3B\x5E\x10\x69\x4C\xE4\x41\x60\xD5\x72\x71\x67\xA2"
"\xD1\xE4\x03\x3C\x47\xD4\x04\x4B\xFD\x85\x0D\xD2\x6B\xB5\x0A\xA5"
"\xFA\xA8\xB5\x35\x6C\x98\xB2\x42\xD6\xC9\xBB\xDB\x40\xF9\xBC\xAC"
"\xE3\x6C\xD8\x32\x75\x5C\xDF\x45\xCF\x0D\xD6\xDC\x59\x3D\xD1\xAB"
"\xAC\x30\xD9\x26\x3A\x00\xDE\x51\x80\x51\xD7\xC8\x16\x61\xD0\xBF"
"\xB5\xF4\xB4\x21\x23\xC4\xB3\x56\x99\x95\xBA\xCF\x0F\xA5\xBD\xB8"
"\x9E\xB8\x02\x28\x08\x88\x05\x5F\xB2\xD9\x0C\xC6\x24\xE9\x0B\xB1"
"\x87\x7C\x6F\x2F\x11\x4C\x68\x58\xAB\x1D\x61\xC1\x3D\x2D\x66\xB6"
"\x90\x41\xDC\x76\x06\x71\xDB\x01\xBC\x20\xD2\x98\x2A\x10\xD5\xEF"
"\x89\x85\xB1\x71\x1F\xB5\xB6\x06\xA5\xE4\xBF\x9F\x33\xD4\xB8\xE8"
"\xA2\xC9\x07\x78\x34\xF9\x00\x0F\x8E\xA8\x09\x96\x18\x98\x0E\xE1"
"\xBB\x0D\x6A\x7F\x2D\x3D\x6D\x08\x97\x6C\x64\x91\x01\x5C\x63\xE6"
"\xF4\x51\x6B\x6B\x62\x61\x6C\x1C\xD8\x30\x65\x85\x4E\x00\x62\xF2"
"\xED\x95\x06\x6C\x7B\xA5\x01\x1B\xC1\xF4\x08\x82\x57\xC4\x0F\xF5"
"\xC6\xD9\xB0\x65\x50\xE9\xB7\x12\xEA\xB8\xBE\x8B\x7C\x88\xB9\xFC"
"\xDF\x1D\xDD\x62\x49\x2D\xDA\x15\xF3\x7C\xD3\x8C\x65\x4C\xD4\xFB"
"\x58\x61\xB2\x4D\xCE\x51\xB5\x3A\x74\x00\xBC\xA3\xE2\x30\xBB\xD4"
"\x41\xA5\xDF\x4A\xD7\x95\xD8\x3D\x6D\xC4\xD1\xA4\xFB\xF4\xD6\xD3"
"\x6A\xE9\x69\x43\xFC\xD9\x6E\x34\x46\x88\x67\xAD\xD0\xB8\x60\xDA"
"\x73\x2D\x04\x44\xE5\x1D\x03\x33\x5F\x4C\x0A\xAA\xC9\x7C\x0D\xDD"
"\x3C\x71\x05\x50\xAA\x41\x02\x27\x10\x10\x0B\xBE\x86\x20\x0C\xC9"
"\x25\xB5\x68\x57\xB3\x85\x6F\x20\x09\xD4\x66\xB9\x9F\xE4\x61\xCE"
"\x0E\xF9\xDE\x5E\x98\xC9\xD9\x29\x22\x98\xD0\xB0\xB4\xA8\xD7\xC7"
"\x17\x3D\xB3\x59\x81\x0D\xB4\x2E\x3B\x5C\xBD\xB7\xAD\x6C\xBA\xC0"
"\x20\x83\xB8\xED\xB6\xB3\xBF\x9A\x0C\xE2\xB6\x03\x9A\xD2\xB1\x74"
"\x39\x47\xD5\xEA\xAF\x77\xD2\x9D\x15\x26\xDB\x04\x83\x16\xDC\x73"
"\x12\x0B\x63\xE3\x84\x3B\x64\x94\x3E\x6A\x6D\x0D\xA8\x5A\x6A\x7A"
"\x0B\xCF\x0E\xE4\x9D\xFF\x09\x93\x27\xAE\x00\x0A\xB1\x9E\x07\x7D"
"\x44\x93\x0F\xF0\xD2\xA3\x08\x87\x68\xF2\x01\x1E\xFE\xC2\x06\x69"
"\x5D\x57\x62\xF7\xCB\x67\x65\x80\x71\x36\x6C\x19\xE7\x06\x6B\x6E"
"\x76\x1B\xD4\xFE\xE0\x2B\xD3\x89\x5A\x7A\xDA\x10\xCC\x4A\xDD\x67"
"\x6F\xDF\xB9\xF9\xF9\xEF\xBE\x8E\x43\xBE\xB7\x17\xD5\x8E\xB0\x60"
"\xE8\xA3\xD6\xD6\x7E\x93\xD1\xA1\xC4\xC2\xD8\x38\x52\xF2\xDF\x4F"
"\xF1\x67\xBB\xD1\x67\x57\xBC\xA6\xDD\x06\xB5\x3F\x4B\x36\xB2\x48"
"\xDA\x2B\x0D\xD8\x4C\x1B\x0A\xAF\xF6\x4A\x03\x36\x60\x7A\x04\x41"
"\xC3\xEF\x60\xDF\x55\xDF\x67\xA8\xEF\x8E\x6E\x31\x79\xBE\x69\x46"
"\x8C\xB3\x61\xCB\x1A\x83\x66\xBC\xA0\xD2\x6F\x25\x36\xE2\x68\x52"
"\x95\x77\x0C\xCC\x03\x47\x0B\xBB\xB9\x16\x02\x22\x2F\x26\x05\x55"
"\xBE\x3B\xBA\xC5\x28\x0B\xBD\xB2\x92\x5A\xB4\x2B\x04\x6A\xB3\x5C"
"\xA7\xFF\xD7\xC2\x31\xCF\xD0\xB5\x8B\x9E\xD9\x2C\x1D\xAE\xDE\x5B"
"\xB0\xC2\x64\x9B\x26\xF2\x63\xEC\x9C\xA3\x6A\x75\x0A\x93\x6D\x02"
"\xA9\x06\x09\x9C\x3F\x36\x0E\xEB\x85\x67\x07\x72\x13\x57\x00\x05"
"\x82\x4A\xBF\x95\x14\x7A\xB8\xE2\xAE\x2B\xB1\x7B\x38\x1B\xB6\x0C"
"\x9B\x8E\xD2\x92\x0D\xBE\xD5\xE5\xB7\xEF\xDC\x7C\x21\xDF\xDB\x0B"
"\xD4\xD2\xD3\x86\x42\xE2\xD4\xF1\xF8\xB3\xDD\x68\x6E\x83\xDA\x1F"
"\xCD\x16\xBE\x81\x5B\x26\xB9\xF6\xE1\x77\xB0\x6F\x77\x47\xB7\x18"
"\xE6\x5A\x08\x88\x70\x6A\x0F\xFF\xCA\x3B\x06\x66\x5C\x0B\x01\x11"
"\xFF\x9E\x65\x8F\x69\xAE\x62\xF8\xD3\xFF\x6B\x61\x45\xCF\x6C\x16"
"\x78\xE2\x0A\xA0\xEE\xD2\x0D\xD7\x54\x83\x04\x4E\xC2\xB3\x03\x39"
"\x61\x26\x67\xA7\xF7\x16\x60\xD0\x4D\x47\x69\x49\xDB\x77\x6E\x3E"
"\x4A\x6A\xD1\xAE\xDC\x5A\xD6\xD9\x66\x0B\xDF\x40\xF0\x3B\xD8\x37"
"\x53\xAE\xBC\xA9\xC5\x9E\xBB\xDE\x7F\xCF\xB2\x47\xE9\xFF\xB5\x30"
"\x1C\xF2\xBD\xBD\x8A\xC2\xBA\xCA\x30\x93\xB3\x53\xA6\xA3\xB4\x24"
"\x05\x36\xD0\xBA\x93\x06\xD7\xCD\x29\x57\xDE\x54\xBF\x67\xD9\x23"
"\x2E\x7A\x66\xB3\xB8\x4A\x61\xC4\x02\x1B\x68\x5D\x94\x2B\x6F\x2A"
"\x37\xBE\x0B\xB4\xA1\x8E\x0C\xC3\x1B\xDF\x05\x5A\x8D\xEF\x02\x2D"
"\x00\x00\x21\x10\x42\x20\x63\x30\x84\x40\xA5\x50\xC6\x60\xE7\x70"
;




unsigned int Calculate_CRC32(char *crc32, int bytes) {
  unsigned int esi_var;
  unsigned int eax,ebx,ecx,ecx1;
  int i;

  esi_var = -1;
  i=bytes;

  if (bytes) {
	  do {
		eax=esi_var;
		ebx=0;
		ebx=crc32[0] & 0xff;
		ecx=eax;
		ecx=ecx & 0xff;
		ecx=ecx ^ ebx;
		eax=eax >> 8;
		memcpy((char *)&ecx1,(char *)CRC_32_Table+ecx*4,4);
		ecx=ecx1;		
		ecx=ecx ^ eax;
		crc32++;
		i--;
		esi_var=ecx;
	  }while(i);
  };

  return esi_var;

};

/////////////////////////////////////////////////

//
// find slot
//
int slot_find(u8 *str) {
	int ret;
	unsigned int ret_data;
	unsigned int a2;
	int i;


	ret_data=0xFFFFFFFF;

	for (i=0;i<5;i++){
		a2=str[i];
		ret=mysub_crc32_from_table_no_call_00853B40(&ret_data, a2);
	};


	ret=ret & 0x7FF;

	return ret;
};

#define _BYTE  unsigned char
#define _WORD  unsigned short
#define _DWORD unsigned long


int mysub_crc32_from_table_no_call_00853B40(unsigned int *ret_data, unsigned int a2)
{
  int result; // eax@1
  unsigned int v3; // eax@1
  int v4; // esi@1
  int v5; // esi@1
  int v6; // edx@1
  int t_data;
  int t_index;

  v3 = a2 >> 8;
  
  t_data=0;
  t_index=(_BYTE)a2 ^ *(_DWORD *)ret_data & 0xFF;
  memcpy((char *)&t_data,(char *)CRC_32_Table+t_index*4,4);
  v4 = (*(_DWORD*)ret_data >> 8) ^ t_data;
  //v4 = (*(_DWORD *)this >> 8) ^ CRC_32_Table[(_BYTE)a2 ^ *(_DWORD *)this & 0xFF];
  *(_DWORD *)ret_data = v4;
  //printf("1: 0x%08X\n",v4);

  t_data=0;
  t_index=(_BYTE)v3 ^ (_BYTE)v4;
  memcpy((char *)&t_data,(char *)CRC_32_Table+t_index*4,4);
  v5 = ((unsigned int)v4 >> 8) ^ t_data;
  //v5 = ((unsigned int)v4 >> 8) ^ CRC_32_Table[(_BYTE)v3 ^ (_BYTE)v4];
  v3 >>= 8;
  *(_DWORD *)ret_data = v5;
  //printf("2: 0x%08X\n",v5);

  t_data=0;
  t_index=(_BYTE)v3 ^ (_BYTE)v5;
  memcpy((char *)&t_data,(char *)CRC_32_Table+t_index*4,4);
  v6 = ((unsigned int)v5 >> 8) ^ t_data;
  //v6 = ((unsigned int)v5 >> 8) ^ CRC_32_Table[(_BYTE)v3 ^ (_BYTE)v5];
  *(_DWORD *)ret_data = v6;
  //printf("3: 0x%08X\n",v6);

  t_data=0;
  t_index=(_BYTE)v6 ^ (unsigned __int16)((_WORD)v3 >> 8);
  memcpy((char *)&t_data,(char *)CRC_32_Table+t_index*4,4);
  result = ((unsigned int)v6 >> 8) ^ t_data;
  //result = ((unsigned int)v6 >> 8) ^ CRC_32_Table[(_BYTE)v6 ^ (unsigned __int16)((_WORD)v3 >> 8)];
  *(_DWORD *)ret_data = result;
  //printf("4: 0x%08X\n",v6);

  return result;
}


