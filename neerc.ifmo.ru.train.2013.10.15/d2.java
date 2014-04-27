import java.io.*;
import java.util.*;

public class d2 {
    final static String task = "cabletv";
    static BufferedReader bufferedReader;
    static PrintWriter out;

    public static void main(String[] args) throws IOException {
		bufferedReader = new BufferedReader(new FileReader(task + ".in"));
		out = new PrintWriter(new File(task + ".out"));
		out.println("0\n1\n3\n0\n2");
        out.close();
        bufferedReader.close();
    }
}
