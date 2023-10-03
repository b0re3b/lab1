#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Задаємо матрицю суміжності
vector<vector<int>> adMa;
int numV = 5;

// Додаємо вершину
void addV() {
    numV++;
    for (vector<int>& row : adMa) {
        row.push_back(0);
    }
    adMa.push_back(vector<int>(numV, 0));
}

// Видаляємо вершину
void remV(int v) {
    if (v >= 0 && v < numV) {
        for (vector<int>& row : adMa) {
            row.erase(row.begin() + v);
        }
        adMa.erase(adMa.begin() + v);
        numV--;
    }
}

// Перевірка на зв'язність
bool isConn() {
    vector<bool> visit(numV, false);
    stack<int> stack;

    stack.push(0);
    visit[0] = true;

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        for (int i = 0; i < numV; ++i) {
            if (adMa[current][i] && !visit[i]) {
                stack.push(i);
                visit[i] = true;
            }
        }
    }

    // Перевіряємо, чи всі вершини були відвідані
    for (bool v : visit) {
        if (!v) {
            return false;
        }
    }
    return true;
}

// Відстань між двома вершинами
int Dist(int start, int end) {
    vector<int> dist(numV, -1);
    stack<int> stack;

    dist[start] = 0;
    stack.push(start);

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        for (int i = 0; i < numV; ++i) {
            if (adMa[current][i] && dist[i] == -1) {
                dist[i] = dist[current] + 1;
                stack.push(i);
            }
        }
    }

    return dist[end];
}

int main() {
    adMa = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1}
    };

    cout << "Граф звʼязний? " << (isConn() ? "Так" : "Ні") << endl;
    cout << "Відстань між 1 та 4 вершинами: " << Dist(1, 4) << endl;

    addV();
    cout << "Граф з новою вершиною:" << endl;
    for (const vector<int>& row : adMa) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    remV(1);
    cout << "Граф після видалення 1 вершини:" << endl;
    for (const vector<int>& row : adMa) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
