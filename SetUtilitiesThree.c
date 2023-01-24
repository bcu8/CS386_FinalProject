//header files included
#include "SetUtilitiesThree.h"

// prototypes

/*
Name: addItem
Process: adds item to set, does not allow duplicates,
         does not allow data to be added to full list,
         returns true if successful, false otherwise
Function Input/Parameters: new item (int)
Function Output/Parameters: pointer to set data (SetType)
Function Output/Returned: Boolean result of action
Device Input/---: none
Device Output/---: none
Dependencies: isInSet
*/
bool addItem( SetType *setData, int newValue )
   {
	//initialize variables
	
	//check if set is full
	if (setData->size >= setData->capacity )
	   {
		//end function
        return setData;
	   }
	//check if set aready contains newValue
	   //function isInSet
    else if (isInSet( setData, newValue))
       {
		//end function
        return setData;
	   }
	//if set isnt full and doesnt contain newValue
	else
	   {	   
	    //append newValue to set
	    setData->setArray[ setData->size ] = newValue;
	
	    //increase size by 1
	    setData->size++;
	
	    //return updated setData
	    return setData;
	   }
   }

/*
Name: copySet
Process: copies all data of one set into other
Function Input/Parameters: source set (const SetType)
Function Output/Parameters: pointer to destination set (SetType)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: none
*/
void copySet( SetType *dest, const SetType source )
   {
	//initialize local variables
	int index;
	
	//loop through both set arrays
	for (index=0; index < source.size; index++)
	   {
		//copy source to dest
		dest->setArray[ index ] = source.setArray[ index ];
	   }
	   
	//copy capacity from source to dest
    dest->capacity = source.capacity;
	
	//copy size from source to dest
	dest->size=source.size;	
   }

/*
Name: deleteItem
Process: searches for item, deletes if found,
         moves array data down by one from above the removed value,
         test loop must stop as soon as item is found (if it is found),
         returns true if item found and removed, false otherwise
Function Input/Parameters: item to delete (int)
Function Output/Parameters: pointer to setData (SetType *) 
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: none
*/
bool deleteItem( SetType *setData, int itemToDelete )
   {
	//initialize local variables
    int currentItem, currentIndex=0;
	
    //check if itemToDelete is in setData
	   //function isInSet
    if (isInSet(setData, itemToDelete))
	   {
		//prime while loop
		currentItem = setData->setArray[ currentIndex ];
	
		//loop through setArray to find location of itemToDelete
		while (currentItem != itemToDelete)
		   {
			//increment currentIndex
            currentIndex++;	

            //reassign currentItem
			currentItem = setData->setArray[ currentIndex ];
		   }
		
		//loop through the rest of the list
		for (currentIndex = currentIndex; currentIndex < setData->size-1; 
		currentIndex++)
		   { 
			//move item in next index to currentIndex
            setData->setArray[currentIndex] = 
			setData->setArray[currentIndex+1];			
		   }
		
		//decrease size by 1
		setData->size--;
		
		return true;
	   }
	   
	//return updated setData  
    return false;    
   }

/*
Name: displaySet
Process: displays series of set values, or displays "Empty Set" if no values
Function Input/Parameters: name of set array (const char *),
                           set data (SetType)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/---: none
Device Output/monitor: data displayed as specified
Dependencies: printf
*/
void displaySet( const char *setName, const SetType setData )
   {
    //initialize local variables
    int currentIndex;

    //print title of set
      //function printf
    printf("\n%s Set Data Display\n  ", setName );

    //check if set is empty
    if (setData.size==0)
       {
        //display empty set
          //function printf
        printf("   Empty Set\n\n");

        //end if
       }
    //if not empty, display data
    else
       {
        //loop through array
        for (currentIndex=0; currentIndex < setData.size; currentIndex++)
           {
            //check if this is last data point
            if (currentIndex==setData.size-1)
               {
                //print data with no comma or space
                  //function printf
                printf("%d\n", setData.setArray[currentIndex]);

                //end if
               }
            //if this is not last data point
            else
               {
                //print value with comma and space
                  //function printf
                printf("%d,  ", setData.setArray[currentIndex]);

                //end else
               }

            //end for
           }

        //end else
       }

    //end function
   }

