#include<iostream>
#include<climits>
#include<ctime>
#include<cstdlib>
using namespace std;

int my_add(int a, int b);

int main()
{
	int n1,n2,sum;
	int i,j;
	srand(time(0));
	for(i = INT_MIN;i<0;i++)
	{
		j  = rand();
		sum = my_add(i,j);
		if(sum != (i+j))
			cout << "ERRORE: " << i<<" + "<<j<<" = "<<sum<<endl;
		if(i%100000000 == 0)
			cout<<i<<endl;
	}
	sum= my_add(n1,n2);
	cout << "somma= " <<sum<<endl;
	return 0;
}

int my_add(int a, int b)
{
	int my_or, my_and, my_xor;
	my_or = a | b;
	my_and = a & b;
	while(my_and != 0)
	{
		my_xor = my_or ^ my_and;
		my_and = my_and & my_or;
		my_and = my_and << 1;
		my_or = my_xor;
	}	
	return my_or;
}
