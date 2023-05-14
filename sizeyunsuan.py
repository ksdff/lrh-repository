import random

def generate_expression(operators, max_num, allow_decimal, allow_parentheses):
    """生成一个随机的四则运算表达式"""
    if allow_parentheses and random.random() > 0.5:
        # 一半的概率加括号
        left = generate_expression(operators, max_num, allow_decimal, False)
        right = generate_expression(operators, max_num, allow_decimal, False)
        operator = random.choice(operators)
        return f"({left} {operator} {right})"
    else:
        left = random.randint(1, max_num) if not allow_decimal else round(random.uniform(1, max_num), 1)
        right = random.randint(1, max_num) if not allow_decimal else round(random.uniform(1, max_num), 1)
        operator = random.choice(operators)
        return f"{left} {operator} {right}"
    
def generate_exercise(num_exercises, operators, max_num, allow_decimal, allow_parentheses):
    """生成指定数量的四则运算题目"""
    exercises = []
    for i in range(num_exercises):
        exercises.append(generate_expression(operators, max_num, allow_decimal, allow_parentheses))
    return exercises

def output_to_file(exercises, filename):
    """将题目输出到文件"""
    with open(filename, "w") as f:
        for i, exercise in enumerate(exercises):
            f.write(f"{i + 1}. {exercise}\n")
    
def output_to_console(exercises):
    """将题目输出到控制台"""
    for i, exercise in enumerate(exercises):
        print(f"{i + 1}. {exercise}")

def main():
    """主函数"""
    # 用户输入
    num_exercises = int(input("请输入题目数量："))
    operators = input("请选择运算符（+、-、*、/），多个运算符用空格分隔：").split()
    max_num = int(input("请输入最大数："))
    allow_decimal = input("是否允许小数？（y/n）：").lower() == "y"
    allow_parentheses = input("是否允许加括号？（y/n）：").lower() == "y"
    output_to = input("请选择输出方式（file表示输出到文件，console表示输出到控制台）：").lower()
    if output_to == "file":
        filename = input("请输入输出文件名：")
        exercises = generate_exercise(num_exercises, operators, max_num, allow_decimal, allow_parentheses)
        output_to_file(exercises, filename)
        print(f"题目已输出到文件{filename}")
    elif output_to == "console":
        exercises = generate_exercise(num_exercises, operators, max_num, allow_decimal, allow_parentheses)
        output_to_console(exercises)
    else:
        print("无效的输出方式")

if __name__ == "__main__":
    main()