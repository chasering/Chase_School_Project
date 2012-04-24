// Name: Chase Ring
// Prog: Assignment 05
// Purp:
//OUTPUT:
//           Your program must be capable of printing the database, or a single
//              record from the database, or updating the database.   
//INPUT:
//           Input to this program is a pair of files provided by the
//              instructor: a data file(rnd) and an index file(ind) made of
//              two-integer structures.  Make sure you create backups because
//              each test of the program will alter the data file.  The data
//              file will consist of records stored in structures similar to
//              those described in program four.  
//PROCESSING:
//           Your program should offer the user the following choices:
//                                                LIST THE FILE 
//                                                SEARCH THE FILE 
//                                                ADD A RECORD 
//                                                DELETE A RECORD 
//                                                EXIT THE PROGRAM
//
//      On LIST THE FILE you should clear the screen and list all
//          records in your database to the output window with appropriate
//          column headings.
//      On SEARCH THE FILE prompt the user for the film id, and then if found
//          in the index table, print that record on the screen with column
//          headings.  Reuse the code to print from the first menu choice.
//          If the record is not found the words "RECORD NOT IN DATABASE"
//              should appear on the screen.             
//      On ADD A RECORD your program should prompt the user for each field
//          needed and add the information to both the data file and the index
//          table.  Get the id first and make sure the record does not already
//          exist.  Incorporate your validation methods from program four into
//          this program in order to add properly edited new records.             
//      On DELETE A RECORD your program should prompt for a film id, then
//          either delete the record from the index or print a message stating
//          that the record does not exist.
//
//For purpose of simplification, when exiting the program do not rewrite your
//  index file to the disk.  When testing do not attempt to add new records
//  after deleting a record.  Each time you test you must start with a fresh
//  copy of the data file.
//
//You must test all menu choices for their appropriateness.  When you turn in
//  the assignment the files you need must be available to your program. 
//
//Unlike assignment 3 you are not to load all the records into a table.  Load
//  only the index.  Data records should be brought into the program one at a
//  time on an as-needed basis.  Use the information found in unit seven.  Do
//  not rewrite the index file: this will make it easier for you to test often
//  simply by recopying your .rnd file.

#include <stdlib.h>	//needed for ato(i,f,etc)
#include <stdio.h>	//needed for printf
#include <iostream>
#include <cstdio>

using namespace std;

int main() {

    system("PAUSE>NUL");
    return 0;
}