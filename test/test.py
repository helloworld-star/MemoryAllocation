import numpy as np


def read_file_to_2d_array(file_name, values_per_line):
    """
    从文本文件中读取数据，并转换为二维数组。
    
    :param file_name: 要读取的文件名
    :param values_per_line: 每行数据的数量
    :return: 转换后的二维数组
    """
    with open(file_name, "r") as f:
        data = []
        for line in f:
            row = [int(x) for x in line.strip().split()]
            if len(row) == values_per_line:
                data.append(row)
    
    # Transfer to 2D array
    array_2d = np.array(data, dtype=np.uint64)
    return array_2d


# Set parameters
values_per_line = 3  # dimension of input and filter
input_file = "Input.txt"
filter_file = "Filter.txt"
output_file = "Output.txt"

# 读取数据
input_array = read_file_to_2d_array(input_file, values_per_line)
filter_array = read_file_to_2d_array(filter_file, values_per_line)
output_array = read_file_to_2d_array(output_file, 32)

# 打印读取结果

total_output = np.dot(input_array, filter_array.T) 
total_output = total_output % 256

file_name = "Output_py.txt"
with open(file_name, "w") as file:
    for line in total_output:
        file.write(f"{line}\n")

total_output = total_output.flatten()

for i in range(len(total_output)):
    if total_output[i] != output_array.flatten()[i]:
        print("Wrong!")
        break
    if i == len(total_output) - 1:
        print("Correct!")