#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	STOP = 0,
	RUNNING,
	PAUSE,
	MAX_STATE,
}CD_STATE;

typedef enum
{
	PRESS_RUNNING = 0,
	PRESS_STOP,
	PRESS_PAUSE,
	MAS_EVENT,
}CD_EVENT;

typedef struct CD_STATE_MACHINE
{
	int state;
	int event;
	void (*func)(unsigned char *);
}STATE_MACHINE;

//定义状态机当前状态
int current_state = STOP;

void change_to_run(unsigned char * user_data)
{
	current_state = RUNNING;
	printf("CD is running\n");
}

void change_to_stop(unsigned char * user_data)
{
	current_state = STOP;
	printf("CD is stop\n");
}

void change_to_pause(unsigned char * user_data)
{
	current_state = PAUSE;
	printf("CD is pause\n");
}

//结构体数组，存储
STATE_MACHINE state_machine[] = {
	{RUNNING, PRESS_RUNNING, NULL},
	{RUNNING, PRESS_PAUSE, change_to_pause},
	{RUNNING, PRESS_STOP, change_to_stop},
	{PAUSE, PRESS_RUNNING, change_to_run},
	{PAUSE, PRESS_PAUSE, NULL},
	{PAUSE, PRESS_STOP, change_to_stop},
	{STOP, PRESS_RUNNING, change_to_run},
	{STOP, PRESS_PAUSE, change_to_pause},
	{STOP, PRESS_STOP, NULL},
	{-1, -1, NULL},
};

void handle_event(int current_state, int event)
{
	int i =0;

	for(i = 0; state_machine[i].state != -1; i++)
	{
		if(state_machine[i].state == current_state && state_machine[i].event == event)
		{
			if(state_machine[i].func != NULL)
			{
				state_machine[i].func(NULL);
			}
			else
			{
				printf("state not change\n");
			}
			break;
		}
	}

}

int main(void)
{
	int event;

	while(1)
	{
		printf("please input event:0(run),1(stop),2(pause)\n");
		scanf("%d", &event);

		handle_event(current_state, event);	
	}

	return 0;
}