#include <stdio.h>
int main()
{
    int i, n, sum=0, ave, clo;
    int x[10]={0};
 
    printf("Input 5 natural numbers from 1 to 10 :\n");
    for (i=0;i<5;i++)
    {
        scanf("%d",&n);
        x[i]=n;
        sum=sum+x[i];
    }
    ave=sum/5;
    clo=x[0];
    for (i=0;i<5;i++)
    {
        if (clo>ave-x[i] && clo<=ave)
            clo=x[i];
        if (clo>ave && clo>=ave-x[i])
            clo=x[i];
    }
    printf("The average is %d.\n",ave);
    printf("The closest number to the average is %d.\n",clo);
    return 0;
}

