//
//udp communication
//

#include<stdio.h>

#include <winsock.h>  
#include "rc4/Expand_IV.h"

extern unsigned int Calculate_CRC32(char *crc32, int bytes);

extern int show_memory(char *mem, int len, char *text);
extern int main_unpack (u8 *indata, u32 inlen);
extern int main_unpack_once (u8 *indata, u32 inlen);

typedef struct _skype_thing {
	u32				type, id, m, n;
} skype_thing;

typedef struct _skype_list
{
	struct _skype_list	*next;
	skype_thing			*thing;
	u32					allocated_things;
	u32					things;
} skype_list;


extern int main_pack(skype_thing *mythings, int mythings_len, u8 *outdata, u32 maxlen);
extern int main_pack_into(skype_list *list, u8 *outdata, u32 maxlen);
extern int encode_to_7bit(char *buf, unsigned int word, int limit);




/*
00-00: 02 00 00 00
04-01: 15 bytes
0000: BA A1 97 19 A6 C4 F0 C6 01 A5 E6 8F 48 FF 32    | ............H.2  |

00-02: 43 00 00 00
05-03: {
03-00: "xoteg_iam"
04-01: 21 bytes
0000: 95 21 7E 88 F4 6D 4E 06 01 C0 A8 01 14 84 48 4E | .!~..mN.......HN |
0010: 55 DF E8 F7 94                                  | U....            |

00-03: E0 63 00 00
05-07: {
00-03: 48 4F 00 00
02-08: 87.64.8.152:28223
00-10: 0A 00 00 00
05-07: }
05-07: {
00-03: 7E 2A 00 00
02-08: 94.109.93.2:3352
00-10: 0A 00 00 00
05-07: }
01-09: 33 50 82 48 F9 F9 A4 59
00-18: 01 00 00 00
00-1B: 06 00 00 00
05-03: }
00-04: 1E 00 00 00
*/
//87.64.8.152:28223
//57400898
//6E3F
//
//94.109.93.2:3352
//5E.6D.5D.2
//0D18

////////////////////////
// udp push prepare //
////////////////////////
int make_udp_push_prepare(u16 seqnum, char *send_pkt, int *s_len) {
	int ret=0;
	u8 result[0x1000];
	int result_len;
	u8 header[0x100];
	int header_len=5;
	int send_len;

	u8 original[]=
"\x42\x2D\x40\x71\xAC\x1F\x3A\x4F\x27\xDE\x1A"
"\xEF\xF4\x44\x2C\xB0\x6C\x73\xE4\x4C\xEC\xFE\xB1\x5A\xB9\x5A\xA6"
"\xAB\x22\x73\xDE\x15\x65\x2E\xAC\xC1\x5B\xAF\x2B\x64\xD6\xB1\x60"
"\xBA\xA1\x97\x19\xA6\xC4\xF0\xC6\x01\xA5\xE6\x8F\x48\xFF\x32\x95"
"\x21\x7E\x88\xF4\x6D\x4E\x06\x01\xC0\xA8\x01\x14\x84\x48\x4E\x55"
"\xDF\xE8\xF7\x94\x98\x08\x40\x57\x3F\x6E\x02\x5D\x6D\x5E\x18\x0D"
"\x33\x50\x82\x48\xF9\xF9\xA4\x59"
;
	u32 original_len=sizeof(original)-1;


	u8 req_user[]="xoteg_iam";

	// xot_iam card
	u8 req_ipblock[]="\x95\x21\x7E\x88\xF4\x6D\x4E\x06\x01\xC0\xA8\x01\x14\x84\x48\x4E"
					 "\x55\xDF\xE8\xF7\x94";
	u32 req_ipblock_len=sizeof(req_ipblock)-1;

	//xoteg_iam card
	u8 INIT_UNK[]="\xBA\xA1\x97\x19\xA6\xC4\xF0\xC6\x01\xA5\xE6\x8F\x48\xFF\x32";
	u32 INIT_UNK_len=sizeof(INIT_UNK)-1;

	u8 rnd64bit_[]="\x33\x50\x82\x48\xF9\xF9\xA4\x59";

	u32 rnd64bit_1=0x48825033;
	u32 rnd64bit_2=0x59A4F9F9;

	u32 ip1;
	u32 port1;
	u32 ip2;
	u32 port2;

	skype_thing	mythings4[] = {
		{00, 0x03, 0x4F48, 0x00},
		{02, 0x08, 0xFF,  0xFF},
		{00, 0x10, 0x0A, 0x00},
	};
	int mythings4_len=3;
	skype_list		list4 = {&list4, mythings4, mythings4_len, mythings4_len};

	skype_thing	mythings3[] = {
		{00, 0x03, 0x2A7E, 0x00},
		{02, 0x08, 0xFF,  0xFF},
		{00, 0x10, 0x0A, 0x00},
	};
	int mythings3_len=3;
	skype_list		list3 = {&list3, mythings3, mythings3_len, mythings3_len};

	skype_thing	mythings2[] = {
		{03, 0x00, (u32 )req_user, 0x00},
		{04, 0x01, (u32 )req_ipblock, req_ipblock_len},
		{00, 0x03, 0x63E0, 0x00},
//		{05, 0x07, (u32 )&list4, 0x00},
		{05, 0x07, (u32 )&list3, 0x00},
		{01, 0x09, rnd64bit_1, rnd64bit_2},
		{00, 0x18, 0x01, 0x00},
		{00, 0x1B, 0x06, 0x00},
		};
	int mythings2_len=7;
	skype_list		list2 = {&list2, mythings2, mythings2_len, mythings2_len};

	skype_thing	mythings[] = {
		{00, 0x00, 0x02, 0x00},
		{04, 0x01, (u32 )INIT_UNK, INIT_UNK_len},
		{00, 0x02, 0x43, 0x00},
		{05, 0x03, (u32 )&list2, 0x00},
		{00, 0x04, 0x1E, 0x00},
	};
	int mythings_len=5;

	skype_list		list = {&list, mythings, mythings_len, mythings_len};

	

	// 
	ip1=inet_addr("71.30.79.66");
	port1=atoi("60462");

	//ip2=inet_addr("71.233.197.167");
	//port2=atoi("58241");

	//ip1=inet_addr("87.64.8.152");
	//port1=atoi("28223");
	//ip2=inet_addr("94.109.93.2");
	//port2=atoi("3352");

	mythings3[1].n=0;
	mythings4[1].n=0;

	mythings3[0].m=0x6832;
	mythings3[1].m=htonl(ip1);
	mythings3[1].n=port1;

	//mythings4[0].m=0x582C;
	//mythings4[1].m=htonl(ip1);
	//mythings4[1].n=port1;


	result_len=main_pack_into(&list, result, sizeof(result)-1 );

	show_memory(result,result_len,"packed42:");
	main_unpack(result,result_len);

	
	/*
	ret=memcmp(result,original,original_len);
	if (ret!=0){
		printf("not equal to original\n");
	};
	*/
	

	header_len=encode_to_7bit(header, result_len+2, header_len);
	if (header_len==-1){
		return -1;
	};

	// pkt size
	send_len=0;
	memcpy(send_pkt+send_len,header,header_len);
	send_len+=header_len;

	// cmd 
	send_pkt[send_len]=(char )0xAA;
	send_len++;
	send_pkt[send_len]=(char )0x03;
	send_len++;

	// seqnum
	seqnum=bswap16(seqnum);
	memcpy(send_pkt+send_len,(char *)&seqnum,2);
	seqnum=bswap16(seqnum);
	send_len+=2;

	// 42 data
	memcpy(send_pkt+send_len,result,result_len);
	send_len+=result_len;


	//show_memory(send_pkt,send_len,"push prepare pkt");

	*s_len=send_len;

	return 0;

};



