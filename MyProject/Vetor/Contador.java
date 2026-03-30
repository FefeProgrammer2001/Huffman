// Classe que implementa um vetor contador de caracteres

public class Contador {
    
    private static final int TAMANHO = 256;
    private final int[] vetorContador;

    public Contador() {
        this.vetorContador = new int[TAMANHO];
    }

    public void contar(byte[] bytes) {
        for(byte b : bytes) {
            vetorContador[b & 0xFF]++; // Transforma o byte em um valor positivo
        }
    }

    public int getFrequencia(int indice) {
        return vetorContador[indice];
    }

    public int[] getVetorContador() {
        return vetorContador;
    }

    public void imprimirContagem() {
        for(int i = 0; i < TAMANHO; i++) {
            if(vetorContador[i] > 0) {
                System.out.printf("Caractere '%c' (ASCII: %d): %d%n", (char) i, i, vetorContador[i]);
            }
        }
    }
}
