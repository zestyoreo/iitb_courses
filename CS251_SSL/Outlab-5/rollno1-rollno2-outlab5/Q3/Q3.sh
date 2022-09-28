#!/bin/bash
N=$1
awk -F":" '{print $2 > $1}' sample.txt
echo $N
sed 's/|/ /g' 0 > 0.1
sed 's/|/ /g' 1 > 1.1
sed 's/-/ /g' word_token_mapping.txt > wtm.txt
rm 0
rm 1
rm word_token_mapping.txt
mv wtm.txt word_token_mapping.txt
awk '{a[$1]++}END{for(k in a)print a[k],k}' RS=" |\n" 0.1 | sort -r > pre_ham.txt
awk '{a[$1]++}END{for(k in a)print a[k],k}' RS=" |\n" 1.1 | sort -r > pre_spam.txt
awk 'NR == FNR{a[$2]=$1;next} {$2=a[$2]}1' word_token_mapping.txt pre_ham.txt > pre_ham
awk 'NR == FNR{a[$2]=$1;next} {$2=a[$2]}1' word_token_mapping.txt pre_spam.txt > pre_spam
rm pre_spam.txt
rm pre_ham.txt
awk '{print $2}' pre_ham | sort > pre_ham.txt
awk '{print $2}' pre_spam | sort > pre_spam.txt
awk 'NR == FNR{a[$2]=$1;next} {$2=$1}1 {$1=a[$2]}1' pre_ham pre_ham.txt > pre_ham2
sort -r -nk1 pre_ham2 >pre_ham3