////////////////////////
// udp request Search //
////////////////////////
int make_udp_push_pkt1(char *ourip,char *destip, u16 seqnum, u32 rnd, char *pkt, int *pkt_len) {
	RC4_context rc4;

	u8 send_pkt[0x1000];
	int send_len;
	int slen;

	u16 seqnum42;

	u32	newrnd, iv, iv3[3];
	u32 targetip;
	u32 publicip;
	u32 pkt_crc32;
	int ret;
	
	
	send_len=0;

	seqnum42=seqnum;
	ret=make_udp_push_prepare(seqnum42, (char *)&send_pkt+send_len, &slen);
	if (ret==-1){
		//printf("prepare failed\n");
		return -1;
	};
	send_len+=slen;


	// make rc4 init
	targetip=inet_addr(destip);
	publicip=inet_addr(ourip);
	//prepare
	newrnd = rnd;
	iv3[0] = ntohl(publicip);
	iv3[1] = ntohl(targetip);
	iv3[2] = seqnum+1;
	//init seed for rc4
	iv = crc32(iv3,3) ^ newrnd;
	//crc32
	pkt_crc32=Calculate_CRC32( (char *)send_pkt,send_len);
	//init rc4 structure by iv
	Skype_RC4_Expand_IV (&rc4, iv, 1);

	
	// encode rc4
	//show_memory(send_pkt,send_len,"bef rc4:");
	RC4_crypt  (send_pkt,send_len, &rc4, 0);
	//show_memory(send_pkt,send_len,"aft rc4:");


	//make send pkt

	//pktnum+1,
	seqnum++;
	seqnum=bswap16(seqnum);
	memcpy(pkt,(char*)&seqnum,2);
	seqnum=bswap16(seqnum);

	//02 - tip dannih ?
	memcpy(pkt+2,"\x02",1);
	
	//init data//our rnd seed?
	newrnd=bswap32(newrnd);
	memcpy(pkt+3,(char*)&newrnd,4);
	newrnd=bswap32(newrnd);
	
	//crc32
	pkt_crc32=bswap32(pkt_crc32);
	memcpy(pkt+7,(char *)&pkt_crc32,4);
	pkt_crc32=bswap32(pkt_crc32);

	//rc4 data
	memcpy(pkt+11,(char *)&send_pkt,send_len);

	//display pkt bef send
	//show_memory(pkt,send_len+11,"send pkt:");

	*pkt_len=send_len+11;


	return 0;
};




int process_udp_push_pkt1(char *pkt,int pkt_len,char *ourip,char *destip) {
	RC4_context rc4;
	u32 newrnd;
	u32 targetip;
	u32 publicip;
	u32	iv3[3];
	u32 iv;
	int header_len;


	//show_memory(pkt,pkt_len,"result len:");

	targetip=inet_addr(destip);
	publicip=inet_addr(ourip);

	newrnd = bswap32(dword(pkt+3));

	iv3[2] = bswap16(word(pkt)); 
	iv3[1] = bswap32(publicip);
	iv3[0] = bswap32(targetip);

	iv = crc32(iv3,3) ^ newrnd;

	Skype_RC4_Expand_IV (&rc4, iv, 1);

	header_len=11;

	//show_memory(pkt+header_len,pkt_len-header_len,"bef rc4:");	
	RC4_crypt (pkt+header_len, pkt_len-header_len, &rc4, 0);
	show_memory(pkt+header_len,pkt_len-header_len,"aft rc4:");	


	main_unpack(pkt+header_len,pkt_len-header_len);


	return 0;
};


