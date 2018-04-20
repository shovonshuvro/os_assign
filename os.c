
#include <stdio.h>
#define MAX_QUEUE_SIZE 100
typedef struct Processes {
int g_no;
int h_time;
int u_time;
} 
Process;
Process * queue[MAX_QUEUE_SIZE];
int front = 0, rear = -1, processed = 0, v_time = 0, tq = 6;
int last_front = 0, last_rear = -1;
void swap(Process * a, Process * b) {
Process temp = * a;
* a = * b;
* b = temp;
}
void sort(Process p[], int n) {
int i, j;
short swapped;	
for (i = 0; i < n; ++i) {
swapped = 0;		
for (j = 0; j < n-i-1; ++j)
{
if (g[j].h_time > g[j+1].h_time)
{
swap(&g[j], &g[j+1]);
swapped = 1;
}
}		
if (swapped == 0)
break;
}
}
void enqueue(Process g[], int n) {
int i, j, can_insert;
for (i = 0; i < n; ++i)
{
can_insert = 1;		
if (g[i].h_time <= v_time && g[i].u_time > 0)
{
if (front == 0) {
queue[++rear] = &g[i];
}
else
{
for (j = last_front; j <= last_rear; ++j) {
if (queue[j]->g_no == g[i].g_no)
can_insert = 0;
}
if (can_insert == 1)
queue[++rear] = &g[i];
}
}
}
for (i = last_front; i <= last_rear; ++i)
{
if (queue[i]->u_time > 0)
queue[++rear] = queue[i];
}
}


void execute() {
int i;	
if (front-1 == rear) {
printf("CPU idle for 1 second.\n");
v_time += 1;
}
else {
last_front = front;
last_rear = rear;
		
for (i = front; i <= rear; ++i, ++front)
{
if (queue[i]->u_time > tq)
{
queue[i]->u_time -= tq;
v_time += tq;
printf("Process number %d excuted till %d seconds.\n", queue[i]->g_no, curr_time);
}
else if (queue[i]->u_time > 0)
{
v_time += queue[i]->u_time;
queue[i]->u_time = 0;
printf("Process number %d excuted till %d seconds.\n", queue[i]->g_no, curr_time);
				
++processed;
}
}
}
}


int main() {
int n, i;
short err_flag = 0;
	
do {
if (err_flag == 1)
fprintf(stderr, "\nNumber of processes should be greater than 1.\n");

printf("Enter the number of processes: ");
scanf("%d", &n);
		
err_flag = 1;
} while (n < 1);
err_flag = 0;
	
Process g[n];
	
for (i = 0; i < n; ++i) {
printf("\n");
printf("Enter arrival time of process %d: ", i+1);
scanf("%d", &g[i].h_time);
		
printf("Enter burst time of process %d: ", i+1);
scanf("%d", &g[i].u_time);
		
g[i].g_no = i+1;
}
	
sort(&g[0], n); 
	
while (1) {
enqueue(g, n);
		
printf("\nIn queue: ");
for (i = 0; i <= rear; ++i) {
printf("%d ", queue[i]->g_no);
}
printf("\nFront = %d, Rear = %d.\n\n", front, rear);
		
execute();
if (processed == n)
break;
}
	
return 0;
}

