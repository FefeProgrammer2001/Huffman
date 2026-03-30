public class NoArvore extends No {
    
    private char caractere;
    private NoArvore esquerda;
    private NoArvore direita;

    public NoArvore(char caractere, int frequencia) {
        super(frequencia);
        this.caractere = caractere;
        this.esquerda = null;
        this.direita = null;
    }

    public NoArvore(int frequencia, NoArvore esquerda, NoArvore direita) {
        super(frequencia);
        this.caractere = '\0';
        this.esquerda = esquerda;
        this.direita = direita;
    }

    public char getCaractere() {
        return caractere;
    }

    public void setCaractere(char caractere) {
        this.caractere = caractere;
    }

    public NoArvore getEsquerda() {
        return esquerda;
    }

    public void setEsquerda(NoArvore esquerda) {
        this.esquerda = esquerda;
    }

    public NoArvore getDireita() {
        return direita;
    }

    public void setDireita(NoArvore direita) {
        this.direita = direita;
    }

    public boolean ehFolha() {
        return esquerda == null && direita == null;
    }
}