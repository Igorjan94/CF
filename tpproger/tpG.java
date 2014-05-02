import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class tpG {

	public static void main(String[] argv) throws ParseException, UnsupportedEncodingException {
		Parser parser = new Parser();
		Scanner sc = new Scanner(System.in);
		String s = sc.nextLine();
		s = s + '\n';
		InputStream stream = new ByteArrayInputStream(s.getBytes("UTF-8"));
		String to = sc.next();
		if (to.charAt(1) != 'O')
			System.out.println(parser.parse(stream).v);
		else
		{
			stream = new ByteArrayInputStream(s.getBytes("UTF-8"));
			String c = parser.parse(stream).v;
			if (!c.contains("x"))
			{
				if (Double.parseDouble(c) == 0)
					System.out.println("ANY NUMBER");
				else
					System.out.println("NO SOLUTIONS");
				sc.close();
				return;
			}
			int k = c.indexOf('x');
			String rrr = c.substring(k + 1);
			if (!rrr.contains("x") && !c.contains("*") && !c.contains("/") && !c.contains("^"))
			{
				c = c.replace('x', '0') + '\n';
				stream = new ByteArrayInputStream(c.getBytes("UTF-8"));
				System.out.format("%.3f\n", -Double.parseDouble(parser.parse(stream).v));
				sc.close();
				return;
			}
			parser.ok = true;
			double l = -100;
			double r = 100;
			double eps = 0.01;
			double sigma = 0.001;
			parser.X = l;
			while (parser.X < r)
			{
				stream = new ByteArrayInputStream(s.getBytes("UTF-8"));
				if (Math.abs(Double.parseDouble(parser.parse(stream).v)) < sigma)
					System.out.print(parser.X + " ");
				parser.X += eps;
			}
		}
		sc.close();
	}
}

enum Token {
	LPAREN, RPAREN, PLUS, MINUS, TIMES, NUMBER, END, CIRCONFLEXE, X, DIVIDE
}

class Tree {
	String node;
	List<Tree> children;
	String v;
	boolean ok = false;

	static String eval(String op, String X, String Y) {
		double x, y;
		try {
			x = Double.parseDouble(X);
			y = Double.parseDouble(Y);
		} catch (Exception e) {
			return X + op + Y;
		}
		switch (op.charAt(0)) {
		case '+':
			return "" + (x + y);
		case '-':
			return "" + (x - y);
		case '*':
			return "" + (x * y);
		case '/':
			return "" + (x / y);
		case '^':
			return "" + Math.pow(x, y);
		default:
			return X + op + Y;
		}
	}

	public Tree(double d) {
		node = "" + d;
		v = "" + d;
		ok = true;
	}

	public Tree(String node, Tree... children) {
		this.node = node;
		this.children = Arrays.asList(children);
	}

	public Tree(String node) {
		if (node.equals("x"))
			v = "x";
		this.node = node;
	}

	public String write() {
		StringBuilder sb = new StringBuilder();
		if (!(node.charAt(0) >= 'A' && node.charAt(0) <= 'Z'))
			sb.append(node);
		if (children != null)
			for (Tree tree : children)
				sb.append(tree.write());
		return sb.toString();
	}

	@Override
	public String toString() {
		return write();
	}
}

class LexicalAnalyzer {

	InputStream is;
	int curChar;
	double prevChar;
	int curPos;
	Token curToken;

	public LexicalAnalyzer(InputStream is) throws ParseException {
		this.is = is;
		curPos = 0;
		nextChar();
	}

	public boolean isBlank(int c) {
		return c == ' ' || c == '\t';
	}

	public void nextChar() throws ParseException {
		curPos++;
		try {
			curChar = is.read();
		} catch (IOException e) {
			throw new ParseException(e.getMessage(), curPos);
		}
	}

	public void nextToken() throws ParseException {
		while (isBlank(curChar)) {
			nextChar();
		}
		prevChar = curChar;
		switch (curChar) {
		case '(':
			nextChar();
			curToken = Token.LPAREN;
			break;
		case ')':
			nextChar();
			curToken = Token.RPAREN;
			break;
		case '*':
			nextChar();
			curToken = Token.TIMES;
			break;
		case '/':
			nextChar();
			curToken = Token.DIVIDE;
			break;
		case '-':
			nextChar();
			curToken = Token.MINUS;
			break;
		case '+':
			nextChar();
			curToken = Token.PLUS;
			break;
		case '^':
			nextChar();
			curToken = Token.CIRCONFLEXE;
			break;
		case 'x':
		case 'X':
			nextChar();
			curToken = Token.X;
			break;
		case '$':
		case -1:
		case '\n':
		case '\r':
			curToken = Token.END;
			break;
		default:
			if ('0' <= curChar && curChar <= '9') {
				StringBuilder sb = new StringBuilder();
				while ('0' <= curChar && curChar <= '9' || curChar == '.' || curChar == ',' || curChar == 'E') {
					sb.append((char) curChar);
					nextChar();
				}
				prevChar = Double.parseDouble(sb.toString());
				curToken = Token.NUMBER;
			} else
				throw new ParseException("Illegal character \'" + curChar + "\'", curPos);
		}
	}

	public Token curToken() {
		return curToken;
	}

	public int curPos() {
		return curPos;
	}
}

