#!/bin/bash

GUESS=-1

ANSWER=$(($RANDOM%100+1))

COUNT=0

while [ $GUESS != $ANSWER ]
do
	COUNT=$(($COUNT+1))

	read -p "Enter your guess [1-100]: " GUESS

	if ! [[ $GUESS =~ ^-?[0-9]+$ ]]
	then
		echo "'$GUESS' is not an integer."

	elif [ $GUESS -lt $ANSWER ]
	then
		echo "Your guess is too low."

	elif [ $GUESS -gt $ANSWER ]
	then
		echo "Your guess is too high."

	fi
done

echo -e "Correct! It took you $COUNT guesses."
