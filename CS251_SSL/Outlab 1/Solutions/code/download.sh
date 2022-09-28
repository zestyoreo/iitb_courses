#!/bin/bash

if [ $# -ne 2 ]
then
	echo 'Usage: bash download.sh <link to directory> <cut-dirs argument>'
	exit 1
fi

wget -qr -nH --cut-dirs=$2 -np -R "index.html*" $1
dirname=$(basename $1)
if [ "$dirname" != "mock_grading" ]
then
	mv $dirname mock_grading
fi
