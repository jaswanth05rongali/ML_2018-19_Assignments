//16EE10037

//RAYAVARAPU RAJA INGERSOLL

//PROGRAMMING ASSIGNMENT - 1

//Use Command Line argument to take file as input i.e. - ./a.out data1.csv

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int main(int argc,char *argv[])
{
    char name[25],str[1000],*p;
    int a[20][9],i=0,j,s[9];
    FILE *f;

    strcpy(name,argv[1]);

    f = fopen(name,"r");

    while(!feof(f))
    {
        fgets(str,1000,f);
    
        p = strtok(str,",");

        for(j=0;(p!=0);)
        {
            a[i][j] = atof(p);
            p = strtok(NULL,",");
            j++;
        }
        i++;
    }

    int n=0;
    for(i=0;i<20;i++){
       if(a[i][8]==1 ){
        if(n==0){
            for(int j=0;j<8;j++){
                s[j]=a[i][j];
                n++;
            }
        }
        else{
           for(int j=0;j<8;j++){
               if (s[j]!=a[i][j])
                  s[j]= -1;
            }
        }
    }
    }
    int q=0;
    for(i=0;i<8;i++){
        if(s[i]!=-1){
             q++;
        }
    }
    cout <<q<<"\t";
    for(i=0;i<8;i++){
        if(s[i]!=-1){
            if(s[i])
             cout<<(i+1);
            else
             cout<<-(i+1);
        }
    }    

    return 0;
}