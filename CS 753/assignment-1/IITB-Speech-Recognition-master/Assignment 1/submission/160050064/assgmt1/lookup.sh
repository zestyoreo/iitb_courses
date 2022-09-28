#!/bin/sh

if [ "$1" -eq 1 ]; then
    fstsymbols --save_isymbols=L.isyms $2 > /dev/null 2>&1
    if awk 'NR > 1 {print $1}' L.isyms | grep -qw $3; then
        echo "0\t1\t$3\n1" | fstcompile --acceptor --keep_isymbols --keep_osymbols -isymbols=L.isyms > A.fst
        fstcompose A.fst $2 | fstproject --project_output | fstprint --acceptor | awk '{printf("%s ",$3)}END{print ""}'
        rm -f A.fst
    else
        echo '<OOV>'
    fi
    rm -f L.isyms
elif [ "$1" -eq 3 ]; then
    echo $3 > W.txt
    python create.py --fst --isyms --name S --file W.txt
    fstsymbols --save_isymbols=QPrefix.isyms $2 > /dev/null 2>&1
    fstcompile --keep_isymbols --keep_osymbols -isymbols=S.isyms -osymbols=QPrefix.isyms S.txt | \
    fstarcsort --sort_type=olabel | fstcompose - $2 | fstrmepsilon | fstdeterminize --det_type="disambiguate" | fstminimize --allow_nondet=true | fstrmepsilon | \
    fstrandgen | fstproject --project_output | fstprint --acceptor | awk '{printf("%s ",$3)}END{print ""}'
    rm -f W.txt S.isyms S.txt QPrefix.isyms
fi