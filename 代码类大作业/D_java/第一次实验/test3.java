import java.util.Scanner;

public class test3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入一个大于三位的整数，程序将帮你判断它是否是水仙花数");
        int temp = sc.nextInt();
        boolean flag = isShuixianNumber(temp);
        if (flag) {
            System.out.println("它是水仙数");
        } else {
            System.out.println("它不是水仙数");
        }
        sc.close();
    }

    public static boolean isShuixianNumber(int num) {
        int rawnumber = num;
        int newnumber = 0;
        while (rawnumber > 0) {
            int digit = rawnumber % 10;
            newnumber = newnumber + digit * digit * digit;
            rawnumber /= 10;
        }
        return num == newnumber;
    }
}
