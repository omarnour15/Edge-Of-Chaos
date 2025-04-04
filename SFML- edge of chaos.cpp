#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <thread>

#include <SFML/Graphics.hpp>

using namespace std;

#define COLOR_0 3   // Black
#define COLOR_1 6   // Orange
#define COLOR_2 14  // Golden Yellow
#define COLOR_3 12  // Light Orange
#define COLOR_4 13  // Peach/Pink

//black and white
#define COLOR_0_BW 20
#define COLOR_1_BW 21

//clear screen function
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif // _WIN32

}




void set_color(int number) {
    if (number == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_0);
    }
    else if (number == 1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_1);
    }
    else if (number == 2) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_2);
    }
    else if (number == 3) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_3);
    }
    else if (number == 4) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_4);
    }

    else if (number == 20) { // well start with 2 for the B&W
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    }
    else if (number == 21) { // well start with 2 for the B&W
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // back to original
    }
}


int height;
int width;

void vet_avg_pi(vector<vector<int>>& grid) {
    const double PI = 3.14159265358979323846;
    for (int i = 1; i < height - 1; i++) {
        for (int j = 0; j < width; j++) {
            double new_value = (grid[i - 1][j] + grid[i][j] + grid[i + 1][j]) / 3.0;
            grid[i][j] = static_cast<int>(floor(new_value * PI)) % 5;
        }
    }
}

void vertical_horizantal_swap(vector<vector<int>>& grid) {
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            if (grid[i][j] == 2 && (grid[i + 1][j] == 0 || grid[i - 1][j] == 0 || grid[i][j + 1] == 0 || grid[i][j - 1] == 0)) {
                //grid[i + 1][j] = grid[i][j];
                //grid[i - 1][j] = grid[i][j];
                //grid[i][j + 1] = grid[i][j];
                grid[i][j - 1] = grid[i][j];

                grid[i][j] = 0;
            }
        }
    }
}

void constant_adder(vector<vector<int>>& grid) {
    const double C = 2.718281828459045; // eulers constant
    bool exitLoop = false;
    for (int i = 0; i < height && !exitLoop; i++) {
        for (int j = 0; j < width; j++) {
            if (C != 0) {
                grid[i][j] = static_cast<int>(floor((grid[i][j] + C))) % 5;
            }
            else {
                exitLoop = true;
                break;
            }
        }
    }
}

void vertical_flip(vector<vector<int>>& grid) {
    for (int i = 1; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i - 1][j] == grid[i][j]) {
                if (grid[i][j] > 1) {
                    grid[i][j] = 0;
                }
                grid[i][j] = 1 - grid[i][j];
            }
        }
    }
}

void isolation(vector<vector<int>>& grid) {
    for (int i = 0; i < height; i++) {
        for (int j = 1; j < width - 1; j++) {
            if (grid[i][j - 1] != grid[i][j] && grid[i][j + 1] != grid[i][j]) {
                if (grid[i][j] == 2 || grid[i][j] == 3 || grid[i][j] == 4) {
                    //grid[i][j] = rand() % 5; // for random action stuff
                    grid[i][j] = 0; // just a normal rule
                }
                else {
                    grid[i][j] = 1 - grid[i][j];
                }
            }
        }
    }
}

void change_of_state(vector<vector<int>>& grid) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width - 2; j++) {
            if (grid[i][j] == grid[i][j + 2]) {
                if (grid[i][j + 1] == 2 || grid[i][j + 1] == 3 || grid[i][j + 1] == 4) {
                    //grid[i][j + 1] = rand() % 5; // for random action stuff
                    grid[i][j] = 0; // just a normal rule
                }
                else {
                    grid[i][j + 1] = 1 - grid[i][j + 1];
                }
            }
        }
    }
}


void diagonal_average_triangle(vector<vector<int>>& grid) {
    const double C = 2.718281828459045; // eulers constant
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            double avg = (grid[i - 1][j - 1] + grid[i - 1][j + 1] + grid[i + 1][j - 1] + grid[i + 1][j + 1]) / 4.0;
            grid[i][j] = static_cast<int>(floor(grid[i][j] * C)) % 5;
        }
    }
}


//rules for BW
void triangle_thing(vector<vector<int>>& grid) {
    for (int i = 0; i < height; i++) {
        for (int j = 1; j < width - 1; j++) {
            grid[i][j] = (grid[i][j - 1] + grid[i][j + 1]) % 2;
        }
    }
}

