import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;

public class Descompressor {

    private static final byte[] MAGIC = new byte[] { 'H', 'U', 'F', 'F' };
    private static final int VERSAO_FORMATO_SUPORTADA = 1;
    
    public void descomprimir(String caminhoEntrada, String caminhoSaida) throws IOException {
        long tempoInicio = System.nanoTime();
        try (DataInputStream in = new DataInputStream(new FileInputStream(caminhoEntrada))) {
            byte[] magicLido = new byte[4];
            in.readFully(magicLido);
            if (!Arrays.equals(magicLido, MAGIC)) {
                throw new IOException("Formato invalido: cabecalho HUFF nao encontrado.");
            }
            int versao = in.readInt();
            if (versao != VERSAO_FORMATO_SUPORTADA) {
                throw new IOException("Versao de formato nao suportada: " + versao);
            }
            int padding = in.readInt();
            int[] frequencias = new int[256];
            for (int i = 0; i < 256; i++) {
                frequencias[i] = in.readInt();
            }
            byte[] dadosComprimidos = in.readAllBytes();
            MinHeap heap = new MinHeap();
            for (int i = 0; i < 256; i++) {
                if (frequencias[i] > 0) {
                    heap.inserir(new NoArvore((char) i, frequencias[i]));
                }
            }
            while (heap.tamanho() > 1) {
                NoArvore esq = heap.removerMinimo();
                NoArvore dir = heap.removerMinimo();
                heap.inserir(new NoArvore(esq.getFrequencia() + dir.getFrequencia(), esq, dir));
            }
            Arvore arvore = new Arvore(heap.removerMinimo());
            StringBuilder bitString = new StringBuilder();
            for (byte b : dadosComprimidos) {
                String bits = String.format("%8s", Integer.toBinaryString(b & 0xFF)).replace(' ', '0');
                bitString.append(bits);
            }
            int totalBits = bitString.length() - padding;
            ByteArrayOutputStream saida = new ByteArrayOutputStream();
            NoArvore atual = arvore.getRaiz();
            for (int i = 0; i < totalBits; i++) {
                char bit = bitString.charAt(i);
                atual = (bit == '0') ? atual.getEsquerda() : atual.getDireita();
                if (atual.ehFolha()) {
                    saida.write((int) atual.getCaractere());
                    atual = arvore.getRaiz();
                }
            }
            Files.write(Paths.get(caminhoSaida), saida.toByteArray());
        }
        long tempoFim = System.nanoTime();
        long tempoMs = (tempoFim - tempoInicio) / 1_000_000;
        System.out.println("Descompressao concluida em " + tempoMs + " ms -> " + caminhoSaida);
    }
}