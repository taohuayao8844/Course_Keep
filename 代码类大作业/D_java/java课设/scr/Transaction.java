

import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.List;

public class Transaction implements Serializable {

    // 收入支出大类
    public enum Type {
        INCOME("收入"),
        EXPENSE("支出");

        private final String description;

        Type(String description) {
            this.description = description;
        }

        public String getDescription() {
            return description;
        }

        @Override
        public String toString() {
            return description;
        }

        public static Type fromDescription(String description) {
            for (Type type : values()) {
                if (type.getDescription().equals(description)) {
                    return type;
                }
            }
            throw new IllegalArgumentException("未知的类�?: " + description);
        }
    }

    // 收入和支出的两个大类包含的小�?
    public enum Category {
        // 支出类别
        CLOTHING("服装"),
        FOOD("饮食"),
        COMMUNICATION("通讯"),
        TRANSPORTATION("交�?"),
        // 收入类别
        PART_TIME("兼职"),
        SCHOLARSHIP("奖学�?"),
        ALLOWANCE("生活�?"),
        OTHERS("其他");

        private final String description;

        Category(String description) {
            this.description = description;
        }

        public String getDescription() {
            return description;
        }

        @Override
        public String toString() {
            return description;
        }

        public static Category fromDescription(String description) {
            for (Category category : values()) {
                if (category.getDescription().equals(description)) {
                    return category;
                }
            }
            throw new IllegalArgumentException("未知的类�?: " + description);
        }

        // 获取所有支出类�?
        public static List<Category> getExpenseCategories() {
            return Arrays.asList(CLOTHING, FOOD, COMMUNICATION, TRANSPORTATION);
        }

        // 获取所有收入类�?
        public static List<Category> getIncomeCategories() {
            return Arrays.asList(PART_TIME, SCHOLARSHIP, ALLOWANCE, OTHERS);
        }
    }

    // 收入和支出的途径
    public enum PaymentMethod {
        ALIPAY("支付�?"),
        WECHAT("微信"),
        BANK_TRANSFER("银行转账");

        private final String description;

        PaymentMethod(String description) {
            this.description = description;
        }

        public String getDescription() {
            return description;
        }

        @Override
        public String toString() {
            return description;
        }

        public static PaymentMethod fromDescription(String description) {
            for (PaymentMethod method : values()) {
                if (method.getDescription().equals(description)) {
                    return method;
                }
            }
            throw new IllegalArgumentException("未知的支付方�?: " + description);
        }
    }

    private String userId;// 用户id
    private Type type;// 支出or收入
    private Category category;// 花在什么地方了
    private double amount;// 金额
    private LocalDateTime dateTime;// 时间
    private PaymentMethod paymentMethod;// 支付方式
    private String description;//备注

    //构建Transaction类方�?
    public Transaction(String userId, Type type, Category category, double amount,
            LocalDateTime dateTime, PaymentMethod paymentMethod, String description) {
        this.userId = userId;
        this.type = type;
        this.category = category;
        this.amount = amount;
        this.dateTime = dateTime;
        this.paymentMethod = paymentMethod;
        this.description = description;
    }

    // GET
    public String getUserId() {return userId;}
    public Type getType() {return type;}
    public Category getCategory() { return category;}
    public double getAmount() {return amount;}
    public LocalDateTime getDateTime() {return dateTime;}
    public PaymentMethod getPaymentMethod() {return paymentMethod;}
    public String getDescription() {return description;}
    @Override
    public String toString() {
        return String.format(
                "Transaction{userId='%s', dateTime=%s, type=%s, category=%s, amount=%.2f, paymentMethod=%s, description='%s'}",
                userId, dateTime, type, category, amount, paymentMethod, description);
    }
}
