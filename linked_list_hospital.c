
/*
File name is linked_list_hospital.c
 Purpose: file contains functions for manipulating singly linked list




 

 */

/******************************************************************/
// INCLUDE

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linked_list_hospital.h"
#include "patient.h"


/************************************************************************/
// Define



/************************************************************************/

/*
Purpose: insert a new node into the list as the first element
input
patient - the patient record

input/output
head - head of linked list

return
A pointer to the node that was allocated.

NULL - if the operation was not successful

*/

ListNode *insertToList(ListNode **head, PatientInfo *patient){
	//create a pointer to a new node
	ListNode *current = NULL;

	//allocate memory for new node
	current = (ListNode *)malloc(sizeof(ListNode));

	//check if sucessful allocation
	if(current == NULL) {
		return NULL;
	}

	//copy over data
	current->patient = *patient;

	//attatch list to new node
	current->next = *head;

	//set the head of list to new node
	*head = current;

	//return pointer to new node
	return current;
}


/************************************************************************/
/*
Purpose: insert a new node into the list after the given node

Input
input
patient - the patient record


return
A pointer to the node that was allocated.

NULL - if the operation was not successful

*/

ListNode *insertAfter(ListNode *node, PatientInfo *patient){
	//create a pointer to a new node
	ListNode *current = NULL;

	//allocate memory for new node
	current = (ListNode *)malloc(sizeof(ListNode));

	//check if allocated properly
	if(current == NULL) {
		return NULL;
	}

	//copy data over
	current->patient = *patient;

	//attatch list to new node
	current->next = node->next;

	//attatch previous node to new node
	node->next = current;

	//return pointer to newly made node
	return current;
}




/************************************************************************/
/*
Purpose: search for the first patient with the matching priority
Input
head - the head of the list
priority - first priority of the patient

output
patient - the patient record

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


ListNode * searchFirstPatientByPriority(ListNode *head, unsigned char priority, PatientInfo *patient){
	//create a pointer to a node and set pointer to begining of list
	ListNode *current = NULL;
	current = head;

	//cycle through list
	while(current != NULL){
		//if patients priority matches, copy out record and return node
		if(current->patient.priorityLevel == priority){
			//printPatient(&current->patient);
			*patient = current->patient;
			return current;
		}
		//increment the node
		current = current->next;
	}
	//if reach here, search failed = return null
	return NULL;
}

/************************************************************************/
/*
Purpose: search for the first patient with the matching criteria.  The criteria is determined
by the comparison function
Input
head - the head of the list
findPatient -  a function pointer that returns a 0 if the patient's record matches that criteria

output
patient - the patient record

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


ListNode * searchNextPatient(ListNode *head, int (*findPatient)(PatientInfo *), PatientInfo *patient)
{
	//create a pointer to a node and set pointer to begining of list
	ListNode *current = NULL;
	current = head;

	//cycle through list
	while(current != NULL){
		//use function to find patients, if found, copy record and return node
		if(findPatient(&current->patient) == 0){
			*patient = current->patient;
			return current;
		}
		//increment node
		current = current->next;
	}

	//if made it this far, search failed = return NULL
	return NULL;

}

/***************************************************************/

/*
Purpose: delete the first node from the list
Input
head - the head of the list

output
head - the head of the list
patient - the patient record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/


int deleteFromList(ListNode **head, PatientInfo *patient){
	//create a pointer to a node and set pointer to begining of list
	ListNode *current = NULL;
	current = *head;

	//check if list is empty and return 1 if so
	if(current == NULL){
		return 1;
	}

	//copy over patient data
	*patient = current->patient;
	//set the new head
	*head = current->next;

	//free the node
	free(current);
	//set to null in case of failure
	current = NULL;

	//since sucess, return 0
	return 0;
}


/***************************************************************/

/*
Purpose: Retrieve the first node that matches the priority.  When found the node is deleted and the patient
information is provided.

Input
head - the head of the list

output
head - the head of the list
patient - the patient record


return

0 if node was deleted
1 if node was not found or list is empty

*/


int retrieveNextPatientByPriority(ListNode **head, unsigned char priority, PatientInfo *patient){

    //create a pointer to the node then set to node that matches
    ListNode *current = NULL;
	current = searchFirstPatientByPriority(*head, priority, patient);

	//if node not found return 1
	if(current == NULL){
		return 1;
	}
	//print out the matched patient's data
	*patient = current->patient;

	//delete the node
	deleteNode(head, current);

	//since sucess, return 0
	return 0;
}

/***************************************************************/

/*
Purpose: Retrieve the patient with the highest criteria to be treated.  The maximum criteria is determined by
a comparePatients function.  Once the patient is found it is deleted from the list and its information is
returned.

Input
head - the head of the list
comparePatients - this function takes two paitent records and compares them.
				It returns, -1, 0 or 1 if p1 < p2, p1 == p2, or p1 > p2, respectively.

output
head - the head of the list
patient - the patient record


return
0 if  patient was found and the node was deleted
1 if no paitent was found or the list is empty


Algorithm:
The function first finds the patient with the hights criteria by comparing all the patients records and
finding the first patient with the maximum criteria to be treated.  It then deletes the patient and returns
its information.
*/


