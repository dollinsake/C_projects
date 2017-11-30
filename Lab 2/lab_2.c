#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "person.h"
#include<ctype.h>
#include<string.h>

static int numRecords = 0;
static int numOfAccesses = 0;

struct person* printAllRecords(struct person* db){//no parameters, numRecords is global


	for (int i = 0; i < numRecords; i++){
		//printf("test print");

		printf("Record %i:\n",i+1);
		printf("Name: %s\n",db[i].name);
		printf("ID Number: %i\n",db[i].IDnumber);

		printf("\n");

	}
}

void printNumOfRecords(){

    printf("Number of records: %i\n",numRecords);
}

void sizeOfDb(){

    int size = sizeof(struct person)*numRecords;

    printf("Size of database: %i\n", size);
}

struct person* addRecord(struct person* oldDB){

  int idEntry;
  char nameEntry[100];
  bool invalidName = true;
  struct person* newDB;
  int dbsize = sizeof(struct person)*numRecords;

  newDB = (struct person*) malloc(sizeof(struct person) * ++numRecords);
  memcpy(newDB,oldDB,dbsize);
  free(oldDB);

    while (invalidName){

        printf("Enter the person's name (< 100 characters): ");
        scanf("%s", nameEntry);
        if (sizeof(nameEntry) > 100){
            printf("Invalid entry.\n");
            invalidName = true;
        }
        else
	  invalidName = false;
    }
    printf("Enter %s's ID (< 100 characters): ",nameEntry);
    scanf("%i", &idEntry);

    numOfAccesses++;

    strcpy(newDB[numRecords - 1].name,nameEntry);
    newDB[numRecords - 1].IDnumber = idEntry;

    return newDB;
}

void autoAddRecords(struct person* db){

  numRecords = 6;

  strcpy(db[0].name,"Yeezy");
  db[0].IDnumber = 000;

  strcpy(db[1].name,"Kid Cudi");
  db[1].IDnumber = 666;

  strcpy(db[2].name,"TravisScott");
  db[2].IDnumber = 8675309;

  strcpy(db[3].name,"Drake");
  db[3].IDnumber = 8;

  strcpy(db[4].name,"Weeknd?");
  db[4].IDnumber = -1;

  strcpy(db[5].name,"Future_hendricks");
  db[5].IDnumber = 44;
}

struct person* deleteRecord(struct person* oldDB){

  if(numRecords > 0)
    {

      struct person* newDB;
      int dbsize = sizeof(struct person)*--numRecords;

      newDB = (struct person*) malloc(sizeof(struct person) * numRecords);

      memcpy(newDB,oldDB,dbsize);
      free(oldDB);

      printf("\nRecord Deleted!\n\n");

      numOfAccesses++;

      return newDB;

    }
  else
    {
      printf("No Records to Delete!\n\n");

      return oldDB;
    }
}

void printNumOfAccesses(){
    printf("Number of accesses: %i\n",numOfAccesses);
}

void main(void){

    bool valid = true;
    char entry;
    int menuValue;

    struct person* dbPointer = (struct person*)malloc(sizeof(struct person)*6);

    autoAddRecords(dbPointer);

    while (valid){  //start menu
        bool done = false;
        printf("\nMENU\n"
            "1. Print all records\n"
            "2. Print number of records\n"
            "3. Print size of database\n"
            "4. Add record\n"
            "5. Delete record\n"
            "6. Print number of accesses to database\n"
            "7. Exit\n");
        printf("Select a menu option: ");
        scanf("%s",&entry);
        printf("\n");
        menuValue = (int)entry; //convert to ASCII
        menuValue -= 48;    //adjust to integer entered

        switch(menuValue)
        {
          case 1:
            printAllRecords(dbPointer);
            valid = true;
            break;
          case 2:
            printNumOfRecords();
            valid = true;
            break;
          case 3:
            sizeOfDb();
            valid = true;
            break;
          case 4:
            dbPointer = addRecord(dbPointer);
            valid = true;
            break;
          case 5:
            dbPointer = deleteRecord(dbPointer);
            valid = true;
            break;
          case 6:
            printNumOfAccesses();
            valid = true;
            break;
          case 7:
            printf("\nGoodbye!\n\n");
            valid = false;
            break;
          default:
            printf("\nInvalid input. Enter a valid menu option.\n"); //add prompt?
            valid = true;
            break;
        }
    }//end while
}//end main
