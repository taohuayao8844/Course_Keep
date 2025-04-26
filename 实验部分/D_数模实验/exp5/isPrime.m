function result = isPrime(n)
%输入n返回一个布尔变量
    if n<=1
        result = false;
    return;
    end
    for i = 2:sqrt(n)
        if mod(n,i) == 0
            result = false;
            return
        end
    end
    result = true;
end