/*
Name: findIntersection
Process: finds the set intersection between two sets,
         assigns to another set,
         loop to find intersection must end when common value found
Function Input/Parameters: sets one and two(const SetType)
Function Output/Parameters: pointer to result set (SetType *)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: isInSet
*/
void findIntersection( SetType *intersectSet, 
                       const SetType oneSet, const SetType otherSet )
   {
	//initialze local variables
    int currentIndex, currentIndexIntersectArr=0;

    //loop through oneSet Array
    for ( currentIndex=0; currentIndex < oneSet.size; currentIndex++)
	   {
        //check if current value of one set array is in other set
		    //function isInSet
		if (isInSet(&otherSet, oneSet.setArray[currentIndex]))
		   {
			//add the value to intersect set
			intersectSet->setArray[currentIndexIntersectArr] = 
			oneSet.setArray[currentIndex];
			
			//increment currentIndexIntersectArr
			currentIndexIntersectArr++;
		   } //end if
		   
	   }//end for
	   
    //update size of intersectArr
    intersectSet->size=currentIndexIntersectArr;	
   }
   
/*
Name: findUnion
Process: finds the set union between two sets,
         assigns to another set,
         loop to find union must end when common value found
Function Input/Parameters: sets one and two(const SetType)
Function Output/Parameters: pointer to result set (SetType *)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: copySet, isInSet
*/
void findUnion( SetType *unionSet, 
                const SetType oneSet, const SetType otherSet )
   {
	//initialize local variables
	int wkgIndex;
	
	//copy otherSet into unionSet
	   //function copySet
	copySet(unionSet, otherSet);
	
	//loop through oneSet
	for ( wkgIndex=0;wkgIndex < oneSet.size; wkgIndex++)
	   {
		//if integer at current index isnt already in unionSet, add it
			//function addItem
		addItem(unionSet, oneSet.setArray[ wkgIndex ]);
		
	   } //end for
	
	//end function
   }

/*
Name: getRandBetween
Process: generates and returns a random value
         between two given values, inclusive
Function Input/Parameters: low, high limits (int)
Function Output/Parameters: none
Function Output/Returned: random value as specified
Device Input/---: none
Device Output/---: none
Dependencies: rand
*/
int getRandBetween( int lowVal, int highVal )
   {
	//calculate range
    int range = highVal - lowVal + 1;

    //return generated value
    return rand() % range + lowVal;
   }
/*
Name: initializeSet
Process: initializes a set with all EVEN values, all ODD values,
         continually INCREMENTED values, or RANDOM three digit values
         depending on the DataSelections constant provided
Function Input/Parameters: start value, number of items (int),
                           capacity of array (int),
                           data values generation enum (DataSelections)
Function Output/Parameters: pointer to set data (SetType *)
Function Output/Returned: none
Device Input/---: none
Device Output/---: none
Dependencies: getRandBetween, isInSet
*/

