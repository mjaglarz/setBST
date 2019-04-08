#include <iostream>
#include <string>
#include "setBST.hpp"

using std::cout;
using std::endl;

template <typename Iterator>
void printDebugInfo(const std::pair<Iterator, bool> &insertInfo){
  cout << (insertInfo.second ? "Added " + std::to_string(*insertInfo.first) : "Couldn't add an element.") << endl;
}

template <typename Iterator>
void printDebugInfo(const Iterator &findInfo){
  cout << (findInfo ? "Found " + std::to_string(*findInfo) : "Couldn't find an element.") << endl;
}

int main(int argc, char* argv[]){
  try{
    SetBST<> set;

    printDebugInfo(set.insert(8));
    printDebugInfo(set.insert(2));
    printDebugInfo(set.insert(1));
    printDebugInfo(set.insert(3));
    printDebugInfo(set.insert(10));
    printDebugInfo(set.insert(9));
    printDebugInfo(set.insert(11));
    printDebugInfo(set.insert(11));

    auto set2 = set;

    set2.remove(2);
    set2.remove(2);
    set2.remove(11);

    printDebugInfo(set2.find(8));
    printDebugInfo(set2.find(11));

    SetBST<int> set3;

    set3 = set;

    cout << "SET1: ";
    for(SetBST<int>::Iterator i = set.begin(); i != set.end(); ++i){
      cout << *i << " ";
    }
    cout << "\nSIZE: " << set.size() << endl;

    cout << "\nSET2: ";
    for(SetBST<int>::Iterator i = set2.begin(); i != set2.end(); ++i){
      cout << *i << " ";
    }
    cout << "\nSIZE: " << set2.size() << endl;

    cout << "\nSET3: ";
    for(SetBST<int>::Iterator i = set3.begin(); i != set3.end(); ++i){
      cout << *i << " ";
    }
    cout << "\nSIZE: " << set3.size() << endl;

  }catch(std::exception const &e){
    std::cerr << e.what() << "\n";
  }

  return 0;
}
