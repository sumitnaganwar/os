#server
//Server.c
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);

    char str1[80];

    while (1) {
        int fd = open(myfifo, O_RDONLY);
        read(fd, str1, sizeof(str1));
        printf("User1: %s\n", str1);
        close(fd);
    }

    return 0;
}



//client.c
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *myfifo = "/tmp/myfifo";

    char str2[80];

    while (1) {
        int fd = open(myfifo, O_WRONLY);
        fgets(str2, sizeof(str2), stdin);
        write(fd, str2, strlen(str2) + 1);
        close(fd);
    }

    return 0;
}


















//output of server
tudent@student:~/Documents$ gcc server.c -o server
student@student:~/Documents$ ./server
User1: HELLO I AM YASH

//output of client
student@student:~/Documents$ gcc client.c -o client
student@student:~/Documents$ ./client
HELLO I AM YASH





/*
1. Named Pipe (FIFO) Creation
A named pipe is a special type of file used for IPC, allowing communication between two processes.
The server and client use a FIFO located at /tmp/myfifo to exchange data.
mkfifo(myfifo, 0666); creates the named pipe with read and write permissions (0666) if it doesn’t already exist.
2. Server Program (server.c)
The server reads data from the FIFO and displays it.

const char *myfifo = "/tmp/myfifo"; defines the FIFO path.
mkfifo(myfifo, 0666); creates the named pipe, if it’s not already there.
Infinite loop (while (1)): The server continuously reads data from the FIFO.
int fd = open(myfifo, O_RDONLY);: Opens the FIFO in read-only mode.
read(fd, str1, sizeof(str1));: Reads the string data from the FIFO into str1.
printf("User1: %s\n", str1);: Prints the received message to the console.
close(fd);: Closes the file descriptor after reading.
3. Client Program (client.c)
The client writes data to the FIFO.

Similar to the server, myfifo is defined with the path to the named pipe.
The client also has an infinite loop (while (1)) where it:
fgets(str2, sizeof(str2), stdin);: Reads a line from the standard input (keyboard) into str2.
int fd = open(myfifo, O_WRONLY);: Opens the FIFO in write-only mode.
write(fd, str2, strlen(str2) + 1);: Writes the data in str2 to the FIFO, including the null-terminator (strlen(str2) + 1).
close(fd);: Closes the file descriptor after writing.
*/