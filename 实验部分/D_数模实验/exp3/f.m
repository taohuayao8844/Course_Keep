function y = f(x)
    if x < 0 && x ~= -3
        y = x^2 + x - 6;
    elseif 0 <= x && x < 5 && x~=3 && x~=2
        y = x^2 - 5*x + 6;
    else
        y = x^2 - x - 1;
    end
end
