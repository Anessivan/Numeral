 
#include <cmath>
#include <iostream> 
#include <fstream>
 #include <omp.h>
 

void bottle_incr(int* point, int size)
{
	int i = 0, j = 0;
	int c = 0;
	for (i = 0; i < size - 1; i++)
		for (j = 0; j < size - 1; j++)
			if (point[j] > point[j + 1])
			{
				c = point[j];
				point[j] = point[j + 1];
				point[j + 1] = c;
			}
}

 int* Find( int N)
 {
     int* temp = new int [N];
     int k = 0;
     int num = 8;
    omp_set_num_threads(num);
    double t1=omp_get_wtime();
    
#pragma omp parallel for
    
     for (int i = 3; i <= N; i +=2)
     {
         for (int j = 2; j * j < i; j++)
         {
             //std:: cout<<i << " " << j <<  "i % j" << i % j << std:: endl;
             if ( i % j == 0) break;
             else if(j + 1  > sqrt(i))
             {
                 temp[k] = i;
                 k++;
                 //std::cout << i << "\n";
             }
         }
     }
    double t2=omp_get_wtime();     
    int* res = new int[k];
    for(int i = 0; i < k; i++)
        res[i] = temp[i];
	bottle_incr(res, k);
	std::ofstream out;
	out.open("../Numeral.txt");
	out << 2 << "\n" << 3 << "\n";
    for (int i = 0; i < k; i++)
        out << res[i] << "\n";
    std::cout<<"num threads: "<< num <<std::endl;
    std::cout<<"time: "<<t2-t1<<"s"<<std::endl;
    delete[] temp;
    return res;
 }
 
 
 int main()
 {
     int* numeral;
     numeral = Find(1000);
	 delete[] numeral;
     return 0;
 }
 
