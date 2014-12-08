import java.util.Scanner;

public class java
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        String s = sc.next();
        if (s.matches(".{5,}") && s.matches(".*[a-z].*") && s.matches(".*[0-9].*") && s.matches(".*[A-Z].*"))
            System.out.println("Correct");
        else
            System.out.println("Too weak");
    }
}
