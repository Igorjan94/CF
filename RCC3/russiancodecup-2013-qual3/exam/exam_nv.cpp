#include <cstdio>

using namespace std;

const int MINUTE = 60;
const int HOUR = 60 * MINUTE;
const int DAY = 24 * HOUR;

int read_time()
{
	int h, m, s;
	scanf("%d:%d:%d", &h, &m, & s);
	return h * 3600 + m * 60 + s;
}

int main()
{
	int t;   
	scanf("%d\n", &t);
	while (t--)
	{
		int S = read_time(), F = read_time();
		int k;
		scanf("%d\n", &k);
		int exam = (F - S + DAY) % DAY;         
		if (exam == 0) exam = DAY;
		if (k * MINUTE <= exam)
		{
			 puts("Perfect");
			 continue;
		}
		if ((k * MINUTE) <= exam + HOUR)
		{
			puts("Test");
			continue;
		}
		puts("Fail"); 
	}
}



