package IDATT2101_DataAlgo.Oving8;

import java.util.*;
import java.io.*;

public class HuffmanJava2 {
    private final static int MAX_BYTE = 256;

    private List<Byte> bytes;
    private int[] freq;
    private String[] bitstrings;
    private DataOutputStream output;

    public HuffmanJava2() {
        this.freq = new int[MAX_BYTE];
        this.bitstrings = new String[MAX_BYTE];
        bytes = new ArrayList<>();
    }

    public void compress(byte[] compressedBytes, String outpath) throws IOException {
        getFreqFromInput(compressedBytes);
        Node root = buildHuffmanTree();
        printCode(root, "");
        writeOutputFile(outpath, compressedBytes);
    }

    private void getFreqFromInput(byte[] compressedBytes) {
        for (int b : compressedBytes) {
            if (b < 0)
                freq[MAX_BYTE + b]++;
            else
                freq[b]++;
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
