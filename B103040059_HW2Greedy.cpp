#include<iostream>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

string Greedy(int N, int Cap, vector<double> &Weight, vector<int> &Value, int &MaxProfit){
	vector<float> CPValue;
	vector<float> tempp;//As a copy of CPValue vector
	string BinSolu="";//To store the binary solution
	int temp;//To store the capacity so it wont change the original Cap
	int j;//Store the previous index of CPValue choosen
	int k;//Coun the CPValue
	double temp1;//To store the highest CPValue
	double temp2=0.0;//To store the profit
	for(int i=0;i<N;i++){
		CPValue.push_back(Value[i]/Weight[i]);
	}
	for(int i=0;i<N;i++){
		BinSolu+="0";
	}
	temp=Cap;
	tempp=CPValue;
	while(1){
		if(temp<0){
			temp+=Weight[j];
			tempp[j]=0.0;
			temp2-=Value[j];
			BinSolu[j]='0';
			break;
		}
		temp1=0.0;
		for(int i=0;i<CPValue.size();i++){
			if(tempp[i]>=temp1){
				temp1=tempp[i];
				j=i;
			}
		}
		temp-=Weight[j];
		tempp[j]=0.0;
		temp2+=Value[j];
		BinSolu[j]='1';
	}
	temp1=0.0;
	while(1){
		if(temp==0){
			break;
		}
		k=0;
		temp1=0;
		for(int i=0;i<tempp.size();i++){
			if(tempp[i]==0){
				k++;
				continue;
			}
			if(tempp[i]>=temp1){
				temp1=tempp[i];
				j=i;
			}
		}
		if(k==N){
			break;
		}
		if(Weight[j]<=temp){
			temp2+=Value[j];
			BinSolu[j]='1';
			temp-=Weight[j];
		}
		tempp[j]=0.0;
	}
	MaxProfit=temp2;
	return BinSolu;
}

void dt01(){
	vector<double> Weight; //To store the weight of items
	vector<int> Value; //To store the value of items
	int Cap; // the capacity
	int N; // To store number of items
	int W; //to store weight interger
	int V; //to store value interger
	int MaxProfit;
	string TheSolu;
	fstream MyFile;
	MyFile.open("dataset/dt01/item.txt");
	if(!MyFile){
		return;
	}
	string Num;
	string temp3="";
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
	TheSolu=Greedy(N,Cap,Weight,Value,MaxProfit);
	cout<<"dt01"<<endl;
	cout<<"Max Profit: "<<MaxProfit<<endl;
	cout<<"The Solution: "<<TheSolu<<endl;
	MyFile.close();
	ofstream Out("HW2 Ans/ans_dt01.txt");
	Out <<"max profit:"<<MaxProfit<<endl;
	Out<<"solution:"<<TheSolu<<endl;
	Out.close();
}

void dt02(){
	vector<double> Weight; //To store the weight of items
	vector<int> Value; //To store the value of items
	int Cap; // the capacity
	int N; // To store number of items
	int W; //to store weight interger
	int V; //to store value interger
	int MaxProfit;
	string TheSolu;
	fstream MyFile;
	MyFile.open("dataset/dt02/item.txt");
	if(!MyFile){
		return;
	}
	string Num;
	string temp3="";
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
	TheSolu=Greedy(N,Cap,Weight,Value,MaxProfit);
	cout<<"dt02"<<endl;
	cout<<"Max Profit: "<<MaxProfit<<endl;
	cout<<"The Solution: "<<TheSolu<<endl;
	MyFile.close();
	ofstream Out("HW2 Ans/ans_dt02.txt");
	Out <<"max profit:"<<MaxProfit<<endl;
	Out<<"solution:"<<TheSolu<<endl;
	Out.close();
}

void dt03(){
	vector<double> Weight; //To store the weight of items
	vector<int> Value; //To store the value of items
	int Cap; // the capacity
	int N; // To store number of items
	int W; //to store weight interger
	int V; //to store value interger
	int MaxProfit;
	string TheSolu;
	fstream MyFile;
	MyFile.open("dataset/dt03/item.txt");
	if(!MyFile){
		return;
	}
	string Num;
	string temp3="";
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
	TheSolu=Greedy(N,Cap,Weight,Value,MaxProfit);
	cout<<"dt03"<<endl;
	cout<<"Max Profit: "<<MaxProfit<<endl;
	cout<<"The Solution: "<<TheSolu<<endl;
	MyFile.close();
	ofstream Out("HW2 Ans/ans_dt03.txt");
	Out <<"max profit:"<<MaxProfit<<endl;
	Out<<"solution:"<<TheSolu<<endl;
	Out.close();
}

int main(){
	dt01();
	cout<<endl;
	dt02();
	cout<<endl;
	dt03();
}

