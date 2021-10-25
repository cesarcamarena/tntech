#!/bin/bash

if [ -z $1 ]
then
	echo "Usage: cacamarena42_files_lab13.sh dir..."
	echo "  dir, a directory"
fi

while [[ -n $1 ]]
do
	if ! [ -e $1 ]
	then
		echo "$1 does not exist."
#	elif ! [ -x $1 ]
#	then
#		echo "$1 is not searchable."
	elif ! [ -d $1 ]
	then
		echo "$1 is not a directory."
	elif [ -d $1 ]
	then
		if ! [ -x $1 ]
		then
			echo "$1 is not searchable."
			shift
			continue
		fi
		echo "$1"
		for x in $1/*; do
			if [ -d $x ]
			then
				echo -e "\t$x is a directory."
			else
				echo -e "\t$x is a regular file."
			fi
			if [ -r $x ]
			then
				echo -e "\t$x is readable."
			fi
			if [ -x $x ]
			then
				echo -e "\t$x is executable/searchable."
			fi
			if [ -w $x ]
			then
				echo -e "\t$x is writeable."
			fi
			done
		else
			echo "$1 is not searchable"
		fi
		shift
done
