#!perl

$msg="";
$msg.="\x01\xb4\xa3\xde\x12\x26\x3b\xb4\x19\x06\x99\xa0\xa0\x7e\x89\x26";
$msg.="\xa7\xb4\xa3\xde\x12\x26\x3b\xb4\x19\x06\x99\xa0\xa0\x7e\x89\x26";
$msg.="\xa7\xb4\xa3\xde\x12\x26\x3b\xb4\x19\x06\x99\xa0\xa0\x7e\x89\x26";
$msg.="\xa7\xb4\xa3\xde\x12\x26\x3b\xb4\x19\x06\x99\xa0\xa0\x7e\x89\x26";

$msg.="\xa7\xb4\xa3\xde\x12\x26\x3b\xb4\x19\x06\x99\xa0\xa0\x7e\x89\x26";
$msg.="\xa7\xb4\xa3\xde\x12\x26\x3b\xb4\x19\x06\x99\xa0\xa0\x7e\x89\x26";
$msg.="\xa7\xb4\xa3\xde\x12\x26\x3b\xb4\x19\x06\x99\xa0\xa0\x7e\x89\x26";
$msg.="\xa7\xb4\xa3\xde\x12\x26\x3b\xb4\x19\x06\x99\xa0\xa0\x7e\x89\x26";


open WR, ">_myin.txt";
binmode (WR);
print WR $msg;
close WR;