void initializeSet( SetType *setData, int setCapacity, int startVal,
                    int numItems, DataSelections dataContained )
   {
	//initilize local variables
      //var to store incrimenting integers put into lists
      int currentItem;

      //set current index to 0
      int currentIndex=0;

      //set currentVal to the first value
      int currentVal=startVal;

      //set interval to 2
      int interval = 2;
	  
	  //set capacity to equal setCapacity
	  setData->capacity=setCapacity;
	  
	  //check if dataContained is RANDOM
	  if (dataContained==RANDOM)
	     {
	      //change the initial currentVal to a random number
		     //function getRandBetween
		  currentVal = getRandBetween( THREE_DIGIT_LOW, 
				                       THREE_DIGIT_HIGH );
		 }

    //determine if we are incrimenting by 1
    if (dataContained == INCREMENTED)
       {
        //change interval to 1
        interval = 1;

        //end if
       }

    //check if dataContained is Odd and start value is even
    else if (dataContained == ODD && startVal % 2 == 0)
       {
        //add 1 to currentVal
        currentVal++;
       } //end else if

    //check if dataContained is EVEN and start value is odd
    else if (dataContained == EVEN && startVal % 2 != 0)
       {
        //add 1 to currentVal
        currentVal++;
       } //end else if

    //loop numItems times
    for (currentItem=1; currentItem <= numItems; 
	     currentItem++)
       {
        //check if we have exceeded capacity
		if (currentIndex > setCapacity)
		   {
			//set size to equal setCapacity 
			setData->size = setCapacity;
			 
		   } //end if
		else
		   {
			//set current position in list to current value
            setData->setArray[currentIndex]=currentVal;

            //update current value
            if (dataContained == RANDOM)
		       { 
				//assign currentVal random number
				   //function getRandBetween
                currentVal = getRandBetween( THREE_DIGIT_LOW, 
				THREE_DIGIT_HIGH ); 					

	            //end if
			   }
		    else
		       {
			    //add interval
		        currentVal+=interval;
		       } //end else

            //incriment currentIndex
            currentIndex++;
			
		   }//end else
			   
        //end loop
       }
	   
	   //update size
	   setData->size=currentIndex;
	
    //end function   
   }

/*
Name: isInSet
Process: searches for given value in set,
         if found, returns true, otherwise returns false,
         must return found result immediately upon finding value
Function Input/Parameters: pointer to set (const *SetType),
                           search value
Function Output/Parameters: none
Function Output/Returned: Boolean result of test, as specified
Device Input/---: none
Device Output/---: none
Dependencies: none
*/
bool isInSet( const SetType *testSet, int searchVal )
   {
	//initialize local variables
	int currentIndex;
	
	//loop through array
	for ( currentIndex=0; currentIndex < testSet->size; 
	      currentIndex++ )
	   {
		//check if value at current index matches searchVal
		if (testSet->setArray[currentIndex] == searchVal)
		   {
			//return true
			return true;
			
			//end if
		   }
		//end for
	   }
	//return false  
	return false;
   }

/*
Name: isSubsetOf
Process: compares two sets to find if one is a subset of the other,
         returns Boolean result of test,
         function must return false as soon as a subset value is not found
Function Input/Parameters: two sets (const SetType)
Function Output/Parameters: none
Function Output/Returned: Boolean result of test, as specified
Device Input/---: none
Device Output/---: none
Dependencies: none
*/
bool isSubSetOf( const SetType oneSet, const SetType psbleSubset )
   {
	//declare local vars
	int currentIndexOneSet;
	int currentIndexPsbleSubset=0;
	bool match;
	
	//loop through psbleSubset
	while ( currentIndexPsbleSubset < psbleSubset.size )
	   {
		//set match to false
		match=false;
		   
		//reset currentIndexOneSet
		currentIndexOneSet=0;
		
		//loop through oneSet
		while (currentIndexOneSet < oneSet.size && !match )
		{
		 //check if current values of oneSet and psbleSubset match
		 if (oneSet.setArray[currentIndexOneSet]==
		 psbleSubset.setArray[currentIndexPsbleSubset])
		    {
		     //set match flag true
		     match=true;
			 
		    } //end if	
		
		 //increment currentIndexOneSet
		 currentIndexOneSet++;
		
		} //end while
		
		//check if no match was found
		if (!match)
		   {
			//return false
			return false; 
			
		   } //end if
		
		//increment currentIndexPsbleSubset
		currentIndexPsbleSubset++;
		
	   } //end while
	   
	//return true
	return true;
   }

