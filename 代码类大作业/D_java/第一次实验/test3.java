import java.util.Scanner;

public class test3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("������һ��������λ�����������򽫰����ж����Ƿ���ˮ�ɻ���");
        int temp = sc.nextInt();
        boolean flag = isShuixianNumber(temp);
        if (flag) {
            System.out.println("����ˮ����");
        } else {
            System.out.println("������ˮ����");
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
