import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;

public class LZDecompress {
    private File fileIn;
    private File fileOut;
    private int indexIn;
    private int bytesToGo;
    private int indexOut;
    private byte[] inByte;
    private byte[] outByte;



    public LZDecompress(File in, File out) throws IOException {
        this.fileIn = in;
        this.fileOut = out;
        this.inByte = new byte[0];
        this.outByte = new byte[0];
        this.indexIn = 0;
        this.indexOut = 0;

        readFile();

        this.bytesToGo = inByte.length;
    }

    private void readFile() throws IOException {
        inByte = Files.readAllBytes(fileIn.toPath());
        outByte = new byte[inByte.length * 2];
    }

    public void decompress() throws IOException {
        while (bytesToGo != 0){
            int count = inByte[indexIn];
            indexIn++;
            if(count < 0){
                int toStart = indexOut;

                if(outByte.length <= indexOut + (-count)){
                    enlarge();
                }

                for(int i = indexOut; i < -count + toStart; i ++, indexOut++, indexIn++){
                    if(inByte.length <= indexIn){
                        break;
                    }
                    outByte[indexOut] = inByte[indexIn];
                }
            } else {
                if(inByte.length <= indexIn){
                    break;
                }
                int lengthCompressed = inByte[indexIn];
                indexIn++;

                if(outByte.length <= indexOut + lengthCompressed){
                    enlarge();
                }

                int startIndex = indexOut;
                for (int i = startIndex - count; i < lengthCompressed + (startIndex - count); i++, indexOut++) {
                    if(outByte.length <= indexOut || outByte.length <= i){
                        break;
                    }
                    outByte[indexOut] = outByte[i];
                }

            }

            bytesToGo = inByte.length - indexIn;
        }

        trim();
        writeFile();
    }

    private void enlarge(){
        //Utvider lista
        byte[] tmp = new byte[outByte.length + outByte.length];
        for(int i = 0; i < indexOut; i ++){
            tmp[i] = outByte[i];
        }
        outByte = tmp;
    }

    private void trim(){
        byte[] tempByteList = new byte[indexOut];

        for(int i = 0; i < indexOut; i ++){
            tempByteList[i] = outByte[i];
        }

        outByte = tempByteList;
    }

    private void writeFile() throws IOException {
        String[] words = new String[indexOut];
        for(int i = 0; i < indexOut; i ++){
            words[i] = String.valueOf(outByte[i]);
        }

        BufferedWriter outputWriter = new BufferedWriter(new FileWriter(fileOut.getPath()));
        String s = new String(outByte, StandardCharsets.UTF_8);
        outputWriter.write(s);
        outputWriter.flush();
        outputWriter.close();
    }
}