/*
    * Estrutura de dados árvore para armazenar os caracteres
    * Após a contagem, os caracteres com maior frequência são posicionados próximos a raíz da árvore
    * Os de menor frequência são posicionados nas partes inferiores da estrutura
*/

public class Arvore {
    
    private final NoArvore raiz;

    public Arvore(NoArvore raiz) {
        this.raiz = raiz;
    }

    // Retorna a raíz da árvore
    public NoArvore getRaiz() {
        return raiz;
    }

    // Gera a tabela de código, chamando o método private gerarCodigos
    public String[] gerarTabela() {
        String[] tabela = new String[256];
        gerarCodigos(raiz, "", tabela);
        return tabela;
    }
    
    // Gera os binários 0 e 1 no arquivo final
    private void gerarCodigos(NoArvore no, String codigo, String[] tabela) {
        if(no == null) return;

        if(no.ehFolha()) {
            tabela[(int) no.getCaractere()] = codigo.isEmpty() ? "0" : codigo;
            return;
        }

        gerarCodigos(no.getEsquerda(), codigo + "0", tabela);
        gerarCodigos(no.getDireita(), codigo + "1", tabela);
    }

    public void imprimirArvore() {
        imprimirPreOrdem(raiz, true);
    }

    private void imprimirPreOrdem(NoArvore no, boolean ehRaiz) {
        if(no == null) return;

        if(ehRaiz) {
            System.out.println("- (RAIZ, " + no.getFrequencia() + ")");
        } else if(no.ehFolha()) {
            System.out.println("- ('" + no.getCaractere() + "', " + no.getFrequencia() + ")");
        } else {
            System.out.println("- (interno, " + no.getFrequencia() + ")");
        }

        imprimirPreOrdem(no.getEsquerda(), false);
        imprimirPreOrdem(no.getDireita(), false);
    }
}