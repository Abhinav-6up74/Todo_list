#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> vs;
int sz = 0;
const string FILENAME = "tasks.txt";

void print_menu() {
  cout << "1. Show all tasks\n2. Add new task\n3. Complete a task\n4. Update a "
          "task\n0. Exit\n";
}

void load_tasks() {
  ifstream fin(FILENAME);
  if (!fin) {
    return;
  }
  string line;
  while (getline(fin, line)) {
    if (!line.empty())
      vs.push_back(line);
  }
  fin.close();
}

void show_all() {
  cout << "-------LIST-------\n";
  if (sz == 0) {
    cout << "(No tasks)\n";
  }
  for (int i = 1; i <= sz; i++) {
    cout << i << ". " << vs[i - 1] << endl;
  }
  cout << "----------------\n";
}

void save_tasks() {
  ofstream fout(FILENAME);
  if (!fout) {
    cout << "Warning: could not save tasks to file\n";
    return;
  }
  for (auto &i : vs) {
    fout << i << "\n";
  }
  fout.close();
}

void new_task() {
  string s;
  cin.ignore();
  getline(cin, s);
  if (s.empty()) {
    cout << "Task can't be empty\n";
    return;
  }
  vs.push_back(s);
  save_tasks();
  cout << "Added\n";
  sz++;
}

void complete_task() {
  if (sz == 0) {
    cout << "No task\n";
    return;
  }
  cout << "Enter task number: ";
  int n;
  cin >> n;
  if (n < 1 || n > sz) {
    cout << "Invalid task number\n";
    return;
  }
  vs.erase(vs.begin() + n - 1);
  save_tasks();
  sz--;
  cout << "Done\n";
  show_all();
}

void update_task() {
  if (sz == 0) {
    cout << "No task\n";
    return;
  }
  cout << "Enter task number: ";
  int n;
  cin >> n;
  if (n < 1 || n > sz) {
    cout << "Invalid task number\n";
    return;
  }
  string s;
  cin.ignore();
  getline(cin, s);
  if (s.empty()) {
    cout << "Task can't be empty. Update abbort\n";
    return;
  }
  vs[n - 1] = s;
  save_tasks();
  cout << "Done\n";
  show_all();
}

int main() {
  cout << "------TODO List------\n";
  load_tasks();
  int choice;
  while (1) {
    print_menu();
    cin >> choice;
    switch (choice) {
    case 1:
      show_all();
      break;
    case 2:
      new_task();
      break;
    case 3:
      complete_task();
      break;
    case 4:
      update_task();
      break;
    case 0:
      cout << "Exiting...\n";
      return 0;
    default:
      cout << "Invalid\n";
    }
  }
}
