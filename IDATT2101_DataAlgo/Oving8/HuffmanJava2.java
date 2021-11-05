package IDATT2101_DataAlgo.Oving8;

import java.util.*;
import java.io.*;

public class HuffmanJava2 {
    private final static int MAX_BYTE = 256;

    private ArrayList<Byte> bytes;
    private int[] freq;
    private String[] bitstrings;
    private DataOutputStream output;

    public HuffmanJava2() {
        this.freq = new int[MAX_BYTE];
        this.bitstrings = new String[MAX_BYTE];
        bytes = new ArrayList<>();
    }

    public void compress(byte[] compressedBytes, String outpath) throws IOException {
        getFrequenciesFromBytes(compressedBytes);
        Node root = buildHuffmanTree();
        printCode(root, "");
        writeOutputFile(outpath, compressedBytes);
    }

    private void getFrequenciesFromBytes(byte[] compressedBytes) {
        for (int b : compressedBytes) {
            if (b < 0)
                freq[MAX_BYTE + b]++;
            else
                freq[b]++;
        }
    }
    private void getFrequenciesFromDIS(DataInputStream input) throws IOException
    {
        freq = new int[MAX_BYTE];

        for (int i = 0; i < freq.length; i++) {
            int frequency = input.readInt();
            freq[i] = frequency;
        }
    }

    private Node buildHuffmanTree() {
        // create nodes and put in queue
        PriorityQueue<Node> queue = new PriorityQueue<>(new Node());
        for (int i = 0; i < freq.length; i++) {
            if (freq[i] == 0)
                continue;
            char c = (char) i;
            int treeFreq = freq[i];
            Node n = new Node();
            n.c = c;
            n.freq = treeFreq;
            n.left = n.right = null;
            queue.add(n);
        }

        // use queue to build tree
        Node root = new Node();
        while (queue.size() > 1) {
            Node right = queue.peek();
            queue.poll();
            Node left = queue.peek();
            queue.poll();

            Node parent = new Node();
            parent.c = '$';
            parent.freq = right.freq + left.freq;
            parent.left = left;
            parent.right = right;
            root = parent;
            queue.add(parent);
        }
        // return top node
        return root;
    }

    private void printCode(Node root, String s) {
        if (root.left == null && root.right == null) {
            bitstrings[root.c] = s;
            System.out.println(root.c + ": " + s);
            return;
        }
        printCode(root.left, s + "0");
        printCode(root.right, s + "1");
    }

    private void writeOutputFile(String outpath, byte[] compressedBytes) throws IOException {
        output = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(outpath)));

        for (int i : freq) {
            output.writeInt(i);
        }
        int lastByte = parseBitString(compressedBytes);
        output.writeInt(lastByte);
        for(Byte b : bytes)
        {
            output.write(b);
        }

        output.close();
    }

    private int parseBitString(byte[] compressedBytes) {
        int input;
        int i = 0;
        int j;
        long currentByte = 0L;

        for (int k = 0; k < compressedBytes.length; k++) {
            input = compressedBytes[k];
            if (input < 0)
                input += MAX_BYTE;
            String bitstring = bitstrings[input];

            j = 0;
            while (j < bitstring.length()) {
                if (bitstring.charAt(j) == '0')
                    currentByte = (currentByte << 1);
                else
                    currentByte = ((currentByte << 1) | 1);
                ++j;
                ++i;
                if (i == 8) {
                    bytes.add((byte) currentByte);
                    i = 0;
                    currentByte = 0L;
                }
            }
        }
        int lastByte = i;
        while(i<8 && i != 0){
            currentByte = (currentByte<<1);
            ++i;
        }
        bytes.add((byte)currentByte);
        return lastByte;
    }

    public byte[] decompress(String file) throws IOException
    {
        DataInputStream input = new DataInputStream(new FileInputStream(file));
        getFrequenciesFromDIS(input);

        int lastByte = input.readInt();
        Node root = buildHuffmanTree();

        byte charByte;
        byte[] bytesArray = input.readAllBytes();
        input.close();

        int l = bytesArray.length;

        if(lastByte>0)l--;
        ArrayList<Byte> outputBytes = new ArrayList<>();
        BitString h = new BitString(0, 0);

        for (int i = 0; i < l; i++) {
            charByte = bytesArray[i];
            BitString bitString = new BitString(8, charByte);
            h = bitString.concat(h, bitString);
            h = writeCharactersTo(root, h, outputBytes);
        }
        if(lastByte>0)
        {
            BitString b = new BitString(lastByte, bytesArray[l] >> (8 - lastByte));
            h = BitString.concat(h, b);
            writeCharactersTo(root, h, outputBytes);           
        }

        //translate arraylist to array
        byte[] outputArray = new byte[outputBytes.size()];
        for (int i = 0; i < outputBytes.size(); i++) {
            outputArray[i] = outputBytes.get(i);
        }

        return outputArray;
    }

    private static BitString writeCharactersTo(Node tree, BitString bitstring, ArrayList<Byte> decompressedBytes) {
        Node tempTree = tree;
        int c = 0;

        for (long j = 1 << bitstring.length - 1; j != 0; j >>= 1) {
            c++;
            if ((bitstring.bits & j) == 0)
                tempTree = tempTree.left;
            else
                tempTree = tempTree.right;

            if (tempTree.left == null) {
                long character = tempTree.c;
                decompressedBytes.add((byte) character);
                long temp = ~(0);
                bitstring.bits = (bitstring.bits & temp);
                bitstring.length = bitstring.length - c;
                c = 0;
                tempTree = tree;
            }
        }

        return bitstring;
    }
    static class BitString {
        int length;
        long bits;

        BitString(int length, long bitsAsLong) {
            this.length = length;
            this.bits = bitsAsLong;
        }

        BitString(int length, byte bits) {
            this.length = length;
            this.bits = convertByte(bits, length);
        }

        static BitString concat(BitString bitstring, BitString other) {
            int length = bitstring.length + other.length;
            long bits = other.bits | (bitstring.bits << other.length);

            if (length > 64)
                throw new IllegalArgumentException(
                        "Bitstring too long: " + bits + ", length=" + length);

            return new BitString(length, bits);
        }

        public long convertByte(byte bite, int length) {
            long temp = 0;
            for (long i = 1 << length - 1; i != 0; i >>= 1)
                if ((bite & i) == 0)
                    temp = (temp << 1);
                 else
                     temp = ((temp << 1) | 1);

            return temp;
        }
    }


}

class Node implements Comparator<Node> {
    int freq;
    char c;

    Node right;
    Node left;

    @Override
    public int compare(Node x, Node y) {
        return x.freq - y.freq;
    }
}
