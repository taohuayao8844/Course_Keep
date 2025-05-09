# 实验内容
# 1.求最大公因数
# 给定两个整数a和b，计算其最大公因数。
# 2.扩展的欧几里得算法
# 输入两个整数a和b，利用扩展欧几里得算法计算其GCD，并输出对应的线性组合系数x和y。
# 3.模幂运算
# 给定整数a，m，n，使用快速幂算法计算 a的m次方modn。

# 第一问最大公因数
# 给出三种方法1、暴力穷举法 2、更相减损法 3、辗转相除法
# 1.暴力穷举法
def gcd_baoli(a, b):
    min_num = min(a, b)
    gcd = 1
    for i in range(1, min_num + 1):
        if a % i == 0 and b % i == 0:
            gcd = i
    return gcd

# 2.更相减损法
def gcd_xiangjian(a, b):
    while a != b:
        if a > b:
            a = a - b
        else:
            b = b - a
    return a

# 3.辗转相除法
def gcd_xiangchu(a, b):
    while b:
        a, b = b, a % b
    return a

## 拓展欧几里得算法
# 4.扩展的欧几里得算法
# 递归终止条件：当 a == 0 时，此时 gcd(a, b) = b ，满足 0 * x + b * y = b ，所以直接返回 (b, 0, 1) ，这里返回的三个值依次为最大公约数 g 、系数 x 、系数 y ，是递归回溯的起始值。
# 递归调用及系数传递：当 a != 0 时，进行递归调用 extended_gcd(b % a, a) 。假设递归调用返回 (g, y, x) ，这里的 g 是 gcd(b % a, a) ，也就是 gcd(a, b) ；y 和 x 是满足 (b % a) * y + a * x = g 的系数 。
# 然后根据推导公式 a * (x - (b // a) * y) + b * y = g ，将当前层计算得到的新 x 值（即 x - (b // a) * y ）和 y 值（就是递归返回的 y ）与最大公约数 g 一起返回 。
# 随着递归不断回溯，每一层计算得到的 x 和 y 会逐步传递到上一层，最终得到满足 a * x + b * y = gcd(a, b) 的 x 和 y 。
def extended_gcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = extended_gcd(b % a, a)
        return (g, x - (b // a) * y, y)

# 模幂运算
# 5.模幂运算
# 3^10=3*3*3*3*3*3*3*3*3*3
#
# //尽量想办法把指数变小来，这里的指数为10
#
# 3^10=(3*3)*(3*3)*(3*3)*(3*3)*(3*3)
#
# 3^10=(3*3)^5
#
# 3^10=9^5
#
# //此时指数由10缩减一半变成了5，而底数变成了原来的平方，求3^10原本需要执行10次循环操作，求9^5却只需要执行5次循环操作，但是3^10却等于9^5,我们用一次（底数做平方操作）的操作减少了原本一半的循环量，特别是在幂特别大的时候效果非常好，例如2^10000=4^5000,底数只是做了一个小小的平方操作，而指数就从10000变成了5000，减少了5000次的循环操作。
#
# //现在我们的问题是如何把指数5变成原来的一半，5是一个奇数，5的一半是2.5，但是我们知道，指数不能为小数，因此我们不能这么简单粗暴的直接执行5/2，然而，这里还有另一种方法能表示9^5
#
# 9^5=（9^4）*（9^1）
#
# //此时我们抽出了一个底数的一次方，这里即为9^1，这个9^1我们先单独移出来,剩下的9^4又能够在执行“缩指数”操作了，把指数缩小一半，底数执行平方操作
#
# 9^5=（81^2）*(9^1)
#
# //把指数缩小一半，底数执行平方操作
#
# 9^5=（6561^1）*(9^1)
#
# //此时，我们发现指数又变成了一个奇数1，按照上面对指数为奇数的操作方法，应该抽出了一个底数的一次方，这里即为6561^1，这个6561^1我们先单独移出来，但是此时指数却变成了0，也就意味着我们无法再进行“缩指数”操作了。
#
# 9^5=（6561^0）*(9^1)*(6561^1)=1*(9^1)*(6561^1)=(9^1)*(6561^1)=9*6561=59049
#
# 我们能够发现，最后的结果是9*6561，而9是怎么产生的？是不是当指数为奇数5时，此时底数为9。那6561又是怎么产生的呢？是不是当指数为奇数1时，此时的底数为6561。所以我们能发现一个规律：最后求出的幂结果实际上就是在变化过程中所有当指数为奇数时底数的乘积。
# ————————————————
# (a的m次方)modn

def mod_pow(a, m, n):
    result = 1
    a = a % n #取余先简略计算
    while m > 0:
        if m % 2 == 1:
            result = (result * a) % n #提出来依然可以使m变成两倍
        m = m >> 1
        a = (a * a) % n
    return result




if __name__ == "__main__":
    # 获取用户输入
    a = int(input("请输入整数a: "))
    b = int(input("请输入整数b: "))
    m = int(input("请输入整数m: "))
    n = int(input("请输入整数n: "))

    # 最大公因数
    print(f"暴力穷举法求 {a} 和 {b} 的最大公因数: {gcd_baoli(a, b)}")
    print(f"更相减损法求 {a} 和 {b} 的最大公因数: {gcd_xiangjian(a, b)}")
    print(f"辗转相除法求 {a} 和 {b} 的最大公因数: {gcd_xiangchu(a, b)}")

    # 扩展欧几里得算法
    g, x, y = extended_gcd(a, b)
    print(f"扩展欧几里得算法求 {a} 和 {b} 的 GCD: {g}，线性组合系数 x: {x}，y: {y}")

    # 模幂运算
    print(f"快速幂算法计算 {a}^{m} mod {n}: {mod_pow(a, m, n)}")