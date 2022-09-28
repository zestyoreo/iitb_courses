#!/bin/sh

python create.py --fst --isyms --osyms --name L --file $1
fstcompile --keep_isymbols --keep_osymbols --isymbols=L.isyms --osymbols=L.osyms L.txt
rm -f L.txt L.isyms L.osyms