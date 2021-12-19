# Employee-Parsing

A05 - Parsing of employees

### main.c

Seperated into three main parts : {
  
  \tGet input : Loop taking in input line by line and passing it to the parser,
  
  Parse input : Use parsing handler functions to idnetify individual parts of the structure whiule skipping over spaces,
  
  Print function : Print output in specified format,
  
  Sort function : Bubble sort to rearrange employees by DOB (Time complexity O(n^2))
  
} 

### fileOperations.c

Open and close file pointer.
Use fgets to read line by line input in a format that can be apssed to existing functions for parsing.

## Author Colin McCormack
