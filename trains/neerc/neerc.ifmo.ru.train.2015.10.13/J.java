import java.util.*;
import java.util.Map.Entry;
import java.io.*;
 
public class J {
    FastScanner in;
    PrintWriter out;
 
    final String inputName = null;
    final String outputName = null;
 
    class Angle {
        long x, y;
 
        public Angle(long x, long y) {
            if (y < 0) {
                y *= -1;
                x *= -1;
            }
 
            if (y == 0) {
                x = 1;
            }
 
            if (x == 0) {
                y = 1;
            }
 
            long g = gcd(Math.abs(x), Math.abs(y));
 
            this.x = x / g;
            this.y = y / g;
        }
 
        @Override
        public int hashCode() {
            return (int) (x * 1235321 + y);
        }
 
        @Override
        public String toString() {
            return "Angle [dx=" + x + ", dy=" + y + "]";
        }
 
        @Override
        public boolean equals(Object obj) {
            if (this == obj)
                return true;
            if (obj == null)
                return false;
            Angle angle = (Angle) obj;
            return x == angle.x && y == angle.y;
        }
    }
 
    class Line implements Comparable<Line> {
        long ax, ay, bx, by;
 
        public Line(int ax, int ay, int bx, int by) {
            this.ax = ax;
            this.ay = ay;
            this.bx = bx;
            this.by = by;
        }
 
        Angle angle() {
            return new Angle(ax - bx, ay - by);
        }
 
        public int compareTo(Line v) {
            Line u = this;
 
            if (u.ax == u.bx) {
                return Long.compare(u.ax, v.ax);
            }
 
            long p = (u.ax * (u.by - u.ay) + u.ay * (u.ax - u.bx)) * (v.ax - v.bx);
            long q = (v.ax * (v.by - v.ay) + v.ay * (v.ax - v.bx)) * (u.ax - u.bx);
 
            return Long.compare(p, q);
        }
 
        @Override
        public String toString() {
            return "Line [ax=" + ax + ", ay=" + ay + ", bx=" + bx + ", by=" + by + "]";
        }
 
    }
 
    long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a % b);
    }
 
    public void solve() {
 
        long mod = 1_000_000_007;
        long inv = 500000004;
 
        int n = in.nextInt();
 
        Map<Angle, List<Line>> q = new HashMap<>(n + 23);
 
        for (int i = 0; i < n; i++) {
            Line line = new Line(in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt());
            Angle key = line.angle();
 
            List<Line> list = q.get(key);
 
            if (list == null) {
                list = new ArrayList<Line>();
                q.put(key, list);
            }
 
            list.add(line);
        }
 
        Map<Angle, Long> w = new HashMap<>(n + 23);
 
        for (Entry<Angle, List<Line>> e : q.entrySet()) {
            Angle angle = e.getKey();
            List<Line> list = e.getValue();
 
            // out.println(angle);
            //
            // for (Line line : list) {
            // out.println("     " + line);
            // }
            Collections.sort(list);
            // out.println("sorted");
            // for (Line line : list) {
            // out.println("     " + line);
            // }
 
            long cnt = 0;
 
            int m = list.size();
 
            int l = 0;
 
            while (l < m) {
                int r = l;
                while (r < m && list.get(l).compareTo(list.get(r)) == 0) {
                    ++r;
                }
                long len = m - r;
                cnt = (cnt + ((r - l) * len) % mod) % mod;
                l = r;
            }
            w.put(angle, cnt);
        }
 
        long ans = 0;
 
        for (Entry<Angle, Long> e : w.entrySet()) {
            Angle angle = e.getKey();
            long u = e.getValue();
 
            Angle ort = new Angle(-angle.y, angle.x);
 
            Long v = w.get(ort);
 
            if (v != null) {
                ans = (ans + (u * v) % mod) % mod;
            }
 
        }
 
        out.println((ans * inv) % mod);
 
    }
 
    public void run() {
        try {
 
            if (inputName == null) {
                in = new FastScanner(null);
            } else {
                in = new FastScanner(new File(inputName));
            }
 
            if (outputName == null) {
                out = new PrintWriter(System.out);
            } else {
                out = new PrintWriter(new File(outputName));
 
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
        new J().run();
    }
}
