#!perl

use bigint;

#primes
$atmp=0xDADDACEFDBA41AA572BEFCE671D6BDE0C7989438D441B92B96B6C33C913FDCFCEF5A09CDEF987083BD14B85A1FE58B6AE4DB70E2C6F6063ADC3933448639F5B3 + 0,"\n";
$btmp=0x99A4AA21F10A511032D64ACBAA1367BE74B84FB7B7684945CAF6BE0CA2CC291BB025DE24D8424B313EA1E6932365444CE58BF603FE47CCD827B96667F9B5C0CB + 0,"\n";

#$a=makenum($atmp);
#$b=makenum($btmp);

$c= $a * $b;

print $c;



### subroutine ###
sub makenum(){
	my $a;

	$a=@_[0];
	$l=length($a);
	$all="";
	for($i=0;$i<$l;$i=$i+2){
		$h=substr($a,$i,2);
		$g=chr(hex($h));
		$all=$all.$g;
	};

	return $all;
};


