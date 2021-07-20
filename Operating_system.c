#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Process{
    char P[10];
    float AT, BT;
    float RT, WT, TT;
    float Start, Finish;
    float Remain;
};
typedef struct Process Process;

void cpy(Process* a, Process* b){
    strcpy(a->P, b->P);
    a->AT = b->AT;
    a->BT = b->BT;
    a->RT = b->RT;
    a->WT = b->WT;
    a->Start = b->Start;
    a->Finish = b->Finish;
    a->Remain = b->Remain;
}
void Swap(Process* a, Process* b){
    Process temp;
    cpy(&temp, a);
    cpy(a, b);
    cpy(b, &temp);
}
void Sort(Process* P, int n){
    for( int i = 1; i < n; i++){
        int j = 1;
        while (j > 0){
            if(P[j].AT < P[j - 1].AT){
                Swap(&P[j - 1], &P[j]);
                j--;
            }
            else
                break;
        }
    }
}
int argMin(Process* P, bool *Queue, int n){
    int k = 0;
    while(!Queue[k])
        ++k;
    for (int i = k + 1; i < n; i++)
        if(Queue[i] && (P[i].Remain < P[k].Remain))
            k = i;
    return k;
}
float Min(float a, int b){
    return (a < b) ? a : b;
}
void SJF(Process* list, int n){
    float time = 0;
    int i, k;
    int iter = 0, count = 0, q = 0;
    bool* Queue = (bool*)malloc(n * sizeof(bool));
    for (i = 0; i < n; i++)
        Queue[i] = false;
    
    while(count < n){
        if(q == 0 && list[iter].AT > time)
            time = list[iter].AT;
        
        while (iter < n)
        {
            if(list[iter].AT <= time){
                Queue[iter] = true;
                iter++;
                q++;
            }
            else
                break;
        }
        
        k = argMin(list, Queue, n);
        Queue[k] = false;
        q--;

        list[k].Start = time;
        time += list[k].BT;
        list[k].Finish = time;

        count++;
    }
    float totWT = 0, totRT = 0, totTT = 0;
    printf("\n____________________________________________________________________________");
    printf("\n| Process | Arrival | Burst | Start | Finish | Respone | Waiting | Turaround\n");
    printf("\n|-----------|---------|-------|-------|--------|---------|---------|----------\n");

    for ( k =0; k < n; k++){
        list[k].RT = list[k].Start - list[k].AT;
        list[k].WT = list[k].Finish - list[k].AT - list[k].BT;
        list[k].TT = list[k].Finish - list[k].AT;

        totWT += list[k].WT;
        totRT += list[k].RT;
        totTT += list[k].TT;

        printf("|%6s   |%6.2f   |%5.2f   |%6.2f  |%6.2f  |%6.2f  |%5.2f  | %8.2f   |\n",
                list[k].P, list[k].AT, list[k].BT, list[k].Start, list[k].Finish, list[k].RT, list[k].WT,list[k].TT);
        printf("|---------------------------------------------------------------------\n");
    }

    printf("\n AVG WT: %.2f\n", totWT/n);
    printf("\n AVG RT: %.2f\n", totRT/n);
    printf("\n AVG TT: %.2f\n", totTT/n);
}
void SRTF(Process* list, int n){
    float time = 0, next;
    int i, k;
    int iter = 0, count = 0, q = 0;
    bool* Queue = (bool*)malloc(n * sizeof(bool));
    for (i = 0; i < n; i++)
        Queue[i] = false;
    
    while(count < n){
        if(q == 0 && list[iter].AT > time)
            time = list[iter].AT;
        
        while (iter < n)
        {
            if(list[iter].AT <= time){
                Queue[iter] = true;
                iter++;
                q++;
            }
            else
                break;
        }
        
        k = argMin(list, Queue, n);
        if(iter < n)
            next = list[iter].AT;
        else
            next = 10000000000000;
        
        if(list[k].Start = -1)
            list[k].Start = time;
        
        if ( time + list[k].Remain <= next){
            time += list[k].Remain;
            list[k].Finish = time;

            Queue[k] = false;
            q--;
            count++;
        }
        else{
            list[k].Remain = list[k].Remain - (next - time);
            time = next;
        }
    }
    float totWT = 0, totRT = 0, totTT = 0;
    printf("\n____________________________________________________________________________");
    printf("\n| Process | Arrival | Burst | Start | Finish | Respone | Waiting | Turaround\n");
    printf("\n|-----------|---------|-------|-------|--------|---------|---------|----------\n");

    for ( k =0; k < n; k++){
        list[k].RT = list[k].Start - list[k].AT;
        list[k].WT = list[k].Finish - list[k].AT - list[k].BT;
        list[k].TT = list[k].Finish - list[k].AT;

        totWT += list[k].WT;
        totRT += list[k].RT;
        totTT += list[k].TT;

        printf("|%6s   |%6.2f   |%5.2f   |%6.2f  |%6.2f  |%6.2f  |%5.2f  | %8.2f   |\n",
                list[k].P, list[k].AT, list[k].BT, list[k].Start, list[k].Finish, list[k].RT, list[k].WT,list[k].TT);
        printf("|---------------------------------------------------------------------\n");
    }

    printf("\n AVG WT: %.2f\n", totWT/n);
    printf("\n AVG RT: %.2f\n", totRT/n);
    printf("\n AVG TT: %.2f\n", totTT/n);
}
int main(){
    int n, i;
    Process* list;
    printf("Nhap so process: ");
    scanf("%d", &n);
    
    list = (Process*)malloc(n * sizeof(Process));

    for( int i = 0 ; i < n; i++){
        printf("  Process %d: ", i + 1);
        scanf("%10s%f%f", &list[i].P, &list[i].AT, &list[i].BT);
        list[i].Remain = list[i].BT;
    }

    SRTF(list, n);
    return 0;
}
