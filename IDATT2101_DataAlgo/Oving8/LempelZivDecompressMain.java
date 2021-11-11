import java.io.File;
import java.io.IOException;

public class LempelZivDecompressMain {
    public static void main(String[] args) throws IOException {
        File fileIn = new File("decompressedHuffman.txt");
        String fileOutPath = "decompressedFinal.lyx";
        File fileOut = new File(fileOutPath);
        if(fileOut.exists()){
            fileOut.delete();
            fileOut = new File(fileOutPath);
        }

        LZDecompress lempelZivDecompress = new LZDecompress(fileIn, fileOut);
        lempelZivDecompress.decompress();
    }
}