//
// setup pkt 2
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../decode41.h"

#include "../global_vars.h"

extern int show_memory(char *mem, int len, char *text);
extern int set_packet_size(char *a1, int c);
extern int encode_to_7bit(char *buf, uint word, uint limit);

extern int make_41cmdencode(char *buf, int buf_len, uint blob_count, uint session_id, uint session_cmd, int dodebug);
extern int make_41encode(char *buf, int buf_len, char *blobptr, int dodebug);



extern uint DEBUG_LEVEL;


int encode41_setup2pkt(char *globalptr, char *buf, int buf_limit_len){
	struct blob_s blob;
	uint session_id;
	uint session_cmd;
	int buf_len;

	struct global_s *global;
	global=(struct global_s *)globalptr;


	session_id=0x44EF;
	session_cmd=0x45;

	memset(buf,0,sizeof(buf));
    buf_len=0;
    buf_len=make_41cmdencode(buf, buf_len, 0x0A, session_id, session_cmd, 0);


    // hz .. blob1
    blob.obj_type = 0;
	blob.obj_index = 0x16;
    blob.obj_data = 1;
	blob.data_ptr = 0;
	blob.data_size = 0;

    buf_len=make_41encode(buf,buf_len,(char *)&blob, 0);

    // hz .. blob2
    blob.obj_type = 0;
	blob.obj_index = 0x1A;
    blob.obj_data = 1;
	blob.data_ptr = 0;
	blob.data_size = 0;

    buf_len=make_41encode(buf,buf_len,(char *)&blob, 0);

    // hz .. blob3
    blob.obj_type = 0;
	blob.obj_index = 2;
	blob.obj_data = global->BLOB_0_2;
    //blob.obj_data = 0x5F349B29;
	blob.data_ptr = 0;
	blob.data_size = 0;

    buf_len=make_41encode(buf,buf_len,(char *)&blob, 0);

    // blob4 ALLOC1 credentials ciphered
    blob.obj_type = 4;
	blob.obj_index = 5;
    blob.obj_data = 0;
	blob.data_ptr = (int)global->CREDENTIALS188;
	blob.data_size = global->CREDENTIALS188_LEN;

    buf_len=make_41encode(buf,buf_len,(char *)&blob, 0);

    // hz .. blob5 
    blob.obj_type = 0;
	blob.obj_index = 0x0D;
    blob.obj_data = 2;
	blob.data_ptr = 0;
	blob.data_size = 0;

    buf_len=make_41encode(buf,buf_len,(char *)&blob, 0);

    // blob6 ALLOC2 challenge_response
    blob.obj_type = 4;
	blob.obj_index = 0x0A;
    blob.obj_data = 0;
	blob.data_ptr = (int)global->CHALLENGE_RESPONSE;
	blob.data_size = sizeof(global->CHALLENGE_RESPONSE);

    buf_len=make_41encode(buf,buf_len,(char *)&blob, 0);

    // hz .. blob7
    blob.obj_type = 0;
	blob.obj_index = 0x19;
    blob.obj_data = 1;
	blob.data_ptr = 0;
	blob.data_size = 0;

    buf_len=make_41encode(buf,buf_len,(char *)&blob, 0);
	
    // blob8 ALLOC3 aes nonce, encrypted by rsa public key
    blob.obj_type = 4;
	blob.obj_index = 0x06;
    blob.obj_data = 0;
	blob.data_ptr = (int)global->LOCAL_NONCE;
	blob.data_size = sizeof(global->LOCAL_NONCE);

    buf_len=make_41encode(buf,buf_len,(char *)&blob, 0);

    // blob9 ALLOC4 local credentials cipher-ed ???
    blob.obj_type = 4;
	blob.obj_index = 0x11;
    blob.obj_data = 0;
	blob.data_ptr = (int)global->LOCAL_UIC;
	blob.data_size = sizeof(global->LOCAL_UIC)-1;

    buf_len=make_41encode(buf,buf_len,(char *)&blob, 0);

    // hz .. blob10
    blob.obj_type = 0;
	blob.obj_index = 0x14;
    blob.obj_data = 0;
	blob.data_ptr = 0;
	blob.data_size = 0;

    buf_len=make_41encode(buf,buf_len,(char *)&blob, 0);



	if ( buf_len > buf_limit_len ){
		if (DEBUG_LEVEL>=100) printf("buffer limit overrun\n");
		return -1;
	};

	return buf_len;

};



