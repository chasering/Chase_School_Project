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
#include <stdio.h>	//needed for printf, fread
#include <iostream>
#include <cstdio>

using namespace std;

//Structures
struct sDate {
    int month;
    int day;
    int year;
};
struct sRecord {
    int film_id;
    char subject[28];
    sDate date;
    char state[3];
    char county[12];
    float length;
    char charge_code;
};
struct indT {
    int id, pos;
};

//Prototypes
void loadIndex(indT ind[]);
void printMenu(char message[30]);
void listTable(indT *ind);
void search(indT *ind, int id, char *message);
void add(indT *ind);
void deleteRec();

int get_film_id(char *howToAsk);                    
void get_subject(char *dest, char *howToAsk);    
void get_date(sDate &dest, char *howToAsk);       
void get_state(char *dest, char *howToAsk);      
void get_county(char *dest, char *howToAsk);     
void get_length(float &dest, char *howToAsk);     
void get_charge_code(char &dest, char *howToAsk);

//Supporting Functions
bool is_int(char from);                             
bool is_double(char *num);                          
void list_all();

//gettersville
int getInt(char []);
double getDouble(char []);
char getChar(char []);
void getString(char [], char *);

int main() {
    /* This line for file restoration --> */ system("copy assignv2.ind.bak assignv2.ind"); system("copy assignv2.rnd.bak assignv2.rnd"); system("cls");
    //variables
    indT ind[50], *indP;        //create index
    indP = ind;
    loadIndex(ind);
    char message[50] = {'\0'};       //for menu messages

    printMenu(message);
    int answer = getInt(""); //atoi(gets(buff));
    while(!(answer == 5)) {
        switch (answer) {
        case 1:
            //List table option selected
            system("CLS");
            listTable(ind);
            strcpy(message, "Table printed.");
            break;
        case 2:
            //Search table option selected
            search(indP
                , getInt("Please enter a film ID to search for: ")
                , message);
            break;
        case 3:
            //Add a Record option selected
            add(ind);
            strcpy(message, "Record Added.");
            break;
        case 4:
            //Delete Record Selected

            strcpy(message, "Record Deleted.");
            break;
        case 99: //list everything in file (hidden option)
            list_all();
            break;
        default:
            strcpy(message, "Invalid option selected, try again.");
            break;
        }
        system("CLS");
        printMenu(message);
        message[0] = '\0';
        answer = getInt("");
    }
    printf("Press something to exit ..");
    system("PAUSE>NUL");
    return 0;
}

