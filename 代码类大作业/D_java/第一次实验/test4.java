public class test4 {
    public static void main(String[] args) {
        int line = 5;
        PrintStar(line);

    }

    public static void PrintStar(int line) {
        for (int i = 0; i < line; i++) {
            for (int j = 0; j < line - i - 1; j++) {
                System.out.print(" ");
            }
            for (int k = 0; k < 2 * i+1; k++) {
                System.out.print("*");
            }
            System.out.println();
        }
    }
}
