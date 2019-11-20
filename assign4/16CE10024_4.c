/*
# 16CE10024

# R.K.S.Jaswanth

# Assignment-4

# While executing the file,
  Please use the following command for compliation --> gcc 16CE10024_4.c -lm 
    &
  Use the following command for execution - ./a.out 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int* numof_r_c(char *fname);
void input_csv(int r,char *fname, double **data);
int learn(double **data, int row, int col, double **test, int index);
double dist(double **a, double **b, int n, int index,int d_ind);
int* sort(double *d, int r);
void mergesort(double *d,int s, int e);
void merge_subsorted(double *A, int start, int mid, int end);

int* numof_r_c(char *fname)
{
    int r=0,col, *p;
    char c;
    FILE *fp;
    fp = fopen(fname, "r");

    p = (int *)malloc(2*sizeof(int));

    for(c = fgetc(fp),r=0,col=0;(c != '\n')&&(c != EOF); c = fgetc(fp)){
        if(c == ','){
            col++;
        }
    }
    r=col;
    for (;(c != EOF); c = fgetc(fp))
    {     
        if(c == ',')
        {
            col = col + 1;
        }
    }  

    p[1] = r+1;
    r = col/r;

    p[0] = r;
    

    fclose(fp);

    return p;
}

void input_csv(int r,char *fname, double **data)
{
    int i = 0,j = 0;
    char line[2000];
    const char *m;
    FILE *fp;
    fp = fopen(fname, "r");

    for (i = 0;((i < r)&&(fgets(line,2000,fp))); ++i)
    {
        m = strtok(line,",");

        for (j = 0;(m && *m); ++j)
        {
            data[i][j] = atof(m);
            m = strtok(NULL, ",");
        }
    }

    fclose(fp);

    return;
}

int learn(double **data, int row, int col, double **test, int index)
{
    int i,j,p,n,*dofk;
    double *d;

    d = (double *)malloc(row*(sizeof(double)));

    for (i = 0; i < row; ++i)
    {
        d[i] = dist(data,test,col-1,index,i);
    }

    dofk = sort(d,row);

    for (j=0,p=0,n=0; j < 5; ++j)
    {
        if(data[dofk[j]][col-1]==0)
            n++;
        else
            p++;
    }

    free(d);

    if(p>n)
        return 1;
    else
        return 0;
}

double dist(double **a, double **b, int n, int index,int d_ind)
{
    double p,sum=0.0;
    int i;

    for (i = 0,sum=0.0; i < n; ++i)
    {
        sum = sum + ((a[d_ind][i]-b[index][i])*(a[d_ind][i]-b[index][i]));
    }

    p = sqrt(sum);
    return p;
}

int* sort(double *d, int r)
{
    int *index,i,j,n,m;
    double *dummy;

    index = (int *)malloc(5*sizeof(int));
    dummy = (double *)malloc(r*(sizeof(double)));

    for (i = 0; i < r; ++i)
    {
        dummy[i] = d[i];
    }

    mergesort(dummy,0,r);

    for (i = 0,n = 0; i < r; ++i)
    {
        if(n==5)
        {
            break;
        }

        m = -1;
        for (j = 0; j < 5; ++j)
            {
                if(d[i]==dummy[j])
                {
                    m = i;
                }
            }

        if(m!=-1)
        {
            index[n] = m;
            n++;
        }        
    }

    free(dummy);

    return index;
}

void mergesort(double *d,int s, int e)
{
    int mid;

    if (e == s + 1)
    {
        return;
    }

    mid = (s + e)/2;

    mergesort(d,s,mid);
    mergesort(d,mid,e);
    merge_subsorted(d,s,mid,e);

    return;
}

void merge_subsorted(double *A, int start, int mid, int end)
{
    int i, j, index=start;
    double tempA[1000];

    for (i = start,j = mid; ((i <=mid-1)||(j<end)) ; )
    {
        if((i<mid)&&(j<end))
        {
            if(A[i]<A[j])
            {
                tempA[index] = A[i];
                i++;
            }
            else
            {
                tempA[index] = A[j];
                j++;
            }
        }   
        else if(i<mid)
        {
            tempA[index] = A[i];
            i++;
        }
        else
        {
            tempA[index] = A[j];
            j++;
        }
        index++;
    }

    for (int i = start; i <end ; ++i)
    {
        A[i] = tempA[i];
    }
}

int main()
{
    int row,col,t_row,i,classvalue,*a;
    char df_name[50],tf_name[50];
    double **data,**test;
    FILE *f_out;

    strcpy(df_name, "data4.csv");
    strcpy(tf_name, "test4.csv");

    a = numof_r_c(df_name);
    row = a[0];
    col = a[1];

    a = numof_r_c(tf_name);
    t_row = a[0];

    data = (double **)malloc(row*sizeof(double *));
    for(i=0;i<row;i++)
    {
        data[i] = (double *)malloc(col*sizeof(double));
    }
    
    test = (double **)malloc(t_row*sizeof(double *));
    for(i=0;i<t_row;i++)
    {
        test[i] = (double *)malloc((col-1)*sizeof(double));
    }

    input_csv(row,df_name,data);
    input_csv(t_row,tf_name,test);

    f_out = fopen("16CE10024_4.out","w");

    i = 0;
    while(i<t_row)
    {
        classvalue = learn(data,row,col,test,i);
        i++;
        
        fprintf(f_out,"%d \t",classvalue);        
    }

    fclose(f_out);           

    return 0;
}
