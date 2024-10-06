##	Michael Cervantes
##	3/11/2023
##	Lab 6 - Producer Consumer Problems 
## 	Description - Signaling from one Task to Another
##	

CC = g++

CFLAGS = -D DEBUG

all : threadSync ProducerConsumer

threadSync : threadSync.c
	gcc $(CFLAGS) -pthread -o threadSync threadSync.c
	
ProducerConsumer : ProducerConsumer.c
	gcc $(CFLAGS) -pthread -o ProducerConsumer ProducerConsumer.c

clean : 
	rm -f threadSync ProducerConsumer
