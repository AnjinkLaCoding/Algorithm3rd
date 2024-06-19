#include<bits/stdc++.h>
#include <fstream>
#include <sstream>

using namespace std;

void File_Output(int Profit, string solution, string FileNum){
    ofstream ToFile;
    bool FileError = false;
    string OutputName = "";

    for(int i=0; i < FileNum.length(); i++){
        if(FileNum[i] == '1'){
            OutputName = "ans_dt01.txt";
            break;
        }
        if(FileNum[i] == '2'){
            OutputName = "ans_dt02.txt";
            break;
        }
        if(FileNum[i] == '3'){
            OutputName = "ans_dt03.txt";
            break;
        }
    }

    //check for file errors
    if(FileError){
        cout << "FileError Occured\n";
        return;
    }
    
    //transfer the result into "ans_dt0X.txt" file
    ToFile.open(OutputName);
    ToFile << "max profit:" << Profit << "\nsolution:" << solution << "\n";
    ToFile.close();
}

void dynamicWay(const int item, const int Cap, vector<int> &weight, vector<int> &value, string FileNum){
    string Solution = "";
    int TheProfit = 0;

    //create a 2d-vector table, Cap as row size, item as column size
    vector<vector<int>> table(item+1, vector<int> (Cap+1, 0));

    //set all column = 0
    for(int i = 0; i <= Cap; i++){
        table[0][i]=0;
    }
    //set all row = 0
    for(int i = 0; i <= item; i++){
        table[i][0]=0;
    }

    for(int i = 1; i <= item; i++){
        for(int j = 1; j <= Cap; j++){
            if(weight[i] <= j){
                table[i][j] = max(value[i]+table[i-1][j-weight[i]], table[i-1][j]);
            }else{
                table[i][j] = table[i-1][j];
            }
        }
    }

    TheProfit = table[item][Cap];

    int temp = Cap;
    for(int i = item; i >= 1; i--){   
        string temp2 = "0";
        if(table[i][temp] != table[i-1][temp]){
            temp2 = "1";
            temp = temp-weight[i];
        }
        temp2 += Solution;
        Solution = temp2;
    }

    File_Output(TheProfit, Solution, FileNum);
}

int main(){
    string FileName;
    ifstream InputFile;
    string FileNum;

    //the input file must be in the same folder
    cout << "input the file name (include it's location): ./";
    cin >> FileName;
    InputFile.open(FileName);

    if(InputFile.is_open()){   
        int item, Cap;
        string TempStr; // store string for temporary time
    
        getline(InputFile, TempStr);
        stringstream iss1;
        iss1.str(TempStr);
        iss1 >> item >> Cap;

        vector <int> Weight, Value;
        //Setting the 0th index of weight and value as 0, index 0 wont be used
        Weight.push_back(0);
        Value.push_back(0);

        int temp; //To store stringstream
        while(getline(InputFile, TempStr)){
            stringstream iss2;
            iss2.str(TempStr);
            iss2>>temp; Weight.push_back(temp);
            iss2>>temp; Value.push_back(temp);
        }
        FileNum = "./" + FileName; //Used later to determine which data is this
        dynamicWay(item, Cap, Weight, Value, FileNum);
    }else{
        //if file not found
        printf("File not Found\n");
        return 1;
    }
    InputFile.close();
    return 0;
}