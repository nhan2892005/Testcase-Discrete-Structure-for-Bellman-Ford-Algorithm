/*
* Faculty of Computer Science and Engineering
* Run test for Bellman Ford algorithm
* Discrete Structures and Its Applications
* Author: Nguyen Phuc Nhan
* Date: 15.05.2024
*/
#include "bellman.h"
#include "tsp.h"
template <typename PHUCNHAN> void setAllElement(PHUCNHAN arr[], PHUCNHAN value, int size){
    for (int idx = 0; idx < size; ++idx) arr[idx] = value;
}
void copyFile(const std::string& sourcePath, const std::string& destinationPath);
void printTestFail(int i);
void comparefile(int start, int end);
bool isNumber(string str);
int cost(int graph[][20], string path);
string result_success = "";
string result_fail = "";

ofstream OUTPUT;
string folder_output = "testcase/output/output";
string input = "testcase/input/input";
string input2 = "testcase/input2/input";
string folder_expect = "testcase/expect/expect";

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); ++(i))
template <typename PHUCNHAN> void printArray(PHUCNHAN arr[], int n) {
    FOR(i, 0, n){
        OUTPUT << arr[i] << " ";
    }
    OUTPUT << std::endl;
}

void run(string task)
{
    if (stoi(task) <= 300)
    {
        // * Get input from 2 file input
        ifstream file_input(input + task+".txt");
        ifstream file_input2(input2 + task+".txt");
        if (file_input.fail() || file_input2.fail())
        {
            std::cout << "Error reading file" << std::endl;
            return;
        }
        int n, m;
        file_input >> n;
        file_input2 >> m;
        if (n != m) {
            std::cout << "My bad, so sorry!" << std::endl;
            return;
        }
        int graph[max_vertices][max_vertices];
        int graph2[max_vertices][max_vertices];
        FOR(i, 0, n)
        {
            FOR(j, 0, n)
            {
                file_input >> graph[i][j];
                file_input2 >> graph2[i][j];
            }
        }
        // * initial BFVal and BFPrev = -1
        int BFVal[max_vertices];
        int BFPrev[max_vertices];
        // * get start vertex
        char start_vertex;
        file_input >> start_vertex;
        // * Do BF for graph 1 n times
        setAllElement<int>(BFVal, -1, n);
        setAllElement<int>(BFPrev, -1, n);
        FOR(i, 0, n)
        {
            BF(graph, n, start_vertex, BFVal, BFPrev);
            OUTPUT << "Step " << i << ": " << std::endl;
            printArray<int>(BFVal, n);
            printArray<int>(BFPrev, n);
        }
        // * Do BF for graph 2 n times
        setAllElement<int>(BFVal, -1, n);
        setAllElement<int>(BFPrev, -1, n);
        FOR(i, 0, n)
        {
            BF(graph2, n, start_vertex, BFVal, BFPrev);
            OUTPUT << "Step " << i << ": " << std::endl;
            printArray<int>(BFVal, n);
            printArray<int>(BFPrev, n);
        }
        // * Do BF for graph 1 mix graph 2 n times
        setAllElement<int>(BFVal, -1, n);
        setAllElement<int>(BFPrev, -1, n);
        FOR(i, 0, n)
        {
            if (i % 2){
                BF(graph2, n, start_vertex, BFVal, BFPrev);
            }else{
                BF(graph, n, start_vertex, BFVal, BFPrev);
            }
            OUTPUT << "Step " << i << ": " << std::endl;
            printArray<int>(BFVal, n);
            printArray<int>(BFPrev, n);
        }
        FOR(i, 0, n){
            FOR(j, 0, n){
                OUTPUT << BF_Path(graph, n, char(i+'A'), char(j+'A')) << endl;
            }
        }
        FOR(i, 0, n){
            FOR(j, 0, n){
                OUTPUT << BF_Path(graph2, n, char(i+'A'), char(j+'A')) << endl;
            }
        }
    }
    else
    {
        // * Test for Traveling Salesman Problem
        ifstream file_input(input + task+".txt");
        if (file_input.fail())
        {
            std::cout << "Error reading file" << std::endl;
            return;
        }
        int n;
        file_input >> n;
        int graph[max_vertices][max_vertices];
        FOR(i, 0, n)
        {
            FOR(j, 0, n)
            {
                file_input >> graph[i][j];
            }
        }
        char start_vertex;
        file_input >> start_vertex;
        OUTPUT << "Traveling Saleman Problem Testcase\n";
        OUTPUT << Traveling(graph, n, start_vertex) << std::endl;
        int output_cost = cost(graph, Traveling(graph, n, start_vertex));
        OUTPUT << "Cost:\n" << output_cost << std::endl;
        int expect_cost = 1e9;
        double diviation = 1.0;
        // read file expect in line 4 to get cost(int)
        ifstream file_expect(folder_expect + task + ".txt");
        if (file_expect.fail())
        {
            std::cout << "Error reading file expect" << std::endl;
            return;
        }
        string line;
        while (getline(file_expect, line))
        {
            if (line == "Cost:")
            {
                file_expect >> expect_cost;
                break;
            }
        }
        diviation = (output_cost - expect_cost) * 1.0 / expect_cost;
        OUTPUT << "Diviation: " << diviation << std::endl;
        if (diviation < 0.05 && diviation > -0.05)
        {
            OUTPUT << "OK" << std::endl;
            result_success += task + " ";
        }
        else
        {
            OUTPUT << "Fail" << std::endl;
            result_fail += task + " ";
        }
    }
}

