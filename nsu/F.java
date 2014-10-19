import java.util.*;
import java.io.*;
 
public class F {
    FastScanner in;
    PrintWriter out;
 
    final String taskName = "xyzx2009";
 
    int atoi(String s, int i)
    {
        int c = 0;
        while (s.charAt(i) >= '0' && s.charAt(i) <= '9')
            c = c * 10 + s.charAt(i++) - 48;
        return c;
    }

    int[] x, y, z;

    int updatez(String s, int temp, int i, int inb, boolean b)
    {
        int c = 0;
        if (s.charAt(i - 1) >= '0' && s.charAt(i - 1) <= '9')
        {
            c = temp;
            if (b)
                c *= inb;
        }
        return c;
    }

    void parse(String s, int w)
    {
        x[w] = y[w] = z[w] = 0;
        int inb = 1, sign = 1, temp = 1;
        boolean b = false;
        for (int i = 0; i < s.length(); ++i)
            switch (s.charAt(i))
            {
            case '(':
                b = true;
                inb = 1;
                break;
            case '=':
                sign *= -1;
            case ')':
                z[w] += updatez(s, temp, i, inb, b);
                temp = sign;
                b = false;
                inb = 1;
                break;
            case 'x':
                x[w] += temp * (b ? inb : 1);
                inb = 1;
                break;
            case 'y':
                y[w] += temp * (b ? inb : 1);
                inb = 1;
                break;
            case '+':
                z[w] += updatez(s, temp, i, inb, b);
                inb = 1;
                if (!b)
                    temp = sign;
                break;
            case '-':
                z[w] += updatez(s, temp, i, inb, b);
                if (b)
                    inb = -1;
                else
                    temp = -sign;
                break;
            default : 
                if (b)
                    inb *= atoi(s, i);
                else
                    temp *= atoi(s, i);
                while (s.charAt(i + 1) <= '9' && s.charAt(i + 1) >= '0')
                    ++i;
            }
    }

    public void solve() {
        x = new int[2];
        y = new int[2];
        z = new int[2];
        String s = in.next();
        String t = in.next();
        s += ')';
        t += ')';
        parse(s, 0);
        parse(t, 1);
        double a, b, c, d, e, f;
        a = x[0];
        b = y[0];
        c = z[0];
        d = x[1];
        e = y[1];
        f = z[1];
        System.out.println(a + " " + b + " " + c);
        System.out.println(d + " " + e + " " + f);
        double x = (b * f - c * e) / (a * e - b * d);
        double y = (f * a - c * d) / (b * d - e * a);
        System.out.println(x);
        System.out.println(y);
    }
 
    public void run() {
        try {
            if (taskName == null) {
                in = new FastScanner(null);
                out = new PrintWriter(System.out);
 
            } else {
                in = new FastScanner(new File("input.txt"));
                out = new PrintWriter(new File("output.txt"));
 
            }
 
            solve();
 
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        FastScanner(File f) {
            try {
                if (f == null) {
                    br = new BufferedReader(new InputStreamReader(System.in));
                } else {
                    br = new BufferedReader(new FileReader(f));
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }
 
        long nextLong() {
            return Long.parseLong(next());
        }
 
        boolean hasNext() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    String line = br.readLine();
                    if (line == null) {
                        return false;
                    }
                    st = new StringTokenizer(line);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.hasMoreTokens();
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
 
    public static void main(String[] arg) {
        new F().run();
    }
}
