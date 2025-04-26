
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class DataManager {
    // 预置文件名
    private static final String TRANSACTIONS_FILE_PATTERN = "transactions_%s.csv";
    // 预置解析数据格式
    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

    // 没啥用
    public DataManager() {

    }

    // 获取用户csv文件文件名
    private String getTransactionsFileName(String userId) {
        return String.format(TRANSACTIONS_FILE_PATTERN, userId);
    }

    // 保存交易记录
    public void saveTransactions(List<Transaction> transactions) {
        if (transactions.isEmpty()) {
            return;
        }

        // 获取用户ID名称
        String userId = transactions.get(0).getUserId();
        String fileName = getTransactionsFileName(userId);

        try (PrintWriter writer = new PrintWriter(new FileWriter(fileName))) {
            // 写入CSV头
            writer.println("userId,dateTime,type,category,amount,paymentMethod,description");

            // 写入数据
            for (Transaction transaction : transactions) {
                writer.println(String.format("%s,%s,%s,%s,%.2f,%s,%s",
                        transaction.getUserId(),
                        transaction.getDateTime().format(DATE_FORMATTER),
                        transaction.getType(),
                        transaction.getCategory(),
                        transaction.getAmount(),
                        transaction.getPaymentMethod(),
                        transaction.getDescription().replace(",", ";")));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // 用户登录时读取历史数据
    public List<Transaction> loadTransactions(String userId) {
        List<Transaction> transactions = new ArrayList<>();
        String fileName = getTransactionsFileName(userId);
        File file = new File(fileName);

        if (!file.exists()) {
            System.out.println("文件不存在: " + fileName);
            createFileIfNotExists(fileName);
            return transactions;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            // 跳过CSV头行
            String line;
            while ((line = reader.readLine()) != null) {
                try {
                    // 使用更可靠的CSV分割方法
                    String[] parts = splitCSVLine(line);
                    if (parts.length < 7) {
                        System.out.println("无效的CSV行（字段数量不足）: " + line);
                        continue;
                    }

                    // 解析每个字段
                    String id = parts[0].trim();

                    // 使用预定义的日期时间格式解析
                    LocalDateTime dateTime = LocalDateTime.parse(parts[1].trim(), DATE_FORMATTER);

                    // 解析类型（收入/支出）
                    Transaction.Type type = Transaction.Type.fromDescription(parts[2].trim());
                    if (type == null) {
                        System.out.println("无效的交易类型: " + parts[2]);
                        continue;
                    }

                    // 解析类别
                    Transaction.Category category = Transaction.Category.fromDescription(parts[3].trim());
                    if (category == null) {
                        System.out.println("无效的交易类别: " + parts[3]);
                        continue;
                    }

                    // 解析金额
                    double amount;
                    try {
                        amount = Double.parseDouble(parts[4].trim());
                    } catch (NumberFormatException e) {
                        System.out.println("无效的金额格式: " + parts[4]);
                        continue;
                    }

                    // 解析支付方式
                    Transaction.PaymentMethod paymentMethod = Transaction.PaymentMethod
                            .fromDescription(parts[5].trim());
                    if (paymentMethod == null) {
                        System.out.println("无效的支付方式: " + parts[5]);
                        continue;
                    }

                    // 处理描述中的分号（之前保存时将逗号替换为分号）
                    String description = parts[6].trim().replace(";", ",");

                    // 创建交易记录对象
                    Transaction transaction = new Transaction(
                            id, type, category, amount, dateTime, paymentMethod, description);
                    transactions.add(transaction);

                } catch (DateTimeParseException e) {
                    System.err.println("日期时间格式解析错误: " + line);
                    System.err.println("错误详情: " + e.getMessage());
                } catch (Exception e) {
                    System.err.println("解析交易记录时出错: " + line);
                    System.err.println("错误详情: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            System.err.println("读取文件时出错: " + fileName);
            e.printStackTrace();
        }

        // 按时间排序
        Collections.sort(transactions, (t1, t2) -> t2.getDateTime().compareTo(t1.getDateTime()));

        return transactions;
    }

    // 处理存进去的每行数据分词
    private String[] splitCSVLine(String line) {
        List<String> result = new ArrayList<>();
        boolean inQuotes = false;
        StringBuilder field = new StringBuilder();

        for (char c : line.toCharArray()) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                result.add(field.toString());
                field = new StringBuilder();
            } else {
                field.append(c);
            }
        }
        result.add(field.toString());

        return result.toArray(new String[0]);
    }

    // 导出交易记录到CSV
    public void exportTransactionsToCSV(String userId, String fileName) {
        List<Transaction> transactions = loadTransactions(userId);
        try (PrintWriter writer = new PrintWriter(new FileWriter(fileName))) {
            // 写入CSV头
            writer.println("日期时间,类型,类别,金额,支付方式,描述");

            // 写入数据
            for (Transaction transaction : transactions) {
                writer.println(String.format("%s,%s,%s,%.2f,%s,%s",
                        transaction.getDateTime().format(DATE_FORMATTER),
                        transaction.getType(),
                        transaction.getCategory(),
                        transaction.getAmount(),
                        transaction.getPaymentMethod(),
                        transaction.getDescription().replace(",", ";")));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // 注册的时候自动生成该用户的csv文件
    public void createTransactionFileForNewUser(String userId) {
        String fileName = getTransactionsFileName(userId);
        createFileIfNotExists(fileName);
    }

    // 生成csv文件
    private void createFileIfNotExists(String fileName) {
        try {
            File file = new File(fileName);
            if (!file.exists()) {
                // 确保父目录存在
                File parentFile = file.getParentFile();
                if (parentFile != null && !parentFile.exists()) {
                    parentFile.mkdirs();
                }

                // 创建文件并写入CSV头
                try (PrintWriter writer = new PrintWriter(new FileWriter(file))) {
                    writer.println("userId,dateTime,type,category,amount,paymentMethod,description");
                }
                System.out.println("已创建新的交易记录文件: " + fileName);
            }
        } catch (IOException e) {
            System.err.println("创建文件失败: " + fileName);
            e.printStackTrace();
        }
    }

}
