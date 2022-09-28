#!/bin/bash

 

mkdir organised
inpu=mock_grading/roll_list
while IFS= read -r line
do
    cd organised
    mkdir $line
    cd ../mock_grading/submissions
    for file in $line*
    do
        cd ../../organised/$line
        ln -s ../../mock_grading/submissions/$file $file
        cd ../../mock_grading/submissions
    done
    cd ../..
done < "$inpu"