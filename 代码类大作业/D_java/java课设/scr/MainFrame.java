

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.time.*;
import java.time.format.DateTimeFormatter;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

//照片要的�?
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.text.DecimalFormat;

// import org.jfree.chart.ChartFactory;
// //图表�?
// import org.jfree.chart.ChartPanel;
// import org.jfree.chart.JFreeChart;
// import org.jfree.chart.plot.PlotOrientation;
// import org.jfree.data.category.DefaultCategoryDataset;
// import org.jfree.data.general.DefaultPieDataset;

public class MainFrame extends JFrame {
    private UserManager userManager;
    private AccountManager accountManager;
    private DataManager dataManager;
    private User currentUser;

    // 登录面板组件
    private JPanel loginPanel;
    private JTextField studentIdField;
    private JPasswordField passwordField;

    // 主面板组�?
    private JPanel mainPanel;
    private JTabbedPane tabbedPane;
    private JPanel userPanel;
    private JPanel transactionPanel;
    private JPanel statisticsPanel;
    private DefaultTableModel transactionTableModel;

    // 照片Jlable以及相对路径
    private static final String DEFAULT_PHOTO_PATH = "picture\\000.jpg";// 默认照片

    // 图表
    private CardLayout cardLayout;

    // 辅助
    private JLabel balanceLabel;
    private JTable summaryTable;
    private DefaultTableModel summaryTableModel;
    private JLabel totalIncomeLabel;
    private JLabel totalExpenseLabel;
    private JLabel totalBalanceLabel;