class Parser {
	LexicalAnalyzer lex;
	double X;
	boolean ok = false;

	void writeln(Object O) {
		//System.out.println(O + " " + lex.curToken);
	}

	Tree E(String acc) throws ParseException {
		writeln(acc + " " + "E");
		switch (lex.curToken()) {
		case MINUS:
			lex.nextToken();
			Tree temp = T(acc);
			Tree y = D("-" + temp.v);
			Tree x = new Tree("E", new Tree("-"), temp, y);
			x.v = y.v;
			return x;
		case NUMBER:
		case X:
		case LPAREN:
			temp = T(acc);
			y = D(temp.v);
			x = new Tree("E", temp, y);
			x.v = y.v;
			return x;
		default:
			throw new ParseException("unexpected " + (char) lex.prevChar, lex.curPos);
		}
	}

	Tree D(String acc) throws ParseException {
		writeln(acc + " " + "D");
		switch (lex.curToken()) {
		case MINUS:
			lex.nextToken();
			Tree temp = T(acc);
			Tree y = D(Tree.eval("-", acc, temp.v));
			Tree x = new Tree("D", new Tree("-"), temp, y);
			x.v = y.v;
			return x;
		case PLUS:
			lex.nextToken();
			temp = T(acc);
			y = D(Tree.eval("+", acc, temp.v));
			x = new Tree("D", new Tree("+"), temp, y);
			x.v = y.v;
			return x;
		case RPAREN:
		case END:
			x = new Tree("D");
			x.v = acc;
			return x;
		default:
			throw new ParseException("unexpected " + (char) lex.prevChar, lex.curPos);
		}
	}

	Tree T(String acc) throws ParseException {
		writeln(acc + " " + "T");
		switch (lex.curToken()) {
		case NUMBER:
		case X:
		case LPAREN:
			Tree temp = F(acc);
			Tree y = S(temp.v);
			Tree x = new Tree("T", temp, y);
			x.v = y.v;
			return x;
		default:
			throw new ParseException("expected NUMBER or '(', got " + (char) lex.prevChar, lex.curPos);
		}
	}

	Tree S(String acc) throws ParseException {
		writeln(acc + " " + "S");
		switch (lex.curToken()) {
		case TIMES:
			lex.nextToken();
			Tree temp = F(acc);
			Tree y = S(Tree.eval("*", acc, temp.v));
			Tree x = new Tree("S", new Tree("*"), temp, y);
			x.v = y.v;
			return x;
		case DIVIDE:
			lex.nextToken();
			temp = F(acc);
			y = S(Tree.eval("/", acc, temp.v));
			x = new Tree("S", new Tree("/"), temp, y);
			x.v = y.v;
			return x;
		case RPAREN:
		case MINUS:
		case PLUS:
		case END:
			x = new Tree("S");
			x.v = acc;
			return x;
		default:
			throw new ParseException("unexpected " + (char) lex.prevChar, lex.curPos);
		}
	}

	Tree F(String acc) throws ParseException {
		writeln(acc + " " + "F");
		switch (lex.curToken()) {
		case NUMBER:
		case X:
		case LPAREN:
			Tree temp = G(acc);
			Tree y = H(temp.v);
			Tree x = new Tree("F", temp, y);
			x.v = y.v;
			return x;
		default:
			throw new ParseException("expected , got " + (char) lex.prevChar, lex.curPos);
		}
	}

	Tree H(String acc) throws ParseException {
		writeln(acc + " " + "H");
		switch (lex.curToken()) {
		case CIRCONFLEXE:
			lex.nextToken();
			Tree temp = G(acc);
			Tree y = H(temp.v);
			Tree x = new Tree("H", new Tree("^"), temp, y);
			x.v = Tree.eval("^", acc, y.v);
			return x;

		case RPAREN:
		case TIMES:
		case DIVIDE:
		case MINUS:
		case PLUS:
		case END:
			x = new Tree("H");
			x.v = acc;
			return x;
		default:
			throw new ParseException("unexpected " + (char) lex.prevChar, lex.curPos);
		}
	}

	Tree G(String acc) throws ParseException {
		writeln(acc + " " + "G");
		double c = lex.prevChar;
		switch (lex.curToken()) {
		case NUMBER:
			lex.nextToken();
			Tree y = new Tree(c);
			Tree x = new Tree("G", y);
			x.v = y.v;
			return x;
		case X:
			lex.nextToken();
			if (ok)
				y = new Tree(X);
			else
				y = new Tree("x");
			x = new Tree("G", y);
			x.v = y.v;
			return x;
		case LPAREN:
			lex.nextToken();
			Tree temp = E("0");
			if (lex.curToken() != Token.RPAREN)
				throw new ParseException("unexpected " + (char) c, lex.curPos);
			lex.nextToken();
			x = new Tree("G", new Tree("("), temp, new Tree(")"));
			x.v = temp.v;
			return x;
		default:
			throw new ParseException("unexpected " + (char) c, lex.curPos);
		}
	}

	Tree parse(InputStream is) throws ParseException {
		lex = new LexicalAnalyzer(is);
		lex.nextToken();
		Tree e = E("0");
		if (lex.curToken != Token.END)
			throw new ParseException("unexpected )", lex.curPos);
		return e;
	}
}