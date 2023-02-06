all: main

main: emergencyRoomMain.o linked_list_hospital.o patient.o
	gcc -o main emergencyRoomMain.o linked_list_hospital.o patient.o

main.o: emergencyRoomMain.c linked_list_hospital.h patient.h
	gcc -c emergencyRoomMain.c

person.o: linked_list_hospital.h linked_list_hospital.c patient.h
	gcc -c linked_list_hospital.c

mystat.o: patient.c patient.h
	gcc -c patient.c

run: all
	./main

clean:
	rm -f main *.o
