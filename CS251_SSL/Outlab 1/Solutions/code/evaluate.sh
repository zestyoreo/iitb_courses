#!/bin/bash

rolls=$(cat mock_grading/roll_list)
touch marksheet.csv
touch distribution.txt
for roll in $rolls
do
	cd organised/$roll
	for filename in $roll*.cpp
	do
		g++ $filename -o executable 2>/dev/null
	done
	mkdir -p student_outputs
	let "score=0"
	for filename in ../../mock_grading/inputs/*.in
	do
		testname=$(basename $filename .in)
		timeout 5 ./executable < $filename >student_outputs/$testname.out 2>/dev/null |:
		cd student_outputs
		let "a=$(diff {../../../mock_grading/outputs/,}$testname.out | wc -l)"
		cd ..
		if [ $a -eq 0 ]
		then
			let "score=score+1"
		fi
	
	done
	echo "$roll,$score"
	cd ../..
done |
sort --field-separator="," -k1 | cat>marksheet.csv

cat marksheet.csv | cut -d ',' -f 2 |
sort --field-separator="," -k1nr | cat>distribution.txt