    public MainFrame() {
        userManager = new UserManager();
        accountManager = new AccountManager();
        dataManager = new DataManager();
        initializeUI();

        // 添加窗口关闭事件处理
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                if (currentUser != null) {
                    dataManager.saveTransactions(
                            accountManager.getUserTransactions(currentUser.getStudentId()));
                }
                System.exit(0);
            }
        });
        
    }

    private void initializeUI() {
        setTitle("个人记账管理系统");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1000, 700);
        setMinimumSize(new Dimension(800, 600));

        cardLayout = new CardLayout();
        getContentPane().setLayout(cardLayout);

        createLoginPanel();
        createMainPanel();

        getContentPane().add(loginPanel, "LOGIN");
        getContentPane().add(mainPanel, "MAIN");

        cardLayout.show(getContentPane(), "LOGIN");
        setLocationRelativeTo(null);
    }

    // 登录界面
    private void createLoginPanel() {
        loginPanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        // 创建标题标签
        JLabel titleLabel = new JLabel("个人记账管理系统");
        titleLabel.setFont(new Font("微软雅黑", Font.BOLD, 24));
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 2;
        gbc.insets = new Insets(0, 0, 20, 0);
        loginPanel.add(titleLabel, gbc);

        // 重置网格宽度和间�?
        gbc.gridwidth = 1;
        gbc.insets = new Insets(5, 5, 5, 5);

        studentIdField = new JTextField(20);
        passwordField = new JPasswordField(20);
        JButton loginButton = new JButton("登录");
        JButton registerButton = new JButton("注册");

        gbc.gridx = 0;
        gbc.gridy = 1;
        loginPanel.add(new JLabel("学号�?"), gbc);

        gbc.gridx = 1;
        loginPanel.add(studentIdField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        loginPanel.add(new JLabel("密码�?"), gbc);

        gbc.gridx = 1;
        loginPanel.add(passwordField, gbc);

        // 创建按钮面板
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        buttonPanel.add(loginButton);
        buttonPanel.add(Box.createHorizontalStrut(20));
        buttonPanel.add(registerButton);

        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.gridwidth = 2;
        gbc.insets = new Insets(20, 0, 0, 0);
        loginPanel.add(buttonPanel, gbc);

        // 添加事件监听�?
        loginButton.addActionListener(e -> handleLogin());
        registerButton.addActionListener(e -> showRegisterDialog());

        // 添加回车键登�?
        passwordField.addActionListener(e -> handleLogin());
    }

    // 用户登录
    private void handleLogin() {
        String studentId = studentIdField.getText();
        String password = new String(passwordField.getPassword());

        if (studentId.isEmpty() || password.isEmpty()) {
            JOptionPane.showMessageDialog(this,
                    "请输入学号和密码�?",
                    "错误",
                    JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (userManager.validateUser(studentId, password)) {
            currentUser = userManager.getUser(studentId);

            // 加载用户的交易记�?
            List<Transaction> transactions = dataManager.loadTransactions(currentUser.getStudentId());
            System.out
                    .println("Loaded " + transactions.size() + " transactions for user " + currentUser.getStudentId());

            // 打印所有加载的交易记录
            for (Transaction t : transactions) {
                System.out.println(t);
            }

            accountManager.setTransactions(transactions);

            // 更新UI显示
            cardLayout.show(getContentPane(), "MAIN");
            refreshAllPanels();

            // 清空登录信息
            studentIdField.setText("");
            passwordField.setText("");
        } else {
            JOptionPane.showMessageDialog(this,
                    "学号或密码错误！",
                    "登录失败",
                    JOptionPane.ERROR_MESSAGE);
        }
    }

    // 用户注册
    private void showRegisterDialog() {
        JDialog dialog = new JDialog(this, "用户注册", true);
        dialog.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        JTextField studentIdField = new JTextField(20);
        JTextField nameField = new JTextField(20);
        JTextField idNumberField = new JTextField(20);
        JTextField classNameField = new JTextField(20);
        JPasswordField passwordField = new JPasswordField(20);
        JPasswordField confirmPasswordField = new JPasswordField(20);

        // 添加输入组件
        gbc.gridx = 0;
        gbc.gridy = 0;
        dialog.add(new JLabel("学号�?"), gbc);
        gbc.gridx = 1;
        dialog.add(studentIdField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        dialog.add(new JLabel("姓名�?"), gbc);
        gbc.gridx = 1;
        dialog.add(nameField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        dialog.add(new JLabel("身份证号�?"), gbc);
        gbc.gridx = 1;
        dialog.add(idNumberField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 3;
        dialog.add(new JLabel("班级�?"), gbc);
        gbc.gridx = 1;
        dialog.add(classNameField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 4;
        dialog.add(new JLabel("密码�?"), gbc);
        gbc.gridx = 1;
        dialog.add(passwordField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 5;
        dialog.add(new JLabel("确认密码�?"), gbc);
        gbc.gridx = 1;
        dialog.add(confirmPasswordField, gbc);

        JButton registerButton = new JButton("注册");
        gbc.gridx = 0;
        gbc.gridy = 6;
        gbc.gridwidth = 2;
        gbc.anchor = GridBagConstraints.CENTER;
        dialog.add(registerButton, gbc);

        registerButton.addActionListener(e -> {
            // 验证输入
            if (studentIdField.getText().isEmpty() || nameField.getText().isEmpty() ||
                    idNumberField.getText().isEmpty() || classNameField.getText().isEmpty() ||
                    passwordField.getPassword().length == 0 ||
                    confirmPasswordField.getPassword().length == 0) {

                JOptionPane.showMessageDialog(dialog,
                        "请填写所有字段！",
                        "错误",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }

            String password = new String(passwordField.getPassword());
            String confirmPassword = new String(confirmPasswordField.getPassword());

            if (!password.equals(confirmPassword)) {
                JOptionPane.showMessageDialog(dialog,
                        "两次输入的密码不一致！",
                        "错误",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }

            if (userManager.userExists(studentIdField.getText())) {
                JOptionPane.showMessageDialog(dialog,
                        "该学号已被注册！",
                        "错误",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }
            // 存入User
            User newUser = new User(
                    studentIdField.getText(),
                    nameField.getText(),
                    idNumberField.getText(),
                    classNameField.getText(),
                    password);
            newUser.setPhotoPath(DEFAULT_PHOTO_PATH);

            userManager.addUser(newUser);

            // 创建交易记录文件
            dataManager.createTransactionFileForNewUser(newUser.getStudentId());

            JOptionPane.showMessageDialog(dialog,
                    "注册成功�?",
                    "成功",
                    JOptionPane.INFORMATION_MESSAGE);

            dialog.dispose();
        });

        dialog.pack();
        dialog.setLocationRelativeTo(this);
        dialog.setVisible(true);
    }

    // 顶部面板�?
    private void createMainPanel() {
        mainPanel = new JPanel(new BorderLayout());

        // 创建顶部面板
        JPanel topPanel = new JPanel(new BorderLayout());
        
        JPanel userInfoPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        JLabel welcomeLabel = new JLabel("欢迎使用个人记账系统");
        welcomeLabel.setFont(new Font("微软雅黑", Font.BOLD, 18));
        userInfoPanel.add(welcomeLabel);

        JPanel balancePanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        balanceLabel = new JLabel("当前余额：�?0.00");
        balanceLabel.setFont(new Font("微软雅黑", Font.PLAIN, 16));
        JButton logoutButton = new JButton("退出登�?");
        balancePanel.add(balanceLabel);
        balancePanel.add(Box.createHorizontalStrut(20));
        balancePanel.add(logoutButton);

        topPanel.add(userInfoPanel, BorderLayout.WEST);
        topPanel.add(balancePanel, BorderLayout.EAST);
        topPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        mainPanel.add(topPanel, BorderLayout.NORTH);

        // 创建选项卡面�?
        tabbedPane = new JTabbedPane();
        initializeUserPanel();
        initializeTransactionPanel();
        initializeStatisticsPanel();

        tabbedPane.addTab("用户信息", userPanel);
        tabbedPane.addTab("收支记录", transactionPanel);
        tabbedPane.addTab("统计报表", statisticsPanel);

        mainPanel.add(tabbedPane, BorderLayout.CENTER);

        // 添加退出登录事�?
        logoutButton.addActionListener(e -> {
            int confirm = JOptionPane.showConfirmDialog(this,
                    "确定要退出登录吗�?",
                    "确认退�?",
                    JOptionPane.YES_NO_OPTION);

            if (confirm == JOptionPane.YES_OPTION) {
                // AccountManager 会自动保存交易数据，所以这里不需要额外保�?
                currentUser = null;
                cardLayout.show(getContentPane(), "LOGIN");
            }
        });

        // 添加窗口关闭事件
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                // AccountManager 已经在每次交易变更时自动保存了，
                // 但为了以防万一，在程序关闭时再保存一�?
                accountManager.saveTransactions();
                dispose();
                System.exit(0);
            }
        });
    }

    // 用户界面函数实现
    private JLabel photoLabel;
    private JLabel[] valueLabels;
    private static final int PHOTO_SIZE = 150;
    private static final String[] LABEL_TEXTS = { "学号�?", "姓名�?", "身份证号�?", "班级�?" };

    // 初始化用户面板，创建并设置整个用户信息面板的布局
    private void initializeUserPanel() {
        userPanel = new JPanel(new BorderLayout());
        JPanel infoPanel = createMainInfoPanel();
        userPanel.add(infoPanel, BorderLayout.NORTH);
    }

    // 创建主信息面板，包含照片面板和详细信息面�?
    private JPanel createMainInfoPanel() {
        JPanel infoPanel = new JPanel(new GridBagLayout());
        infoPanel.setBorder(BorderFactory.createTitledBorder("个人信息"));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        // 添加照片面板
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.anchor = GridBagConstraints.CENTER;
        infoPanel.add(createPhotoPanel(), gbc);

        // 添加详细信息面板
        gbc.gridx = 1;
        gbc.fill = GridBagConstraints.BOTH;
        infoPanel.add(createDetailsPanel(), gbc);

        return infoPanel;
    }

    // 创建照片面板，包含用户照片的标签
    private JPanel createPhotoPanel() {
        JPanel photoPanel = new JPanel(new BorderLayout());
        photoPanel.setBorder(BorderFactory.createEmptyBorder(5, 10, 5, 20));

        photoLabel = createPhotoLabel();
        loadDefaultPhoto();

        photoPanel.add(photoLabel, BorderLayout.CENTER);
        return photoPanel;
    }

    // 创建并返回一个用于显示用户照片的 JLabel
    private JLabel createPhotoLabel() {
        JLabel label = new JLabel();
        label.setPreferredSize(new Dimension(PHOTO_SIZE, PHOTO_SIZE));
        label.setBorder(BorderFactory.createLineBorder(Color.GRAY));
        label.setHorizontalAlignment(JLabel.CENTER);
        return label;
    }

    // 加载默认用户照片（以及设定照片）并设置到 photoLabel �?
    private void loadUserPhoto(User user) {
        String photoPath = user.getPhotoPath();
        if (photoPath != null && !photoPath.isEmpty()) {
            try {
                BufferedImage originalImage = ImageIO.read(new File(photoPath));
                if (originalImage != null) {
                    Image scaledImage = originalImage.getScaledInstance(
                            PHOTO_SIZE, PHOTO_SIZE, Image.SCALE_SMOOTH);
                    photoLabel.setIcon(new ImageIcon(scaledImage));
                }
            } catch (IOException ex) {
                System.err.println("无法加载用户照片: " + ex.getMessage());
                loadDefaultPhoto(); // 加载默认照片
            }
        } else {
            loadDefaultPhoto(); // 如果没有照片路径，则加载默认照片
        }
    }

    private void loadDefaultPhoto() {
        try {
            BufferedImage originalImage = ImageIO.read(new File(DEFAULT_PHOTO_PATH));
            if (originalImage != null) {
                Image scaledImage = originalImage.getScaledInstance(
                        PHOTO_SIZE, PHOTO_SIZE, Image.SCALE_SMOOTH);
                photoLabel.setIcon(new ImageIcon(scaledImage));
            }
        } catch (IOException ex) {
            System.err.println("无法加载默认照片: " + ex.getMessage());
        }
    }

    //////////////////////////////////////////////////////////////个人信息
    // 创建详细信息面板，包含用户的各项信息标签及值�?
    // 创建详细信息面板，包含用户的各项信息标签及�?
    private JPanel createDetailsPanel() {
        JPanel detailsPanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        JLabel[] labels = new JLabel[LABEL_TEXTS.length];
        valueLabels = new JLabel[LABEL_TEXTS.length];

        for (int i = 0; i < LABEL_TEXTS.length; i++) {
            // 创建标签
            labels[i] = new JLabel(LABEL_TEXTS[i]);
            gbc.gridx = 0;
            gbc.gridy = i;
            gbc.anchor = GridBagConstraints.EAST;
            detailsPanel.add(labels[i], gbc);

            // 创建值标�?
            valueLabels[i] = new JLabel();
            gbc.gridx = 1;
            gbc.anchor = GridBagConstraints.WEST;
            detailsPanel.add(valueLabels[i], gbc);
        }
        addChangePasswordButton(detailsPanel, gbc);

        return detailsPanel;
    }

    //////////////////////////////////////////////////////////修改密码
    // 添加“修改密码”按钮到详细信息面板
    private void addChangePasswordButton(JPanel panel, GridBagConstraints gbc) {
        JButton changePasswordButton = new JButton("修改密码");
        changePasswordButton.addActionListener(e -> showChangePasswordDialog());// 跳转到密码页�?

        gbc.gridx = 0;
        gbc.gridy = LABEL_TEXTS.length;
        gbc.gridwidth = 2;
        gbc.anchor = GridBagConstraints.CENTER;
        gbc.insets = new Insets(15, 5, 5, 5);

        panel.add(changePasswordButton, gbc);
    }

    // 修改密码的页面（一页面的）
    private void showChangePasswordDialog() {
        JDialog dialog = new JDialog(this, "修改密码", true);
        dialog.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        JPasswordField oldPasswordField = new JPasswordField(20);
        JPasswordField newPasswordField = new JPasswordField(20);
        JPasswordField confirmPasswordField = new JPasswordField(20);

        gbc.gridx = 0;
        gbc.gridy = 0;
        dialog.add(new JLabel("原密码："), gbc);
        gbc.gridx = 1;
        dialog.add(oldPasswordField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        dialog.add(new JLabel("新密码："), gbc);
        gbc.gridx = 1;
        dialog.add(newPasswordField, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        dialog.add(new JLabel("确认新密码："), gbc);
        gbc.gridx = 1;
        dialog.add(confirmPasswordField, gbc);

        JButton confirmButton = new JButton("确认修改");
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.gridwidth = 2;
        gbc.anchor = GridBagConstraints.CENTER;
        dialog.add(confirmButton, gbc);

        confirmButton.addActionListener(e -> {
            String oldPassword = new String(oldPasswordField.getPassword());
            String newPassword = new String(newPasswordField.getPassword());
            String confirmPassword = new String(confirmPasswordField.getPassword());

            if (!userManager.validateUser(currentUser.getStudentId(), oldPassword)) {
                JOptionPane.showMessageDialog(dialog,
                        "原密码错误！",
                        "错误",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }

            if (!newPassword.equals(confirmPassword)) {
                JOptionPane.showMessageDialog(dialog,
                        "两次输入的新密码不一致！",
                        "错误",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }

            userManager.changePassword(currentUser.getStudentId(), newPassword);
            JOptionPane.showMessageDialog(dialog,
                    "密码修改成功�?",
                    "成功",
                    JOptionPane.INFORMATION_MESSAGE);
            dialog.dispose();
        });

        dialog.pack();
        dialog.setLocationRelativeTo(this);
        dialog.setVisible(true);
    }

    // 添加纪录页面生成
    private void initializeTransactionPanel() {
        transactionPanel = new JPanel(new BorderLayout());

        // 创建输入面板
        JPanel inputPanel = new JPanel(new GridBagLayout());
        inputPanel.setBorder(BorderFactory.createTitledBorder("添加记录"));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        // 添加输入组件
        JComboBox<Transaction.Type> typeCombo = new JComboBox<>(Transaction.Type.values());
        JComboBox<Transaction.Category> categoryCombo = new JComboBox<>(Transaction.Category.values());
        JTextField amountField = new JTextField(10);
        JComboBox<Transaction.PaymentMethod> methodCombo = new JComboBox<>(Transaction.PaymentMethod.values());
        JTextField descriptionField = new JTextField(20);

        gbc.gridx = 0;
        gbc.gridy = 0;
        inputPanel.add(new JLabel("类型�?"), gbc);
        gbc.gridx = 1;
        inputPanel.add(typeCombo, gbc);

        gbc.gridx = 2;
        inputPanel.add(new JLabel("类别�?"), gbc);
        gbc.gridx = 3;
        inputPanel.add(categoryCombo, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        inputPanel.add(new JLabel("金额�?"), gbc);
        gbc.gridx = 1;
        inputPanel.add(amountField, gbc);

        gbc.gridx = 2;
        inputPanel.add(new JLabel("支付方式�?"), gbc);
        gbc.gridx = 3;
        inputPanel.add(methodCombo, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        inputPanel.add(new JLabel("描述�?"), gbc);
        gbc.gridx = 1;
        gbc.gridwidth = 3;
        inputPanel.add(descriptionField, gbc);

        JButton addButton = new JButton("添加记录");
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.gridwidth = 4;
        gbc.anchor = GridBagConstraints.CENTER;
        inputPanel.add(addButton, gbc);

        addButton.addActionListener(e -> {
            try {
                if (amountField.getText().isEmpty()) {
                    JOptionPane.showMessageDialog(this,
                            "请输入金额！",
                            "错误",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }

                double amount = Double.parseDouble(amountField.getText());
                if (amount <= 0) {
                    JOptionPane.showMessageDialog(this,
                            "金额必须大于0�?",
                            "错误",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }

                Transaction transaction = new Transaction(
                        currentUser.getStudentId(),
                        (Transaction.Type) typeCombo.getSelectedItem(),
                        (Transaction.Category) categoryCombo.getSelectedItem(),
                        amount,
                        LocalDateTime.now(),
                        (Transaction.PaymentMethod) methodCombo.getSelectedItem(),
                        descriptionField.getText());

                accountManager.addTransaction(transaction);
                dataManager.saveTransactions(
                        accountManager.getUserTransactions(currentUser.getStudentId()));
                refreshTransactionTable();
                updateBalance();

                // 清空输入�?
                amountField.setText("");
                descriptionField.setText("");
                typeCombo.setSelectedIndex(0);
                categoryCombo.setSelectedIndex(0);
                methodCombo.setSelectedIndex(0);

                JOptionPane.showMessageDialog(this, "记录添加成功�?");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this,
                        "请输入有效的金额�?",
                        "错误",
                        JOptionPane.ERROR_MESSAGE);
            }
        });

        transactionPanel.add(inputPanel, BorderLayout.NORTH);

        // 创建交易记录表格
        String[] columnNames = { "日期时间", "类型", "类别", "金额", "支付方式", "描述" };
        transactionTableModel = new DefaultTableModel(columnNames, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };

        JTable transactionTable = new JTable(transactionTableModel);
        transactionTable.getTableHeader().setReorderingAllowed(false);
        JScrollPane scrollPane = new JScrollPane(transactionTable);
        transactionPanel.add(scrollPane, BorderLayout.CENTER);

        // 添加底部按钮面板
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        JButton exportButton = new JButton("导出记录");
        JButton deleteButton = new JButton("删除记录");

        exportButton.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser();
            fileChooser.setDialogTitle("选择导出位置");
            fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
            fileChooser.setSelectedFile(new File("transactions.csv"));

            if (fileChooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
                String fileName = fileChooser.getSelectedFile().getAbsolutePath();
                if (!fileName.toLowerCase().endsWith(".csv")) {
                    fileName += ".csv";
                }
                dataManager.exportTransactionsToCSV(currentUser.getStudentId(), fileName);
                JOptionPane.showMessageDialog(this, "导出成功�?");
            }
        });

        deleteButton.addActionListener(e -> {
            int selectedRow = transactionTable.getSelectedRow();
            if (selectedRow >= 0) {
                int confirm = JOptionPane.showConfirmDialog(this,
                        "确定要删除选中的记录吗�?",
                        "确认删除",
                        JOptionPane.YES_NO_OPTION);

                if (confirm == JOptionPane.YES_OPTION) {
                    accountManager.removeTransaction(selectedRow);
                    dataManager.saveTransactions(
                            accountManager.getUserTransactions(currentUser.getStudentId()));
                    refreshTransactionTable();
                    updateBalance();
                }
            } else {
                JOptionPane.showMessageDialog(this,
                        "请先选择要删除的记录�?",
                        "提示",
                        JOptionPane.INFORMATION_MESSAGE);
            }
        });

        buttonPanel.add(exportButton);
        buttonPanel.add(deleteButton);
        transactionPanel.add(buttonPanel, BorderLayout.SOUTH);
    }

    //
    private static class MonthlySummary {
        double income;
        double expense;

        MonthlySummary(double income, double expense) {
            this.income = income;
            this.expense = expense;
        }

        double getBalance() {
            return income - expense;
        }
    }

    // 数据可视化（页面3�?
    private void initializeStatisticsPanel() {

        statisticsPanel = new JPanel(new BorderLayout());

        // 创建左侧表格面板
        JPanel tablePanel = new JPanel(new BorderLayout());
        String[] columnNames = { "年份", "月份", "收入金额", "支出金额", "结余" }; // 添加结余�?
        summaryTableModel = new DefaultTableModel(columnNames, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };
        summaryTable = new JTable(summaryTableModel);
        

        // 设置表格列宽
        summaryTable.getColumnModel().getColumn(0).setPreferredWidth(60); // 年份
        summaryTable.getColumnModel().getColumn(1).setPreferredWidth(50); // 月份
        summaryTable.getColumnModel().getColumn(2).setPreferredWidth(100); // 收入
        summaryTable.getColumnModel().getColumn(3).setPreferredWidth(100); // 支出
        summaryTable.getColumnModel().getColumn(4).setPreferredWidth(100); // 结余

        // 设置表格行高
        summaryTable.setRowHeight(30);

        //添加表格
        JScrollPane scrollPane = new JScrollPane(summaryTable);
        scrollPane.setPreferredSize(new Dimension(600, 400));
        tablePanel.add(scrollPane, BorderLayout.CENTER);

        // 添加刷新按钮和时间范围选择
        JPanel controlPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        JButton refreshButton = new JButton("刷新数据");
        JComboBox<String> timeRangeCombo = new JComboBox<>(new String[] { "最�?12个月", "本年�?", "去年" });// 下拉按键

        controlPanel.add(new JLabel("时间范围�?"));
        controlPanel.add(timeRangeCombo);
        controlPanel.add(refreshButton);

        tablePanel.add(controlPanel, BorderLayout.NORTH);

        // 添加统计信息面板
        JPanel summaryPanel = new JPanel(new GridLayout(1, 3, 10, 0));
        totalIncomeLabel = new JLabel("总收入：¥0.00");
        totalExpenseLabel = new JLabel("总支出：¥0.00");
        totalBalanceLabel = new JLabel("总结余：¥0.00");// 下方

        summaryPanel.add(totalIncomeLabel);
        summaryPanel.add(totalExpenseLabel);
        summaryPanel.add(totalBalanceLabel);

        tablePanel.add(summaryPanel, BorderLayout.SOUTH);

        // 刷新按钮事件
        refreshButton.addActionListener(e -> {
            String selectedRange = (String) timeRangeCombo.getSelectedItem();
            updateStatistics(selectedRange);
        });

        // 时间范围选择事件
        timeRangeCombo.addActionListener(e -> {
            String selectedRange = (String) timeRangeCombo.getSelectedItem();
            updateStatistics(selectedRange);
        });

        statisticsPanel.add(tablePanel, BorderLayout.CENTER);

        // 初始加载数据
        updateStatistics("最�?12个月");
    }

    private void updateStatistics(String timeRange) {
        if (currentUser == null)
            return;

        // 清空表格
        summaryTableModel.setRowCount(0);

        // 获取所有交易记�?
        List<Transaction> transactions = accountManager.getUserTransactions(currentUser.getStudentId());
        if (transactions == null || transactions.isEmpty()) {
            System.out.println("表格是空�?");
            return;
        } else {
            System.out.println("交易列表大小�?" + transactions.size());
        }

        // 根据选择的时间范围筛选数�?
        LocalDate now = LocalDate.now();
        LocalDate startDate;
        LocalDate endDate = now;

        switch (timeRange) {
            case "本年�?":
                startDate = LocalDate.of(now.getYear(), 1, 1);
                break;
            case "去年":
                startDate = LocalDate.of(now.getYear() - 1, 1, 1);
                endDate = LocalDate.of(now.getYear() - 1, 12, 31);
                break;
            default: // "最�?12个月"
                startDate = now.minusMonths(11).withDayOfMonth(1);
                break;
        }

        // 调用 calculateMonthlySummary 方法，获取汇总数�?
        Map<YearMonth, MonthlySummary> monthlyData = calculateMonthlySummary(transactions, startDate, endDate);
        System.out.println("数据汇总如�?");
        System.out.println(monthlyData);// 调试
        // 初始化总收入和总支�?
        double totalIncome = 0.0;
        double totalExpense = 0.0;

        // 更新表格数据并在控制台打�?
        DecimalFormat df = new DecimalFormat("#,##0.00");
        for (Map.Entry<YearMonth, MonthlySummary> entry : monthlyData.entrySet()) {
            YearMonth ym = entry.getKey();
            MonthlySummary summary = entry.getValue();
            double balance = summary.income - summary.expense;

            totalIncome += summary.income;
            totalExpense += summary.expense;

            String monthStr = String.format("%02d", ym.getMonthValue());
            String yearMonthStr = ym.getYear() + "�?" + monthStr + "�?";

            // 将数据添加到表格
            Object[] rowData = {
                    ym.getYear(),
                    monthStr,
                    "¥" + df.format(summary.income),
                    "¥" + df.format(summary.expense),
                    "¥" + df.format(balance)
            };
            summaryTableModel.addRow(rowData);

            // 在控制台打印数据
            System.out.println("月份�?" + yearMonthStr);
            System.out.println("总收入：" + df.format(summary.income));
            System.out.println("总支出：" + df.format(summary.expense));
            System.out.println("结余�?" + df.format(balance));
            System.out.println("---------------------------");
        }

        // 更新总计标签
        double totalBalance = totalIncome - totalExpense;

        System.out.println(totalIncome);
        System.out.println(totalExpense);
        System.out.println(totalBalance);
        
        totalIncomeLabel.setText("总收入：¥" + df.format(totalIncome));
        totalExpenseLabel.setText("总支出：¥" + df.format(totalExpense));
        totalBalanceLabel.setText("总结余：¥" + df.format(totalBalance));
        // 更新表格模型后，通知表格已更�?
        summaryTableModel.fireTableDataChanged();

    }

    private Map<YearMonth, MonthlySummary> calculateMonthlySummary(List<Transaction> transactions, LocalDate startDate,
            LocalDate endDate) {
        Map<YearMonth, MonthlySummary> monthlySummaryMap = new LinkedHashMap<>();

        // 初始化月份数�?
        YearMonth startYM = YearMonth.from(startDate);
        YearMonth endYM = YearMonth.from(endDate);
        YearMonth currentYM = startYM;

        while (!currentYM.isAfter(endYM)) {
            monthlySummaryMap.put(currentYM, new MonthlySummary(0.0, 0.0));
            currentYM = currentYM.plusMonths(1);
        }

        // 遍历交易数据，按照月份汇总收入和支出
        for (Transaction transaction : transactions) {
            LocalDate date = transaction.getDateTime().toLocalDate();
            YearMonth transactionYM = YearMonth.from(date);

            // 判断交易日期是否在范围内
            if ((transactionYM.equals(startYM) || transactionYM.isAfter(startYM)) &&
                    (transactionYM.equals(endYM) || transactionYM.isBefore(endYM))) {

                // 获取对应月份的汇总对�?
                MonthlySummary summary = monthlySummaryMap.get(transactionYM);

                if (summary == null) {
                    // 如果月份不存在于映射中，初始化一个新�?
                    summary = new MonthlySummary(0.0, 0.0);
                    monthlySummaryMap.put(transactionYM, summary);
                }

                String monthStr = String.format("%02d", transactionYM.getMonthValue());

                // 累加收入或支�?
                if (transaction.getType() == Transaction.Type.INCOME) {
                    summary.income += transaction.getAmount();
                    System.out.println("累加收入�?" + transaction.getAmount() + "�?"
                            + transactionYM.getYear() + "�?" + monthStr + "�?"
                            + "总收入：" + summary.income);
                } else if (transaction.getType() == Transaction.Type.EXPENSE) {
                    summary.expense += transaction.getAmount();
                    System.out.println("累加支出�?" + transaction.getAmount() + "�?"
                            + transactionYM.getYear() + "�?" + monthStr + "�?"
                            + "总支出：" + summary.expense);
                }
            } else {
                System.out.println("交易不在时间范围内，跳过�?" + transaction);
            }
        }

        return monthlySummaryMap;
    }

    // 5个组件刷新总函�?
    private void refreshAllPanels() {
        if (currentUser == null) {
            clearAllPanels();
            return;
        }
        updateUserPhoto();
        updateUserInfo();
        refreshTransactionTable();
        updateBalance();
        updateStatistics("最�?12个月"); // 或根据需要传入的时间范围
    }

    // 组件1更新用户照片
    private void updateUserPhoto() {
        if (currentUser != null) {
            loadUserPhoto(currentUser); // 加载当前用户的照�?
        }
    }

    // 组件2更新用户信息
    private void updateUserInfo() {
        if (currentUser != null && valueLabels != null) {
            valueLabels[0].setText(currentUser.getStudentId());
            valueLabels[1].setText(currentUser.getName());
            valueLabels[2].setText(currentUser.getIdNumber());
            valueLabels[3].setText(currentUser.getClassName());
        }
    }

    // 组件3更新表格
    private void refreshTransactionTable() {
        transactionTableModel.setRowCount(0);
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

        for (Transaction transaction : accountManager.getUserTransactions(currentUser.getStudentId())) {
            transactionTableModel.addRow(new Object[] {
                    transaction.getDateTime().format(formatter),
                    transaction.getType(),
                    transaction.getCategory(),
                    String.format("%.2f", transaction.getAmount()),
                    transaction.getPaymentMethod(),
                    transaction.getDescription()
            });
        }
    }

    // 组件4余额更新
    private void updateBalance() {
        double balance = accountManager.calculateBalance(currentUser.getStudentId());
        balanceLabel.setText(String.format("当前余额：�?%.2f", balance));
    }

    // 清除所有面板信�?
    private void clearAllPanels() {
        photoLabel.setIcon(null);
        Component[] components = ((JPanel) userPanel.getComponent(0)).getComponents();
        for (Component component : components) {
            if (component instanceof JLabel) {
                ((JLabel) component).setText("");
            }
        }
    }

}
