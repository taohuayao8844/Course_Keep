

import java.io.*;
import java.util.*;
import java.time.*;
import java.time.format.DateTimeFormatter;

public class AccountManager {
    private Map<String, User> users;
    private List<Transaction> transactions;
    private static final String TRANSACTIONS_FILE = "transactions.csv";
    private static final DateTimeFormatter DATE_FORMATTER = 
        DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
    
    public AccountManager() {
        users = new HashMap<>();
        transactions = new ArrayList<>();
        loadTransactions(); // 构造时加载交易记录
    }
    
    // 用户管理
    public void addUser(User user) {
        users.put(user.getStudentId(), user);
    }
    
    public User getUser(String studentId) {
        return users.get(studentId);
    }
    
    // 交易管理
    public void addTransaction(Transaction transaction) {
        transactions.add(transaction);
        saveTransactions(); // 添加交易后自动保�?
    }
    
    public void removeTransaction(int index) {
        if (index >= 0 && index < transactions.size()) {
            transactions.remove(index);
            saveTransactions(); // 删除交易后自动保�?
        }
    }
    
    // 获取用户的所有交�?
    public List<Transaction> getUserTransactions(String userId) {
        return transactions.stream()
            .filter(t -> t.getUserId().equals(userId))
            .toList();
    }
    
    // 设置用户的交易记�?
    public void setTransactions(List<Transaction> newTransactions) {
        if (newTransactions != null) {
            this.transactions = new ArrayList<>(newTransactions);
            saveTransactions(); // 设置新的交易列表后保�?
        }
    }
    
    // 计算用户余额
    public double calculateBalance(String userId) {
        return transactions.stream()
            .filter(t -> t.getUserId().equals(userId))
            .mapToDouble(t -> t.getType() == Transaction.Type.INCOME ? 
                        t.getAmount() : -t.getAmount())
            .sum();
    }
    
    // 保存交易记录到CSV文件
    public void saveTransactions() {
        try (PrintWriter writer = new PrintWriter(new FileWriter(TRANSACTIONS_FILE))) {
            // 写入CSV�?
            writer.println("UserId,Type,Category,Amount,DateTime,PaymentMethod,Description");
            
            // 写入每条交易记录
            for (Transaction t : transactions) {
                writer.printf("%s,%s,%s,%.2f,%s,%s,%s%n",
                    t.getUserId(),
                    t.getType(),
                    t.getCategory(),
                    t.getAmount(),
                    t.getDateTime().format(DATE_FORMATTER),
                    t.getPaymentMethod(),
                    t.getDescription().replace(",", ";") // 防止描述中的逗号影响CSV格式
                );
            }
        } catch (IOException e) {
            System.err.println("保存交易记录时出�?: " + e.getMessage());
        }
    }
    
    // 从CSV文件加载交易记录
    private void loadTransactions() {
        File file = new File(TRANSACTIONS_FILE);
        if (!file.exists()) {
            return; // 如果文件不存在，直接返回
        }
        
        transactions.clear(); // 清空现有记录
        
        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line = reader.readLine(); // 跳过表头
            
            while ((line = reader.readLine()) != null) {
                try {
                    String[] parts = line.split(",");
                    if (parts.length >= 7) {
                        Transaction transaction = new Transaction(
                            parts[0], // userId
                            Transaction.Type.valueOf(parts[1]), // type
                            Transaction.Category.valueOf(parts[2]), // category
                            Double.parseDouble(parts[3]), // amount
                            LocalDateTime.parse(parts[4], DATE_FORMATTER), // dateTime
                            Transaction.PaymentMethod.valueOf(parts[5]), // paymentMethod
                            parts[6] // description
                        );
                        transactions.add(transaction);
                    }
                } catch (Exception e) {
                    System.err.println("解析交易记录行时出错: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            System.err.println("加载交易记录时出�?: " + e.getMessage());
        }
    }
    
    // 获取所有交易记�?
    public List<Transaction> getAllTransactions() {
        return new ArrayList<>(transactions);
    }
}
