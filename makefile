CC = gcc
CFLAGS = -lcurl

downloadDF: latestdf.c
	$(CC) -o downloadDF latestdf.c $(CFLAGS)


