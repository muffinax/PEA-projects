#include <iostream>
#include "TSPData.h"
#include "DFSAlgorithm.h"
#include "BFSAlgorithm.h"
#include "LCAlgorithm.h"

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
    cout<<" 2 - BFS"<<endl;
    cout<<" 3 - LC"<<endl;
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
    cout<<"DFS";
    dfsAlgorithm.showResult();
}

void runBFS() {
    BFSAlgorithm bfsAlgorithm = BFSAlgorithm();
    bfsAlgorithm.run(tspData);
    cout<<"BFS";
    bfsAlgorithm.showResult();
}

void runLC() {
    LCAlgorithm lcAlgorithm = LCAlgorithm();
    lcAlgorithm.run(tspData);
    cout<<"LC";
    lcAlgorithm.showResult();
}

void runExperiments() {
    int N;
    cout << "Enter number of cities: ";
    cin >> N;

    int nDFS=0, xDFS=0, nBFS=0, xBFS=0, nLC=0, xLC=0;
    long long timeDFS=0, timeBFS=0, timeLC=0;

    for(int i = 0; i < 100; i++) {
        tspData.generateAsymetricData(N, 99);

        // 1. DFS
        DFSAlgorithm dfs;
        dfs.run(tspData);
        if(dfs.getTime()!=-1){
            timeDFS+=dfs.getTime();
            nDFS++;
        }
        else    xDFS++;


        // 2. BFS
        BFSAlgorithm bfs;
        bfs.run(tspData);
        if(bfs.getTime()!=-1){
            timeBFS+=bfs.getTime();
            nBFS++;
        }
        else    xBFS++;

        // 3. LC
        LCAlgorithm lc;
        lc.run(tspData);
        if(lc.getTime()!=-1){
            timeLC+=lc.getTime();
            nLC++;
        }
        else    xLC++;
    }

    cout << endl << "Percentage of stopped algorithms:" << endl;
    cout << "DFS: " << xDFS << "%" << endl;
    cout << "BFS: " << xBFS << "%" << endl;
    cout << "LC: " << xLC << "%" << endl;

    cout << endl << "Average time for N=" << N << ":" << endl;
    if (nDFS > 0)   cout << "DFS: " << (double)timeDFS / nDFS << " microseconds" << endl;
    else cout<<"DFS: All tests took over 5 min"<<endl;
    if (nBFS > 0)   cout << "BFS: " << (double)timeBFS / nBFS << " microseconds" << endl;
    else cout<<"BFS: All tests took over 5 min"<<endl;
    if (nLC > 0)    cout << "LC: " << (double)timeLC / nLC << " microseconds" << endl;
    else cout<<"LC: All tests took over 5 min"<<endl;
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
                        case '2':
                            runBFS(); break;
                        case '3':
                            runLC(); break;
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