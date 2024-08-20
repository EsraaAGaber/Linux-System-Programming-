#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

void myprint(char *buf)
{
    char buff[] = "eror";

    if (write(1, buf, strlen(buf)) == -1)
    {
        write(1, buff, 4);
    }
    write(1, "\n", 1);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        myprint("Error: please provide 2 arguments for cp only");
        return 0;
    }

    int newfd = open(argv[1], O_RDONLY);
    if (newfd == -1)
    {
        myprint("Error: can't open source file");
        return 0;
    }

    int tofd = open(argv[2], O_WRONLY | O_CREAT, 0666);
    if (tofd == -1)
    {
        myprint("Error: can't open target file");
        close(newfd);
        return 0;
    }

    char buf[100];
    while (1)
    {
        int sz = read(newfd, buf, sizeof(buf));
        if (sz == 0)
        {
            myprint("Process is done!");
            break;
        }
        else if (sz == -1)
        {
            myprint("Error while reading");
            break;
        }
        if (write(tofd, buf, sz) == -1)
        {
            myprint("Error while writing");
            break;
        }
    }

    if (close(newfd) == -1)
    {
        myprint("Error while closing source file");
    }
    if (close(tofd) == -1)
    {
        myprint("Error while closing target file");
    }

    return 0;
}
