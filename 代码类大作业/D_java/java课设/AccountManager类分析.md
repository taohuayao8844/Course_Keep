## 私有属性

1. **users**:
   - 类型：`Map<String, User>`
   - 描述：存储用户信息，键为学号，值为用户对象。
2. **transactions**:
   - 类型：`List<Transaction>`
   - 描述：存储交易记录的列表。
3. **TRANSACTIONS_FILE**:
   - 类型：`String`
   - 描述：交易记录存储的 CSV 文件名。
4. **DATE_FORMATTER**:
   - 类型：`DateTimeFormatter`
   - 描述：用于格式化和解析日期时间的格式化器。

### 构造方法

- AccountManager()
  - 初始化 `users` 和 `transactions`，并调用 `loadTransactions()` 方法加载交易记录。