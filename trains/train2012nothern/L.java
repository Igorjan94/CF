import java.util.*;
import java.io.*;

public class L {
    FastScanner in;
    PrintWriter out;

    class Tree
    {
        int[] ans;
        int count;
        int w;
        ArrayList<Tree> children;
        Tree()
        {
            ans = new int[26];
            children = new ArrayList<>();
            count = 0;
        }

        Tree(int r, int w)
        {
            ans = new int[26];
            children = new ArrayList<>();
            count = r;
            this.w = w;
        }

        int cnt()
        {
            int t = 0;
            for (int i = 0; i < 26; ++i)
                if (ans[i] == 1)
                    t++;
            return t;
        }

        @Override
        public String toString()
        {
            String s = "(" + (char) (w + 'a') + " : " + count;
            for (Tree t : children)
                s += t.toString();
            s += ")";
            return s;
        }

    }

    void insert(Tree root, int l, int r, int w)
    {
        root.count += r;
        root.ans[w] = 1;
        if (root.children.size() == 0)
        {
            if (root.w != w)
            {
                root.children.add(new Tree(l, root.w));
                root.children.add(new Tree(r, w));
                root.children.add(new Tree(root.count - l - r, root.w));
            }
            return;
        }
        int sum = 0;
        int i = -1;
        for (Tree t : root.children)
        {
            i++;
            sum += t.count;
            if (sum == l)
            {
                root.children.add(i, new Tree(r, w));
                return;
            }
            else
                if (sum >= l)
                {
                    insert(t, l - sum + t.count, r, w);
                    return;
                }
        }
    }

    void delete(Tree root, int l, int r)
    {
        if (root.children.size() == 0)
        {
            int t = Math.min(r - l, root.count - l);
            root.count -= t;
            return;
        }
        int sum = 0;
        for (Tree t : root.children)
        {
            sum += t.count;
            if (sum >= l)
            {
                delete(t, l - sum + t.count, r - sum + t.count);
                break;
            }
        }
        sum = 0;
        ArrayList<Tree> temp = new ArrayList<>();
        boolean flag = false;
        for (Tree t : root.children)
        {
            sum += t.count;
            if (sum < l || !flag)
            {
                temp.add(t);
                continue;
            }
            if (sum >= r)
            {
                flag = true;
                delete(t, l - sum + t.count, r - sum + t.count);
                break;
            }
        }
        root.children = temp;
        root.count = 0;
        for (Tree t : root.children)
            root.count += t.count;
    }

    int count(Tree root, int l, int r)
    {
        int sum = 0;
        int ans = 0;
        if (root.children.size() == 0)
            return 1;
        for (Tree t : root.children)
        {
            sum += t.count;
            if (sum >= l)
            {
                ans += count(t, l - sum + t.count, r - sum + t.count);
                break;
            }
        }
        sum = 0;
        for (Tree t : root.children)
        {
            sum += t.count;
            if (sum >= r)
            {
                ans += count(t, l - sum + t.count, r - sum + t.count);
                break;
            }
            else
                ans += t.cnt();
        }
        return ans;
    }

    public void solve() throws IOException {
        int n = in.nextInt();
        Tree root = null;
        while (n --> 0)
        {
            char c = in.next().charAt(0);
            int l = in.nextInt();
            int r = in.nextInt();
            if (c == '+')
            {
                int w = in.next().charAt(0) - 'a';
                if (root == null)
                    root = new Tree(r, w);
                else
                    insert(root, l - 1, r, w);
            }
            else
                if (c == '-')
                    delete(root, l, r);
                else
                    out.println(count(root, l, r));
        } 
    }

    public void run() {
        try {
            in = new FastScanner(new File("log.in"));
            out = new PrintWriter(new File("log.out"));

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
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
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
        new L().run();
    }
}
