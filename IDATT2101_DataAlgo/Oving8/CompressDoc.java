
import java.io.*;
import java.nio.file.Files;

public class CompressDoc {
    public static void main(String[] args) throws IOException
    {
        String in = "IDATT2101_DataAlgo\\Oving8\\diverse.lyx";
        String out = "IDATT2101_DataAlgo\\Oving8\\compressedFinal";

        CompressDoc c = new CompressDoc();
        c.compressDocument(in, out);
    }

    //I was prepared to work with bytes instead of text from LZ, so I need translate to bytes here.
    public void compressDocument(String in, String out) throws IOException
    {
        LZ77 lz77 = new LZ77();
        byte[] compressedBytes = lz77.compress(in);
        File file = new File(in);
        byte[] filecontent = Files.readAllBytes(file.toPath());
        Huffman h = new Huffman();
        h.compress(compressedBytes, out);
    }
}
