
OBJ_SERVER = dhtserver.o map.o
OBJ_CLIENT = client.o map.o

TARGET_SERVER = dhtserver
TARGET_CLIENT = client 

CC = gcc

${TARGET_CLIENT}:${OBJ_CLIENT} ${TARGET_SERVER}
	$(CC) $(OBJ_CLIENT) -o $@ -Wall -lpthread

${TARGET_SERVER}:${OBJ_SERVER}
	$(CC) $(OBJ_SERVER) -o $@ -Wall

dhtserver.o:dhtserver.c
	${CC} -c dhtserver.c -Wall

client.o:client.c
	${CC} -c client.c -Wall

map.o:map.c
	${CC} -c map.c -Wall

.PHONY:clean
clean:
	rm *.o -rf
	rm ${TARGET_SERVER} ${TARGET_CLIENT} -rf