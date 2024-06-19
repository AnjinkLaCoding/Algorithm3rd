#include <bits/stdc++.h>
#include <fstream>
#include <sstream>

using namespace std;

void File_Output(int Profit, const vector<int> &solution, string FileNum){
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
    
    ToFile.open(OutputName);
    ToFile << "max profit:" << Profit << "\nsolution:";
    for(int i=0; i<solution.size(); i++)
        ToFile << solution[i];
    ToFile << "\n";
    ToFile.close();
}
void GA(const int, const int, vector<int>&, vector<int>&, string);

int main()
{
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
        GA(item, Cap, Weight, Value, FileNum);
    }else{
        //if file not found
        printf("File not Found\n");
        return 1;
    }
    InputFile.close();
    return 0;
}

void GA(const int items, const int capacity, 
                    vector<int>& weight, vector<int>& value, 
                    string o_str)
{
    vector<int> solution(items, 0);
    int max_profit = 0;

    int population_size = 100,
        num_runs = 30,
        //eval_max = 1000; //For dt01=1000, dt02=10000, dt03=1000000
        //eval_max = 10000;
        eval_max = 1000000;

    double crossover_rate = 0.6,
           mutation_rate = 0.01;

    double avg_obj_val = 0;
    vector<double> avg_obj_val_eval(eval_max, 0);

    srand(time(NULL));
    //Looping for the run
    for(int r = 1; r <= num_runs; r++){
        int eval = 0;

        //1. generate the random population
        // a 2D vector with row equal "population_size", and each rows have vector of intergers with the size of items
        vector<vector<int>> population(population_size, vector<int> (items));
        
        for(int i = 0; i < population_size; i++){
            for(int j = 0; j < items; j++){
                int temp = rand() % 2;
                population[i][j]=temp;
            }
        }
        //end of initial population

        while(eval < eval_max){
            //2. make the evaluation, get objective value of each population. Check for all possible combination
            // a 2D vector with row equal "population_size", and each rows is a vector of 2 elemets that initializes as 0
            vector<vector<int>> obj_value(population_size, vector<int> (2, 0));

            for (int p = 0; p < population_size; p++)
            {
                for(int len = 0; len < items; len++)
                {
                    if(population[p][len] == 1)
                    {
                        obj_value[p][1] += weight[len+1];

                        if(obj_value[p][1] > capacity){
                            obj_value[p][1] -= weight[len+1];
                            population[p][len] = 0;
                            continue;
                        }
                        obj_value[p][0] += value[len+1];
                    }
                }
            }
            //end of evaluation, obj_value have all possible combination
            
            
            //update current best solution and max_profit
            for(int i = 0; i < population_size; i++){
                if(obj_value[i][0] > max_profit)
                {
                    max_profit = obj_value[i][0];
                    solution = population[i];
                }
            }

            for(int i = 0; i < population_size; i++)
            {
                if(max_profit < obj_value[i][0])
                    max_profit = obj_value[i][0];
                if(eval < eval_max)
                    avg_obj_val_eval[eval++] += max_profit;
            }
            if(eval >= eval_max)break;

            //3. make a selection tournament
            // To randomly choose players and then compare it each other to get a couple of possible solution.(Like nature selection, the strongest survived)
            int player_count = 4,
                tourney_round = population_size;

            vector<vector<int>> temp_population(population_size);
            
            for(int tourney=0; tourney < tourney_round; tourney++)
            {
                int chosen_player = rand() % tourney_round;
                int curr_ov = obj_value[chosen_player][0];
                for(int j = 1; j < player_count; j++)
                {
                    int n = rand() % population_size;
                    if(obj_value[n][0] > curr_ov)
                    {
                        chosen_player = n;
                        curr_ov = obj_value[chosen_player][0];
                    }
                }
                temp_population[tourney] = population[chosen_player];
            }
            population = temp_population;
            //end of tournament selection

            //4. crossover: one-point crossover method
            // Take two solution, then swap some of the solution to the other. (Just like 2 genes combined)
            int half_population = population.size()/2;
            for(int i = 0; i < half_population; i++)
            {
                const double f = static_cast<double>(rand()) / RAND_MAX;
                if(f < crossover_rate) {
                    int slice = rand() % population[0].size();
                    for(int j = slice; j < population[0].size(); j++)
                        swap(population[i][j], population[half_population+i][j]);
                }
            }
            //end of crossover

            //5. mutation
            // A rare case just like virus mutation or else.
            for (size_t i = 0; i < population.size(); i++){
                for (size_t j = 0; j < population[0].size(); j++){
                    const double f = static_cast<double>(rand()) / RAND_MAX;
                    if (f < mutation_rate)
                        population[i][j] = !population[i][j];
                }
            }
            //end of mutation
            
            
        }
        avg_obj_val += max_profit;
    }
    // Calculate the average profit after 30 runs
    avg_obj_val /= num_runs;

    for (int i = 0; i < eval_max; i++) {
        avg_obj_val_eval[i] /= num_runs;
        cout << fixed << setprecision(3) << avg_obj_val_eval[i] << endl;
    }

    //go to the output;
    File_Output(max_profit, solution, o_str);
}
