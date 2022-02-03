#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <iterator>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;
    vector<int> aux_stack;
  int max=0;

  public:

    void Push(int value) {
        if (value>=max)
        {
          max=value;
          aux_stack.push_back(value);
        }
        stack.push_back(value);
    }

    void Pop() {
        assert(stack.size());
        if(max==stack.back())  {
          aux_stack.pop_back();
          max=aux_stack.back();
        }
        stack.pop_back();
    }

    int Max() const {
        assert(stack.size());
        return *max_element(stack.begin(), stack.end());
    }

    int maxBetter2() {
      return max;
    }

  /*  int maxBetter() const
    {
      assert(stack.size());
      vector<int> aux_stack_(stack);
      sort(aux_stack_.begin(), aux_stack_.end());
      return aux_stack_.back();
    }  */
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.maxBetter2() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}
