
import java.io.*;
import java.util.*;

public class D {
    final static String task = "auxiliary";

    class Point {
        int x, y;

        Point(int x, int y) {
            this.x = x;
            this.y = y;

        }

        @Override
        public boolean equals(Object o) {
            Point p = (Point) o;
            return x == p.x && y == p.y;
        }

        @Override
        public int hashCode() {
            return x ^ y;
        }

    }

    ArrayList<Point> h = new ArrayList<Point>(4096);
    ArrayList<Point> points = new ArrayList<Point>(4096);

    void QH(Point a, Point b) {
        Point q = null;
        int max = 0;
        for (Point c : points) {
            int dist = (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);

            if (dist > max) {
                q = c;
                max = dist;
            }
        }
        if (q != null) {
            h.add(q);
            QH(a, q);
            QH(q, b);
        }
    }

    void run() {
        int n = nextInt();
        Set<Point> hs = new HashSet<Point>(n);
        for (int i = 0; i < n; i++) {
            hs.add(new Point(nextInt(), nextInt()));
        }

        for (Point p : hs) {
            points.add(p);
        }

        if (points.size() == 1) {
            out.println(0.0);
            return;
        }
        Point a = points.get(0);
        Point b = points.get(1);
        if (points.size() == 2) {
            out.println(Math.sqrt((double) ((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y))));
            return;
        }

        for (Point p : points) {
            if (p.x < a.x) {
                a = p;
            }
            if (p.x > b.x) {
                b = p;
            }
        }
        h.add(a);
        h.add(b);
        QH(a, b);
        QH(b, a);

        double ans = 0;
        for (Point u : h) {
            for (Point v : h) {
                double d = Math.sqrt((double) ((v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y)));
                if (d > ans) {
                    ans = d;
                }
            }
        }
        out.println(ans);

    }

    int nextInt() {
        return Integer.parseInt(next());
    }

    long nextLong() {
        return Long.parseLong(next());
    }

    String next() {
        while (stringTokenizer == null || !stringTokenizer.hasMoreTokens()) {
            stringTokenizer = new StringTokenizer(nextLine());
        }
        return stringTokenizer.nextToken();
    }

    String nextLine() {
        try {
            return bufferedReader.readLine();
        } catch (IOException err) {
            return null;
        }
    }

    static BufferedReader bufferedReader;
    static StringTokenizer stringTokenizer;
    static PrintWriter out;

    public static void main(String[] args) throws IOException {
        bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
        new D().run();
        out.close();
        bufferedReader.close();
    }
}
