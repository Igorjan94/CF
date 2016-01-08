import java.util.*;
import java.io.*;
 
public class H {
    FastScanner in;
    PrintWriter out;
 
    final String inputName = null;
    final String outputName = null;
 
    class Node {
        int b = 1, w = 0;
        int f, t;
        Node l, r;
 
        int color = 0;
 
        Node(int i) {
            f = t = i;
        }
 
        Node(Node l, Node r) {
            this.l = l;
            this.r = r;
            f = l.f;
            t = r.t;
            w = l.w + r.w;
            b = l.b + r.b;
        }
 
        int get(int i) {
            if (i < f || t < i) {
                return -1;
            }
 
            if (color != -1) {
                return color;
            }
 
            return Math.max(l.get(i), r.get(i));
        }
 
        void paint(int from, int to, boolean c) {
            if (to < from || t < from || to < f) {
                return;
            }
 
            if (from <= f && t <= to) {
                if (c) {
                    color = 1;
                    w = t - f + 1;
                    b = 0;
                } else {
                    b = t - f + 1;
                    w = 0;
                    color = 0;
                }
                return;
            }
 
            if (color != -1) {
                l.paint(f, t, color == 1);
                r.paint(f, t, color == 1);
                color = -1;
            }
 
            l.paint(from, to, c);
            r.paint(from, to, c);
 
            w = l.w + r.w;
            b = l.b + r.b;
        }
 
    }
 
    public void solve() {
        int m = 1_000_000;
 
        Node[] tree = new Node[m];
        for (int i = 0; i < m; i++) {
            tree[i] = new Node(i);
        }
 
        while (m > 1) {
            int k = 0;
            for (int i = 1; i < m; i += 2) {
                tree[k++] = new Node(tree[i - 1], tree[i]);
            }
            if (m % 2 == 1) {
                tree[k++] = tree[m - 1];
            }
            m = k;
        }
        Node root = tree[0];
        int n = in.nextInt();
 
        while (--n >= 0) {
            int q = in.nextInt();
            if (q == 1) {
                int l = in.nextInt() - 1, r = in.nextInt() - 1;
                int c = in.nextInt();
                root.paint(l, r, c == 1);
            } else if (q == 2) {
                int i = in.nextInt() - 1;
 
                if (root.get(i) == 0) {
                    out.println("WHITE");
                } else {
                    out.println("BLACK");
                }
            } else {
 
                int c = in.nextInt();
 
                if (c == 0) {
                    out.println(root.b);
                } else if (c == 1) {
                    out.println(root.w);
                } else {
                    out.println(0);
                }
 
            }
        }
 
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
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        void close() throws IOException {
            br.close();
        }
 
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
        new H().run();
    }
}
