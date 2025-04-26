

import javax.swing.SwingUtilities;

public class main {  // 修改类名为 Main
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MainFrame frame = new MainFrame();  // 创建 MainFrame 实例
            frame.setVisible(true);  // 设置窗口可见
        });
    }
}
