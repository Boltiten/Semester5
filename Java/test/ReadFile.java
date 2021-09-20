package Java.test;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class ReadFile {
    public static void main(String[] args) throws FileNotFoundException {
        System.out.println();
        String file_name = "Java\\test\\ReadFile.txt";

        File file = new File(file_name);
        Scanner sc = new Scanner(file);

        // Oppgave variabler
        String line = "";
        int[] num_chars = new int[30];

        while (sc.hasNextLine()) {
            line = sc.nextLine();
            for (int i = 0; i < line.length(); i++) {
                line = line.toLowerCase();
                countInLine(num_chars, line.charAt(i));
            }
        }
        System.out.println("There are " + num_chars[14] + " o's in the file");
        sc.close();

    }

    public static void countInLine(int[] num_chars, char c) {
        switch (c) {
            case 'a':
                num_chars[0]++;
                break;
            case 'b':
                num_chars[1]++;
                break;
            case 'c':
                num_chars[2]++;
                break;
            case 'd':
                num_chars[3]++;
                break;
            case 'e':
                num_chars[4]++;
                break;
            case 'f':
                num_chars[5]++;
                break;
            case 'g':
                num_chars[6]++;
                break;
            case 'h':
                num_chars[7]++;
                break;
            case 'i':
                num_chars[8]++;
                break;
            case 'j':
                num_chars[9]++;
                break;
            case 'k':
                num_chars[10]++;
                break;
            case 'l':
                num_chars[11]++;
                break;
            case 'm':
                num_chars[12]++;
                break;
            case 'n':
                num_chars[13]++;
                break;
            case 'o':
                num_chars[14]++;
                break;
            case 'p':
                num_chars[15]++;
                break;
            case 'q':
                num_chars[16]++;
                break;
            case 'r':
                num_chars[17]++;
                break;
            case 's':
                num_chars[18]++;
                break;
            case 't':
                num_chars[19]++;
                break;
            case 'u':
                num_chars[20]++;
                break;
            case 'v':
                num_chars[21]++;
                break;
            case 'w':
                num_chars[22]++;
                break;
            case 'x':
                num_chars[23]++;
                break;
            case 'y':
                num_chars[24]++;
                break;
            case 'z':
                num_chars[25]++;
                break;
            case 'æ':
                num_chars[26]++;
                break;
            case 'ø':
                num_chars[27]++;
                break;
            case 'å':
                num_chars[28]++;
                break;
            default:
                num_chars[29]++;
                break;
        }
    }
}
