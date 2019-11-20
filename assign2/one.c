#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double log_2(double p);
void entropy();

double log_2(double p)
{
	double val,n,d;

	if (p==0.0)
	{
		return 0.0;
	}

	n = log10(p);
	d = log10(2.0);

	val = (n/d);
	return val;
}

void entropy(){

	double e,p1,p2,m,n;
	int i,j;

	j = 10;
	i = 14;

	m = (double)i;
	n = (double)j;

	printf("%lf\n", m);
	printf("%lf\n", n);

	p1 = (n/(m+n));
	p2 = (m/(m+n)); 

	e = -(p1*log_2(p1))-(p2*log_2(p2));

	printf("%lf\n",e );
}



int main(int argc, char const *argv[])
{
	entropy();
    
    return 0;
}
