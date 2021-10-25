#!/bin/bash

sum=`expr $1 + $2`
echo "$1 + $2 = $sum"

diff=`expr $1 - $2`
echo "$1 - $2 = $diff"

product=`expr $1 \* $2`
echo "$1 * $2 = $product"

quotient=`expr $1 / $2`
echo "$1 / $2 = $quotient"

modulo=`expr $1 % $2`
echo "$1 % $2 = $modulo"

exponent=$(($1 ** $2))
echo "$1 ^ $2 = $exponent"
