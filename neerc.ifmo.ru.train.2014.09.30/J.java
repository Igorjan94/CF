import java.util.*;
import java.io.*;
 
public class J {
    FastScanner in;
    PrintWriter out;
 
    final String taskName = "xyzx2009";
 
    public void solve() {
        System.out.println("lol");
        System.out.println("WTF");
        if (true)
            return;
        ArrayList<String> s = new ArrayList<String>(1024);
        ArrayList<String> ans = new ArrayList<String>(1024);
        StringBuilder sb = new StringBuilder();
 
        while (in.hasNext()) {
 
            String word = in.next();
            s.add(word.replaceAll("\\.", ""));
            while (in.hasNext() && !word.contains(".")) {
                word = in.next();
                s.add(word.replaceAll("\\.", ""));
            }
 
            boolean hasNOT = false;
            boolean hasNO = false;
 
            // for (int i = 0; i < s.size(); i++) {
            // word = s.get(i).toLowerCase();
            // if (word.equals("not")) {
            // hasNOT = true;
            // for (int j = 0; j < s.size(); j++) {
            // sb.append(s.get(j));
            // sb.append(' ');
            // }
            // ans.add(sb.toString());
            // sb = new StringBuilder();
            // break;
            // }
            // if (word.equals("no")) {
            // hasNO = true;
            // for (int j = 0; j < s.size(); j++) {
            // sb.append(s.get(j));
            // sb.append(' ');
            // }
            // ans.add(sb.toString());
            // sb = new StringBuilder();
            // break;
            // }
            // }
 
            if (!hasNOT) {
 
                for (int i = 0; i < s.size(); i++) {
                    word = s.get(i).toLowerCase();
                    if (word.equals("can") || word.equals("may") || word.equals("must") || word.equals("should")) {
 
                        for (int j = 0; j <= i; j++) {
                            sb.append(s.get(j));
                            sb.append(' ');
                        }
 
                        sb.append("not");
                        int j = i + 1;
 
                        // if (j != s.size() && (s.get(j).equals("not"))) {
                        // ++j;
                        // }
 
                        for (j = i + 1; j <= s.size(); j++) {
                            if (j == s.size()) {
                                sb.append('.');
                            } else {
                                sb.append(' ');
                                sb.append(s.get(j));
                            }
                        }
                        ans.add(sb.toString());
                        sb = new StringBuilder();
                    }
 
                    if (word.equals("is") || word.equals("are")) {
                        for (int j = 0; j <= i; j++) {
                            sb.append(s.get(j));
                            sb.append(' ');
                        }
                        sb.append("no");
 
                        int j = i + 1;
 
                        if (j != s.size() && (s.get(j).toLowerCase().equals("a") || s.get(j).toLowerCase().equals("the"))) {
                            ++j;
                        }
 
                        for (; j <= s.size(); j++) {
                            if (j == s.size()) {
                                sb.append('.');
                            } else {
                                sb.append(' ');
                                sb.append(s.get(j));
                            }
                        }
                        ans.add(sb.toString());
                        sb = new StringBuilder();
                    }
 
                }
 
            }
 
            s.clear();
        }
 
        out.println(ans.size());
        for (String str : ans) {
            out.println(str);
        }
    }
 
    public void run() {
        try {
            if (taskName == null) {
                in = new FastScanner(null);
                out = new PrintWriter(System.out);
 
            } else {
                in = new FastScanner(new File(taskName + ".in"));
                out = new PrintWriter(new File(taskName + ".out"));
 
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
        new J().run();
    }
}