//Functions
void loadIndex(indT ind[]) {
    //vars
    FILE *fp;
    int intBuff;
    //work
    if(!(fp = fopen("assignv2.ind", "rb"))) {
        printf("For some reason, we couldn't open the file for output. Better check with HAL..\n");
    }
    for(int x = 0; x < 50; x++) {
        fread(&intBuff, sizeof(int), 1, fp);
        if(!(feof(fp))) {
            ind[x].id = intBuff;
            fread(&intBuff, sizeof(int), 1, fp);
            ind[x].pos = intBuff;
        } else {
            for(int y = x; y < 50; y++) {
                ind[y].id = 99999;
                ind[y].pos = 99999;
            }
            x = 50;
            fclose(fp); //fp->assignv2.ind
        }
    }
}
void printMenu(char message[30]) {
    printf("Select one of the following options:\n");
    printf("\n");
    printf("\t(1)\tList the File\n");	
    printf("\t(2)\tSearch the File\n");
    printf("\t(3)\tAdd a Record\n");
    printf("\t(4)\tDelete a Record\n");
    printf("\t(5)\tExit The Program\n");
    printf("\n");
    printf("%s\n", message);
    printf("Please enter the number for the selections above: ");
}
void listTable(indT ind[]) {
    sRecord record;
    int intBuff;
    FILE *fp;
    if(!(fp = fopen("assignv2.rnd", "rb"))) {
        printf("For some reason, we couldn't open the file for output. Better check with HAL..\n");
    }
    printf("%6s|%-26s|%-8s|%-5s|%-10s|%-8s|%-s\n", "FilmID", "Subject", "Date",
        "State", "County", "Length", "Charge Code");
    for(int x = 0; ind[x].pos != 99999; x++) {
        fseek(fp, ind[x].pos * sizeof(sRecord), SEEK_SET);
        fread(&record, sizeof(record), 1, fp);
        printf("%6i|%-26s|%2i/%2i/%2i|%-5s|%-10s|%-6f|%c\n", record.film_id, record.subject, record.date.month, record.date.day, record.date.year, record.state, record.county, record.length, record.charge_code);
        printf("------+--------------------------+--------+-----+----------+--------+---------\n");
    }
    fclose(fp); //fp->assignv2.ind
    printf("\n");
    system("PAUSE");
}
void search(indT *indP, int id, char *message) {
    int x;
    for(x = 0; indP[x].id != 99999; x++) {}

    bool found = false;
    int first = 0;
    int middle = 0;
    int last = x;
    int spot = -2;
    while((!found) && (last >= first)) {
        middle = ((first + last) / 2);
        if(indP[middle].id == id) {
            spot = middle;
            found = true;
        }
        else if (indP[middle].id < id) {
            first = middle + 1;
        }
        else {
            last = middle - 1;
        }
    }
    if (spot >= 0) {
        strcpy(message, "Previous search record was found.");
        system("CLS");
        sRecord record;
        FILE *fp;
        if(!(fp = fopen("assignv2.rnd", "rb"))) {
            printf("For some reason, we couldn't open the file for output. Better check with HAL..\n");
        } else {
            fseek(fp, indP[spot].pos * sizeof(sRecord), SEEK_SET);
            fread(&record, sizeof(record), 1, fp);
            fclose(fp);
        }

        printf("\n%6s|%-26s|%-8s|%-5s|%-10s|%-8s|%-s\n", "FilmID", "Subject", "Date", "State", "County", "Length", "Charge Code");
        printf("------+--------------------------+--------+-----+----------+--------+---------\n");
        printf("%6i|%-26s|%-2i/%-2i/%-2i|%-5s|%-10s|%-6f|%c\n\n", record.film_id, record.subject, record.date.month, record.date.day, record.date.year, record.state, record.county, record.length, record.charge_code);
        system("PAUSE");
    } else {
        strcpy(message, "RECORD NOT FOUND");
    }
    system("PAUSE");
}
void add(indT ind[]) {
    //record *rp, int recordCount
    FILE * fp;
    if((fp = fopen("assignv2.rnd", "rb")) == NULL) {
        printf("Couldn't open file.");
    } else {
        sRecord record;
        record.film_id = get_film_id("Enter a number between 0 and 15000 (or a negative number to quit): ");
        get_subject(record.subject, "Please enter the subject: ");
        get_date(record.date, "Please enter the date in xx/xx/xxxx format: ");
        get_state(record.state, "Please enter the state in CAPITAL two letter abbreviation: ");
        get_county(record.county, "Please enter the county: ");
        get_length(record.length, "Please enter the length: ");
        get_charge_code(record.charge_code, "Please enter the charge code: ");
        // The record is complete. Now add code to add it.
        
        // Find first 99999 space in index
        int x; for(x = 0; ind[x].id != 99999; x++) {/* nothing to see here */}
        
        fseek(fp, 0, SEEK_END);
        fwrite(&record, sizeof(sRecord), 1, fp);
        ind[x].id = record.film_id;
        ind[x].pos = x;
        fclose(fp);
    }
}
void deleteRec() {
}
/*#####################################
##                                   ##
##     Record Getting Functions      ##
##                                   ##
#####################################*/
int get_film_id(char *howToAsk) {
    char buff[40];
    bool valid_num = false;
    bool first;

    while(!valid_num) {
        valid_num = true; //assume it's good, then prove it wrong.
        first = true;

        printf("%s", howToAsk);
        gets(buff);

        if (!strcmp(buff, "")) {
            printf("Sorry, but <RETURN> is not a number.\n");
        }
        else {
            for (int x = 0; x < strlen(buff); x++) {
                if(first) {
                    first = false;
                    if (buff[0] != '-') {
                        if(!is_int(buff[0])) { //getting true here means they put in a - then a non number
                            x = strlen(buff);
                            valid_num = false;
                            printf("Numbers only please!\n");
                        }
                    }//else buff[0] == '-'
                }
                else if (!is_int(buff[x])) {
                    x = strlen(buff);
                    valid_num = false;
                    printf("Numbers only please!\n");
                }
            }//end for
        }
        if (valid_num) {
            if (atoi(buff) > 15000) {
                valid_num = false;
                printf("Number can't be higher than 15000.\n");
            }
        }
    }
    return atoi(buff);
}
void get_subject(char *dest, char *howToAsk) {
    bool valid = false;
    char buff[40];
    while(!valid) {
        printf("%s", howToAsk);
        gets(buff);
        if(strlen(buff) == 0) {
            printf("You have to at least enter SOMETHING into the subject.\n");
        }
        else if(strlen(buff) > 28) {
            printf("Subject cannot be longer than 27 chars (28th for \\0)\n");
        }
        else {
            valid = true;
        }
    }
    strcpy(dest, buff);
}
void get_date(sDate &dest, char *howToAsk) {
    char buff[40];
    char month[3], day[3], year[5];
    int intMonth, intDay, intYear;
    bool valid = false;
    bool validFormat = false;
    bool innerValid = false;

    while(!valid) {
        valid = true; //assume their input is good, else the ifs below will tell
        validFormat = false;//make sure the next while loop runs.
        while(!validFormat) {
            validFormat = true;//assume what they entered will be okay, so that the following test get skipped, else they'll trigger a redo
            //ask the important question
            printf("%s", howToAsk);
            gets(buff);
            buff[10] = '\0'; //just in case they add something longer than the allowed amount

            for(int x = 0; x < 10; x++) {
                if ((x != 2) && (x != 5)) {
                    if (!is_int(buff[x]) )
                    {
                        x = 11; //dump out loop
                        printf("Please only enter numbers for the dates.\n");
                        validFormat = false; //make sure inner loops goes again
                    }
                }
                else if (buff[x] != '/') {
                    x = 11;
                    printf("Both date separators must be a forward slash \"/\"\n");
                    validFormat = false; //make sure inner loops goes again
                }
            }
        }//end validFormat
        //do date range validation down here

        //move everything into their respective 'areas'
        month[0] = buff[0]; month[1] = buff[1];
        month[2] = '\0'; //move the two month numbers over
        day[0] = buff[3]; day[1] = buff[4];
        day[2] = '\0'; //move the two day numbers over
        year[0] = buff[6]; year[1] = buff[7]; year[2] = buff[8]; year[3] = buff[9];
        year[4] = '\0';//move the 4 year numbers over

        intMonth = atoi(month);
        intDay   = atoi(day);
        intYear  = atoi(year);

        if(intMonth > 12) {
            valid = false;
            printf("Highest month is 12.\n");
        }//end if intMonth > 12
        else if(intDay > 31) {
            valid = false;
            printf("No month has more than 31 days.\n");
        }//end if intDay
        else if((intMonth == 4) || (intMonth == 6) || (intMonth == 9) || (intMonth == 11)) {
            if (intDay > 30) {
                valid = false;
                printf("Month #%i only has at most 30 days.\n", intMonth);
            }
        }
        else if(intMonth == 2) {
            if(intDay > 28) {
                valid = false;
                printf("Month #%i only has at most 28 days.\n", intMonth);
            }
        }
        if (intDay < 1) {
            valid = false;
            printf("No month has 0 or less days.\n");
        }
    }// end while(!valid)
    //if it gets to here, it's good, let's do something about it
    dest.month = intMonth;
    dest.day   = intDay;
    dest.year  = intYear;
}//end func
void get_state(char *dest, char *howToAsk) {
    static char stateList[50][3];
    static bool first = true;
    bool valid = false;
    char buff[40];
    char stateInput[3];

    if (first) {
        FILE *fp;
        if(!(fp = fopen("STATES.DAT", "r"))) {
            printf("\n\n*** Error opening file: STATES.DAT ***\n\n");
        } else {
            char buff[40];
            for(int x = 0; x < 50; x++) {
                fgets(buff, 40, fp);
                fgets(buff, 40, fp); //this is to discard the full state name.
                buff[strlen(buff) - 1] = '\0';
                strcpy(stateList[x], buff);
            } //end for loop that loads the array from the file
        }// end else opened
        first = false; //set so that it doesn't run this area again.
    }//end if(first)

    while (!valid) {
        printf("%s", howToAsk);
        gets(stateInput);

        for (int x = 0; x < 50; x++) {
            if (!strcmp(stateList[x], stateInput)) {
                valid = true;
                x = 50;
                strcpy(dest, stateInput);
            }// end if strcmp
        }//end for
        if(!valid) {
            printf("Invalid state entered.\n");
        }
    }//end while
}
void get_county(char *dest, char *howToAsk) {
    char buff[40];
    printf("%s", howToAsk);
    gets(buff);
    buff[strlen(buff) - 1] = '\0';
    strcpy(dest, buff);
}
void get_length(float &dest, char *howToAsk) {
    char buff[40];
    bool valid = false;

    while(!valid) {
        printf("%s", howToAsk);
        gets(buff);

        if (is_double(buff)) {
            if((atof(buff) <= 30) && (atof(buff) >= 0)) {
                valid = true;
                dest = atof(buff);
            } else {
                printf("Invalid number entered, please enter a number between 0 and 30.\n");
            }
        }
        else {
            printf("Invalid number entered.\n");
        }
    }
}
void get_charge_code(char &dest, char *howToAsk) {
    char buff[40];
    bool valid = false;

    while(!valid) {
        printf("%s", howToAsk); gets(buff);
        if((toupper(buff[0]) < 'A') || (toupper(buff[0]) > 'R')) {
            printf("Invalid char entered. Must be between A and R.\n");		    
        } else {
            valid = true;
        }
    }
    dest = toupper(buff[0]);
}