/*
Name: runMerge
Process: merges SetType arrays brought in between a low, middle, 
         and high index segment of the array,
         must dynamically create (and release) internal array
         must use three array transfer loops
Function input/parameters: pointer to set (SetType *), 
                           low index, middle index, high index (int)                           
Function output/parameters: pointer to updated set (SetType *)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: malloc, free
*/
void runMerge( SetType *setData, int lowIndex, int middleIndex, 
               int highIndex )
   {
	//init local variables
	
	//create working index variables
	int leftSetIndex, rightSetIndex, combinedSetIndex;
	
	//find length of left subset
	   //note the +1 counts the middle index in leftLength
	   //there is no +1 for rightLength because we are excluding 
	   //middleIndex from rightLength
	int leftLength = middleIndex - lowIndex + 1;
	
	//find length of right subset
	int rightLength = highIndex - middleIndex;
	
	//allocate the space to store the leftSet and create leftSet 
	//pointer to point to it
	   //functions malloc, sizeof
	int *leftSet = (int *)malloc( leftLength * sizeof( int ) );
	
	//allocate the space to store the rightSet and create rightSet 
	//pointer to point to it
	   //functions malloc, sizeof
	int *rightSet = (int *)malloc( rightLength * sizeof( int ) );	
	
	//loop through leftSet
	for (leftSetIndex = 0; leftSetIndex < leftLength; leftSetIndex++)
	   {
		//store vals from lowIndex to middleIndex+1 in leftSet
		leftSet[ leftSetIndex ] = setData->setArray[ lowIndex + 
		leftSetIndex ];  
	   }
	   
	//loop through rightSet
	for ( rightSetIndex = 0; rightSetIndex < rightLength; rightSetIndex++ )
	   {
		//store vals from middleIndex+1 to highIndex in rightSet
		rightSet[ rightSetIndex ] = setData->setArray[ middleIndex +1+
		rightSetIndex ];
	   }
	
	//now sort the values and add them to setData.setArray
	for ( leftSetIndex = 0, rightSetIndex = 0, combinedSetIndex = lowIndex;
	      combinedSetIndex <= highIndex; 
		  combinedSetIndex++)
       {
		   
		//check if current value of left set is lesser than right set and
		//we still have leftSet Values to consider
		if ( (leftSet[ leftSetIndex ] <= rightSet[ rightSetIndex ] && 
		   (leftSetIndex < leftLength)) || 
	       ((leftSetIndex < leftLength) && (rightSetIndex >= rightLength)))
		   {
            //copy leftSet value to combined set
			setData->setArray[ combinedSetIndex ] = 
			leftSet[ leftSetIndex ];
			
			//increment leftSetIndex
			leftSetIndex++;
			
		   } // end if
		   
		//else if current val of rightSet is lesser or we run out of left
		//set values
        else
		   {
			//copy rightSet value to combined set
			setData->setArray[ combinedSetIndex ] = 
			rightSet[ rightSetIndex ];
			
			//increment rightSetIndex
			rightSetIndex++;
			
		   } //end else if
		   
	   } //end for
	   
	//free leftSet
       //function free
    free(leftSet);

    //free rightSet
       //function free
	free(rightSet);

   }

/*
Name: runMergeSort
Process: sorts Set data using merge sort algorithm,
         calls helper function with appropriate indices
Function input/parameters: pointer to set data (SetType *)
Function output/parameters: pointer to updated set data (SetType *)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: runMergeSortHelper
*/
void runMergeSort( SetType *setData )
   {
	//initialize local variables
	//initialize low indx to the lowest possible index which is 0
	int lowIndex = 0;
	
	//initialize highIndex to the highest possible index which is 
	//stored in the size variable
	int highIndex = setData->size;
	
	//begin recursive process of dividing array into sub arrays
	    //function runMergeSortHelper
	runMergeSortHelper( setData, lowIndex, highIndex);	
   }

