#include <iostream>
using namespace std;
// team names: Noor Omar Burini 136799 , Roaa Ziad Batta 137307

struct process {
    string name;
    int arrival_time;
    int process_time;
    int turnaround;
    int delay;
    int response;
};

int main() {
    FILE* stream;
    freopen_s(&stream,"in.txt", "r", stdin);
    freopen_s(&stream,"out.txt", "w", stdout);

    process p[10];
    int n;
    int count = 0; //num of done processes
    int new_p = 0; //num of arrived processes
    string output = "";
    int min_arr = 999; //minimum arrival time

    int shortest = 999;
    int point = 0; // the point we finish excute current process
    int c = 0;//num of processes have the same process time

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i].name >> p[i].arrival_time >> p[i].process_time;

        if (p[i].arrival_time < min_arr)
            min_arr = p[i].arrival_time;
    }

    while (count < n) {

        for (int i = 0; i < n; i++) {
            if ((p[i].arrival_time <= point || p[i].arrival_time == min_arr) && p[i].process_time != 0)
                new_p++; //num of processes arrive in a specific time 
        }

        if (new_p == 1) // we have one process arrives
        {
            for (int i = 0; i < n; i++)
                if ((p[i].arrival_time <= point || p[i].arrival_time == min_arr) && p[i].process_time != 0) {

                    if (p[i].arrival_time == min_arr && p[i].arrival_time > point)
                        point += (p[i].arrival_time - point);

                    output += p[i].name;
                    p[i].response = point - p[i].arrival_time;
                    point += p[i].process_time;
                    p[i].turnaround = point - p[i].arrival_time;
                    p[i].delay = p[i].turnaround - p[i].process_time;
                    p[i].process_time = 0;
                    count++;
                    new_p--;

                    min_arr = 999;
                    for (int j = 0; j < n; j++) {
                        if (p[j].arrival_time < min_arr && p[j].process_time != 0)
                            min_arr = p[j].arrival_time;
                    }

                    break;
                }
        }
        else if (new_p > 1) // more than one process arrive (we need to check processing time)
        {
            while (new_p != 0) {

                for (int i = 0; i < n; i++) {
                    if ((p[i].arrival_time <= point || p[i].arrival_time == min_arr) && p[i].process_time != 0) { //find the shortest process
                        if (p[i].process_time < shortest)
                            shortest = p[i].process_time;
                    }
                }

                for (int i = 0; i < n; i++) {
                    if ((p[i].arrival_time <= point || p[i].arrival_time == min_arr) && p[i].process_time != 0)
                        if (p[i].process_time == shortest) //num of processes have the same process time 
                            c++;
                }

                for (int i = 0; i < n; i++) {
                    if ((p[i].arrival_time <= point || p[i].arrival_time == min_arr) && p[i].process_time != 0) {

                        if (p[i].arrival_time == min_arr && p[i].arrival_time > point)
                            point += (p[i].arrival_time - point);

                        if(c==1)
                            if (p[i].process_time == shortest) { //execute the shortest process                   
                                output += p[i].name;
                                p[i].response = point - p[i].arrival_time;
                                point += p[i].process_time;
                                p[i].turnaround = point - p[i].arrival_time;
                                p[i].delay = p[i].turnaround - p[i].process_time;
                                p[i].process_time = 0;
                                count++;
                                new_p--;
                                shortest = 999;
                                c = 0;

                                min_arr = 999;
                                for (int j = 0; j < n; j++) {
                                    if (p[j].arrival_time < min_arr && p[j].process_time != 0)
                                        min_arr = p[j].arrival_time;
                                }

                                break;
                            }

                        else if(c>1)
                            if (p[i].arrival_time==min_arr && p[i].process_time == shortest) { //execute the first arrive process                   
                                output += p[i].name;
                                p[i].response = point - p[i].arrival_time;
                                point += p[i].process_time;
                                p[i].turnaround = point - p[i].arrival_time;
                                p[i].delay = p[i].turnaround - p[i].process_time;
                                p[i].process_time = 0;
                                count++;
                                new_p--;
                                shortest = 999;
                                c = 0;

                                min_arr = 999;
                                for (int j = 0; j < n; j++) {
                                    if (p[j].arrival_time < min_arr && p[j].process_time != 0)
                                        min_arr = p[j].arrival_time;
                                }

                                break;
                            }

                    }
                }
            }
        }
    }
    cout << output << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i].name << ": (response = " << p[i].response << ", turnaround = " <<
            p[i].turnaround << ", delay = " << p[i].delay << ")" << endl;
    }
}