import java.util.*;
import java.io.*;
 
public class G {
 
    class SumNode {
        long n;
        int f, t;
 
        SumNode l, r, p;
 
        public SumNode(int i, long n) {
            f = t = i;
            this.n = n;
        }
 
        public SumNode(SumNode l, SumNode r) {
            this.l = l;
            this.r = r;
            n = l.n + r.n;
            l.p = r.p = this;
            f = l.f;
            t = r.t;
        }
 
        void update() {
            if (l != r) {
                n = l.n + r.n;
            }
            if (p != null) {
                p.update();
            }
        }
 
        void set(long n) {
            this.n = n;
            if (p != null) {
                p.update();
            }
        }
 
        long getSum(int from, int to) {
            if (t < from || to < f) {
                return 0;
            }
 
            if (from <= f && t <= to) {
                return n;
            }
 
            if (l != r) {
                return l.getSum(from, to) + r.getSum(from, to);
            }
 
            return 0;
        }
 
    }
 
    class HeapNode implements Comparable<HeapNode> {
        long n;
        int i;
 
        public HeapNode(int i, long n) {
            this.i = i;
            this.n = n;
        }
 
        public HeapNode(SumNode sn) {
            this.i = sn.f;
            this.n = sn.n;
        }
 
        @Override
        public int compareTo(HeapNode hn) {
            int cmp = Integer.compare(hn.i, i);
            if (cmp != 0) {
                return cmp;
            }
            return Long.compare(n, hn.n);
        }
    }
 
    public void solve() {
        int n = in.nextInt(), k = in.nextInt();
        long min = Long.MAX_VALUE;
 
        SumNode[] a = new SumNode[n], t = new SumNode[n];
 
        for (int i = 0; i < n; i++) {
            a[i] = t[i] = new SumNode(i, in.nextInt());
            min = Math.min(min, a[i].n);
        }
 
        {
            int s = n;
            while (s > 1) {
                int p = 0;
                for (int i = 1; i < s; i += 2) {
                    t[p++] = new SumNode(t[i - 1], t[i]);
                }
                if (s % 2 == 1) {
                    t[p++] = t[s - 1];
                }
                s = p;
            }
        }
 
        PriorityQueue<HeapNode> q = new PriorityQueue<HeapNode>(n + 1);
 
        long ans = 0;
 
        for (int i = 0; i < k - 1; i++) {
            q.add(new HeapNode(a[i]));
 
        }
 
        for (int r = k - 1; r < n; r++) {
            q.add(new HeapNode(a[r]));
            int l = r - k + 1;
            while (true) {
                long sum = t[0].getSum(l, r);
                if (sum < 0) {
                    break;
                }
                HeapNode hn = q.poll();
 
                if (hn.n > min) {
                    long d = Math.min(hn.n - min, sum + 1);
                    ans += d;
 
                    a[hn.i].set(a[hn.i].n - d);
                    hn.n -= d;
                     
                    if (hn.n > min) {
                        q.add(hn);
                    }
                }
 
            }
        }
 
        out.println(ans);
 
        for (int i = 0; i < n; i++) {
            out.print(a[i].n);
            out.print(' ');
 
        }
    }
 
    FastScanner in;
    PrintWriter out;
 
    public void run() {
        in = new FastScanner();
        out = new PrintWriter(System.out);
 
        solve();
 
        out.close();
    }
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
 
        String nextLine() {
            try {
                return br.readLine();
            } catch (IOException e) {
                return null;
            }
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(nextLine());
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
 
    public static void main(String[] arg) {
        new G().run();
    }
}