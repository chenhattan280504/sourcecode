#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;

struct maze {
    int cells[6][5];
};

// Hàm để đọc dữ liệu mê cung từ tệp
maze docMazeTuFile(const string& input) {
    ifstream nhap("input.txt");

    maze duLieuMaze;

    if (nhap.is_open()) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++) {
                nhap >> duLieuMaze.cells[i][j];
            }
        }
        nhap.close();
    } else {
        cerr << "Lỗi: Không thể mở tệp " << input << endl;
        duLieuMaze = {
            {{2, 1, 14, 12, 17},
             {3, 16, 22, 91, 23},
             {4, 56, 87, 31, 65},
             {27, 43, 90, 100, 101},
             {76, 54, 32, 99, 66},
             {178, 154, 150, 200, 543}}
        };
    }

    return duLieuMaze;
}

struct RobotBD {
    int x;
    int y;
};

// Print maze cells
void In_maze(const maze& mazeData) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            cout << mazeData.cells[i][j] << " ";
        }
        cout << endl;
    }
}

// tim duong đi cho 1 robot 
vector<int> findRobotPath(const maze& mazeData, const RobotBD& startPos, const vector<int>& otherRobotPath) {
    int x = startPos.x;
    int y = startPos.y;

    vector<int> path;
    path.push_back(mazeData.cells[x][y]);

    int visited[6][5] = {0};

    //  Danh dau cac o ma robot da di
    for (int i = 0; i < otherRobotPath.size(); i++) {
        int value = otherRobotPath[i];
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 5; k++) {
                if (mazeData.cells[j][k] == value) {
                    visited[j][k] = 1;
                    break;
                }
            }
        }
    }

    while (true) {
        int max_value = -1;
        int next_x = x, next_y = y;

        if (x > 0 && mazeData.cells[x - 1][y] > max_value && visited[x - 1][y] == 0) {
            max_value = mazeData.cells[x - 1][y];
            next_x = x - 1;
            next_y = y;
        }

        if (x < 5 && mazeData.cells[x + 1][y] > max_value && visited[x + 1][y] == 0) {
            max_value = mazeData.cells[x + 1][y];
            next_x = x + 1;
            next_y = y;
        }

        if (y > 0 && mazeData.cells[x][y - 1] > max_value && visited[x][y - 1] == 0) {
            max_value = mazeData.cells[x][y - 1];
            next_x = x;
            next_y = y - 1;
        }

        if (y < 4 && mazeData.cells[x][y + 1] > max_value && visited[x][y + 1] == 0) {
            max_value = mazeData.cells[x][y + 1];
            next_x = x;
            next_y = y + 1;
        }

        if (max_value == -1) {
            break;
        }

        visited[x][y] = 1;

        x = next_x;
        y = next_y;
        path.push_back(mazeData.cells[x][y]);
    }

    return path;
}

// tinh tong diem ma robot di qua
int Tinh_Tong_Diem(const vector<int>& path) {
    int sum = 0;
    for (int i = 0; i < path.size(); i++) {
        sum += path[i];
    }
    return sum;
}

