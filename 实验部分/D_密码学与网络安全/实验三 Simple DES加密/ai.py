# IP变化 Initial Permutationn
class IP_box:
    def __init__(self, In_length, Out_order):
        self.In_length = In_length
        self.Out_order = Out_order

    def use(self, input):
        out = [input[i - 1] for i in self.Out_order]
        return out


class S_box:
    def __init__(self, table):
        self.table = table

    def use(self, input_data):
        '''
        根据S盒进行变换
        :param input:4位输入
        :return:2位输出
        '''
        row = int(input_data[0] + input_data[3], 2)
        col = int(input_data[1] + input_data[2], 2)
        output_data = self.table[row][col]
        return bin(output_data).zfill(2)


# 子密钥生成 Key Generation
class KeyGenerator:
    def __init__(self):
        self.P10 = IP_box(10, [3, 5, 2, 7, 4, 10, 1, 9, 8, 6])
        self.P8 = IP_box(8, [6, 3, 7, 4, 8, 5, 10, 9])
        self.LShift1 = IP_box(5, [2, 3, 4, 5, 1])
        self.LShift2 = IP_box(5, [2, 3, 4, 5, 1])

    def use(self, key):
        x = self.P10.use(key)
        left, right = self.LShift1.use(x[:5]), self.LShift2.use(x[5:])
        x = left + right
        key1 = self.P8.use(x)
        left, right = self.LShift1.use(left), self.LShift2.use(right)
        x = left + right
        key2 = self.P8.use(x)
        return key1, key2


# 轮函数 Round Function
class RoundFunction:
    def __init__(self):
        self.EP = IP_box(4, [4, 1, 2, 3, 2, 3, 4, 1])
        self.SBox1 = S_box([[1, 0, 3, 2], [3, 2, 1, 0], [0, 2, 1, 3], [3, 1, 3, 2]])
        self.SBox2 = S_box([[0, 1, 2, 3], [2, 0, 1, 3], [3, 0, 1, 0], [2, 1, 0, 3]])
        self.P4 = IP_box(4, [2, 4, 3, 1])

    def xor_strings(self, s1, s2):
        """对两个二进制字符串进行逐位异或"""
        return ''.join('1' if b1 != b2 else '0' for b1, b2 in zip(s1, s2))

    def use(self, input, subkey):
        x = self.EP.use(input)
        # 将整数列表转换为字符串
        x_str = "".join(str(bit) for bit in x)
        # 将子密钥列表转换为字符串
        subkey_str = "".join(map(str, subkey))
        # 使用自定义的xor_strings函数进行异或运算
        x_xor = self.xor_strings(x_str, subkey_str)
        x_left, x_right = x_xor[:4], x_xor[4:]
        x_left = self.SBox1.use(x_left)
        x_right = self.SBox2.use(x_right)
        # 将S盒输出的字符串转换为列表
        x = self.P4.use(list(x_left + x_right))
        return x


def char_to_binary(char: str) -> str:
    '''
    将字符转为ASCII码后转化为二进制
    :param char:字符
    :return:二进制的字符
    '''
    if len(char) != 1:
        raise ValueError("输入必须是单个字符")
    # 获取 ASCII 码
    ascii_code = ord(char)
    # 转换为 8 位二进制字符串
    binary_str = bin(ascii_code)[2:].zfill(8)
    return binary_str


def binary_to_char(binary_str):
    ascii_code = chr(int(binary_str, 2))
    return ascii_code


# 加密类
class Simple_DES:
    def __init__(self):
        self.keygenerate = KeyGenerator()
        self.IP = IP_box(8, [2, 6, 3, 1, 4, 8, 5, 7])
        self.IP_inv = IP_box(8, [4, 1, 3, 5, 7, 2, 8, 6])
        self.roundF = RoundFunction()

    def xor_strings(self, s1, s2):
        """对两个二进制字符串进行逐位异或"""
        return ''.join('1' if b1 != b2 else '0' for b1, b2 in zip(s1, s2))

    def encrypt(self, M, key):
        # 将字符串明文转换为列表
        M_list = [int(bit) for bit in M]
        key1, key2 = self.keygenerate.use(key)
        x = self.IP.use(M_list)
        left, right = x[:4], x[4:]
        # 轮函数处理
        f1 = self.roundF.use(right, key1)
        # 将列表转换为字符串进行异或
        left_str = "".join(map(str, left))
        f1_str = "".join(map(str, f1))
        step1_left = self.xor_strings(left_str, f1_str)
        step1 = [int(bit) for bit in step1_left] + right  # 合并左右部分
        print("第一轮:" + "".join(str(bit) for bit in step1))
        # 第二轮
        f2 = self.roundF.use(step1[4:], key2)
        step1_left_str = "".join(map(str, step1[:4]))
        f2_str = "".join(map(str, f2))
        step2_left = self.xor_strings(step1_left_str, f2_str)
        step2 = [int(bit) for bit in step2_left] + step1[4:]

        # 最终置换
        out = self.IP_inv.use(step2)
        return "".join(map(str, out))

    def decrypt(self, C, key):
        # 将字符串密文转换为列表
        C_list = [int(bit) for bit in C]
        key1, key2 = self.keygenerate.use(key)
        x = self.IP.use(C_list)
        left, right = x[:4], x[4:]

        # 第一轮（使用key2）
        f1 = self.roundF.use(right, key2)
        left_str = "".join(map(str, left))
        f1_str = "".join(map(str, f1))
        step1_left = self.xor_strings(left_str, f1_str)
        step1 = [int(bit) for bit in step1_left] + right

        # 第二轮（使用key1）
        f2 = self.roundF.use(step1[4:], key1)
        step1_left_str = "".join(map(str, step1[:4]))
        f2_str = "".join(map(str, f2))
        step2_left = self.xor_strings(step1_left_str, f2_str)
        step2 = [int(bit) for bit in step2_left] + step1[4:]

        # 最终置换
        out = self.IP_inv.use(step2)
        return "".join(map(str, out))


if __name__ == '__main__':
    C = input("请输入要加密的单个明文字符: ")
    C_bin = char_to_binary(C)
    print("要加密的明文为: " + C_bin)

    key = [1, 0, 1, 0, 0, 0, 0, 0, 1, 0]
    print("密钥为: " + str(key))
    sdes = Simple_DES()

    # 加密
    cipher_text = sdes.encrypt(C_bin, key)
    print("加密的密文为: " + cipher_text)

    # 解密（验证）
    plain_text = sdes.decrypt(cipher_text, key)
    print("解密的明文为: " + plain_text)
    print("原始字符: " + C + ", 解密字符: " + binary_to_char(plain_text))