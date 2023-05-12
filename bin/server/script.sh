#!/bin/bash

delta_limit=20
toto=0

while read line
do
	if [[ ${toto} -eq 0  ]]; then
	    date_begin=$(date +%s);
	    toto=1; 
	    n1=$RANDOM
	    n2=$RANDOM
	    n3=$RANDOM
	    res=$(($n1 * $n2 + $n3))
	    echo $n1 '*' $n2 '+' $n3;
	else 
	    date_delta=$(($(date +%s) - $date_begin))
	    echo "debug: ${date_delta}"
	    if [[ "${date_delta}" -gt "${delta_limit}" ]]; then echo "Timeout"; exit 84; toto=0; fi
	    if [[ "${line}" -eq "${res}" ]]; then echo "EPICTF{p1ng_p0ng}"; else echo "KO, debug: ${res}"; fi
	fi
done

