#include <iostream>
#include "TSPData.h"
#include "DFSAlgorithm.h"

using namespace std;
TSPData tspData = TSPData();

char menu(){
    char x;
    cout << endl;
    cout << "MENU"<<endl;
    cout<< "Choose one option:"<<endl;
    cout<<" 1 - Open data from file"<<endl;
    cout<<" 2 - Generate random data"<<endl;
    cout<<" 3 - Show last saved data"<<endl;
    cout<<" 4 - Run chosen algorithm on last saved data"<<endl;
    cout<<" 5 - Run experiments (STARTS 100 TESTS!!!)"<<endl;
    cout<<" e - End program" << endl;
    cin>>x;
    return x;
}

char menuAlgorythm(){
    char x;
    cout << endl;
    cout << "RUN ALGORITHM"<<endl;
    cout<< "Choose algorithm to run:"<<endl;
    cout<<" 1 - DFS"<<endl;
    cout<<" e - Back" << endl;
    cin>>x;
    return x;
}

void openFile(){
    string filename;
    cout<<"Enter file name: ";
    cin>>filename;
    tspData.getDataFromFile(filename);
}

void generateData(){
    int num, max;
    cout<<"Enter the number of cities: ";
    cin>>num;
    cout<<"Enter max path cost: ";
    cin>>max;
    tspData.generateAsymetricData(num,max);
}

void runDFS() {
    DFSAlgorithm dfsAlgorithm = DFSAlgorithm();
    dfsAlgorithm.run(tspData);
    dfsAlgorithm.showResult();
}

void runExperiments() {
    int N;
    cout << "Enter number of cities: ";
    cin >> N;

    long long timeDFS=0;

    for(int i = 0; i < 100; i++) {
        tspData.generateAsymetricData(N, 100);

        // 1. DFS
        DFSAlgorithm dfs;
        dfs.run(tspData);
        timeDFS+=dfs.getTime();
    }

    cout << endl << "Average time for N=" << N << ":" << endl;
    cout << "BF: " << (double)timeDFS / 100.0 << " microseconds" << endl;
}

int main(){
    srand(time(NULL));
    char choice;
    while(true){
        choice = menu();
        switch (choice) {
            case '1':
                openFile(); break;
            case '2':
                generateData(); break;
            case '3':
                tspData.showData(); break;
            case '4':
                char alg;
                while(true){
                    alg=menuAlgorythm();
                    switch (alg) {
                        case '1':
                            runDFS(); break;
                        case 'e':
                            break;
                        default:
                            cout<<endl<<"Choose option from the list!"<<endl;
                    }
                    if(alg=='e')    break;
                }
                break;
            case '5':
                runExperiments();
                break;
            case 'e':
                cout<<"Shutting down program"<<endl;
                exit(0);
            default:
                cout<<endl<<"Choose option from MENU!"<<endl;
        }
    }
    return 0;
}