import java.util.Scanner;

import java.util.Scanner;

public class test2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("������һ�� 1����99999 ֮������������򽫰����ж����Ƿ��ǻ�����");
        int temp = sc.nextInt();
        int bit = Integer.toString(temp).length();
        boolean flag = isHuiwenNumber(temp);
        System.out.print("����������Ǹ�" + bit + "λ��,");
        if (flag) {
            System.out.println("���ǻ�����");
        } else {
            System.out.println("�����ǻ�����");
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