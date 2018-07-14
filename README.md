# pharmacy-counting-mengzhao

coding approach:
1. read the data from the input file. each word or number is ended by ','. each record is ended by '\n'.
2. if one record is read from the file, search the drug name of this record in a struct array 'cost'.
3. if the drug name exists in 'cost', update the total cost and number of prescriber of this drug in 'cost'; otherwise, add this drug to 'cost' as a new one.
4. repeat 1-3 until all data are read from the input file.
5. find the drug with the maximum cost and save it in the output file. repeat this step until all drugs are saved in the output file.

running instructions:
1. this program is written in C language
2. users may need to change the path and the name of the input/output files if these files are not in the right locations. line 70 and 75 of the program.
3. this program uses three header files: <stdio.h>, <stdlib.h> and <string.h>
