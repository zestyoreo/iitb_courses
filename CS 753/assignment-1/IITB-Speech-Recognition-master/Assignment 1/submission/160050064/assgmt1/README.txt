--------------
    README
--------------

    -   fst.py contains my own custom FST class implementation.
    -   create.py reads the lex.txt file to generate the fst's in the AT&T format. (used by both 3.1 and 3.2)
    -   modify.py modifies the given fst to generate a prefix/suffix fst for parts 3.3 and 3.4
    -   lookup-merge.py does exactly what lookup-merge.sh is supposed to do. (the .sh file contains a direct call to .py file only)

    - For running lookup.sh, the format is the same as specified in the assignment pdf except that an additional first argument specifies which part of question it is. For example in 3.3, you may run the command as './lookup.sh 3 QPrefix.fst PRES' where 3 denotes it's 3.[3] (3rd part of this question).
