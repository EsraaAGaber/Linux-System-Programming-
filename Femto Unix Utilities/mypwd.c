#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
void myprint(char *buf)
{
        char buff[] = "eror";

        if (write(1, buf, strlen(buf)) == -1)
        {
                write(1, buff, 4);
        }
        write(1, "\n", 1);
}
int main()
{
        // ssize_t write(int fd, const void buf[.count], size_t count);
        // char *getcwd(char buf[.size], size_t size);
        char *buf, *buff;
        buff = getcwd(buf, 100);
        if (buff == NULL)
        {
                myprint("bad pwd!!");
        }
        else
        {
                myprint(buf);
        }
}
