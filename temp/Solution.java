import java.util.Arrays;
import java.util.Scanner;

public class Solution {

  @SuppressWarnings("resource")
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    int[] a = new int[n + 1];
    for (int i = 0; i < n - 1; i++) 
      a[i] = in.nextInt();
    System.out.println("NO WTF, only hardcore!");
  }
}
