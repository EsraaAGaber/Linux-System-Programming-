#include <unistd.h>
#include <string.h>
// ssize_t write(int fd, const void buf[.count], size_t count)
int main(int argc, char *argv[])
{
	char buff[] = "eror";
	for (int i = 1; i < argc; i++)
	{
		if (write(1, argv[i], strlen(argv[i])) == -1)
		{
			write(1, buff, 5);
		}
		write(1, " ", 1);
	}
	write(1, "\n", 1);
}
