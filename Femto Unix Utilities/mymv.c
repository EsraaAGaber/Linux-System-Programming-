#include <stdio.h>

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
        myprint("Error: please provide 2 arguments for mv only");
        return 0;
    }
    // int rename(const char *oldpath, const char *newpath);
    if (rename(argv[1], argv[2]) == -1)
    {
        myprint("Error while moving\n");
    }
    else
    {
        myprint("process is done\n");
    }

    return 0;
}
