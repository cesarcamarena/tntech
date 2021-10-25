#!/bin/bash

if [ -z $1 ]
then
	int=$(($RANDOM%22))
	count=$(grep -e "^.\{$int\}$" /usr/share/dict/words | wc -l)

	random=$(($RANDOM%$count))
	echo "$(grep -e "^.\{$int\}$" /usr/share/dict/words | sed "$random! d")"

elif ! [[ $1 =~ ^-?[0-9]+$ ]]
then
	echo "'$1' is not a positive integer"

elif [ $1 -le 0 ]
then
	echo "'$1' is not a positive integer."

else
	count=$(grep -e "^.\{$1\}$" /usr/share/dict/words | wc -l)

	random=$(($RANDOM%$count))
	echo "$(grep -e "^.\{$1\}$" /usr/share/dict/words | sed "$random! d")"

fi
