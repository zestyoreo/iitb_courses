#!/bin/sh

mkdir -p $2
./create-dict.sh $1 > L.fst
./create-let-dict.sh $1 L.fst > Q.fst
./create-prefix-dict.sh Q.fst > "$2/QPrefix.fst"
./create-suffix-dict.sh Q.fst > "$2/QSuffix.fst"