/*#####################################
##                                   ##
##       Supporting Functions        ##
##                                   ##
#####################################*/
bool is_int(char from) {
    bool valid = false;
    if (isdigit(from)) {
        valid = true;
    }
    return valid;
}
bool is_double(char *num) {
    int dec_count = 0;
    int loop = 0;

    for(int x = 0; x < strlen(num); x++) {
        if (num[x] == '.') {
            dec_count++;
        } 
        else if (!isdigit(num[x])) {
            return false;
        }
        else if (dec_count > 1) {
            return false;
        }
    }
    return true;
}

//gettersville
int getInt(char howToAsk[101]) {
    char buffer[40];
    printf("%s", howToAsk);
    gets(buffer);
    return atoi(buffer);
}
double getDouble(char howToAsk[101]) {
    char buffer[40];
    printf("%s", howToAsk);
    gets(buffer);
    return atof(buffer);
}
char getChar(char howToAsk[101]) {
    char buffer[40];
    printf("%s", howToAsk);
    gets(buffer);
    return buffer[0];
}
void getString(char howToAsk[101], char *dest) {
    char buffer[40];
    printf("%s", howToAsk);
    gets(buffer);
    strcpy(dest, buffer);
}
void list_all() {
    FILE *sec;
    int tmp = 0;
    sRecord stuff;
    int x, y;

    if(!(sec = fopen("assignv2.rnd", "rb"))) {
        printf("For some reason, we couldn't open the file for output. Better check with HAL..\n");
    }
    printf("%6s|%-26s|%-8s|%-5s|%-10s|%-8s|%-s\n", "FilmID", "Subject", "Date",
        "State", "County", "Length", "FILE POS");
    for(x = 0, y = 0; x < 10000; x++) {
        fseek(sec, x * sizeof(sRecord), SEEK_SET);
        fread(&stuff, sizeof(sRecord), 1, sec);
        if(stuff.film_id != tmp) {
            tmp = stuff.film_id;
            printf("%6i|%-26s|%2i/%2i/%2i|%-5s|%-10s|%-6f|%i\n", stuff.film_id, stuff.subject, stuff.date.month, stuff.date.day, stuff.date.year, stuff.state, stuff.county, stuff.length, x);
            y++;
        }
    }
    printf("%i entries found..\n", y);
    system("PAUSE>NUL");
    fclose(sec);
}