/*

==============================================
PKT:
==============================================
Session id:  0x000044EF (17647)
Session cmd: 0x00000045 (69)
MAIN: size(0x000000C8)
00000000 00000016 00000001 00000000 | 00000000 00000000 0000001A 00000001 
00000000 00000000 00000000 00000002 | 5F349B29 00000000 00000000 00000004 
00000005 00000000 00320A60 00000188 | 00000000 0000000D 00000002 00000000 
00000000 00000004 0000000A 00000000 | 00320C18 00000080 00000000 00000019 
00000001 00000000 00000000 00000004 | 00000006 00000000 00322378 00000080 
00000004 00000011 00000000 00322430 | 00000188 00000000 00000014 00000000 
00000000 00000000 

next bytes: 0x00000000 0x00000016 0x00000001 0x00000000 0x00000000 
obj_type :  0x00000000
obj_index:  0x00000016
data:       0x00000001
data_ptr:   0x00000000 0x00000000

next bytes: 0x00000000 0x0000001A 0x00000001 0x00000000 0x00000000 
obj_type :  0x00000000
obj_index:  0x0000001A
data:       0x00000001
data_ptr:   0x00000000 0x00000000

next bytes: 0x00000000 0x00000002 0x5F349B29 0x00000000 0x00000000 
obj_type :  0x00000000
obj_index:  0x00000002
data:       0x5F349B29
data_ptr:   0x00000000 0x00000000

next bytes: 0x00000004 0x00000005 0x00000000 0x00320A60 0x00000188 
obj_type :  0x00000004
obj_index:  0x00000005
data:       0x00000000
data_ptr:   0xALLOC001 0x00000188

next bytes: 0x00000000 0x0000000D 0x00000002 0x00000000 0x00000000 
obj_type :  0x00000000
obj_index:  0x0000000D
data:       0x00000002
data_ptr:   0x00000000 0x00000000

next bytes: 0x00000004 0x0000000A 0x00000000 0x00320C18 0x00000080 
obj_type :  0x00000004
obj_index:  0x0000000A
data:       0x00000000
data_ptr:   0xALLOC002 0x00000080

next bytes: 0x00000000 0x00000019 0x00000001 0x00000000 0x00000000 
obj_type :  0x00000000
obj_index:  0x00000019
data:       0x00000001
data_ptr:   0x00000000 0x00000000

next bytes: 0x00000004 0x00000006 0x00000000 0x00322378 0x00000080 
obj_type :  0x00000004
obj_index:  0x00000006
data:       0x00000000
data_ptr:   0xALLOC003 0x00000080

next bytes: 0x00000004 0x00000011 0x00000000 0x00322430 0x00000188 
obj_type :  0x00000004
obj_index:  0x00000011
data:       0x00000000
data_ptr:   0xALLOC004 0x00000188

next bytes: 0x00000000 0x00000014 0x00000000 0x00000000 0x00000000 
obj_type :  0x00000000
obj_index:  0x00000014
data:       0x00000000
data_ptr:   0x00000000 0x00000000


ALLOCATED: 1 size(0x00000188)
00000104 00000001 9A1247C4 422535E2 | D528A73E 8C2B3E28 26631055 3FA315DB 
93D7D3A5 C44B44EB E0AEB979 E5CF3ABE | 8FA1D571 94D2E8E4 0E526DA3 7BDBE49E 
2C9E1843 3807F350 358E430A 7E69F03D | 09267F7E 92B3E43B 173D2480 50782D52 
E4CE8185 3EA33BEC 1532F85B 228004D3 | CDFA5BC6 9734BEB7 67C6CD79 476A6B99 
A3F6689C 1E471AA9 43162EB9 3EA484AA | CA0ACF97 5D660959 FAEB9C7D 6DC05B53 
CF57C390 C4A9FECA EA7584C9 0D649D14 | 8C33A680 094B865E D815BBEE A0DA4B03 
470BD2A2 97AF3229 949E71B1 8CCB276D | 84447825 2781D0C3 A2DD9A89 4C4F9147 
258349DE 9A47D051 7F222BDB FDA5FF2C | 6FFDBCC6 95E589A2 D0038C2C 249A2EFE 
CBA19F69 64B21059 776A4BDE CB6396CB | BCC2C910 D09B4A31 73C56017 186CAB55 
D5CD8F0B E0C54696 040C2168 C61A4451 | 2B449C61 2AF386C0 EB5144D2 42D87964 
A0BD08AD FFBBD965 522411C2 D986004B | 1672D161 7DB674EC C4CE23CF 77D0413B 
5A5EB6B6 537AA763 82AC162C D9D2E7CD | 7FA774A1 CE9F3CA3 3F6D7B32 23C56797 
5754D55D 8929280C 

ALLOCATED: 2 size(0x00000080)
7DC1C367 C03663D6 12504035 1FBC853C | CB291A9D 3C6FFC9D 313B1216 0AD4F2F0 
771858B7 9ED6B1DC 746CB556 5711CF3A | 5590215A 988D73AC 4F7BBA36 FD638642 
BEE4F2BE 9EE214E8 85AA292E 225288B1 | 89B542DF 79C5EE80 7B8867CF C9FAF7B2 
51E3F5FB 6ACB0102 533F8D8E E92EAE21 | DDDB78CF 21E928AD EE04CDC2 79B10BC9 

ALLOCATED: 3 size(0x00000080)
96613C07 061A410B 24BBD532 96989E30 | AB9F2CBE 8CAF510C AE8865FD 6AFC6FFC 
6ECDDB1B 50B222A9 0600929E E7823EBD | A0A96A19 087364C1 4DC54819 550147FF 
F81AE0C4 1DC03FD1 C910F324 AA089058 | 0802EE29 FA056B66 233E697D 0DAFA99B 
82DB54D1 B29C637A F7CC4CB4 F43C6B24 | CFB70967 EB8B4272 1B50D37B C39CB6DE 

ALLOCATED: 4 size(0x00000188)
00000104 00000001 4C74490E 80535FC5 | 3FA24F13 E891BF3B 42F47817 3F1CBBBB 
E57089CC ACF1F252 9A8394DB 8BB77FD0 | A43565BB 44BD16B2 E852016B 1E9F7BAE 
157C3DAD 1A5F276E A502B0AB 2BC4C260 | B01C9F40 93ABE988 73AF02EE 48937D95 
0C507938 F7EF7134 27C62E6B 05384861 | 020140BE C4C4D4A5 D5DDECC7 A1C061DB 
D411B42F A9ACD07B 1F4B8CE6 FB0B20B4 | 7ACA10DD 4F2EF762 B80B556F D8CD2CF2 
D4CAE201 F78F90A0 4573AA98 3C9A2DB7 | 1C00285E 732E4105 DF62EA1E 8F72FE32 
6A971ED8 829F18C7 C9AA4B2F 754AFB74 | 4E8B9FBC 7219586F 9A788BB3 EEAB8C95 
8069A811 02607B71 D9851094 730D1FFA | FBA44D86 C9A45484 3F4793B7 970E6BB4 
3F8C3723 F327EBB8 3FAA3757 D471A72F | 99D736A7 454D45BB 392C295D 389FF49F 
74DBDB07 1B64DDB8 6327CA64 8C387123 | 6DE66CA4 1C3DEA0C B2481CA8 C97EFEF3 
DF9B2ADE BFB3DFD3 B4482514 399E18D5 | 7FA64545 40BC6FFE 1E703B7E 4429559A 
9D85B4C6 903D4D74 67A277EA 45D11AA0 | 31DF9BB9 18AA9604 2C9AF628 E8F51D7D 
3A469441 5C1826AC 


*/



