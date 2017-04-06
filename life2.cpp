#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <conio.h>

struct map
{
    std::vector<std::vector<char>> field, newField; //переменные, хранящие в себе новое и старое поля
    int x, y; //размер поля
    map(int _x, int _y)//конструктор
    {
        x = _x;
        y = _y;
        field.resize(x);
        newField.resize(x);
        for (int i = 0; i < x; ++i)
        {
            field[i].resize(y);
            newField[i].resize(y);
        }
    }

    int countAlive(int x, int y) //функция, подсчитывающая, сколько вокруг ячеек со значением "a" (Alive)
    {
        int countAlive = 0;
        if (field[(x+field.size()-1)%field.size()][y] == 'a') countAlive++;
        if (field[(x+field.size()-1)%field.size()][(y+field[x].size()-1)%field[x].size()] == 'a') countAlive++;
        if (field[(x+field.size()-1)%field.size()][(y+1)%field[x].size()] == 'a') countAlive++;
        if (field[x][(y+field[x].size()-1)%field[x].size()] == 'a') countAlive++;
        if (field[x][(y+1)%field[x].size()] == 'a') countAlive++;
        if (field[(x+1)%field.size()][(y+field[x].size()-1)%field[x].size()] == 'a') countAlive++;
        if (field[(x+1)%field.size()][y] == 'a') countAlive++;
        if (field[(x+1)%field.size()][(y+1)%field[x].size()] == 'a') countAlive++;
        return countAlive;
    }

    int countInfected(int x, int y) //функция, подсчитывающая, сколько вокруг ячеек со значением "i" (Infected)
    {
        int countInfected = 0;

        if (field[(x+field.size()-1)%field.size()][y] == 'i') countInfected++;
        if (field[(x+field.size()-1)%field.size()][(y+field[x].size()-1)%field[x].size()] == 'i') countInfected++;
        if (field[(x+field.size()-1)%field.size()][(y+1)%field[x].size()] == 'i') countInfected++;
        if (field[x][(y+field[x].size()-1)%field[x].size()] == 'i') countInfected++;
        if (field[x][(y+1)%field[x].size()] == 'i') countInfected++;
        if (field[(x+1)%field.size()][(y+field[x].size()-1)%field[x].size()] == 'i') countInfected++;
        if (field[(x+1)%field.size()][y] == 'i') countInfected++;
        if (field[(x+1)%field.size()][(y+1)%field[x].size()] == 'i') countInfected++;
        return countInfected;
    }

    int countZombie(int x, int y)//функция, подсчитывающая, сколько вокруг ячеек со значением "z" (zombie)
    {
        int countZombie = 0;

        if (field[(x+field.size()-1)%field.size()][y] == 'z') countZombie++;
        if (field[(x+field.size()-1)%field.size()][(y+field[x].size()-1)%field[x].size()] == 'z') countZombie++;
        if (field[(x+field.size()-1)%field.size()][(y+1)%field[x].size()] == 'z') countZombie++;
        if (field[x][(y+field[x].size()-1)%field[x].size()] == 'z') countZombie++;
        if (field[x][(y+1)%field[x].size()] == 'z') countZombie++;
        if (field[(x+1)%field.size()][(y+field[x].size()-1)%field[x].size()] == 'z') countZombie++;
        if (field[(x+1)%field.size()][y] == 'z') countZombie++;
        if (field[(x+1)%field.size()][(y+1)%field[x].size()] == 'z') countZombie++;
        return countZombie;
    }

    void newPositin() //функция, создающая новую конфигурацию поля, изменяя состояние предыдущего в соотвествии с правилами и подсчитанным количеством клеток вокруг
    {
        for (int i = 0; i < x; ++i)
        {
            for (int j = 0; j < y; ++j)
            {
                if (field[i][j] == 'a' && countZombie(i, j) >= 4 && countZombie(i, j) < 8)
                    newField[i][j] = 'i';
                else if ((field[i][j] == 'a' || field[i][j] == 'i') && countZombie(i, j) == 8)
                    newField[i][j] = 'a';
                else if (field[i][j] == 'i' && countAlive(i, j) >= 4 && countAlive(i, j) < 8)
                    newField[i][j] = 'a';
                else if (field[i][j] == 'i' && countAlive(i, j) == 8)
                    newField[i][j] = 'z';
                else if (field[i][j] == 'a' && countInfected(i, j) >= 4)
                    newField[i][j] = 'i';
                else if (field[i][j] == 'z' && countAlive(i, j) == 4 && countInfected(i, j) == 4)
                    newField[i][j] = 'a';
                else
                    newField[i][j] = field[i][j];
                std::cout << newField[i][j];
            }
            std::cout << std::endl;
        }
        field = newField;
    }
};


int main()
{
    int a, b;
    char in;
    std::cout << "Enter size of the field" << std::endl;
    std::cin >> a >> b;
    map m(a, b);

    std::cout << "Now enter your configuration" << std::endl;
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; ++j)
        {
            std::cin >> in;
            m.field[i][j] = in;
            if (in == 'a' || in == 'i'|| in == 'z')
                m.field[i][j] = in;
            else
                std::cout << "Wrong initialization" << std::endl;

        }
    }

    //ожидание в течерение одной секунды и отчистка консоли
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    while(!kbhit())//пока пользователь не нажмет клавишу
    {
        m.newPositin();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        system("cls");
    }
    return 0;
}

