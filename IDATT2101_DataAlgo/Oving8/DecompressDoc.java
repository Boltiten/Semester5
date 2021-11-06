import java.io.BufferedOutputStream;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

public class DecompressDoc {
    public static void main(String[] args) throws IOException
    {
        String compressed = "IDATT2101_DataAlgo\\Oving8\\compressedFile";
        String out = "IDATT2101_DataAlgo\\Oving8\\decompressedFile.lyx";

        DecompressDoc d = new DecompressDoc();
        d.decompressDocument(compressed, out);

    }

    public void decompressDocument(String in, String out) throws IOException
    {
        Huffman h = new Huffman();
        byte[] decompressedBytes = h.decompress(in);
        OutputStream outputwriter = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(out)));
        for (byte b : decompressedBytes) {
            outputwriter.write(b);
        }
        outputwriter.close();
    }
    
}
