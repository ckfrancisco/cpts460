#include "ucode.c"

int console;

// P1's code
int parent()
{
    int pid, status;

    while(1){
        printf("INIT : wait for ZOMBIE child\n\r");
        pid = wait(&status);

        if (pid==console){
            // if console login process died
            printf("INIT: forks a new console login\n\r");
            console = fork(); // fork another one

            if (console)
                continue;
            else
                exec("login /dev/tty0"); // new console login process
            }

        printf("INIT: I just buried an orphan child proc %d\n\r", pid);
    }
}

main()
{
    int in, out;
    // STAT buf;

    // file descriptors for terminal I/O
    in = open("/dev/tty0", O_RDONLY); // file descriptor 0
    out = open("/dev/tty0", O_WRONLY); // for display to console

    // fstat(in, &buf);
    // printf("    IN DEV=%d INO=%d\n\r", buf.st_dev, buf.st_ino);
    // fstat(out, &buf);
    // printf("    IN DEV=%d INO=%d\n\r", buf.st_dev, buf.st_ino);
    
    printf("INIT: fork a login proc on console\n\r");
    console = fork();
    
    if (console) // parent
        parent();
    else // child: exec to login on tty0
        exec("login /dev/tty0");
}