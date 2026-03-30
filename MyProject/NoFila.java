public class NoFila extends No {
    
    private NoArvore noArvore;

    private NoFila proximo;

    public NoFila(NoArvore noArvore) {
        super(noArvore.getFrequencia());
        this.noArvore = noArvore;
        this.proximo = null;
    }

    public NoArvore getNoArvore() {
        return noArvore;
    }

    public void setNoArvore(NoArvore noArvore) {
        this.noArvore = noArvore;
    }

    public NoFila getProximo() {
        return proximo;
    }

    public void setProximo(NoFila proximo) {
        this.proximo = proximo;
    }
}