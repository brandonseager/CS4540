#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int global; /* In BSS segement, will automatically be assigned '0'*/

int main()
{
    pid_t child_pid;
    int status;
    int local = 0;
    int result = 0;
    /* now create new process */
    child_pid = fork();

    if (child_pid >= 0) /* fork succeeded */
    {
        if (child_pid == 0) /* fork() returns 0 for the child process */
        {
            printf("child process!\n");

            // Increment the local and global variables
            local++;
            global=5;

            printf("child PID =  %d, parent pid = %d\n", getpid(), getppid());
            printf("\n child's local = %d, child's global = %d\n",local,global);

            char *cmd[] = {"ls",(char*)0};
            result = execv("/bin",cmd); // call whoami command
	    printf("call result is %d\n", result);
	    exit(0);
         }
         else /* parent process */
         {
             printf("parent process!\n");
             printf("parent PID =  %d, child pid = %d\n", getpid(), child_pid);
             wait(&status); /* wait for child to exit, and store child's exit status */
             printf("Child exit code: %d\n", WEXITSTATUS(status));

             //The change in local and global variable in child process should not reflect here in parent process.
             printf("\n Parent'z local = %d, parent's  global = %d\n",local,global);

             printf("Parent says bye!\n");
             exit(0);  /* parent exits */
         }
    }
    else /* failure */
    {
        perror("fork");
        exit(0);
    }
}
