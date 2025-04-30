def caesar_cipher_encrypt(M, k):
    '''
    使用凯撒密码对明文进行加密
    :param M:明文
    :param k:偏移量
    :return:加密完成的明文C分别为大小写不变、大小写互换、全大写、全小写
    '''
    C = ""
    shift = k % 26
    for i in M:
        if i.islower():
            newchar = chr((ord(i) - ord("a") + shift) % 26 + ord("a"))
        elif i.isupper():
            newchar = chr((ord(i) - ord("A") + shift) % 26 + ord("A"))
        else:
            newchar = i
        C += newchar
    return C
def swap_letter(C):
    '''
    将字符串中的小写变成大写，大写变成小写
    :param C:字符串
    :return:转换后的字符串
    '''
    result = ""
    for char in C:
        if char.islower():
            result += char.upper()
        elif char.isupper():
            result += char.lower()
        else:
            result += char
    return result

def ceasar_cipher_decrypt(C, k):
    '''
    对凯撒加密进行解密
    :param C:加密后的密文
    :param k: 偏移量
    :return: 解密后的密文
    '''
    M = ""
    shift = k % 26
    for i in C:
        if i.islower():
            newchar = chr((ord(i) - ord("a") - shift) % 26 + ord("a"))
        elif i.isupper():
            newchar = chr((ord(i) - ord("A") - shift) % 26 + ord("A"))
        else:
            newchar = i
        M += newchar
    return M



if __name__ == '__main__':
    M = input("请输入明文字符串:")
    k = int(input("请输入偏移量K:"))
    C = caesar_cipher_encrypt(M, k)
    M1 = ceasar_cipher_decrypt(C,k)
    print("加密完成的密码(大小写不变)是:" + C)
    print("加密完成的密码(大小写互换)是:" + swap_letter(C))
    print("加密完成的密码(全大写)是:" + C.upper())
    print("加密完成的密码(大小写不变)是:" + C.lower())

    print("针对大小写不变的凯撒加密的解密后的明文为:"+M1)
    if M == M1:
        print("加密解密正确")
