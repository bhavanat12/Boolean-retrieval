Bhavana Talluri
S20170010025
Assignment 1
11:55PM 09-09-2019


ASSUMPTIONS:

1. The path is set for the files in my local machine. To run it on a different system, just the lines 42 and 44 needs to be edited.

2. Since my code is running on a MacOs, I have explicitly put a condition to not consider the hidden files - . , .. , .DS_Store.

3. 9 documents are taken into consideration (avoiding the 10th doc, which is creating the problem in sorting. The sorted output is like 1,10,2,3,....)

4. Each document contains minimum of 20 words.

5. Hyderabad is one of the words that's occuring in atleast 5 documents.




CODE:

1. Works for all kinds of boolean operators - AND, OR, AND NOT, OR NOT between terms.

2. Works for queries of the format - X* and *X.

3. Works for the AND, OR operations of the wildcard queries.

2. Permuterm index (for the form X*Y) has been constructed using the linked list datastructure. 
