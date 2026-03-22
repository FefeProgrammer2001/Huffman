import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Compressor {
    
    private static final byte[] MAGIC = new byte[] { 'H', 'U', 'F', 'F' };
    private static final int VERSAO_FORMATO = 1;
    
    public void comprimir(String caminhoEntrada, String caminhoSaida) throws IOException {
        long tempoInicio = System.nanoTime();
        byte[] bytes = Files.readAllBytes(Paths.get(caminhoEntrada));
        int[] frequencias = new int[256];
        for (byte b : bytes) {
            frequencias[b & 0xFF]++;
        }
        System.out.println("--------------------------------------------------");
        System.out.println("ETAPA 1: Tabela de Frequencia de Caracteres");
        System.out.println("--------------------------------------------------");
        for (int i = 0; i < 256; i++) {
            if (frequencias[i] > 0) {
                System.out.printf("Caractere '%c' (ASCII: %d): %d%n", (char) i, i, frequencias[i]);
            }
        }
        MinHeap heap = new MinHeap();
        for (int i = 0; i < 256; i++) {
            if (frequencias[i] > 0) {
                heap.inserir(new NoArvore((char) i, frequencias[i]));
            }
        }
        System.out.println("--------------------------------------------------");
        System.out.println("ETAPA 2: Min-Heap Inicial (Fila Dinamica)");
        System.out.println("--------------------------------------------------");
        heap.imprimirMinHeap();
        while (heap.tamanho() > 1) {
            NoArvore esq = heap.removerMinimo();
            NoArvore dir = heap.removerMinimo();
            NoArvore pai = new NoArvore(esq.getFrequencia() + dir.getFrequencia(), esq, dir);
            heap.inserir(pai);
        }
        Arvore arvore = new Arvore(heap.removerMinimo());
        System.out.println("--------------------------------------------------");
        System.out.println("ETAPA 3: Arvore de Huffman");
        System.out.println("--------------------------------------------------");
        arvore.imprimirArvore();
        String[] tabela = arvore.gerarTabela();
        System.out.println("--------------------------------------------------");
        System.out.println("ETAPA 4: Tabela de Codigos de Huffman");
        System.out.println("--------------------------------------------------");
        for (int i = 0; i < 256; i++) {
            if (tabela[i] != null) {
                System.out.printf("Caractere '%c': %s%n", (char) i, tabela[i]);
            }
        }
        StringBuilder bitString = new StringBuilder();
        for (byte b : bytes) {
            bitString.append(tabela[b & 0xFF]);
        }
        int padding = 8 - (bitString.length() % 8);
        if (padding == 8) {
            padding = 0;
        }
        for (int i = 0; i < padding; i++) {
            bitString.append('0');
        }
        byte[] dadosComprimidos = new byte[bitString.length() / 8];
        for (int i = 0; i < dadosComprimidos.length; i++) {
            String byteBits = bitString.substring(i * 8, i * 8 + 8);
            dadosComprimidos[i] = (byte) Integer.parseInt(byteBits, 2);
        }
        try (DataOutputStream out = new DataOutputStream(new FileOutputStream(caminhoSaida))) {
            out.write(MAGIC);
            out.writeInt(VERSAO_FORMATO);
            out.writeInt(padding);
            for (int freq : frequencias) {
                out.writeInt(freq);
            }
            out.write(dadosComprimidos);
        }
        long tempoFim = System.nanoTime();
        long tempoMs = (tempoFim - tempoInicio) / 1_000_000;
        int bitsOriginais = bytes.length * 8;
        int bitsComprimidos = bitString.length() - padding;
        double taxa = 100.0 * (1.0 - (double) bitsComprimidos / bitsOriginais);
        System.out.println("--------------------------------------------------");
        System.out.println("ETAPA 5: Resumo da Compressao");
        System.out.println("--------------------------------------------------");
        System.out.printf("Tamanho original....: %d bits (%d bytes)%n", bitsOriginais, bytes.length);
        System.out.printf("Tamanho comprimido..: %d bits (%d bytes)%n", bitsComprimidos, (bitsComprimidos + 7) / 8);
        System.out.printf("Taxa de compressao..: %.2f%%%n", taxa);
        System.out.printf("Tempo de execucao...: %d ms%n", tempoMs);
        System.out.println("--------------------------------------------------");
    }
}