/*
"\xEF\x89\x01\x45\x41\x0A\x00\x16\x01\x00\x1A\x01\x00\x02\xA9\xB6"
"\xD2\xF9\x05\x04\x05\x88\x03\x00\x00\x01\x04\x00\x00\x00\x01\x9A"
"\x12\x47\xC4\x42\x25\x35\xE2\xD5\x28\xA7\x3E\x8C\x2B\x3E\x28\x26"
"\x63\x10\x55\x3F\xA3\x15\xDB\x93\xD7\xD3\xA5\xC4\x4B\x44\xEB\xE0"
"\xAE\xB9\x79\xE5\xCF\x3A\xBE\x8F\xA1\xD5\x71\x94\xD2\xE8\xE4\x0E"
"\x52\x6D\xA3\x7B\xDB\xE4\x9E\x2C\x9E\x18\x43\x38\x07\xF3\x50\x35"
"\x8E\x43\x0A\x7E\x69\xF0\x3D\x09\x26\x7F\x7E\x92\xB3\xE4\x3B\x17"
"\x3D\x24\x80\x50\x78\x2D\x52\xE4\xCE\x81\x85\x3E\xA3\x3B\xEC\x15"
"\x32\xF8\x5B\x22\x80\x04\xD3\xCD\xFA\x5B\xC6\x97\x34\xBE\xB7\x67"
"\xC6\xCD\x79\x47\x6A\x6B\x99\xA3\xF6\x68\x9C\x1E\x47\x1A\xA9\x43"
"\x16\x2E\xB9\x3E\xA4\x84\xAA\xCA\x0A\xCF\x97\x5D\x66\x09\x59\xFA"
"\xEB\x9C\x7D\x6D\xC0\x5B\x53\xCF\x57\xC3\x90\xC4\xA9\xFE\xCA\xEA"
"\x75\x84\xC9\x0D\x64\x9D\x14\x8C\x33\xA6\x80\x09\x4B\x86\x5E\xD8"
"\x15\xBB\xEE\xA0\xDA\x4B\x03\x47\x0B\xD2\xA2\x97\xAF\x32\x29\x94"
"\x9E\x71\xB1\x8C\xCB\x27\x6D\x84\x44\x78\x25\x27\x81\xD0\xC3\xA2"
"\xDD\x9A\x89\x4C\x4F\x91\x47\x25\x83\x49\xDE\x9A\x47\xD0\x51\x7F"
"\x22\x2B\xDB\xFD\xA5\xFF\x2C\x6F\xFD\xBC\xC6\x95\xE5\x89\xA2\xD0"
"\x03\x8C\x2C\x24\x9A\x2E\xFE\xCB\xA1\x9F\x69\x64\xB2\x10\x59\x77"
"\x6A\x4B\xDE\xCB\x63\x96\xCB\xBC\xC2\xC9\x10\xD0\x9B\x4A\x31\x73"
"\xC5\x60\x17\x18\x6C\xAB\x55\xD5\xCD\x8F\x0B\xE0\xC5\x46\x96\x04"
"\x0C\x21\x68\xC6\x1A\x44\x51\x2B\x44\x9C\x61\x2A\xF3\x86\xC0\xEB"
"\x51\x44\xD2\x42\xD8\x79\x64\xA0\xBD\x08\xAD\xFF\xBB\xD9\x65\x52"
"\x24\x11\xC2\xD9\x86\x00\x4B\x16\x72\xD1\x61\x7D\xB6\x74\xEC\xC4"
"\xCE\x23\xCF\x77\xD0\x41\x3B\x5A\x5E\xB6\xB6\x53\x7A\xA7\x63\x82"
"\xAC\x16\x2C\xD9\xD2\xE7\xCD\x7F\xA7\x74\xA1\xCE\x9F\x3C\xA3\x3F"
"\x6D\x7B\x32\x23\xC5\x67\x97\x57\x54\xD5\x5D\x89\x29\x28\x0C\x00"
"\x0D\x02\x04\x0A\x80\x01\x7D\xC1\xC3\x67\xC0\x36\x63\xD6\x12\x50"
"\x40\x35\x1F\xBC\x85\x3C\xCB\x29\x1A\x9D\x3C\x6F\xFC\x9D\x31\x3B"
"\x12\x16\x0A\xD4\xF2\xF0\x77\x18\x58\xB7\x9E\xD6\xB1\xDC\x74\x6C"
"\xB5\x56\x57\x11\xCF\x3A\x55\x90\x21\x5A\x98\x8D\x73\xAC\x4F\x7B"
"\xBA\x36\xFD\x63\x86\x42\xBE\xE4\xF2\xBE\x9E\xE2\x14\xE8\x85\xAA"
"\x29\x2E\x22\x52\x88\xB1\x89\xB5\x42\xDF\x79\xC5\xEE\x80\x7B\x88"
"\x67\xCF\xC9\xFA\xF7\xB2\x51\xE3\xF5\xFB\x6A\xCB\x01\x02\x53\x3F"
"\x8D\x8E\xE9\x2E\xAE\x21\xDD\xDB\x78\xCF\x21\xE9\x28\xAD\xEE\x04"
"\xCD\xC2\x79\xB1\x0B\xC9\x00\x19\x01\x04\x06\x80\x01\x96\x61\x3C"
"\x07\x06\x1A\x41\x0B\x24\xBB\xD5\x32\x96\x98\x9E\x30\xAB\x9F\x2C"
"\xBE\x8C\xAF\x51\x0C\xAE\x88\x65\xFD\x6A\xFC\x6F\xFC\x6E\xCD\xDB"
"\x1B\x50\xB2\x22\xA9\x06\x00\x92\x9E\xE7\x82\x3E\xBD\xA0\xA9\x6A"
"\x19\x08\x73\x64\xC1\x4D\xC5\x48\x19\x55\x01\x47\xFF\xF8\x1A\xE0"
"\xC4\x1D\xC0\x3F\xD1\xC9\x10\xF3\x24\xAA\x08\x90\x58\x08\x02\xEE"
"\x29\xFA\x05\x6B\x66\x23\x3E\x69\x7D\x0D\xAF\xA9\x9B\x82\xDB\x54"
"\xD1\xB2\x9C\x63\x7A\xF7\xCC\x4C\xB4\xF4\x3C\x6B\x24\xCF\xB7\x09"
"\x67\xEB\x8B\x42\x72\x1B\x50\xD3\x7B\xC3\x9C\xB6\xDE\x04\x11\x88"
"\x03\x00\x00\x01\x04\x00\x00\x00\x01\x4C\x74\x49\x0E\x80\x53\x5F"
"\xC5\x3F\xA2\x4F\x13\xE8\x91\xBF\x3B\x42\xF4\x78\x17\x3F\x1C\xBB"
"\xBB\xE5\x70\x89\xCC\xAC\xF1\xF2\x52\x9A\x83\x94\xDB\x8B\xB7\x7F"
"\xD0\xA4\x35\x65\xBB\x44\xBD\x16\xB2\xE8\x52\x01\x6B\x1E\x9F\x7B"
"\xAE\x15\x7C\x3D\xAD\x1A\x5F\x27\x6E\xA5\x02\xB0\xAB\x2B\xC4\xC2"
"\x60\xB0\x1C\x9F\x40\x93\xAB\xE9\x88\x73\xAF\x02\xEE\x48\x93\x7D"
"\x95\x0C\x50\x79\x38\xF7\xEF\x71\x34\x27\xC6\x2E\x6B\x05\x38\x48"
"\x61\x02\x01\x40\xBE\xC4\xC4\xD4\xA5\xD5\xDD\xEC\xC7\xA1\xC0\x61"
"\xDB\xD4\x11\xB4\x2F\xA9\xAC\xD0\x7B\x1F\x4B\x8C\xE6\xFB\x0B\x20"
"\xB4\x7A\xCA\x10\xDD\x4F\x2E\xF7\x62\xB8\x0B\x55\x6F\xD8\xCD\x2C"
"\xF2\xD4\xCA\xE2\x01\xF7\x8F\x90\xA0\x45\x73\xAA\x98\x3C\x9A\x2D"
"\xB7\x1C\x00\x28\x5E\x73\x2E\x41\x05\xDF\x62\xEA\x1E\x8F\x72\xFE"
"\x32\x6A\x97\x1E\xD8\x82\x9F\x18\xC7\xC9\xAA\x4B\x2F\x75\x4A\xFB"
"\x74\x4E\x8B\x9F\xBC\x72\x19\x58\x6F\x9A\x78\x8B\xB3\xEE\xAB\x8C"
"\x95\x80\x69\xA8\x11\x02\x60\x7B\x71\xD9\x85\x10\x94\x73\x0D\x1F"
"\xFA\xFB\xA4\x4D\x86\xC9\xA4\x54\x84\x3F\x47\x93\xB7\x97\x0E\x6B"
"\xB4\x3F\x8C\x37\x23\xF3\x27\xEB\xB8\x3F\xAA\x37\x57\xD4\x71\xA7"
"\x2F\x99\xD7\x36\xA7\x45\x4D\x45\xBB\x39\x2C\x29\x5D\x38\x9F\xF4"
"\x9F\x74\xDB\xDB\x07\x1B\x64\xDD\xB8\x63\x27\xCA\x64\x8C\x38\x71"
"\x23\x6D\xE6\x6C\xA4\x1C\x3D\xEA\x0C\xB2\x48\x1C\xA8\xC9\x7E\xFE"
"\xF3\xDF\x9B\x2A\xDE\xBF\xB3\xDF\xD3\xB4\x48\x25\x14\x39\x9E\x18"
"\xD5\x7F\xA6\x45\x45\x40\xBC\x6F\xFE\x1E\x70\x3B\x7E\x44\x29\x55"
"\x9A\x9D\x85\xB4\xC6\x90\x3D\x4D\x74\x67\xA2\x77\xEA\x45\xD1\x1A"
"\xA0\x31\xDF\x9B\xB9\x18\xAA\x96\x04\x2C\x9A\xF6\x28\xE8\xF5\x1D"
"\x7D\x3A\x46\x94\x41\x5C\x18\x26\xAC\x00\x14\x00\xFF\xFF"
"\x00\x00"
;

*/

