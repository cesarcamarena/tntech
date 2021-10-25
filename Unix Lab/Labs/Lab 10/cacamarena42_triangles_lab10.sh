#!/bin/bash

if [ $1 -eq $2 ] && [ $2 -eq $3 ] && [ $1 -eq $3 ]
then
	echo equilateral triangle

elif [ $1 -eq $2 ] || [ $2 -eq $3 ] || [ $1 -eq $3 ]
then
	echo isosceles triangle

elif [ $(($1 + $2)) -gt $3 ] || [ $(($1 + $3)) -gt $2 ] || [ $(($2 + $3)) -gt $1 ]
then
	echo scalene triangle
else
	echo not a triangle
fi
