

import java.io.Serializable;

public class User implements Serializable {
    private String studentId;      //学号
    private String name;          // 姓名
    private String idNumber;      // 身份证号
    private String className;     // 班级
    private String password;      // 登录密码
    private String photoPath;     //照片路径
    
    public User(String studentId, String name, String idNumber, String className, String password) {
        this.studentId = studentId;
        this.name = name;
        this.idNumber = idNumber;
        this.className = className;
        this.password = password;
        this.photoPath = String.format("picture\\%s.jpg", studentId);
    }
    
    // 对外
    public String getStudentId() { return studentId; }
    public void setStudentId(String studentId) { this.studentId = studentId; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getIdNumber() { return idNumber; }
    public void setIdNumber(String idNumber) { this.idNumber = idNumber; }
    public String getClassName() { return className; }
    public void setClassName(String className) { this.className = className; }
    public String getPassword() { return password; }
    public void setPassword(String password) { this.password = password; }
    public String getPhotoPath() {return photoPath;}
    public void setPhotoPath(String photoPath) {this.photoPath = photoPath;}
    @Override
    public String toString() {
        return name + " (" + studentId + ")";
    }
}
