//comments:
//NAME: Danfeng Wang, SECTION 2.
//DATE: 2016-03-07
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <time.h>

void action(){}
void child(char*);
int main(int argc, char *argv[])
{
	pid_t pid1, pid2,pid3;
	int win;
	FILE *fp;
	char winner[10];
	int score;

	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);

	printf("This is a 3-players game with a referee.Please input your winning total>>");
	scanf("%d", &win);

	if((pid1=fork()) == 0) child("TOTO");
	if((pid2=fork()) == 0) child("TITI");
	if((pid3=fork()) == 0) child("TWTW");
	sleep(1);
	signal(SIGUSR1,action);
	while(1)
	{   
			printf("\nReferee: TOTO plays\n");
			kill(pid1, SIGUSR1);

			pause();
			fp= fopen("1.txt","r");
		    if(fp== NULL)
		    {
		    	printf("ERROR:  referee opens file failed.\n");
		    	exit(1);
		    }
		    fscanf(fp,"%s %d",winner,&score);
		    if(score>=win)
		    {
				printf("\nReferee: game over %s won with the socre %d\n", winner,score);
				kill(0,SIGTERM);
				fclose(fp);
			}
			fclose(fp);
			printf("\nReferee: TITI plays\n");
			kill(pid2,SIGUSR1);

			pause();
			fp= fopen("1.txt","r");
		    if(fp== NULL)
		    {
		    	printf("ERROR:  referee opens file failed.\n");
		    	exit(1);
		    }
		    fscanf(fp,"%s %d",winner,&score);
		    if(score>=win)
		    {
				printf("\nReferee: game over %s won with the socre %d\n", winner,score);
				kill(0,SIGTERM);
				fclose(fp);
			}
			fclose(fp);
			printf("\nReferee: TWTW plays\n");
			kill(pid3,SIGUSR1);
			
			pause();
			fp= fopen("1.txt","r");
		    if(fp== NULL)
		    {
		    	printf("ERROR:  referee opens file failed.\n");
		    	exit(1);
		    }
		    fscanf(fp,"%s %d",winner,&score);
		    if(score>=win)
		    {
				printf("\nReferee: game over %s won with the socre %d\n", winner,score);
				kill(0,SIGTERM);
				fclose(fp);
			}
			fclose(fp);
	}
}

void child(char *s)
{
	int points=0,dice;
	long int ss=0;
	FILE *fd;
	while(1)
	{
		signal(SIGUSR1,action);
		pause();
		fd= fopen("1.txt","w+");
		if(fd== NULL)
		{
		    printf("ERROR: open file failed.\n");
		    exit(1);
		}
		//printf("%s: playing my dice\n", s);
		dice=(int) time(&ss)%30 + 1;
		//printf("%s: got %d points\n", s,dice);
		points+=dice;
		fprintf(fd,"%s %d",s,points);
		rewind(fd);
		fclose(fd);
		sleep(3);
		kill(getppid(),SIGUSR1);
	}
}

