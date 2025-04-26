function result = fn2(n)
%函数2
    result = 0;
    for i = 1:n
        result = result + (n + 1) * n;
    end
end