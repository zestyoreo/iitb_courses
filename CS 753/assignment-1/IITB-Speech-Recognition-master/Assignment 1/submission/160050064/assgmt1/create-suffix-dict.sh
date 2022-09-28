#!/bin/sh

fstsymbols --save_isymbols=Q.isyms --save_osymbols=Q.osyms $1 | fstpush --push_labels | fstrmepsilon | fstminimize --allow_nondet=true | fstprint > Q.txt
python modify.py --suffix --name Q --file Q.txt
fstcompile --keep_isymbols --keep_osymbols --isymbols=Q.isyms --osymbols=Q.osyms QSuffix.txt
rm -f Q.isyms Q.osyms Q.txt QSuffix.txt