#!/bin/bash

mkdir organised
rolls=$(cat mock_grading/roll_list)
for roll in $rolls
do
	mkdir -p organised/$roll
	cd mock_grading/submissions
	for filename in $roll*
	do
		cd ../../organised/$roll
		ln -s ../../mock_grading/submissions/$filename $filename
	done
	cd ../..
done

