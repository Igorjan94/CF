using System;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Collections.Generic;

class Program
{
	static void Main()
	{
        int[] a = Console.ReadLine().Split().Select(x => int.Parse(x)).ToArray();
        int x1 = a[0];
        int y1 = a[1];
        int x2 = a[2];
        int y2 = a[3];
        int w = int.Parse(Console.ReadLine());

		Console.WriteLine(ans);
	}
}
