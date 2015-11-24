public class TemplateImpl<T> implements Template<T> {
    public void lol(T s) {
        System.out.println(s);
    }
    public T get(T s) {
        return s;
    }
}
