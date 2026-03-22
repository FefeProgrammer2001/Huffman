public class MinHeap {
    
    private final FilaDinamica fila;

    public MinHeap() {
        this.fila = new FilaDinamica();
    }

    public int tamanho() {
        return fila.getTamanho();
    }

    public void inserir(NoArvore noArvore) {
        fila.inserir(noArvore);
    }

    public NoArvore removerMinimo() {
        return fila.removerMinimo();
    }

    public void imprimirMinHeap() {
        fila.imprimirFila();
    }
}