public class Aimpl extends TemplateImpl<Integer> implements A {
    public void good(int x) {
        System.out.println("::A, System.out.println(" + x + ");");
    }
}
