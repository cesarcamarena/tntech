#!/bin/bash

if [ -z $1 ];
then
	echo "error: no file provided"
	exit 0
fi

if [ ! -e $1 ];
then
	echo "error: $1: no such file"
	exit 0
fi

FULLPATH=$1
FILEPATH=$(dirname $FULLPATH)
FILENAME=$(basename $FULLPATH)
DATE=$(date +%F)

NEWFILENAME="${FILEPATH}/${DATE}_${FILENAME}"

cp $FULLPATH $NEWFILENAME
