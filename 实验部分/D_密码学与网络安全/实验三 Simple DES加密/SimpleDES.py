#IP变化 Initial Permutationn
class IP_box:
    def __init__(self,In_length,Out_order):
        self.In_length = In_length
        self.Out_order = Out_order
    def use(self,input):
        out=[input[i-1]for i in self.Out_order]
        return out

class S_box:
    def __init__(self,table):
        self.table = table
    def use(self,input_data):
        '''
        根据S盒进行变换
        :param input:4位输入
        :return:2位输出
        '''
        row = int(input_data[0] + input_data[3], 2)
        col = int(input_data[1] + input_data[2], 2)
        output_data = self.table[row][col]
        return list(bin(output_data)[2:].zfill(2))


#子密钥生成 Key Generation
class KeyGenerator:
    def __init__(self):
        self.P10 = IP_box(10,[3,5,2,7,4,10,1,9,8,6])
        self.P8 = IP_box(10,[6,3,7,4,8,5,10,9])
        self.LShift1= IP_box(5,[2,3,4,5,1])
        self.LShift2= IP_box(5,[3,4,5,1,2])#左移2位

    def use(self, key):
        x = self.P10.use(key)
        left, right = x[:5], x[5:]
        # 第一次左移1位
        left,right = self.LShift1.use(left),self.LShift1.use(right)
        x1 = left + right
        key1 = self.P8.use(x1)
        # 第二次左移2位
        left,right = self.LShift2.use(left),self.LShift2.use(right)
        x2 = left + right
        key2 = self.P8.use(x2)
        return key1, key2

#轮函数 Round Function
class RoundFunction:
    def __init__(self):
        self.EP=IP_box(4,[4,1,2,3,2,3,4,1])
        self.SBox0=S_box([[1, 0, 3, 2], [3, 2, 1, 0], [0, 2, 1, 3], [3, 1, 3, 2]])
        self.SBox1=S_box([[0,1,2,3],[2,0,1,3],[3,0,1,0],[2,1,0,3]])
        self.P4=IP_box(4,[2,4,3,1])

    def xor_list(self, l1, l2):
        return [str(int(a) ^ int(b)) for a, b in zip(l1, l2)]

    def use(self,input,subkey):
        x=self.EP.use(input)
        x_str = "".join(x)
        # print("EP后为:" +x_str)
        x=self.xor_list(x_str,subkey)
        # print("异或后为:"+"".join(x))
        xleft,xright=x[:4],x[4:]#取出左右部分

        xleft=self.SBox0.use(xleft)
        # print("S0和为:"+"".join(xleft))
        xright=self.SBox1.use(xright)
        # print("S1和为:"+"".join(xright))

        x=self.P4.use(xleft+xright)
        # print("P4后为:"+"".join(x))
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



#加密类
class Simple_DES:
    def __init__(self):
        self.keygenerate = KeyGenerator()
        self.IP = IP_box(8, [2,6,3,1,4,8,5,7])
        self.IP_inv = IP_box(8, [4,1,3,5,7,2,8,6])
        self.roundF = RoundFunction()

    def xor_list(self, l1, l2):
        return [str(int(a) ^ int(b)) for a, b in zip(l1, l2)]

    def encrypt(self, M, key):
        key1, key2 = self.keygenerate.use(key)
        print("生成的密钥1为:" + "".join(key1))
        print("生成的密钥2为:" + "".join(key2))

        x = self.IP.use(M)
        print("IP变化后的数据为:" + "".join(x))
        left, right = x[:4], x[4:]
        #对右半部分进行处理
        step=self.roundF.use(right, key1)
        #进行异或
        step1 = self.xor_list(step, left)
        print("异或结果为:" + "".join(step1))
        # 注意 step1 = 左右拼接
        step1 = step1 + right
        print("拼接结果为:" + "".join(step1))
        #开始第二次
        #交换SW
        left, right = step1[4:], step1[:4]
        # 对右半部分进行处理
        step = self.roundF.use(right, key2)
        # 进行异或
        step2 = self.xor_list(step, left)
        print("异或结果为:" + "".join(step2))
        # 注意 step1 = 左右拼接
        step2 = step2 + right
        print("拼接结果为:" + "".join(step2))

        out = self.IP_inv.use(step2)
        return out

    def decrypt(self, C, key):
        key1, key2 = self.keygenerate.use(key)
        x = self.IP.use(C)
        left, right = x[:4], x[4:]
        step = self.roundF.use(right, key2)
        step1 = self.xor_list(step, left)
        step1 = step1 + right
        left, right = step1[4:], step1[:4]
        step = self.roundF.use(right, key1)
        step2 = self.xor_list(step, left)
        step2 = step2 + right
        out = self.IP_inv.use(step2)
        return out


if __name__ == '__main__':
    C = input("请输入要加密的单个明文字符:")
    C_bin = char_to_binary(C)
    print("要加密的明文为:" + C_bin)

    key = "1010000010"
    print("密钥为:" + str(key))

    sdes=Simple_DES()
    #加密
    cipher_text=sdes.encrypt(C_bin,key)
    print("加密的密文为:"+"".join(cipher_text))
    encrypt_text=sdes.decrypt(cipher_text,key)
    print("解密的密文为:" + "".join(encrypt_text))
    print("解密的密文ASCII为:"+binary_to_char("".join(encrypt_text)))