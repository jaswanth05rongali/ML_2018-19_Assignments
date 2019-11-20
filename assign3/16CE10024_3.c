/*
# 16CE10024

# R.K.S.Jaswanth

# Assignment-3

# While executing the file,
  Please use the following command for compliation - gcc 16CE10024_3.c and
  Use the following command for execution - ./a.out 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int learn(int **data,int row,int col,int **test,int n);
int* numof_r_c(char *fname);
void input_csv(int r,char *fname, int **data);

int learn(int **data,int row,int col,int **test,int n)
{
    int i,j;
    double p=0,q=0,prob_m=1.0,prob_q=1.0,t_p_prob,t_n_prob,np,nn,prob_p,prob_n;
    
    for(np=0,nn=0,i=0;i<row;i++)
    {
        if(data[i][col-1]==1)
        {
            np = np + 1;
        }
        else
        {
            nn = nn + 1;
        }
    }
    
    prob_p = (np/(np+nn));
    prob_n = (nn/(np+nn));
    
    np = np + 2;
    nn = nn + 2;
    
    for(i=0;i<col-1;i++)
    {
        p=0;
        q=0;
        for(j=0;j<row;j++)
        {
            if(data[j][col-1]==1)
            {
                if(data[j][i]==test[n][i])
                {
                    p = p+1;
                }
            }
            else
            {
                if(data[j][i]==test[n][i])
                {
                    q = q+1;
                }
            }
        }
        
        p = p+1;
        q = q+1;
        
        prob_m *= (p/np);
        prob_q *= (q/nn);
    }
    
    t_p_prob = prob_p * prob_m;
    t_n_prob = prob_n * prob_q;
    
    if(t_p_prob>t_n_prob)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int* numof_r_c(char *fname)
{
    int r=0,col, *p;
    char c;
    FILE *fp;
    fp = fopen(fname, "r");

    p = (int *)malloc(2*sizeof(int));

    for (c = getc(fp),col=0; c != EOF; c = getc(fp))
    {
        if (c == '\n') 
        {
            r = r + 1;
        }
        col = col + 1;
    }  

    col = col/(r*2);

    p[0] = r;
    p[1] = col;

    fclose(fp);

    return p;
}

void input_csv(int r,char *fname, int **data)
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

int main()
{
    int **data,row,col,**test,t_row,i,j,classvalue,*a,output[50];
    char df_name[50],tf_name[50];
    FILE *f_out;

    strcpy(df_name, "data3.csv");
    strcpy(tf_name, "test3.csv");

    a = numof_r_c(df_name);
    row = a[0];
    col = a[1];

    a = numof_r_c(tf_name);
    t_row = a[0];
    
    data = (int **)malloc(row*sizeof(int *));
    for(i=0;i<row;i++)
    {
        data[i] = (int *)malloc(col*sizeof(int));
    }
    
    test = (int **)malloc(t_row*sizeof(int *));
    for(i=0;i<t_row;i++)
    {
        test[i] = (int *)malloc((col-1)*sizeof(int));
    }

    input_csv(row,df_name,data);
    input_csv(t_row,tf_name,test);
    
    f_out = fopen("16CE10024_3.out","w");

    i = 0;
    while(i<t_row)
    {
        classvalue = learn(data,row,col,test,i);
        output[i] = classvalue;
        i++;
        
        fprintf(f_out,"%d \t",classvalue);        
    }

    return 0;
}