int main() {
    string traLoi;
    do {
        maze duLieuMaze = docMazeTuFile("input.txt");

        cout << "Me cung robot:" << endl;
        In_maze(duLieuMaze);
        cout << endl;

        int luachon;
        cout << "1 - duong di cua 1 robot." << endl;
        cout << "2 - so sanh duong di cua 2 robot." << endl;
        cout << "3 - Duong di 2 robot khong trung nhau" << endl;
        cout << "Nhap lua chon :";
        cin >> luachon;
        ofstream output("output.txt",ios::app);
        switch (luachon) {
            case 1: {
                RobotBD startPos;
                cout << "Nhap vi tri robot: ";
                cin >> startPos.x >> startPos.y;

                vector<int> robotPath = findRobotPath(duLieuMaze, startPos, {});

                cout << "Duong di cua robot:";
                output << "Duong di cua robot:";
                for (int i = 0; i < robotPath.size(); i++) {
                    cout << robotPath[i] << " ";
                    output << robotPath[i] << " ";
                }
                cout << endl;
                output << endl;


                int pathSum = Tinh_Tong_Diem(robotPath);
                output << "Tong diem cua robot : " << pathSum << endl;

                cout << "Tong diem cua robot : " << pathSum << endl;

                break;
            }
            case 2: {
                RobotBD startPos1, startPos2;
                cout << "Nhap vi tri robot 1 :";
                cin >> startPos1.x >> startPos1.y;
                cout << "Nhap vi tri robot 2 :";
                cin >> startPos2.x >> startPos2.y;

                vector<int> robotPath1 = findRobotPath(duLieuMaze, startPos1, {});
                vector<int> robotPath2 = findRobotPath(duLieuMaze, startPos2, {});

                cout << "Duong di cua robot 1: ";
                output << "Duong di cua robot 1: ";  
                for (int i = 0; i < robotPath1.size(); i++) {
                    cout << robotPath1[i] << " ";
                    output << robotPath1[i] << " ";
                }
                cout << endl;
                output << endl;

                cout << "duong di cua robot 2: ";
                output << "duong di cua robot 2: ";
                for (int i = 0; i < robotPath2.size(); i++) {
                    cout << robotPath2[i] << " ";
                    output << robotPath2[i] << " ";
                }
                cout << endl;
                output << endl;

                cout << "Cac o ma robot trung nhau: ";
                output << "Cac o ma robot trung nhau: ";
                for (int i = 0; i < robotPath1.size(); i++) {
                    for (int j = 0; j < robotPath2.size(); j++) {
                        if (robotPath1[i] == robotPath2[j]) {
                            cout << robotPath1[i] << " ";
                            output << robotPath1[i] << " ";
                            break;
                        }
                    }
                }
                cout << endl;
                output << endl;

                int pathSum1 = Tinh_Tong_Diem(robotPath1);
                int pathSum2 = Tinh_Tong_Diem(robotPath2);

                cout << "Tong diem cua robot 1: " << pathSum1 << endl;
                cout << "Tong diem cua robot 2: " << pathSum2 << endl;
                output << "Tong diem cua robot 1: " << pathSum1 << endl;
                output << "Tong diem cua robot 2: " << pathSum2 << endl;

                if (pathSum1 > pathSum2) {
                    cout << "Robot 1 chien thang" << endl;
                    output << "Robot 1 chien thang" << endl;
                } else {
                    cout << "Robot 2 chien thang" << endl;
                    output << "Robot 2 chien thang" << endl;
                }

                break;
            }
            case 3: {
                RobotBD startPos1, startPos2;
                cout << "Nhap vi tri Robot 1: ";
                cin >> startPos1.x >> startPos1.y;
                cout << "Nhap vi tri Robot 2: ";
                cin >> startPos2.x >> startPos2.y;

                vector<int> robotPath1 = findRobotPath(duLieuMaze, startPos1, {});
                vector<int> robotPath2 = findRobotPath(duLieuMaze, startPos2, robotPath1);

                cout << "Duong di cua robot 1: ";
                output << "Duong di cua robot 1: ";
                for (int i = 0; i < robotPath1.size(); i++) {
                    cout << robotPath1[i] << " ";
                    output << robotPath1[i] << " ";
                }
                output << endl;

                cout << "Duong di cua robot 2: ";
                output << "Duong di cua robot 2: ";
                for (int i = 0; i < robotPath2.size(); i++) {
                    cout << robotPath2[i] << " ";
                    output << robotPath2[i] << " ";
                }
                cout << endl;
                output << endl;

                int pathSum1 = Tinh_Tong_Diem(robotPath1);
                int pathSum2 = Tinh_Tong_Diem(robotPath2);

                cout << "Tong diem duong di cua robot 1: " << pathSum1 << endl;
                cout << "Tong diem duong di cua robot 2: " << pathSum2 << endl;
                output << "Tong diem duong di cua robot 1: " << pathSum1 << endl;
                output << "Tong diem duong di cua robot 2: " << pathSum2 << endl;

                if (pathSum1 > pathSum2) {
                    cout << "Robot 1 chien thang" << endl;
                    output << "Robot 1 chien thang" << endl;
                } else {
                    cout << "Robot 2 chien thang" << endl;
                    output << "Robot 2 chien thang" << endl;
                }

                break;
            }

            default:
                cout << "Lua chon khong hop le." << endl;
                break;
        }

        cout << "Ban co muon tiep tuc (Y/N) ? ";
        cin >> traLoi;
    } while (traLoi == "Y" || traLoi == "y");

    return 0;
}