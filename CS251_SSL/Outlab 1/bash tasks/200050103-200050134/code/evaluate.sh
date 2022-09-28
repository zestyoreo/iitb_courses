#!/bin/bash
score () {
    cd organised/$num
    mkdir student_outputs
    let "score = 0"
    for fil in *.cpp
    do
        g++ -o executable $fil 2>/dev/null
    done
    
    cd ../../mock_grading/inputs

    for fil in *.in
    do
        out_filename="${fil%in}out"
        # Learned how to prevent segmentation fault errors from https://stackoverflow.com/questions/23954607/redirection-of-a-out-is-not-capturing-segmentation-fault
        { timeout 5s ./../../organised/$num/executable < $fil > ../../organised/$num/student_outputs/$out_filename 2> /dev/null; } 2> out_err
        if [[ $? -eq 0 ]]
        then
            diff ../../organised/$num/student_outputs/$out_filename ../outputs/$out_filename > /dev/null
            if [[ $? -eq 0 ]]
            then
                let score++
            fi
        fi
        
    done
    if [[ -f out_err ]]
    then
        rm out_err
    fi
    cd ../..
    return $score
}

touch marksheet.csv
touch distribution.txt
roll=$(sort mock_grading/roll_list)
for num in $roll
do 
    score
    myS=$?
    printf "%s,%s \n" $num $myS>>marksheet.csv
    printf "%s \n" $myS>>dis.txt
done
sort -r dis.txt > distribution.txt
rm dis.txt
