import java.util.Scanner;

import java.util.Scanner;

public class test2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入一个 1——99999 之间的整数，程序将帮你判断它是否是回文数");
        int temp = sc.nextInt();
        int bit = Integer.toString(temp).length();
        boolean flag = isHuiwenNumber(temp);
        System.out.print("你输入的数是个" + bit + "位数,");
        if (flag) {
            System.out.println("它是回文数");
        } else {
            System.out.println("它不是回文数");
        }
        sc.close();
    }

    public static boolean isHuiwenNumber(int num) {
        int rawnumber = num;
        int newnumber = 0;
        while (rawnumber > 0) {
            int digit = rawnumber % 10;
            newnumber = newnumber * 10 + digit;
            rawnumber /= 10;
        }
        return num == newnumber;
    }
}