int retrieveNextPatientByCriteria(ListNode **head, int (*comparePatients)(PatientInfo *p1, PatientInfo *p2, int currentTime), int currentTime, PatientInfo *patient){
	//create a pointer to a node and set pointer to begining of list
	ListNode *current = NULL;
	current = *head;

    //create a pointer for the highest priority node
	ListNode *highest = NULL;

	// check if list is empty
	if(*head == NULL){
		return 1;
	}

	//cycle through list
	while(current->next != NULL){
		//if next patient priority is greater than current set next node to highest
		if(comparePatients(&current->patient, &current->next->patient, currentTime) == -1){
			highest = current->next;
		//if current patient priority is greater than next, set current node to highest
		}else if(comparePatients(&current->patient, &current->next->patient, currentTime) == 1){
			highest = current;
		}
		//increment node
		current = current->next;
	}

	//after found highest, send out data
	*patient = highest->patient;

	//delete the highest node
	deleteNode(head, highest);

	//return 0 since sucess
	return 0;

}



/************************************************************************/
/*
Purpose: deletes all nodes from the list
input/output
head - the head of the list


*/


void deleteList(ListNode **head){
	//create a pointer to a node and set pointer to begining of list
	ListNode *current = NULL;
	current = *head;

	//cycle through list
	while(current != NULL){
		//delete first node then increment node
		deleteFromList(head, &current->patient);
		current = current->next;
	}

}



/************************************************************************/
/*
Purpose: prints all the records in the list

input
head - the head of the list
myPrint - a function pointer for print the patient information.
*/


void printList(ListNode *head, void (*myPrint)(PatientInfo *patient)){
	//create a pointer to a node and set pointer to begining of list
	ListNode *current = NULL;
	current = head;

	//cycle through list
	while(current != NULL){
		//use the printPatient function and print current node patient data
		myPrint(&current->patient);
		//increment node
		current = current->next;
	}

}


/************************************************************************/
/*
Purpose: counts the number of patients that are waiting to be treted
input
head - the head of the list

return
the number of registered patients

*/


int numPatientsInEmergency(ListNode *head){
	//create a pointer to a node and set pointer to begining of list
	ListNode *current = NULL;
	current = head;

	//create a counter to keep track of number of nodes
	int counter = 0;

	//cycle through list
	while(current != NULL){
		//each time there is a node, increment counter and node
		counter ++;
		current = current->next;
	}
	return counter;



}

/************************************************************************/
/*
Purpose: counts the number of patients with a matching priority
input
head - the head of the list


return
the number of patients with a matching priority


*/


int countPatients(ListNode *head, unsigned char priority){
	//create a pointer to a node and set pointer to begining of list
	ListNode *current = NULL;
	current = head;

	//create a counter to keep track of number of nodes
	int counter = 0;

	//cycle through list
	while(current != NULL){
		//each time priority matches for a node, increment counter and node
		if(current->patient.priorityLevel == priority){
			counter++;
		}
		current = current->next;
	}
	return counter;
}
/********************************************************************/
/*
purpose: delete a node in the list
input
head - the head of the list
key - a pointer to a node that is to be deleted

return
0 - returns 0 if the deletion was sucessful
1 - return 1 if the deletion was not sucessful
*/

int deleteNode(ListNode **head, ListNode *key){
	//create a pointer to a node and set pointer to begining of list
	ListNode *current = NULL;
	current = *head;

	//cycle through the list
	while(current != NULL){
		//if the next node is to be deleted, set current next to deleted node's next
		if(current->next == key){
			current->next = key->next;

			//set next to null incase then free the node
			key->next = NULL;
			free(key);
			return 0;
		}
		//increment node
		current = current->next;
	}
	//if failed to delete, return 1
	return 1;
}


/************************************************************************/
/*

Purpose: store all the patients records in the file by printing out the information i.e., in ASCII readable format.


input
filename - the name of the file to be used for storing the data
head - the head of the  list

Algorithm:
use the '$' character as a delimeter between the fields
For example:
Miya                 $Bronson                 $ 9700    $ 20  $ 2 $ Broken Bone
*/

// Backup Functions
int createAsciiBackup(char *fileName, ListNode *head)

{
	// add code

	// open the file

	// store each patient records in the file

	// close the file

    return(0);
}

/************************************************************************/
/*

Purpose: store all the patients records in the file in their binary format.


input
filename - the name of the file to be used for storing the data
head - the head of the  list



*/

int createBinaryBackup(char *fileName, ListNode *head)
{
	// add code

	// open the file

	// store each patient records in the file

	// close the file

    return(0);
}

////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// BONUS SECTION



/************************************************************************/
/*

Purpose: removes all Patients with priority less than or equal to the given priority
(remove all patients with priorityLevel <= priority).


input
head - the head of the  list

Ouput
head - the head of the list where all patients with priorityLevel < priority are removed

*/

int releasePatients(ListNode **head, unsigned char priority)

/* code */
{
	// add code

	// remove all patients that head is pointing to and meet the criteria


	// remove all other patients that meet the crieria
	return(0);

}

/************************************************************************/
/*
Purpose: prints all the patients' records in the list in reverse order using recursion

input
head - the head of the list
*/


void printListReverse(ListNode *head, void (*myPrint)(PatientInfo *patient))
{
	// add code



}





/*****************************************************************************/

/************************************************************************/
/*
Purpose: Reverse the list such that the last node in the list becomes the first node and the first node in the list becomes the last node.

Restrictions:
1.	This operation must be achieved using recursive calls
2.	No memory is to be allocated or released at any time during the execution of the function



input
head - the head of the list


Returns:
the head of the new list
*/

ListNode *reverse(ListNode *head)


{

	/* Add code */


}
