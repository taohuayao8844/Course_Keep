function wage = calculate_wage(work_hours)
    if work_hours > 120
        overtime_hours = work_hours - 120;
        wage = 120 * 84 + overtime_hours * 84 * 1.15;
    elseif work_hours < 60
        wage = work_hours * 84 - 700;
    else
        wage = work_hours * 84;
    end
end
