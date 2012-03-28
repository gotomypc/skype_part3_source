//
// Util.c
//

#include <stdio.h>
#include <stdlib.h>

#include <windows.h>  


////////////////////////////////
// Calculate crc32 for 41 ?
/////////////////////////////////
char word_9A8844[]=
"\x00\x00\x21\x10\x42\x20\x63\x30\x84\x40\xA5\x50\xC6\x60\xE7\x70"
"\x08\x81\x29\x91\x4A\xA1\x6B\xB1\x8C\xC1\xAD\xD1\xCE\xE1\xEF\xF1"
"\x31\x12\x10\x02\x73\x32\x52\x22\xB5\x52\x94\x42\xF7\x72\xD6\x62"
"\x39\x93\x18\x83\x7B\xB3\x5A\xA3\xBD\xD3\x9C\xC3\xFF\xF3\xDE\xE3"
"\x62\x24\x43\x34\x20\x04\x01\x14\xE6\x64\xC7\x74\xA4\x44\x85\x54"
"\x6A\xA5\x4B\xB5\x28\x85\x09\x95\xEE\xE5\xCF\xF5\xAC\xC5\x8D\xD5"
"\x53\x36\x72\x26\x11\x16\x30\x06\xD7\x76\xF6\x66\x95\x56\xB4\x46"
"\x5B\xB7\x7A\xA7\x19\x97\x38\x87\xDF\xF7\xFE\xE7\x9D\xD7\xBC\xC7"
"\xC4\x48\xE5\x58\x86\x68\xA7\x78\x40\x08\x61\x18\x02\x28\x23\x38"
"\xCC\xC9\xED\xD9\x8E\xE9\xAF\xF9\x48\x89\x69\x99\x0A\xA9\x2B\xB9"
"\xF5\x5A\xD4\x4A\xB7\x7A\x96\x6A\x71\x1A\x50\x0A\x33\x3A\x12\x2A"
"\xFD\xDB\xDC\xCB\xBF\xFB\x9E\xEB\x79\x9B\x58\x8B\x3B\xBB\x1A\xAB"
"\xA6\x6C\x87\x7C\xE4\x4C\xC5\x5C\x22\x2C\x03\x3C\x60\x0C\x41\x1C"
"\xAE\xED\x8F\xFD\xEC\xCD\xCD\xDD\x2A\xAD\x0B\xBD\x68\x8D\x49\x9D"
"\x97\x7E\xB6\x6E\xD5\x5E\xF4\x4E\x13\x3E\x32\x2E\x51\x1E\x70\x0E"
"\x9F\xFF\xBE\xEF\xDD\xDF\xFC\xCF\x1B\xBF\x3A\xAF\x59\x9F\x78\x8F"
"\x88\x91\xA9\x81\xCA\xB1\xEB\xA1\x0C\xD1\x2D\xC1\x4E\xF1\x6F\xE1"
"\x80\x10\xA1\x00\xC2\x30\xE3\x20\x04\x50\x25\x40\x46\x70\x67\x60"
"\xB9\x83\x98\x93\xFB\xA3\xDA\xB3\x3D\xC3\x1C\xD3\x7F\xE3\x5E\xF3"
"\xB1\x02\x90\x12\xF3\x22\xD2\x32\x35\x42\x14\x52\x77\x62\x56\x72"
"\xEA\xB5\xCB\xA5\xA8\x95\x89\x85\x6E\xF5\x4F\xE5\x2C\xD5\x0D\xC5"
"\xE2\x34\xC3\x24\xA0\x14\x81\x04\x66\x74\x47\x64\x24\x54\x05\x44"
"\xDB\xA7\xFA\xB7\x99\x87\xB8\x97\x5F\xE7\x7E\xF7\x1D\xC7\x3C\xD7"
"\xD3\x26\xF2\x36\x91\x06\xB0\x16\x57\x66\x76\x76\x15\x46\x34\x56"
"\x4C\xD9\x6D\xC9\x0E\xF9\x2F\xE9\xC8\x99\xE9\x89\x8A\xB9\xAB\xA9"
"\x44\x58\x65\x48\x06\x78\x27\x68\xC0\x18\xE1\x08\x82\x38\xA3\x28"
"\x7D\xCB\x5C\xDB\x3F\xEB\x1E\xFB\xF9\x8B\xD8\x9B\xBB\xAB\x9A\xBB"
"\x75\x4A\x54\x5A\x37\x6A\x16\x7A\xF1\x0A\xD0\x1A\xB3\x2A\x92\x3A"
"\x2E\xFD\x0F\xED\x6C\xDD\x4D\xCD\xAA\xBD\x8B\xAD\xE8\x9D\xC9\x8D"
"\x26\x7C\x07\x6C\x64\x5C\x45\x4C\xA2\x3C\x83\x2C\xE0\x1C\xC1\x0C"
"\x1F\xEF\x3E\xFF\x5D\xCF\x7C\xDF\x9B\xAF\xBA\xBF\xD9\x8F\xF8\x9F"
"\x17\x6E\x36\x7E\x55\x4E\x74\x5E\x93\x2E\xB2\x3E\xD1\x0E\xF0\x1E"
;




////////////////////////////////
//calculate crc32
/////////////////////////////////
//crc table
//1024 bytes
//+16

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

///////////////////////////////////////////////////////////////////////////
// Calculate crc32 for 41 ?
///////////////////////////////////////////////////////////////////////////
int Calculate_CRC32_For41(char *data, int len)
{
  unsigned int eax; // eax@1
  unsigned int edx; // edx@1
  unsigned int ebx;
  unsigned int esi;
  unsigned int edi;
  unsigned int ecx;
  unsigned int my_this=0;
  char *bin;

  eax=len;
  edx = (unsigned int )data;
  esi=my_this;

  ecx=eax;//len

  eax--;

  if ( ecx )
  {
	edi=eax+1;
    do
    {


      eax=esi & 0xffff;
	  ebx=0;
	  
	  //printf("\nNEW eax=0x%08X\n",eax);
	  
	  bin=(char *)edx;
	  ebx=bin[0] & 0xff;

	  //printf("ebx=0x%08X\n",ebx);

	  ecx=eax;
	  ecx=ecx & 0xffff;
	  ecx=ecx >> 8;

	  //printf("ecx=0x%08X\n",ecx);

	  ecx=ecx ^ ebx;

	  //printf("ecx=0x%08X\n",ecx);

	  ebx=0;

	  //mov bh,al
	  ebx=(eax & 0xff) * 0x100;

	  //printf("ebx=0x%08X\n",ebx);

	  eax=(word_9A8844[ecx*2+1] & 0xff) * 0x100 + (word_9A8844[ecx*2] & 0xff);

	  //printf("table eax=0x%08X\n",eax);

	  eax= (eax & 0xffff) ^ (ebx & 0xffff);

	  //printf("eax=0x%08X\n",eax);

	  edx=edx++;
	  edi--;
	  esi=eax & 0xffff;

	  //printf("esi=0x%08X\n",esi);

    }
    while ( edi );
  }

  return eax;
}


