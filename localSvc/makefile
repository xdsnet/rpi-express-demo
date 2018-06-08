all : rootServer userClient userClientR
rootServer: server.c
	gcc -Wall -o bin/rootServer server.c -lwiringPi

userClient: client.c
	gcc -Wall -o bin/userClient client.c

userClientR: clientR.c
	gcc -Wall -o bin/userClientR clientR.c
