#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

char **spilt(char *sentence, int *wordCount)
{
    char **words = NULL;
    char *word = strtok(sentence, " ");

    int count = 0;

    while (word != NULL)
    {
        words = realloc(words, sizeof(char *) * (count + 1));
        words[count] = malloc(strlen(word) + 1);
        strcpy(words[count], word);
        count++;
        word = strtok(NULL, " ");
    }

    *wordCount = count;
    return words;
}
char IS_VAR(char *sentence)
{
    char f = 0;
    for (int i = 0; i < strlen(sentence); i++)
    {

        if (sentence[i] == '=')
            f++;
    }
    if (f == 1)
        return 1;
    return 0;
}
typedef struct shell_variables
{
    char name[20];
    char value[20];
} shell_var_t;
shell_var_t env_var[100];
int count_env = 0;

int main(int argc, char *argv[])
{
    shell_var_t local_var[100];
    int count_local = 0;

    while (1)
    {
        char buf[100];
        printf("3ayza ahhh?? >>");
        fgets(buf, 100, stdin);
        int sz = strlen(buf);
        if (sz <= 1)
            continue;
        buf[sz - 1] = '\0';

        int num_argv = 0;
        char **new_argv = spilt(buf, &num_argv);

        char VAR = IS_VAR(buf);

        if (VAR)
        {
            //  char *word = strtok(sentence, " ");
            char *word;
            word = strtok(buf, "=");
            strcpy(local_var[count_local].name, word);
            word = strtok(NULL, "=");
            strcpy(local_var[count_local].value, word);

            count_local++;
        }
        else if (strcmp(new_argv[0], "exit") == 0)
        {
            break;
        }
        else if (strcmp(new_argv[0], "export") == 0)
        {
            if (num_argv != 2)
            {
                printf("eror 2 export require 1 arg. \n");
            }
            else
                for (int i = 0; i < count_local; i++)
                {

                    if (strcmp(local_var[i].name, new_argv[1]) == 0)
                    {
                        strcpy(env_var[count_env].name, local_var[i].name);
                        strcpy(env_var[count_env].value, local_var[i].value);
                        count_env++;
                        break;
                    }
                }
        }
        else if (strcmp(new_argv[0], "set") == 0)
        {
            for (int i = 0; i < count_env; i++)
            {
                printf("env value [%d]: %s = %s\n", i + 1, env_var[i].name, env_var[i].value);
            }
        }
        else
        {
            int new_pid = fork();

            if (new_pid > 0)
            {
                // perant
                int stat;
                wait(&stat);
            }
            else if (new_pid == 0)
            {
                // child
                execvp(new_argv[0], new_argv);
                printf("child is fail\n");
                return -1;
            }
            else
            {
                printf("fork is faild\n");
            }
        }
    }
    return 0;
}
