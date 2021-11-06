
import java.io.*;
import java.nio.file.Files;

public class CompressDoc {
    public static void main(String[] args) throws IOException
    {
        String in = "IDATT2101_DataAlgo\\Oving8\\diverse.txt";
        String out = "IDATT2101_DataAlgo\\Oving8\\compressedFile";

        CompressDoc c = new CompressDoc();
        c.compressDocument(in, out);
    }

    public void compressDocument(String in, String out) throws IOException
    {
        File file = new File(in);
        byte[] filecontent = Files.readAllBytes(file.toPath());
        Huffman h = new Huffman();
        h.compress(filecontent, out);
    }
}
