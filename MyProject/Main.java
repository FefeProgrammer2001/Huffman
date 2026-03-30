public class Main {
    public static void main(String[] args) {
        if(args.length != 3) {
            System.out.println("Uso:");
            System.out.println("  Comprimir: java -jar huffman.jar -c <entrada> <saida.huff>");
            System.out.println("  Descomprimir: java -jar huffman.jar -d <entrada.huff> <saida>");
            System.exit(1);
        }

        String operacao = args[0];
        String arquivoEntrada = args[1];
        String arquivoSaida = args[2];

        try {
            if(operacao.equals("-c")) {
                new Compressor().comprimir(arquivoEntrada, arquivoSaida);
            } else if(operacao.equals("-d")) {
                new Descompressor().descomprimir(arquivoEntrada, arquivoSaida);
            } else {
                System.out.println("Operacao invalida. Use -c para comprimir ou -d para descomprimir");
                System.exit(1);
            }
        } catch(Exception e) {
            System.err.println("Erro: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