void fractal_triangle(vector<vector<int>>& grid) {
    for (int i = 1; i < height; i++) {
        for (int j = 1; j < width - 1; j++) {
            grid[i][j] = (grid[i - 1][j - 1] + grid[i - 1][j + 1]) % 2;
        }
    }
}

void diagonal_triangle(vector<vector<int>>& grid) {
    for (int i = 0; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            if (grid[i + 1][j - 1] == 0 && grid[i + 1][j + 1] == 0 && grid[i][j] == 1) {
                grid[i + 1][j - 1] = 1;
                grid[i + 1][j + 1] = 1;
            }
            else if (grid[i + 1][j + 1] == 0 && grid[i][j] == 1) {
                grid[i + 1][j + 1] = 1;
            }
        }
    }
}

void mirror(vector<vector<int>>& grid) {
    for (int i = 0; i < height; i++) {
        for (int j = 1; j < width - 1; j++) {
            if (grid[i][j] == 1) {
                grid[i][width - j] = 1;
            }
        }
    }
}

void wave(vector<vector<int>>& grid) {
    for (int i = 1; i < height; i++) {
        for (int j = 1; j < width - 1; j++) {
            grid[i][j] = (grid[i - 1][j - 1] + grid[i - 1][j + 1]) % 2;
        }
    }
}

void sin_wave(vector<vector<int>>& grid) {
    for (int i = 1; i < height; i++) {
        for (int j = 1; j < width - 1; j++) {

            const float frequency = 2.0;
            const float amplitude = min(width / 2 - 1, 10.2f);
            int shift = width / 2;

            int column = round(sin(i * frequency) * amplitude) + shift;

            if (column >= 0 && column < width) {
                grid[i][column] = 1;
            }
        }
    }
}

void weird_wave(vector<vector<int>>& grid, const float frequency, const float ampl, int thickness) {
    for (int i = 0; i < height - 1; i++) {
        const float amplitude = min(width / 2 - 1, ampl);
        int shift = width / 2;

        int target = round(sin(i * frequency) * amplitude) + shift;

        for (int j = 0; j < width - 1; j++) {
            if (abs(j - target) <= thickness) {
                grid[i][j] = 1;
            }
            else { grid[i][j] = 0; }
        }
    }
}

int main() {
    /*sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }




        window.clear();
        window.draw(shape);
        window.display();
    }*/
    srand(time(0));
    ios::sync_with_stdio(false);

    vector<vector<int>> grid;

    int yes_no;
    cout << "black and white, or colors: ";
    cin >> yes_no;

    //with colors
    if (yes_no == 1) {
        cout << "whats the height of the array: ";
        cin >> height;
        cout << endl;

        cout << "whats the width of the array: ";
        cin >> width;
        cout << endl;

        vector<int> empty_vector;
        empty_vector.resize(width, 0);
        grid.resize(height, empty_vector);

            for (auto& vec : grid) {
                for (auto& x : vec) {
                    x = (rand() % 5);
                }
            }


            //rules

            //change_of_state(grid);
            //vertical_flip(grid);
            //constant_adder(grid);
            //vertical_horizantal_swap(grid);
            isolation(grid);
            vet_avg_pi(grid);
            //diagonal_average_triangle(grid);

            // Changing the colors of the text
            int last_color = -1;
            bool changed = false;

            for (const vector<int>& vec : grid) {
                for (const int& x : vec) {
                    if (x != last_color) {
                        set_color(x);
                        last_color = x;
                    }
                    cout << x;
                }
                cout << "\n";// add a line break after each row
            }
            set_color(7);
            
    }
    //B&W
    else {
        cout << "whats the height of the array: ";
        cin >> height;
        cout << endl;

        cout << "whats the width of the array: ";
        cin >> width;
        cout << endl;

        vector<int> empty_vector;
        empty_vector.resize(width, 0);
        grid.resize(height, empty_vector);

        grid[0][width / 2] = 1;

        //rules
        //triangle_thing(grid);
        //fractal_triangle(grid);
        //diagonal_triangle(grid);
        //mirror(grid);
        //wave(grid);
        //sin_wave(grid);
        weird_wave(grid, 3.0, 20.2, 3);
        mirror(grid);

        for (const auto& vec : grid) {
            for (const auto& x : vec) {
                if (x == 0) { set_color(COLOR_0_BW); cout << x << ""; }
                else if (x == 1) { set_color(COLOR_1_BW); cout << x << ""; }
                set_color(7);

            }
            cout << endl;
        }
    }

}