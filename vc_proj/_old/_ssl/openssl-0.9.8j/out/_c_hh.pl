#!perl

# pkt 45 1 to xot

$a ="7DC1C367C03663D6125040351FBC853CCB291A9D3C6FFC9D313B12160AD4F2F0";
$a.="771858B79ED6B1DC746CB5565711CF3A5590215A988D73AC4F7BBA36FD638642";
$a.="BEE4F2BE9EE214E885AA292E225288B189B542DF79C5EE807B8867CFC9FAF7B2";
$a.="51E3F5FB6ACB0102533F8D8EE92EAE21DDDB78CF21E928ADEE04CDC279B10BC9";

$l=length($a);

$all="";
for($i=0;$i<$l;$i=$i+2){
	$h=substr($a,$i,2);
	$g=chr(hex($h));
	$all=$all.$g;
};

open WR, ">_myin451.txt";
binmode WR;
print WR $all;
close WR;

