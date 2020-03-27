#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define A_BIT (1 << 0)
#define B_BIT (1 << 1)
#define C_BIT (1 << 2)
#define D_BIT (1 << 3)

pair<int, int> process2Nums(int i, int j);
vector<int> getRange(int firstNum, int lastNum);

int main(){
    string myLine;
    ifstream myfile ("input.txt");
    stringstream ss;
    int i,j;
    vector<pair<int, int>> inputs;
    vector<int> resPerInput;
    pair<int, int> tempCount;
    vector<int> results;
    if (myfile.is_open()){
        while(getline(myfile, myLine)){
            ss << myLine;
            ss >> i >> j;
            vector<int> rangeVec = getRange(i,j);
            if(rangeVec.size()%2==0){
                for (int i = 0; i < rangeVec.size(); i+=2){
                    tempCount = process2Nums(rangeVec[i],rangeVec[i+1]);
                    resPerInput.push_back(tempCount.first);
                    resPerInput.push_back(tempCount.second);
                }                
            }else{
                for (int i = 0; i < rangeVec.size()-1; i+=2){
                    tempCount = process2Nums(rangeVec[i],rangeVec[i+1]);
                    resPerInput.push_back(tempCount.first);
                    resPerInput.push_back(tempCount.second);
                }
                tempCount = process2Nums(rangeVec[rangeVec.size()-1],1);
                resPerInput.push_back(tempCount.first);
            }
            results.push_back(*(max_element(resPerInput.begin(), resPerInput.end())));
            inputs.push_back(make_pair(i, j));
            resPerInput.clear();
            ss.clear();
        }
    }else{
        cout << "Unable to open file";
    }
    for(int i = 0; i < results.size(); i++){
        cout << inputs[i].first << " " << inputs[i].second << " " << results[i] << endl;
    }
    
    return EXIT_SUCCESS;
}

pair<int, int> process2Nums(int i, int j){
    pair<int, int> counter;
    int icount = 0;
    int jcount = 0;
    while ((i != 1) && (j != 1)){
        bool conditionA = (i%2==0) && (j%2==0); // both integers are even
        bool conditionB = (i%2==0) && (j%2!=0); // i is even and j is odd
        bool conditionC = (i%2!=0) && (j%2==0); // i is odd and j is even
        bool conditionD = (i%2!=0) && (j%2!=0); // both integers are odd
        // Switch/Case code extracted from https://stackoverflow.com/questions/8644096/multiple-conditions-in-switch-case and edited
        switch( (conditionA ? A_BIT : 0) | (conditionB ? B_BIT : 0) | (conditionC ? C_BIT : 0) | (conditionD ? D_BIT : 0) ){
        case A_BIT:                 //condition A is true, everything else is false.
            // cout << "both integers are even" << endl;
            i /= 2;
            j /= 2;
            break;
        case B_BIT:                 //condition B is true, everything else is false.
            // cout << "i is even and j is odd" << endl;
            i /= 2;
            j = 3*j+1;
            break;
        case C_BIT:         //conditions C is true, everything else is false.
            // cout << "i is odd and j is even" << endl;
            i = 3*i+1;
            j /= 2;
            break;
        case D_BIT:                 //condition D is true, everything else is false.
            // cout << "both integers are odd" << endl;
            i = 3*i+1;
            j = 3*j+1;
            break;
        default:
            // cout << "Something is wrong" << endl;
            break;
        }
        icount++;
        jcount++;
    }
    if(i == 1){
        while (j != 1){
            int conditionj = (j%2 == 0) ? 1 : 0; // 1: j is even, 0: j is odd;
            switch (conditionj){
            case 0:
                j = 3*j+1;
                break;
            case 1:
                j /= 2;
                break;
            default:
                break;
            }
            jcount++;
        }
    }else{
        while (i != 1){
            int conditioni = (i%2 == 0) ? 1 : 0; // 1: i is even, 0: i is odd;
            switch (conditioni){
            case 0:
                i = 3*i+1;
                break;
            case 1:
                i /= 2;
                break;
            default:
                break;
            }
            icount++;
        }
    }
    icount++;
    jcount++;
    counter = make_pair(icount, jcount);
    return counter;
}
vector<int> getRange(int firstNum, int lastNum){
    vector<int> rangeVec;
    if(lastNum < firstNum){
        int temp = firstNum;
        firstNum = lastNum;
        lastNum = temp;
    }
    for (int iter = firstNum; iter <= lastNum; iter++){
        rangeVec.push_back(iter);
    }
    return rangeVec;
    
}