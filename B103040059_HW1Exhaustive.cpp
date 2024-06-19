#include<iostream>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<sstream>
#include<cmath>

using namespace std;
string ExhaustiveSearch(int N, int Cap, vector<int> Weight, vector<int> Value, int &MaxProfit){
	vector<string> Solutions; //To store the binary solution and search for the max solutions
	string Binary="";
	int PosCase;// to store the possible combination of N items
	int temp;
	int temp1;
	int coun;//to count the binary
	string TheBinary="";
	PosCase = pow(2,N)-1;
	Solutions.push_back("0000000000");
	for(int i=1;i<=PosCase;i++){
		coun=0;
		Binary="";
		temp=i;
		while(temp!=0){
			if(temp%2==0){
				Binary+="0";
			}else{
				Binary+="1";
			}
		temp/=2;
		}
		coun=Binary.length();
		while(coun<N){
			Binary+="0";
			coun++;
		}
		Solutions.push_back(Binary);
	}
	for(int i=0;i<Solutions.size();i++){
		coun=0;
		temp=0;
		temp1=0;
		Binary=Solutions[i];
		while(coun<N){
			if(Binary[coun]=='1'){
				temp+=Weight[coun];
				temp1+=Value[coun];
			}
			coun++;
		}
		if(temp>Cap){
			continue;
		}
		if(MaxProfit<=temp1){
			MaxProfit=temp1;
			TheBinary=Binary;
		}
		
	}
	return TheBinary;
}

void dt01(){
	vector<int> Weight; //To store the weight of items
	vector<int> Value; //To store the value of items
	string TheBinary;
	int Cap; // the capacity
	int N; // To store number of items
	int W; //to store weight interger
	int V; //to store value interger
	int MaxProfit=0;
	fstream MyFile;
	MyFile.open("dataset/dt01/item.txt");
	if(!MyFile){
		return;
	}
	string Num;
	string temp="";
	stringstream tempp;
	getline(MyFile,Num);
	tempp.str(Num);
	tempp>>N>>Cap;
	while(getline(MyFile,Num)){
		tempp.clear();
		tempp.str(Num);
		tempp>>W>>V;
		Weight.push_back(W);
		Value.push_back(V);
	}
	TheBinary=ExhaustiveSearch(N,Cap,Weight,Value,MaxProfit);
	cout<<"dt01"<<endl;
	cout<<"Max Profit: "<<MaxProfit<<endl;
	cout<<"The solution: "<<TheBinary<<endl;
	MyFile.close();
	ofstream Out("HW1 Ans/ans_dt01.txt");
	Out <<"max profit:"<<MaxProfit<<endl;
	Out<<"solution:"<<TheBinary<<endl;
	Out.close();
}

void dt02(){
	vector<int> Weight; //To store the weight of items
	vector<int> Value; //To store the value of items
	string TheBinary;
	int Cap; // the capacity
	int N; // To store number of items
	int W; //to store weight interger
	int V; //to store value interger
	int MaxProfit=0;
	fstream MyFile;
	MyFile.open("dataset/dt02/item.txt");
	if(!MyFile){
		return;
	}
	string Num;
	string temp="";
	stringstream tempp;
	getline(MyFile,Num);
	tempp.str(Num);
	tempp>>N>>Cap;
	while(getline(MyFile,Num)){
		tempp.clear();
		tempp.str(Num);
		tempp>>W>>V;
		Weight.push_back(W);
		Value.push_back(V);
	}
	TheBinary=ExhaustiveSearch(N,Cap,Weight,Value,MaxProfit);
	cout<<endl<<"dt02"<<endl;
	cout<<"Max Profit: "<<MaxProfit<<endl;
	cout<<"The solution: "<<TheBinary<<endl;
	MyFile.close();
	ofstream Out("HW1 Ans/ans_dt02.txt");
	Out <<"max profit:"<<MaxProfit<<endl;
	Out<<"solution:"<<TheBinary<<endl;
	Out.close();
}

void dt03(){
	vector<int> Weight; //To store the weight of items
	vector<int> Value; //To store the value of items
	string TheBinary;
	int Cap; // the capacity
	int N; // To store number of items
	int W; //to store weight interger
	int V; //to store value interger
	int MaxProfit=0;
	fstream MyFile;
	MyFile.open("dataset/dt03/item.txt");
	if(!MyFile){
		return;
	}
	string Num;
	string temp="";
	stringstream tempp;
	getline(MyFile,Num);
	tempp.str(Num);
	tempp>>N>>Cap;
	while(getline(MyFile,Num)){
		tempp.clear();
		tempp.str(Num);
		tempp>>W>>V;
		Weight.push_back(W);
		Value.push_back(V);
	}
	TheBinary=ExhaustiveSearch(N,Cap,Weight,Value,MaxProfit);
	cout<<endl<<"dt03"<<endl;
	cout<<"Max Profit: "<<MaxProfit<<endl;
	cout<<"The solution: "<<TheBinary<<endl;
	MyFile.close();
	ofstream Out("HW1 Ans/ans_dt03.txt");
	Out <<"max profit:"<<MaxProfit<<endl;
	Out<<"solution:"<<TheBinary<<endl;
	Out.close();
}

int main(){
	dt01();
	dt02();
	dt03();
}

