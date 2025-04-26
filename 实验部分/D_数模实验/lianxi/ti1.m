% 定义数据集
data = [10, 12, 11, 13, 15, 14, 12, 11, 10, 13];

% 计算均值和标准差
mean_value = mean(data);
std_dev = std(data);

% 计算 3σ 范围
lower_bound = mean_value - 3 * std_dev;
upper_bound = mean_value + 3 * std_dev;

% 检查数据是否在 3σ 范围内
out_of_range = data(data < lower_bound | data > upper_bound);

% 显示结果
disp(['均值: ', num2str(mean_value)]);
disp(['标准差: ', num2str(std_dev)]);
disp(['3σ 范围: [', num2str(lower_bound), ', ', num2str(upper_bound), ']']);
disp('超出 3σ 范围的数据点:');
disp(out_of_range);
