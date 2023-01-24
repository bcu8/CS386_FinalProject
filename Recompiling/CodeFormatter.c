#include "StandardConstants.h"
#include "File_Input_Utility.h"
#include "Console_IO_Utility.h"
#include "File_Output_Utility.h"
//#include <string.h>

/*This program takes in a .c file of improperly formatted code then formats it 
according to Professor Leverington's preference. The output file has the same name 
as the input with "FORMATTED" appended to the original file name.

This program will make the students life easier as they no longer have to worry about 
how tabs will make their code look outside of the editor. 
It also notifies student if there are lines exceeding 80 charactes so that they may 
avoid those GUR reductions as well. 

The graders experience will also become easier and more efficient.
*/

//constants
const char *OUT_FILE_STAMP="FORMATTED.c";

//prototypes

/*function takes in an input file name and appends OUT_FILE_STAMP. Then returns resulting string using parameter outString*/
void createOutputFileName(const char *inString, char *outString)
   {
	strcpy(outString,inString);

	outString[strlen(outString)-2]=NULL_CHAR;
	
	strcat(outString, OUT_FILE_STAMP);
   }
   
/*function takes in pointer to input file, pointer to currentChar, pointer to lastChar, and iteration. Returns true if file has more data, false if file has ended. updates current and last char as return parameters*/   
bool getNextChar(FILE *filePtr, char *currentChar, char *lastChar, int i )
   {
	//if not first iteration, update lastChar
	if ( i != 0 )
	   {
	    *lastChar = *currentChar;
	   }
	
	//return false if end of file detected
	if ( feof( filePtr ) )
	   {
		return false;		
	   }
	//otherwise update currentChar and return true
	*currentChar = fgetc(filePtr);
	return true;	
   }
   
bool isWhiteSpace(char chr )
   {
	if (chr == '\t' || chr == '\r' || chr == '\v' || chr == '\f' || chr == ' ')
	   {
		return true;   
	   }
	return false;
   }
   
bool writeFormattedFile(FILE *inputFilePtr, bool outputOpen, char *outFileName)
   {
	//initialize variables
	char currentChar, lastChar, trashChar=' ';
	int leadingSpaces = 0;
	int i=0,lineLength=0, currentLine=1;	
	   
	   
	//check if input and output files sucessfully opened
	if ( outputOpen && inputFilePtr!=NULL )
	   {		
		   
		//start while loop to get next char, loop ends when no more chars found
		while ( getNextChar( inputFilePtr, &currentChar, &lastChar, i ) )
		   {						
			//if char is a new line
			if ( currentChar == '\n' )
			   {
				//write new line
				writeEndlineToFile();
				
				//check line length
				if (lineLength > 80)
			       {
				    //if line length exceeds 80 notify user
				    printf("Line %d exceeds 80 characters\n", currentLine);
			       }
				
				//reset line length
				lineLength=0;
				
				//increment current line
				currentLine++;
				
				//read through characters until white space is gone
				while ( isWhiteSpace(trashChar) )
				   {
					trashChar = fgetc(inputFilePtr);
				   }
				
				//store new currentChar
				currentChar=trashChar;
				
				//reset trashChar
				trashChar=' ';							   

				//determine if change in leading spaces is necessary
				if ( currentChar == '{' )
					{
					leadingSpaces+=3; 
				
					//print leading spaces
					writeCharactersToFile(leadingSpaces, ' ');
			
					//print currentChar to outFile
					writeCharacterToFile(currentChar);
					}
				else if ( currentChar == '}' )
					{
						
					//print leading spaces
					writeCharactersToFile(leadingSpaces, ' ');
			
					//print currentChar to outFile
					writeCharacterToFile(currentChar);
					
					leadingSpaces-=3;								
					}
				else if (leadingSpaces==0)
					{			
					//print currentChar to outFile
					writeCharacterToFile(currentChar);  
			        }
				else
				   {
					//print leading spaces
					writeCharactersToFile(leadingSpaces + 1, ' ');
			
					//print currentChar to outFile
					writeCharacterToFile(currentChar);
					
					//update line length
					lineLength=leadingSpaces+1;
				   }					
					   
			   }
			else 
			   {
				//print currentChar to outFile
				writeCharacterToFile(currentChar);   
				
				//increment line length
				lineLength++;
			   }
			   			
			//increment iteration
			i++;
		   }
		   
		//close input and output files
		closeOutputFile();
		fclose(inputFilePtr);
	   }
	//if file didnt open, notify user
	else
	   {
		if (inputFilePtr==NULL)
		   {			
		    printf("Input file not found\n");
		   }
		   
		if (!outputOpen)
		   {			
		    printf("output file couldn\'t open\n");
		   }
		   
		//notify user of program end
		printf("PROGRAM END\n");
	
		//return false
		return false;
	   }
	
	//tell user new file name
	printf("\nName of output file: \"%s\"\n\n",outFileName);
	
	//notify user of program end
	printf("PROGRAM END\n");
	
	return true;
   }

//main
int main()
   {
	//initialize variables
	char fileName[40];
	char outFileName[41];
	FILE *inputFilePtr; 
	//FILE *outputFilePtr;
	bool outputOpen;
	
	//print title and purpose
	printf("\n\nLeverington Safe Code Formatter\n");
	printf("===============================\n\n");
	
	printf("This program takes in a file name, formats the code\nthen outputs the formatted code to a new .c file with\n\"FORMATTED\" appended to the original file name\n\n");
	
	//prompt for name of input file
	printf("File Name (must end in .c): ");
	getInputString(fileName, false );
	printf("\n");
	
	//open input file 
	inputFilePtr = fopen(fileName, "r");
	
	//create output file name
	createOutputFileName(fileName, outFileName);
	
	//openOutput
	outputOpen=openOutputFile(outFileName);
	
	writeFormattedFile(inputFilePtr, outputOpen, outFileName);
	
	//end main
	return 0;
   }
	