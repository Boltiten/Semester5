//package IDATT2101_DataAlgo.Oving8;

import java.util.*;
import java.io.*;

public class Huffman {

    private static final int MAX_BYTE = 256;
    private ArrayList<Byte> bytes;
    private int[] freq;
    private String[] bitstrings;


    //Constructor
    public Huffman() {
        this.freq = new int[MAX_BYTE];
        this.bitstrings = new String[MAX_BYTE];
        bytes = new ArrayList<>();
    }

    //compress input into final file. Takes input as array of bytes, could and possibly should be changed to take file.
    public void compress(byte[] compressedBytes, String outpath) throws IOException {
        //Get the frequency to order the Nodes in the huffman tree
        getFrequenciesFromBytes(compressedBytes);
        //Builds a huffman tree based on the frequency and sets root as last node to read from.
        Node root = buildHuffmanTree();
        //print the tree
        printCode(root, "");
        //Write file to output path. takes the input as bytes.
        writeOutputFile(outpath, compressedBytes);
    }

    //Counts number of apperences of an int in the bytes, ints go from -128 to 127, so we have to add some to chatch the bytes that fall under 0, since arrays dont go negative
    private void getFrequenciesFromBytes(byte[] compressedBytes) {
        for (int b : compressedBytes) {
            if (b < 0)
                freq[MAX_BYTE + b]++;
            else
                freq[b]++;
        }
    }
    //set the frequency table for the data in the input stream.
    private void getFrequenciesFromDIS(DataInputStream input) throws IOException
    {
        freq = new int[MAX_BYTE];

        for (int i = 0; i < freq.length; i++) {
            int frequency = input.readInt();
            freq[i] = frequency;
        }
    }


    private Node buildHuffmanTree() {
        //Priority queue, so good, wish I used that in the c++

        //This first forloop basicly creates a Node for each of the frequencies, and sets the data for the frequency. Also ignores those chars that doesn't appear.
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

        /**
         * Priority queue lets me catch the smallest node with peek()
         * I then remove the node from the queue with poll, but have it stored in "right", so the next lowest node was the second smallest, which will be "left".
         * Then I create a parent node that points to the left and right node.
         * The parent node has the frequency sum of the left and right node, and we put that back in the queue. With the compare function we made it will automaticly 
         * end up in the correct spot in the queue.
         */

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

    /**
     * This reads through the huffman tree.
     * It checks if the node pointers are empty, if they are then that means it is a leaf node and should contain a char, which we store.
     * If the check fails, then it is a parent node and will have a left and right node pointer.
     * We do a recursive call for the left and right node, and will add 0 to the string for when we go left and 1 for when we go right.
     * This runs until we have made a bitstring for all the leaf nodes in the huffman tree.
     */
    private void printCode(Node root, String s) {
        if (root.left == null && root.right == null) {
            bitstrings[root.c] = s;
            System.out.println(root.c + ": " + s);
            return;
        }
        printCode(root.left, s + "0");
        printCode(root.right, s + "1");
    }

    /**
     * Here we write the compressed file
     * First forloop writes the frequencies
     * second forloop writes the bytes.
     * Just before the second forloop we run parseBitString() which translates the input bytes into the bitstrings we made in printCode()
     */
    private void writeOutputFile(String outpath, byte[] compressedBytes) throws IOException {
        DataOutputStream output = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(outpath)));

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

    /**
     * This reads the bytes, converts to bitstring with the values from the frequency table
     * checks if the bitstring is filled up to 8
     * if yes then it writes it to a new "compressed" byte.
     * if no then it continues to fill with the next byte.
     * The byte is likely shorter as a bitstring because in the huffman tree, more common bytes will have a shorter path, like 011, which will be 3/8 of a byte.
     */
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

    /**
     * We also have to decompress the file
     * We start by taking in the path to the file we want to decompress
     * We then set the frequency table that we wrote in the beginning
     * Then we build the huffman tree, which will look the same as the one we made when we compresed.
     * Then we read all the bytes into an array
     * In the for loop we start reading the bytes and build them back into uncompressed bytes.
     * if statement to catch the last byte incase it wasn't full.
     */
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
            h = Huffman.BitString.concat(h, bitString);
            writeCharactersTo(root, h, outputBytes);
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

    /**
     * Reads the huffman tree, travels it based on the bitstring on the byte
     * finds the character at the end of the bitstring, then restarts from top to read the next char.
     */
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

    //Structure of a bitstring
    //concat for building longer strings.
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

//Huffman Node
//stores frequency and character.
//Parent nodes requires pointers to left and right node
//overrides the compare function for the Priority queue so it sorts based on frequency. 
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
