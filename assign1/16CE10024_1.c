/*
# 16CE10024

# R.K.S.Jaswanth

# Assignment-1

# While executing the file(Give the file_name as command line argument),
  Please use the following command - ./a.out filename 
  for e.g. - ./a.out data1.csv --> where data1.csv is the input file. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inputcsv(int, char *,int **); 
int* num_r_c(char *);

int* num_r_c(char *fname)
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

void inputcsv(int r,char *fname, int **data)
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
}

int main(int argc, char const *argv[])
{
    int *c,i,j,n,*m,row,col,**data,*p;
    char f_name[50];

    if (argc < 1){
        printf("Give proper input accordingly.\n");
        exit(0);
    }

    strcpy(f_name, argv[1]);

    p = num_r_c(f_name);

    row = p[0];
    col = p[1];

    data = (int **)malloc(row * sizeof(int *));
    for (i = 0; i < row; ++i){
        data[i] = (int *)malloc(col * sizeof(int));
    }

    inputcsv(row,f_name, data);

    for (i = 0; i < row; ++i)
    {
        for (j = 0; j < col; ++j)
        {
            if ((data[i][j]!=0)&&(data[i][j]!=1))
            {
                printf("Give proper inputs.\n");
                exit(0);
            }
        }
    }

    c = (int *)malloc(col * sizeof(int));
    m = (int *)malloc(col * sizeof(int));

    for (i = 0; i < col-1; ++i)
    {
        c[i] = data[0][i];
    }

    for (i = 1; i < row; ++i)
    {
        for (j = 0; j < col-1; ++j)
        {
            if(data[i][col-1]==0)
            {
                continue;
            }
            else
            {
                if((data[i][j])!=c[j])
                {
                    c[j] = -10;
                }
            }
        }
    }

    n = 0;

    for (i = 0; i < col-1; ++i)
    {
        if(c[i]!=-10)
        {
            if(c[i]==0)
            {
                m[n] = -i-1;
                n++;
            }
            else
            {
                m[n] = i+1;
                n++;
            }
        }       
    }

    free(c);

    for (i = 0; i < row; ++i)
    {
        free(data[i]);
    }

    free(data);

    printf("%d \t",n);

    for (i = 0; i < n; ++i)
    {
        printf("%d \t",m[i]);
    }

    free(m);

    printf("\n");

    return 0;
}
