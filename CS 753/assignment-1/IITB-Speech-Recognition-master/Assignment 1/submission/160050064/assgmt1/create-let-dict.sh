#!/bin/sh

fstsymbols --save_isymbols=L.isyms $2 > /dev/null 2>&1
python create.py --fst --osyms --name S --file $1
fstcompile --keep_isymbols --keep_osymbols --isymbols=L.isyms --osymbols=S.osyms S.txt | fstinvert | fstarcsort --sort_type=olabel | fstcompose - $2
rm -f L.isyms S.txt S.osyms