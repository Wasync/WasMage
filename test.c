        #include <stdio.h>

#include <stdlib.h>
float *Calc_prom(int Cant_N,int *Num)
{

    int cont,Anum=0;
    float *Prom;

    for(cont=0;cont<Cant_N;cont++)
    {
        Anum=Anum+Num[cont];
    }
    Prom=Anum/Cant_N;
    return Prom;

}
main()
{
    float *Prom;
    int Cant_N;
    int *Num;
    int cont;
    printf("\n Please enter the amount of numbers you want to average: ");
    scanf("%i",&Cant_N);
    Num=(int *)malloc(sizeof(int)*Cant_N);
    for(cont=0; cont<Cant_N;cont++)
    {
        printf("\n Enter number[%i]: ",cont+1);
        scanf("%i",&Num[cont]);
    }
    Prom=Calc_prom(Cant_N,Num);
    printf("\n **************************** \n");
    printf("\n The average is: %f\n",Prom);
    printf("\n **************************** \n");
    free(Num);
}
