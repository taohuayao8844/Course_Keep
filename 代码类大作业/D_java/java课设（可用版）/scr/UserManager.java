

import java.io.*;
import java.util.*;

public class UserManager {
    //用户名数据存储
    private static final String CSV_FILE = "users.csv";//不可变
    private Map<String, User> users;
    private User currentUser; // 当前用户对象
    
    public UserManager() {
        users = new HashMap<>();
        loadUsers();
    }

    public void addUser(User user) {
        users.put(user.getStudentId(), user);
        saveUsers();//将用户数据保存到 CSV 文件
    }

    public User getUser(String studentId) {
        return users.get(studentId);
    }

    public Collection<User> getAllUsers() {
        return users.values();
    }

    // 检查用户是否存在
    public boolean userExists(String studentId) {
        return users.containsKey(studentId);
    }

    // 修改密码
    public void changePassword(String studentId, String newPassword) {
        User user = users.get(studentId);
        if (user != null) {
            user.setPassword(newPassword);
            saveUsers();
        }
    }

    private void loadUsers() {
        File file = new File(CSV_FILE);
        if (!file.exists()) {
            return;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] data = line.split(",");
                if (data.length >= 5) {
                    User user = new User(data[0], data[1], data[2], data[3], data[4]);
                    users.put(user.getStudentId(), user);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void saveUsers() {
        try (PrintWriter writer = new PrintWriter(new FileWriter(CSV_FILE))) {
            for (User user : users.values()) {
                writer.println(String.format("%s,%s,%s,%s,%s",
                    user.getStudentId(),
                    user.getName(),
                    user.getIdNumber(),
                    user.getClassName(),
                    user.getPassword()
                ));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public boolean validateUser(String studentId, String password) {
        User user = users.get(studentId);
        return user != null && user.getPassword().equals(password);
    }

    public User getCurrentUser() {
        return currentUser;
    }
}
