This folder has a solution to the assignment. A lot of you have earned full credit, so for those of you who want to understand something you didn't get, you can look here, or ask your friends, who might have done it better :)

There are a bunch of outputs in this directory: these are the expected tree structures we compared your code's behaviour with. 

We ran 2 test cases one after the other, the first steps being:

A: bash download.sh https://www.cse.iitb.ac.in/~vahanwala/ssl21/big_mock_case/ 2
B: bash download.sh https://www.cse.iitb.ac.in/~vahanwala/ssl21/hidden_test/big_mock_case/ 3


A few of you missed out on full credit because the directory structure/name didn't match exactly after the wget step, or you mistakenly generated/removed/retained more files than necessary, or you used absolute paths while creating symbolic links, or you got the sort wrong while creating the final csv and text files. Don't worry, the semester is long enough to compensate.

SCHEME:

1 mark for download.sh exiting gracefully with the expected error message if there are less than 2 arguments, 4 marks for downloading test case A correctly, 5 for downloading B correctly.

10 marks each for organising A and B correctly.

4 marks each for matching the expected directory structure, outputting the correct marksheet.csv and the correct distribution.txt, for both test cases. (Exception: marksheet.csv for B carries 5 marks)

CRIBS POLICY:

Use the floated Google form (https://forms.gle/8tNDXAeBHgTcGeh57), and only the form, to let us know if, given the scheme, you disagree with the credit we've awarded you. All the discussion will be based on the code you turned in, and we won't allow any modifications to it. 

Fill the form only if you believe that the behaviour of the submitted code can be interpreted as satisfying a reasonable interpretation of the problem statement. We trust that these discussions will happen with responsibility and respect.