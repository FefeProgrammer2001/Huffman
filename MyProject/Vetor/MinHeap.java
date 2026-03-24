public class MinHeap {

    private NoArvore[] heap;
    private int tamanho;
    private static final int CAPACIDADE_INICIAL = 256;

    public MinHeap() {
        this.heap = new NoArvore[CAPACIDADE_INICIAL];
        this.tamanho = 0;
    }

    public int tamanho() {
        return tamanho;
    }

    public void inserir(NoArvore noArvore) {
        if(tamanho == heap.length) {
            NoArvore[] novoHeap = new NoArvore[heap.length * 2];
            System.arraycopy(heap, 0, novoHeap, 0, tamanho);
            heap = novoHeap;
        }

        heap[tamanho] = noArvore;
        tamanho++;
        subir(tamanho - 1);
    }

    public NoArvore removerMinimo() {
        if(tamanho == 0) return null;

        NoArvore minimo = heap[0];

        heap[0] = heap[tamanho - 1];
        heap[tamanho - 1] = null;
        tamanho--;
        descer(0);

        return minimo;
    }

    private void subir(int indice) {
        while(indice > 0) {
            int pai = (indice - 1) / 2;
            if(heap[indice].getFrequencia() < heap[pai].getFrequencia()) {
                trocar(indice, pai);
                indice = pai;
            } else {
                break;
            }
        }
    }

    private void descer(int indice) {
        while (true) { 
            int menor = indice;
            int esq = 2 * indice + 1;
            int dir = 2 * indice + 2;
            
            if(esq < tamanho && heap[esq].getFrequencia() < heap[menor].getFrequencia()) {
                menor = esq;
            }
            if(dir < tamanho && heap[dir].getFrequencia() < heap[menor].getFrequencia()) {
                menor = dir;
            }

            if(menor != indice) {
                trocar(indice, menor);
                indice = menor;
            } else {
                break;
            }
        }
    }

    private void trocar(int i, int j) {
        NoArvore temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    public void imprimirHeap() {
        StringBuilder sb = new StringBuilder("[ ");
        for(int i = 0; i < tamanho; i++) {
            NoArvore na = heap[i];
            if(na.ehFolha()) {
                sb.append("No('").append(na.getCaractere())
                  .append("',").append(na.getFrequencia()).append(")");
            } else {
                sb.append("No(interno,").append(na.getFrequencia()).append(")");
            }
            if(i < tamanho - 1) sb.append(", ");
        }
        sb.append(" ]");
        System.out.println(sb);
    }
}