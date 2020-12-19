 
#include <cmath>
#include <iostream> 
 #include <omp.h>
 
 int* Find( int N)
 {
     int* temp = new int [N];
     int k = 0;
     int num = 4;
    omp_set_num_threads(num);
    double t1=omp_get_wtime();
    
#pragma omp parallel for
    
     for (int i = 2; i <= N; i++)
     {
         for (int j = 2; j * j < i; j++)
         {
             //std:: cout<<i << " " << j <<  "i % j" << i % j << std:: endl;
             if ( i % j == 0) break;
             else if(j + 1  > sqrt(i))
             {
                 temp[k] = i;
                 k++;
                 std::cout << i << "\n";
             }
         }
     }
     double t2=omp_get_wtime();     
    int* res = new int[k];
    for(int i = 0; i < k; i++)
        res[i] = temp[i];
    for (int i = 0; i < k; i++)
        std::cout << res[i] << std::endl;
    std::cout<<"num threads: "<< num <<std::endl;
    std::cout<<"time: "<<t2-t1<<"s"<<std::endl;
    delete[] temp;
    return res;
 }
 
 int main()
 {
     int* numeral;
     numeral = Find(30);
     delete[] numeral;
     return 0;
 }
 
