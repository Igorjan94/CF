using System;
 
class pr
{
    public static void Main ()
    {
         int ok = 0, ok1 = 0, ok2 = 0, ok3 = 0;
         string s = Console.ReadLine();
         if (s.Length >= 5)
             ok3 = 1;
         for (int i = 0; i < s.Length; i++)
         {
             if (s[i] >= 'a' && s[i] <= 'z')
                 ok = 1;
             if (s[i] >= 'A' && s[i] <= 'Z')
                 ok1 = 1;
             if (s[i] >= '0' && s[i] <= '9')
                 ok2 = 1;
         }         
         if (ok + ok1 + ok2 + ok3 == 4)
              Console.WriteLine("Correct");
         else
              Console.WriteLine("Too weak");
    }
}
