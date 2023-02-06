Program author: Jason Huynh

Purpose: Create a program that creates and manipulates a linked list with each node being a patient in a hospital with differnt kinds of data

Source files:  emergencyRoomMain.c linked_list_hospital.c linked_list_hospital.h patient.c patient.h

exact compilation command: "gcc emergencyRoomMain.c linked_list_hospital.c patient.c"

Launching and operation instructions:
1. To launch the program, compile the files then type "./a.out" 
2. When you first launch the program, it will display all of the data


Software organization: For this software, there are 6 files emergencyRoomMain.c, linked_list_hospital.c, linked_list_hospital.h, patient.c, patient.h, Makefile

The emergencyRoomMain.c file contains the main method and a function to delete a node.

The linked_list_hospital.c file contains functions related to inserting, deleteing, counting, searching, and retrieveing the linked list

The patient.c file contains functions related to printing, comparing and finding patients.

The linked_list_hospital.h file contains function prototypes for the linked_list_hospital.c file and the definiton of struct for nodes.

The patient.h file contains the definitions of 1 structure, the patient information.

The Makefile file contains the commands to compile and run the rest of the files.



Issues/Limitations: None



Revision:
a. 19/11/2021, Jason Huynh - edit/revision
