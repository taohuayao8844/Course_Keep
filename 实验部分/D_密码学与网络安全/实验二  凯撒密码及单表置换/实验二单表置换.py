class SubstitutionCipher:
    '''
    置换表类型定义
    '''
    def __init__(self):
        # 初始化原始字母表
        self.alphabet = 'abcdefghijklmnopqrstuvwxyz'
    #构建自己的初始变量
    def generate_substitution_table(self, keyword):
        '''
        生成加密后的置换表
        :param keyword:密钥
        :return: 置换后的置换表
        '''
        # 处理密钥词组，转换为大写并移除重复字符
        unique_chars = []#中继存储密钥词组
        for char in keyword.upper():
            if char not in unique_chars and char in self.alphabet.upper():
                unique_chars.append(char)
        # 按字母表顺序添加剩余字符
        for char in self.alphabet.upper():
            if char not in unique_chars:
                unique_chars.append(char)
        # 生成置换表
        substitution_table = {}
        for i, original_char in enumerate(self.alphabet):#生成：[(0, 'a'),..]即(i,'X')
            substitution_table[original_char] = unique_chars[i]#变成{'a':'X'}新的映射表
        return substitution_table

    def generate_decryption_table(self, keyword):
        '''
        生成解密用的逆置换表
        :param keyword: 密钥
        :return: 解密置换表
        '''
        # 生成加密置换表
        encrypt_table = self.generate_substitution_table(keyword)#字典操作
        # 创建逆置换表
        decrypt_table = {}
        for original, substituted in encrypt_table.items():
            decrypt_table[substituted] = original
        return decrypt_table#新的字典

    def encrypt(self, M, keyword):
        """使用置换表加密明文"""
        # 生成置换表
        table = self.generate_substitution_table(keyword)

        # 加密过程
        ciphertext = []
        for char in M:
            if char in table:
                ciphertext.append(table[char])
            else:
                ciphertext.append(char)
        return ''.join(ciphertext)

    def decrypt(self, ciphertext, keyword):
        """使用逆置换表解密密文"""
        # 生成逆置换表
        table = self.generate_decryption_table(keyword)

        # 解密过程
        plaintext = []
        for char in ciphertext:
            if char in table:
                plaintext.append(table[char])
            else:
                plaintext.append(char)

        return ''.join(plaintext)

if __name__ == "__main__":
    cipher = SubstitutionCipher()#新建一个类

    keyword = input("请输入加密的密钥:")
    M = input("请输入加密的明文:")

    # 生成置换表并打印
    encrypt_table = cipher.generate_substitution_table(keyword)
    print("加密置换表:")

    count = 0
    for original, substituted in encrypt_table.items():
        print(f"{original} -> {substituted}", end="\t")
        count += 1
        if count % 5 == 0:  # 每5个元素换行
            print()  # 仅换行
    if count % 5 != 0:
        print()  # 确保最后有换行符

    # 加密并打印结果
    C = cipher.encrypt(M, keyword)
    print(f"\n明文: {M}")
    print(f"密文: {C}")

    # 解密并打印结果
    decrypted_text = cipher.decrypt(C, keyword)
    print(f"解密后: {decrypted_text}")