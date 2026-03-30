public class FilaDinamica {
    
    private NoFila cabeca;
    private int tamanho;

    public FilaDinamica() {
        this.cabeca = null;
        this.tamanho = 0;
    }

    public int getTamanho() {
        return tamanho;
    }

    public boolean ehVazia() {
        return cabeca == null;
    }

    public void inserir(NoArvore noArvore) {
        NoFila novoNo = new NoFila(noArvore);

        if(ehVazia() || novoNo.getFrequencia() <= cabeca.getFrequencia()) {
            novoNo.setProximo(cabeca);
            cabeca = novoNo;
        } else {
            NoFila atual = cabeca;
            while(atual.getProximo() != null && atual.getProximo().getFrequencia() < novoNo.getFrequencia()) {
                atual = atual.getProximo();
            }
            novoNo.setProximo(atual.getProximo());
            atual.setProximo(novoNo);
        }

        tamanho++;
    }

    public NoArvore removerMinimo() {
        if(ehVazia()) return null;

        NoFila removido = cabeca;
        cabeca = cabeca.getProximo();
        tamanho--;

        return removido.getNoArvore();
    }

    public void imprimirFila() {
        StringBuilder sb = new StringBuilder("[ ");
        NoFila atual = cabeca;
        while(atual != null) {
            NoArvore na = atual.getNoArvore();
            if(na.ehFolha()) {
                sb.append("No('").append(na.getCaractere()).append("',").append(na.getFrequencia()).append(")");
            } else {
                sb.append("No(interno,").append(na.getFrequencia()).append(")");
            }
            if(atual.getProximo() != null) sb.append(", ");
            atual = atual.getProximo();
        }
        sb.append(" ]");
        System.out.println(sb);
    }
}