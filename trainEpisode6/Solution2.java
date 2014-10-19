import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.util.Map.Entry;
import static java.lang.Math.*;

public class Solution
{
    int k = 16;
    double eps = 0.001;

    class Team implements Comparable<Team>
    {
        String name;
        int time, n;
        double[]          l = new double[k];
        int[]      count = new int[k];
        boolean[] solved = new boolean[k];

        public Team(String name)
        {
            this.name = name;
            time = 0;
        }

        @Override
        public int compareTo(Team t)
        {
            int cmp = f(this, t);
            if (cmp != 0)
                return cmp;
            return name.compareTo(t.name);
        }
    }

    int f(Team a, Team b)
    {
        int cmp = Integer.compare(b.n, a.n);
        if (cmp != 0)
            return cmp;
        cmp = Integer.compare(a.time, b.time);
        if (cmp != 0)
            return cmp;
        for (int i = a.n; i >= 0; --i)
        {
            cmp = Double.compare(a.l[i], b.l[i]);
            if (cmp != 0)
                return cmp;
        }
        return 0;
    }

    void run()
    {
        int tests = nextInt();

        while (--tests >= 0)
        {
            int n = nextInt(), m = nextInt();
            Team[] team = new Team[n];
            Map<String, Integer> id = new HashMap<String, Integer>(n + 3);
            for (int i = 0; i < n; i++)
            {
                String s = next();
                team[i] = new Team(s);
                id.put(s, i);
            }
            int same = 0;
            int lastTime = 0;

            while (--m >= 0)
            {
                int time    = nextInt();
                int i       = id.get(next());
                int problem = next().codePointAt(0) - 'A';
                boolean ok  = next().equals("accepted");
                if (ok)
                {
                    if (time == lastTime)
                        same++;
                    else
                    {
                        lastTime = time;
                        same = 0;
                    }
                    if (team[i].solved[problem])
                        continue;
                    team[i].solved[problem] = true;
                    team[i].time += time + team[i].count[problem] * 20;
                    team[i].l[team[i].n++] = time + 0.5 - eps * same;
                }
                else
                    team[i].count[problem]++;
            }
            for (Team T : team)
            {
                out.println(T.name);
                for (int j = 0; j < T.l.length; ++j)
                    out.print(T.l[j] + " ");
                out.println();
            }

            Arrays.sort(team);

            for (int i = 0, j = 0; i < n; i++)
            {
                if (i == 0 || f(team[i], team[i - 1]) != 0)
                    out.print(j = i + 1);
                else
                    out.print(j);
                out.println(" " + team[i].name + " " + team[i].n + " " + team[i].time);
            }
        }

    }

    int[][] nextMatrix(int n, int m)
    {
        int[][] matrix = new int[n][m];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                matrix[i][j] = nextInt();
            }

        return matrix;
    }

    String next()
    {
        while (!st.hasMoreTokens())
        {
            st = new StringTokenizer(nextLine());
        }

        return st.nextToken();
    }

    boolean hasNext()
    {
        while (!st.hasMoreTokens())
        {
            String line = nextLine();

            if (line == null)
            {
                return false;
            }

            st = new StringTokenizer(line);
        }

        return true;
    }

    int[] nextArray(int n)
    {
        int[] array = new int[n];

        for (int i = 0; i < n; i++)
        {
            array[i] = nextInt();
        }

        return array;
    }

    int nextInt()
    {
        return Integer.parseInt(next());
    }

    long nextLong()
    {
        return Long.parseLong(next());
    }

    double nextDouble()
    {
        return Double.parseDouble(next());
    }

    String nextLine()
    {
        try
        {
            return in.readLine();
        }
        catch (IOException err)
        {
            return null;
        }
    }

    static PrintWriter out;
    static BufferedReader in;
    static StringTokenizer st = new StringTokenizer("");
    static Random rnd = new Random();

    public static void main(String[] args) throws IOException
    {
        out = new PrintWriter(System.out);
        // out = new PrintWriter(new File("hc.txt"));
        in = new BufferedReader(new InputStreamReader(System.in));
        new Solution().run();
        out.close();
        in.close();
    }
}





