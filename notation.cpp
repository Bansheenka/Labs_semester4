#include <iostream>
#include <string>
#include <stack>
#include <map>

struct Not
{
    std::stack<float> numbers; //стек, в котором будут храниться значения
    std::string input; //вводимая строка
    float a, b, c; //переменные, значения которых могут быть заданы отдельно
    float first = 0;
    float second = 0;
    float result = 0;
    std::map<std::string, int> koefs; //map для хранения переменных и их значений

    bool isSign(std::string inp) //функция проверки на то, является ли данная строка математическим знаком или нет
    {
        if (inp == "+" || inp == "-" || inp == "*" || inp == "/")
            return true;
        else
            return false;
    }

    float count() //функция подсчета значения выражения
    {
        while (std::cin.get() != '=') //считывание до тех пор, пока не будет встречен знак "="
        {
            std::cin >> input;
            if (input == "=")
                return result;
            if (!isSign(input))
            {
                try //проверка, чтобы не было возможности искать переменную, не хранящуюся в map
                {
                     numbers.push(koefs.at(input));
                }
                catch(const std::out_of_range &)
                {
                    numbers.push(std::stof(input));
                }
            }

            else
            {
                first = numbers.top();
                numbers.pop();
                second = numbers.top();
                numbers.pop();

                if (input == "+")
                    result = second + first;
                if (input == "-")
                    result = second - first;
                if (input == "*")
                    result = second * first;
                if (input == "/")
                    result = second / first;

                numbers.push(result);
            }
        }
    }

    void CinMemb () //функиця считывания переменных и добавления их в map
    {
        std::cin >> a >> b >> c;
        koefs.insert(std::pair<std::string,int>("a",a));
        koefs.insert(std::pair<std::string,int>("b",b));
        koefs.insert(std::pair<std::string,int>("c",c));

    }
};


int main()
{
    Not n;
    bool b = true; //булева переменная для прекращения работы программы
    std::string cont; //строка, вводимая пользователем для остановки программы
    do{ //один раз программа все равно обязана выполниться, затем в зависимости от значения флага b
        std::cout << "Are there some variables?" << std::endl;
        std::string answer;
        std::cin >> answer;
        if (answer == "Yes")
        {
            std::cout << "Enter values of variables: " << std::endl;
            n.CinMemb();
            std::cout << "Now enter your expression: " << std::endl;
        }
        float res = n.count();
        std::cout << "Result = " << res << std::endl;
        std::cin >> cont;
        if (cont == "exit") //для выхода из программы вводится "exit", при желании продолжить любая другая строка
            b = false;
    }
    while(b); //исполнять, пока пользователь не введет "exit", и значение флага не поменяется
    return 0;
}