/*
Name: runMergeSortHelper
Process: recursively breaks given set segments down 
         to smaller segments between lowIndex and highIndex (inclusive),
         then sorts data using merge sort function for segments created
Function input/parameters: pointer to setData (SetType *), 
                           low & high inclusive indices (int)
Function output/parameters: pointer to updated setData (SetType *)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: runMergeSortHelper (recursive), runMerge
*/
void runMergeSortHelper( SetType *setData, int lowIndex, int highIndex )
   {
	//initialize local variables
	int middleIndex;
	
	//check if the number of given array elements is greater than 1
	if (highIndex > lowIndex)
	   {
	    //calculate value of the midIndex using midIndex formula
	    middleIndex = (lowIndex +  highIndex - 1 ) / 2;

        //make recursive call to sort the left half of array
	       //function runMergeSortHelper
	    runMergeSortHelper(setData, lowIndex, middleIndex);

        //make recursive call to sort the right half of array	
	        //function runMergeSortHelper
	    runMergeSortHelper(setData, middleIndex + 1, highIndex);
	
		//now merge the 2 subsets into a sorted set
		   //function runMergeSort
		runMerge(setData, lowIndex, middleIndex, highIndex);
	   }
   }
	

/*
Name: runPartition
Process: partitions set data using the first value as the partition value;
         when this function is complete the partition value is
         in the correct location in the array
Function input/parameters: pointer to set data (SetType *)
Function output/parameters: pointer to updated set data (SetType *)
Function output/returned: partition value index within array
Device input/file: none
Device output/monitor: none
Dependencies: swapValues
*/
int runPartition( SetType *setData, int lowIndex, int highIndex )
   {
	//initialize local variables
	int partitionValue = setData->setArray[ lowIndex ];
	int index, swapIndex = highIndex;
	
	//loop backwards through lowIndex to highIndex of setArray 
	for (index = highIndex; index > lowIndex; index--)
	   {
		//check if current value belongs behind partition value
        if ( partitionValue <= setData->setArray[ index ])
		   {
			//swap val at index with val at swapIndex
				//function swapValues
			swapValues( &setData->setArray[ index ], 
			&setData->setArray[ swapIndex ]);
			
			//decrement swapIndex
			swapIndex--;
		   }
	   }
	   
	//swap the partition value with the value at swapIndex
	    //function swapValues
    swapValues( &setData->setArray[ swapIndex ], 
	&setData->setArray[ lowIndex ]);
	
	//return index of partition value
	return swapIndex;
   }

/*
Name: runQuickSort
Process: sorts set data using quick sort algorithm,
         calls helper with appropriate indices to implement sort
Function input/parameters: pointer to set data (SetType *)
Function output/parameters: pointer to updated set data (SetType *)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: runQuickSortHelper
*/
void runQuickSort( SetType *setData )
   {
	//initialize local variables
	//set initial high and low index vals to encompass entire array
	int lowIndex=0;
	int highIndex=setData->size;
	
	//begin recursive process
	   //function runQuickSortHelper
	runQuickSortHelper(setData, lowIndex, highIndex);
   }
      
/*
Name: runQuickSortHelper
Process: helper function run with parameters that partition arrays
         on a given (first) element of an array segment,
         then recursively sort left and right sides of given partition value
Function input/parameters: pointer to set data (SetType *) 
         low & high inclusive indices (int)
Function output/parameters: pointer to updated set data (SetType *)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: runPartition, runQuickSortHelper
*/
void runQuickSortHelper( SetType *setData, int lowIndex, int highIndex )
   {
	//initialize local vars
	int partitionIndex;

    //check if we have more than 1 value to partition
	if (highIndex > lowIndex)
       {	
	    //partition array and store position of partition val in partitionIndex
		    //function runPartition
        partitionIndex = runPartition( setData, lowIndex, highIndex );
		
	    //recursive call to sort values to the left of the partitionIndex
		    //function runQuickSortHelper
	    runQuickSortHelper(setData, lowIndex, partitionIndex - 1);
	
	    //recursive call to sort values to the right of the partitionIndex
		    //function runQuickSortHelper
	    runQuickSortHelper(setData, partitionIndex + 1, highIndex);
       }
	
   }

/*
Name: swapValues
Process: swaps data between two set data quantities (integers)
Function input/parameters: two value pointers (int *),
                           function must be called with addresses
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void swapValues( int *one, int *other )
   {
	//assign one to temp
    int temp = *one;

    //assign other to one
	*one = *other;

    //assign temp to other
	*other = temp;
   }