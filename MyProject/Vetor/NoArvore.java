public class NoArvore {
    private char caractere;
    private int frequencia;
    private NoArvore esquerda;
    private NoArvore direita;

    public NoArvore(char caractere, int frequencia) {
        this.caractere = caractere;
        this.frequencia = frequencia;
        this.esquerda = null;
        this.direita = null;
    }

    public NoArvore(int frequencia, NoArvore esquerda, NoArvore direita) {
        this.caractere = '\0';
        this.frequencia = frequencia;
        this.esquerda = esquerda;
        this.direita = direita;
    }

    public char getCaractere() { return caractere; }
    public void setCaractere(char caractere) { this.caractere = caractere; }

    public int getFrequencia() { return frequencia; }
    public void setFrequencia(int frequencia) { this.frequencia = frequencia; }

    public NoArvore getEsquerda() { return esquerda; }
    public void setEsquerda(NoArvore esquerda) { this.esquerda = esquerda; }

    public NoArvore getDireita() { return direita; }
    public void setArvore(NoArvore direita) { this.direita = direita; }

    public boolean ehFolha() {
        return esquerda == null && direita == null;
    }
}