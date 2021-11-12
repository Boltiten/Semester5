import java.io.BufferedOutputStream;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

public class DecompressDoc {
    public static void main(String[] args) throws IOException
    {
        String compressed = "IDATT2101_DataAlgo\\Oving8\\compressedFinal";
        String out = "IDATT2101_DataAlgo\\Oving8\\decompressed.lyx";

        DecompressDoc d = new DecompressDoc();
        d.decompressDocument(compressed, out);

    }

    //I was prepared to work with bytes instead of text from LZ, so I need translate to text here.
    public void decompressDocument(String in, String out) throws IOException
    {
        Huffman h = new Huffman();
        byte[] decompressedBytes = h.decompress(in);
        /* OutputStream outputwriter = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(out)));
        for (byte b : decompressedBytes) {
            outputwriter.write(b);
        }
        outputwriter.close(); */
        LZ77 lz77 = new LZ77();
        lz77.deCompress(decompressedBytes, out);
    }
    
}
