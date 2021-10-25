#!/bin/bash

if [ -z $1 ]
then
	echo "Usage: "
	echo "./cacamarena42_primes_lab11.sh num"
	echo "  num, a positive integer"
	exit 0

elif ! [[ $1 =~ ^-?[0-9]+$ ]]
then
	echo "error, '$1' is not an integer"
	exit 0

elif [ $1 -le 0 ]
then
	echo "error, num must be a positive integer"
	echo "Usage: "
	echo "./cacamarena42_primes_lab11.sh num"
	echo "  num, a positive integer"
	exit 0

elif [ $1 -gt 0 ]
then
	max_limit=$(expr $1 - 1)
	for value in $( seq 2 $max_limit )
	do
		is_prime=true;
		halfway_point=$(expr $value / 2)
		for possible in $(seq 2 $halfway_point)
		do
			result=$(expr $value % $possible)
			if [ $result -eq 0 ]
			then
				is_prime=false;
			fi
		done
		if [ "$is_prime" = true ]
		then
			echo -n " $value"
		fi
	done

	echo ""
else
	echo ""
fi
