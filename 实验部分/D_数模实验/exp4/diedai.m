function [x_final, num_iterations] = diedai(a, b, x0, dx, max_iterations)
    % 参数:
    %   a, b: 常数
    %   x0: 初始值
    %   dx: 收敛条件
    %   max_iterations: 最大迭代次数
    
    x = x0;
    for n = 1:max_iterations
        x_new = (a / (b + x)) / 2;
        if abs(x_new - x) < dx
            x_final = x_new;
            num_iterations = n;
            fprintf('迭代收敛于 %.6f，迭代次数为 %d\n', x_final, num_iterations);
            return;
        end
        x = x_new;
    end
    x_final = x;
    num_iterations = max_iterations;
    fprintf('超过最大迭代次数,迭代结果为 %.6f\n', x_final);
end