int main(int argc, char *argv[])
{
	std::cout << "Start run test for Discrete Structure Assignment" << std::endl;


    int START = 1, END = 300;
    int fullTask = 300;

    if (argc == 1)
    {
        std::cout << "Running test : ";
        START = 1;
        END = 306;
        FOR(i, START, END + 1)
        {
            std::cout << i << " ";
            OUTPUT.open(folder_output + to_string(i) + ".txt");
            run(to_string(i));
            OUTPUT.close();
        }
    }

    else if(argc == 2)
    {
        string stringTask = argv[1];
        if (isNumber(stringTask))
        {
            std::cout << "checking test : " << argv[1];
            START = stoi(stringTask);
            END = stoi(stringTask);
            OUTPUT.open(folder_output + stringTask + ".txt");
            run(stringTask);
            OUTPUT.close();            
        }
        else
        {
            std::cout << "Please re-enter the correct command" << std::endl;
            std::cout << "./main task1\n./main task2\n./main task3\n./main task4\n./main task5\n./main number" << std::endl;
            return 0;
        }
    }
    else if (argc == 3 && isNumber(argv[1]) && isNumber(argv[2]))
    {
        std::cout << "checking test : ";
        START = stoi(argv[1]);
        END = stoi(argv[2]);
        FOR(i, START, END + 1)
        {
            std::cout << i << " ";
            OUTPUT.open(folder_output + to_string(i) + ".txt");
            run(to_string(i));
            OUTPUT.close();
        }           
    }
    else 
    {
        std::cout << "Please re-enter the correct command" << std::endl;
        std::cout << "./main task1\n./main task2\n./main task3\n./main task4\n./main task5\n./main number" << std::endl;
        return 0;
    }

	std::cout << "\nOK: runs without errors\n" << std::endl;
    if (START > 300)
    {
        std::cout << "In Traveling Salesman Problem" << std::endl;
        std::cout << "Success: " << result_success << std::endl;
        std::cout << "Fail: " << result_fail << std::endl;
    }
    else if (END > 300)
    {
        std::cout << "In Bellman Ford Algorithm" << std::endl;
        comparefile(START, 300);
        std::cout << "In Traveling Salesman Problem" << std::endl;
        std::cout << "Success: " << result_success << std::endl;
        std::cout << "Fail: " << result_fail << std::endl;
    }
    else if (END <= 300){
        std::cout << "In Bellman Ford Algorithm" << std::endl;
        comparefile(START, END);
    }
        
    return 0;
}
bool isNumber(string str) {
    FOR(i, 0, str.length()){
        char c = str[i];
        if (!isdigit(c)) return false;
    }
    return true;
}

void comparefile(int start, int end)
{
	vector<int> result;
	FOR(i, start, end + 1)
	{
		ifstream read_output(folder_output + to_string(i) + ".txt");
		ifstream read_expect(folder_expect + to_string(i) + ".txt");
		if (read_output.fail())
		{
			std::cout << "Error reading file output"<< end;
			return;
		}
        if (read_expect.fail())
        {
            std::cout << "Error reading file expect"<< end;
            return;
        }
		string s1, s2;
		while (read_output >> s1 && read_expect >> s2)
		{
			if (s1 != s2)
			{
				result.push_back(i);
				break;
			}
		}
		if (read_output >> s1 || read_expect >> s2)
		{
			if (result.size() == 0 || result.size() > 0 && result[result.size() - 1] != i)
				result.push_back(i);
		}
	}

	if (result.size() == 0)
	{
		std::cout << "Success: test " << start << " to " << end << std::endl;
	}
	else
	{
		std::cout << "percent success : " << (1 - result.size() * 1.0 / (end - start + 1)) * 100 << "%" << std::endl;
		std::cout << "Fail : test [";
		FOR(i, 0, result.size() - 1)
		{
			std::cout << result[i] << ", ";
		}
		std::cout << result[result.size() - 1] << "]\n";
        std::cout << "link check comparefile: https://www.diffchecker.com/text-compare/" << std::endl;
		//printTestFail(result[0]);
	}
}

void copyFile(const std::string& sourcePath, const std::string& destinationPath) {
    std::ifstream sourceFile(sourcePath, std::ios::binary);
    std::ofstream destinationFile(destinationPath, std::ios::binary);

    if (!sourceFile) {
        std::cerr << "Error opening source file: " << sourcePath << std::endl;
        return;
    }


    if (!destinationFile) {
        std::cerr << "Error opening destination file: " << destinationPath << std::endl;
        return;
    }

    destinationFile << sourceFile.rdbuf();

    if (!destinationFile) {
        std::cerr << "Error copying data from " << sourcePath << " to " << destinationPath << std::endl;
    }
}
int cost(int graph[][20], string path)
{
    int n = path.length();
    int cost = 0;
    for (int i = 0; i < n - 1; i+=2)
    {
        cost += graph[path[i] - 'A'][path[i + 2] - 'A'];
    }
    return cost;
}