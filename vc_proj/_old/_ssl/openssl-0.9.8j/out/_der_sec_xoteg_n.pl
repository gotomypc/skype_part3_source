#!perl
# create der rsa secret key 
# xoteg_iam NEW

$der_start="\x30\x82\x02\x5D\x02\x01\x00\x02\x81\x81\x00";
$der_end="\x02\x03\x01\x00\x01";

$der_start2="\x02\x81\x80";


$xoteg_pub="";
$xoteg_pub.="\xB7\x32\xC6\x3D\x99";
$xoteg_pub.="\x00\x99\xB4\xC2\x8E\xB4\x2C\x63\xBC\x14\x64\xF2\x88\xCB\xE1\x5C";
$xoteg_pub.="\x2A\x87\xD0\x62\x0C\x7E\x4F\x4E\xE2\xC3\x35\x3F\x29\x20\x75\x5A";
$xoteg_pub.="\xDC\x58\x50\x99\x9A\x99\x4B\x13\xB3\xCE\x37\xD9\x3B\x9B\x10\x46";
$xoteg_pub.="\x8A\xEE\x7C\x28\xDD\x75\xAC\xBE\xEF\x83\x15\x57\xDD\x32\xC3\x03";
$xoteg_pub.="\x80\xED\xBE\x33\xAE\xBD\x03\x7B\x18\x8D\x63\x8C\xF8\xCA\xCA\x93";
$xoteg_pub.="\xAE\xFD\xA5\x9A\x6F\x02\xB0\x95\x13\x2B\xC0\xD6\x71\x15\x9A\x0C";
$xoteg_pub.="\xD4\x8A\xAE\xA7\x94\xDD\x68\xDE\x9D\x34\xA1\x24\xA6\x2B\xDC\x1A";
$xoteg_pub.="\x7F\x45\x9D\x87\x30\x91\xDC\x69\xFC\x32\xD1";



$xoteg_sec="";
$xoteg_sec.="\x43\x73\x9C\x6E\x1D\xA1\x8C\xF6\x73\x14\x1B\xDE\xA4\x32\x21\xC8";
$xoteg_sec.="\x31\x4C\x90\xD4\xBF\x1C\xA1\xB8\xE6\x00\xF7\x98\xB7\xD0\xE2\x52";
$xoteg_sec.="\xFE\x98\x63\xED\x11\xB1\x43\x8B\x19\xA3\x44\x81\xD2\x15\x47\xFE";
$xoteg_sec.="\x64\x2B\x80\x22\x73\xF6\xBF\x6C\x53\x97\x86\xB6\x3D\xEE\xED\xF2";
$xoteg_sec.="\x14\x58\x71\x4E\x2B\xDC\x38\x4C\x3A\x74\x5B\x7D\x0B\x1E\xE1\x9E";
$xoteg_sec.="\xCE\x67\x4C\x8F\xD7\x10\xEB\x07\x69\xAD\x41\x35\x4D\x2D\xA6\xEA";
$xoteg_sec.="\x8F\x0C\xDF\x6F\xF9\x07\xDA\x81\xEC\xB4\xDD\xCE\x2D\xC5\xBF\xB3";
$xoteg_sec.="\x93\x66\x3D\x77\x12\xC2\x61\x63\x65\xF3\xA3\xC0\xF8\x36\xB8\x49";


$der_rest="";
$der_rest.="\x02\x41\x00\xE1\x76\xF6\x30\x5C\xF5\xE1\xA8\x2E\x05";
$der_rest.="\xE1\x4D\x95\xE8\x7A\x75\x8B\x2E\x93\x84\xCE\xE2\x19\xBD\x55\x16";
$der_rest.="\x67\xA5\x5A\x8F\x80\xDE\xC1\xA7\x8F\xD6\x6E\x25\x72\x38\xFA\x17";
$der_rest.="\x8E\x51\x83\xA6\x68\x00\xDE\x15\xF7\x13\x15\x36\x97\xF7\x10\x47";
$der_rest.="\xD9\x25\xB6\x3F\x3E\xC1\x02\x41\x00\xC9\x8A\xB3\x14\x27\x59\x16";
$der_rest.="\x2B\x91\x96\x51\x6B\xAD\x86\xAC\xDB\xC4\x1E\x99\x8B\x54\xB5\xF4";
$der_rest.="\x5C\xC9\x7E\x83\xB5\xF7\x3B\x46\x03\x3A\xF3\x70\xFC\x04\xCC\xDB";
$der_rest.="\xCB\x68\xA6\x6D\x58\x96\x7B\x39\x31\x4C\xC0\xDA\xDB\x8C\x3B\x95";
$der_rest.="\x4C\xFB\x55\x93\x55\x1C\xB9\xBC\xA5\x02\x41\x00\xCD\x5C\xFC\x15";
$der_rest.="\x45\x37\x39\x59\x64\xC2\x3A\x5B\xDF\x05\xA8\x35\x54\x97\x12\x0B";
$der_rest.="\x50\x1D\xA5\xF0\x4C\x86\x61\xD5\xBD\x4D\x24\xC6\xC1\x81\x8C\x84";
$der_rest.="\x76\x43\x69\x6C\xF8\x6F\x68\x54\x5B\x23\xC1\x6B\xB8\xDE\x2C\xF4";
$der_rest.="\x96\xC7\xE9\x57\x42\xDF\x0E\xAD\x48\xF9\x06\x81\x02\x40\x45\x45";
$der_rest.="\x0B\xA9\xC8\xA0\x60\xF3\x56\x95\xA0\xA4\x6E\xBE\xD4\x18\xB0\xBE";
$der_rest.="\x87\xAD\x90\xCE\xFD\x0F\x0B\x1E\x15\xAC\xEC\x2D\x8E\x31\xBC\x08";
$der_rest.="\x41\xF4\x0C\xBE\x50\x69\x08\x2D\xF3\x75\x38\x3B\x5F\xFB\xE6\xD2";
$der_rest.="\x7E\x26\x69\x7B\x6D\x24\x49\x5A\x2F\x4A\x58\x96\x2A\x15\x02\x41";
$der_rest.="\x00\xE0\x10\x37\xA5\x94\xF9\xBC\x94\x77\x48\xA2\x16\x8B\xE6\x78";
$der_rest.="\xA8\xDC\xC8\xFA\x3A\xCA\x36\xCD\x37\x60\x12\xB7\x2E\xEB\xA3\xD3";
$der_rest.="\x3C\x31\xE4\xEA\x3B\xF1\xE0\xFC\xE3\xB5\x84\x55\x85\x05\x37\x20";
$der_rest.="\x1B\xB6\xCA\x6F\xF2\x1A\xD6\xA5\xD0\x1D\x82\xBF\x02\xF9\xD4\x63";
$der_rest.="\x98";


open WR, ">_xoteg_sec_new.der";
binmode (WR);

print WR $der_start;
print WR $xoteg_pub;
print WR $der_end;

print WR $der_start2;
print WR $xoteg_sec;

print WR $der_rest;

close WR;

