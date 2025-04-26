function [x, y] = line_solution(A, b)
    [m, n] = size(A);
    
    if norm(b) > 0
        if rank(A) == rank([A, b])
            if rank(A) == n
                disp('原方程组有唯一解 x');
                x = A\b;
                y = [];
            else
                disp('原方程组有无穷个解, 特解为 x, 其齐次方程组的基础解系为 y');
                x = A\b
                y = null(A, 'r')
            end
        else
            disp("无解");
            x = [];
            y = [];
        end
    else
        disp("零解 x");
        x = zeros(n, 1);
        if rank(A) < n
            disp("无穷个解, 基础解系为");
            y = null(A, 'rational');
        else
            y = [];
        end
    end
end
