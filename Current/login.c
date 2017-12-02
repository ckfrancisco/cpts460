/****************** Algorithm of login *******************/
// login.c : Upon entry, argv[0]=login, argv[1]=/dev/5X #include "ucode.c"

#include "ucode.c"

int tokenize(int fd, char *buf, char token, int position)
{
    int nbytes = 0;

    while(read(fd, buf, 1) > 0)
    {
        nbytes++;
        if(*buf == token)
            break;
    }

    lseek(fd, position, 0);

    read(fd, buf, nbytes);
    buf[nbytes] = 0;

    return nbytes;
}

int myatoi(char *buf)
{
    int result = 0;

    while(*buf)
    {
        result += (*buf - '0');

        if(*(buf++))
            result *= 10;
    }
}

int mystrcmp(char *s1, char *s2)
{
    while(*(s1++) == *(s2++) && *s1 && *s2);

    if(!(*s1 && *s2))
        return 1;
    return 0;
}

main(int argc, char *argv[])
{
    int in, out, err, passwd;
    char name[128], password[128];

    int line, position;
    char buf1[256], buf2[256];
    int uid, gid;

    int count = 0;
    int nbytes = 0;
    
    close(0); close(1); close(2);
    in  = open(argv[1], O_RDONLY); 
    out = open(argv[1], O_WRONLY);
    err = open(argv[1], O_WRONLY);

    fixtty(argv[1]);                    // set tty name string in PROC.tty

    passwd = open("/etc/passwd", O_RDONLY);  // open /etc/passwd file for READ;

    while(1){
        printf("login:");
        gets(name);
        printf("password:");
        gets(password);

        line = position = 0;

        while(tokenize(passwd, buf1, '\r', line))
        {
            printf("COUNT=%d NBYTES=%d STRING=%s\n\r", count, nbytes, buf1);
            line += tokenize(passwd, buf1, '\n', line);
            line += tokenize(passwd, buf1, '\n', line);
            printf("COUNT=%d NBYTES=%d STRING=%s\n\r", count++, nbytes, buf1);
        }

        close(in); close(out); close(err); close(passwd);
        printf("login failed, try again\n");
    }
}