#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define num_test 1000 //the num of test number
#define num_chromosome 10 //the num of chromosome
//#define file_name 123.txt //the file need to read in
#define enlarge 100 //use for enlarge the percentage
typedef struct
{
    double decimal_num[3],decimal_num_new[3],answer[num_test];
    char binary_num[16];
    double adaptive_function;
} num;

double power(double num,double power)
{
    double temp=num;
    int i;
    if(power==0)
    {
        return 1;
    }
    else
    {
        for(i=0; i<power-1; i++)
        {
            num*=temp;
        }
        return num;
    }
}
void binary(num chromosome[])
{
    int i,j,c;
    int change;
    for(i=0; i<num_chromosome; i++)
    {
        for(j=0; j<3; j++)
        {
            change=chromosome[i].decimal_num[j];
            if(j==2)
            {
                for(c=14; c>7; c--)
                {
                    chromosome[i].binary_num[c]=change%2+'0';
                    change/=2;
                }
                chromosome[i].binary_num[15]='\0';
            }
            else
            {
                for(c=3+j*4; c>j*4-1; c--)
                {
                    chromosome[i].binary_num[c]=change%2+'0';
                    change/=2;
                }
                chromosome[i].binary_num[15]='\0';
            }
        }
    }
}
void decimal(num chromosome[])
{
    int i,j,c,change,power_num;
    for(i=0; i<num_chromosome; i++)
    {
        for(j=0; j<3; j++)
        {
            chromosome[i].decimal_num[j]=0;
        }
    }
    for(i=0; i<num_chromosome; i++)
    {
        power_num=3;
        c=0;
        for(j=0; j<15; j++)
        {

            chromosome[i].decimal_num[c]+=(chromosome[i].binary_num[j]-'0')*power(2,power_num);
            power_num--;
            //	printf("%d\n",realnum[i][c]);

            if(j==3||j==7)
            {
                c++;
                if(j==7)
                {
                    power_num=6;
                }
                else
                {
                    power_num=3;
                }
            }
        }
    }
}
void read(double test[][num_test])
{
	FILE *fp;
	int i=0,j=0;
	fp= fopen("data.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%lf %lf",&test[0][i],&test[1][i]);
        i++;
	}
}
void num_ran(num chromosome[])
{
    int i,j;
    for(i=0;i<num_chromosome;i++)
	{
		for(j=0;j<3;j++)
	    {
	    	if(j==2)
	    	{
	    		chromosome[i].decimal_num[j]=rand()%100;
	    	}
	    	else
	    	{
	    		chromosome[i].decimal_num[j]=rand()%10;
	    	}
	    }
	}
}
int main()
{
    num chromosome[num_chromosome];
    srand(time(NULL));
    double test[2][num_test],ans[3],all_adaptive_function=0;
    int power_num; //the variable for power
    int i,j,k,c;
    int random_num,random_num1,random_num2;
    int time=1;
    read(test);
    num_ran(chromosome);
    while(1)
	{
        printf("%d\n",time);
        all_adaptive_function=0;
		for(i=0;i<num_chromosome;i++)
        {
            for(j=0;j<num_test;j++)
            {

                    chromosome[i].answer[j]=chromosome[i].decimal_num[0]*test[0][j]*test[0][j]+chromosome[i].decimal_num[1]*test[0][j]+chromosome[i].decimal_num[2];

            }
            chromosome[i].adaptive_function=0;
            for(j=0;j<num_test;j++)
            {
             	chromosome[i].adaptive_function+=power(chromosome[i].answer[j]-test[1][j],2)/1000;
            }
          //printf("%lf\n",average[i]);
            chromosome[i].adaptive_function=sqrt(chromosome[i].adaptive_function);

            if(chromosome[i].adaptive_function==0)
            {
            	for(c=0;c<3;c++)
            	{
            		ans[c]=chromosome[i].decimal_num[c];
            	}
            	break;
            }
            chromosome[i].adaptive_function=1/chromosome[i].adaptive_function;
        }

        for(i=0;i<num_chromosome;i++)
        {
        	all_adaptive_function+=chromosome[i].adaptive_function;
        }
        for (i = 0; i < 10; i++)
        {
        	chromosome[i].adaptive_function/=all_adaptive_function;
        	chromosome[i].adaptive_function*=enlarge;
        	if(i!=0)
        	{
        		chromosome[i].adaptive_function+=chromosome[i-1].adaptive_function;
        	}
        }
        for(i=0;i<num_chromosome;i++){

                printf("%.0lf %.0lf %.0lf %lf\n",chromosome[i].decimal_num[0],chromosome[i].decimal_num[1],chromosome[i].decimal_num[2],chromosome[i].adaptive_function);


        }
        printf("\n");
        //system("pause");
        c=0;
        for(i=0;i<num_chromosome;i++)
        {
        	random_num=rand()%101;
        	//printf("ran%d:%d\n",i,ran);

        	for(j=0;j<num_chromosome;j++)
        	{
        		if(j==0)
        		{
        			if(random_num<=chromosome[j].adaptive_function)
        			{
        				for(k=0;k<3;k++)
        				{
        					chromosome[i].decimal_num_new[k]=chromosome[j].decimal_num[k];
        				}
        				c++;
                        break;
        			}
        		}
        		else
        		{
        			if(random_num>chromosome[j-1].adaptive_function&&random_num<=chromosome[j].adaptive_function)
        			{
        				for(k=0;k<3;k++)
        				{
        					chromosome[i].decimal_num_new[k]=chromosome[j].decimal_num[k];
        				}
        				c++;
                        break;

        			}
        		}
        	}
        }
        for(i=0;i<num_chromosome;i++)
        {
            for(j=0;j<3;j++)
            {
                chromosome[i].decimal_num[j]=chromosome[i].decimal_num_new[j];
            }
        }
        binary(chromosome);
        for (i = 0; i < num_chromosome; i+=2)
        {
        	random_num=rand()%15;
        	char temp_str;
        	for(c=random_num;c<15;c++)
        	{
        		temp_str=chromosome[i].binary_num[c];
        		chromosome[i].binary_num[c]=chromosome[i+1].binary_num[c];
        		chromosome[i+1].binary_num[c]=temp_str;
        	}
        }
        random_num1=rand()%num_chromosome;
        random_num2=rand()%15;
        if(chromosome[random_num1].binary_num[random_num2]=='1')
        {
        	chromosome[random_num1].binary_num[random_num2]='0';
        }
        else
        {
        	chromosome[random_num1].binary_num[random_num2]='1';
        }
        decimal(chromosome);
        time++;
	}
	printf("ans is:a=%lf,b=%lf,c=%lf",ans[0],ans[1],ans[2]);
    return 0;
}
