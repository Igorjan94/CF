#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int n, m, i, j, *frst_matrix, *scnd_matrix, *answ_matrix;

void read_matrix()
{

        printf("\nready to read\n\n");
            printf("enter size of matrix\n");
                scanf("%d%d", &n, &m);

                    if(n < 1 || m < 1)
                            {
                                        printf("program close.\n");
                                                exit(0);
                                                    }

                        frst_matrix = malloc((n * m) * sizeof(int));
                            scnd_matrix = (int *)malloc((n * m) * sizeof(int));

                                printf("enter first matrix:\n");
                                    for (i = 0; i < n; i++)
                                                for (j = 0; j < m; j++)
                                                            {
                                                                            printf("enter %d %d element: ", i + 1, j + 1);
                                                                                        scanf("%d", &frst_matrix[i * n + j]);
                                                                                                }
                                        printf("first matrix complite\n");

                                            printf("\nenter second matrix:\n");
                                                for (i = 0; i < n; i++)
                                                            for (j = 0; j < m; j++)
                                                                        {
                                                                                        printf("enter %d %d element: ", i + 1, j + 1);
                                                                                                    scanf("%d", &scnd_matrix[i * n + j]);
                                                                                                            }

                                                    printf("read complite\n");

                                                        int shmid;
                                                            char pathname[] = "main.c";
                                                                key_t key;

                                                                    key = ftok(pathname, 0);
                                                                        if ((shmid = shmget(key,(3*n*m+2)*sizeof(int),0666|IPC_CREAT|IPC_EXCL)) < 0)
                                                                                {
                                                                                            shmid = shmget(key, (3*n*m+2)*sizeof(int), 0);
                                                                                                }
                                                                            answ_matrix = (int*)shmat(shmid, NULL, 0);
}

void sum_matrix()
{
        printf("\nstarted sum...\n");

            for (i = 0; i < n; i++)
                        for (j = 0; j < m; j++)
                                        answ_matrix[i * n + j] = frst_matrix[i * n + j] + scnd_matrix[i * n + j];

                free(frst_matrix);
                    free(scnd_matrix);

                        printf("sum complite\n");
}

void write_matrix()
{
        printf("\nstarted write...\n");
            for (i = 0; i < n; i++)
                    {
                                for (j = 0; j < m; j++)
                                                printf("%d ", answ_matrix[i * n + j]);
                                        printf("\n");
                                            }

                free(answ_matrix);
                    printf("write success\n");
}

int main()
{
        printf("program start\n");

            while(1)
                    {

                                read_matrix();

                                        pid_t process;
                                                process = fork();
                                                        if (process ==0)
                                                                    {
                                                                                    sum_matrix();
                                                                                                return 0;
                                                                                                        }
                                                                waitpid(process, NULL, 0);

                                                                        process = fork();
                                                                                if (process ==0)
                                                                                            {
                                                                                                            write_matrix();
                                                                                                                        return 0;
                                                                                                                                }
                                                                                        waitpid(process, NULL, 0);

                                                                                            }

                return 0;
}
