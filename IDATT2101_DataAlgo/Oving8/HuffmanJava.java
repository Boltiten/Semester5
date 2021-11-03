package IDATT2101_DataAlgo.Oving8;
import java.io.*;
import java.util.*;


public class HuffmanJava{
    public static void main(String[] args) 
    {
        //Entry
        int size = 6;
        char[] charArray = { 'a', 'b', 'c', 'd', 'e', 'f' };
        int[] charfreq = { 5, 9, 12, 13, 16, 45 };
        /* 
        DataInputStream input = new DataInputStream(new BufferedInputStream(new FileInputStream("diverse.txt")));
        DataOutputStream output = new DataOutputStream(new BufferedOutputStream(new FileOutputStream("diverseHuffed.txt")));
         */


        PriorityQueue<Node> queue = new PriorityQueue<Node>(size, new CompareNodes());
        //inputs
        for (int i = 0; i < size; i++) {
            Node n = new Node();
            n.c = charArray[i];
            n.freq = charfreq[i];
            n.left = n.right = null;
            queue.add(n);
        }
        Node root = null;
        while(queue.size() > 1)
        {
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
        printCode(root, "");
        //Writeout
        /* output.writeLong(l); */
    }
    public static void printCode(Node root, String s)
    {
        if(root.left == null && root.right == null)
        {
            System.out.println(root.c + ": " + s);
            return;
        }
        printCode(root.left, s + "0");
        printCode(root.right, s + "1");
    }
}

class Node{
    int freq;
    char c;

    Node right;
    Node left;
}
class CompareNodes implements Comparator<Node> {
    public int compare(Node x, Node y){
        return x.freq - y.freq;
    }
}

