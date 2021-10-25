#!/bin/bash

sum=0

if [ -z $1 ]
then
	echo "Usage:  cacamarena42.sh num..."
	echo "  num, an integer"

	exit
fi

while [[ $# -gt 0 ]]
do
	if ! [[ $1 =~ ^[\-0-9]+$ ]]
	then
		echo "cacamarena42_adder_lab13.sh: argument '$1' is not an integer."
		echo "Usage:  cacamarena42.sh num..."
		echo "  num, an integer"

		exit
	else
		sum=$(expr $sum + $1)
		shift
	fi
done

echo $sum
