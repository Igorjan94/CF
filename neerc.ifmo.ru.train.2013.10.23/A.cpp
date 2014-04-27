#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
 
using namespace std;
 
int main()
{
    
    int w,d;
    while (true)
    {
                 map<int,int> a;
          scanf("%d %d",&w,&d);
          if(w == 0 && d == 0)
               return 0;
                
          int ans = 0;
           
          for(int i = 0; i < w; i++)
          {
                    int h;
                    scanf("%d",&h);
                    a[h]++;
                    ans += h;
          }
           
          for(int i = 0; i < d; i++)
          {
                  int h;  
                  scanf("%d",&h);
                  if(a[h])
                  {
                          a[h]--;                  
                  }      else {
                         ans += h;            
                  }
          }
           
          printf("%d\n",ans);
    }
    return 0;
}