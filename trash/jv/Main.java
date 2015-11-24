public class Main {
    public static void main(String[] argv) {
        Aimpl a = new Aimpl();
        a.good(5);
        a.lol(10);
        System.out.println(a.get(5));
        X x = new X();
        x.good("qwerty");
        x.lol("1234");
        System.out.println(x.get("1.0"));
    }
}
