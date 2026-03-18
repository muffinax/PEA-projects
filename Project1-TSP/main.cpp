#include <iostream>
#include "TSPData.h"
#include "RandomAlgorithm.h"
#include "BruteForceAlgorithm.h"
#include "NNAlgorithm.h"
#include "RNNAlgorithm.h"

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
    cout<<" 1 - Brute Force"<<endl;
    cout<<" 2 - Random"<<endl;
    cout<<" 3 - Nearest Neighbour"<<endl;
    cout<<" 4 - Repetitive Nearest Neighbour"<<endl;
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

void runBF(){
    BruteForceAlgorithm bfAlgorithm = BruteForceAlgorithm();
    bfAlgorithm.run(tspData);
    bfAlgorithm.showResult();
}

void runRandom(){
    int n;
    RandomAlgorithm randomAlgorithm = RandomAlgorithm();
    cout<<"Enter number of permutations: "<<endl;
    cin>>n;
    randomAlgorithm.setNumberOfTries(n);
    randomAlgorithm.run(tspData);
    randomAlgorithm.showResult();
}

void runNN(){
    NNAlgorithm nnAlgorithm = NNAlgorithm();
    nnAlgorithm.run(tspData);
    nnAlgorithm.showResult();
}

void runRNN(){
    RNNAlgorithm rnnAlgorithm = RNNAlgorithm();
    rnnAlgorithm.run(tspData);
    rnnAlgorithm.showResult();
}

void runExperiments() {
    int N;
    cout << "Enter number of cities: ";
    cin >> N;

    double sumErrNN = 0, sumErrRNN = 0, sumErrRand = 0;
    long long timeBF =0, timeNN =0, timeRNN =0, timeRand =0;

    for(int i = 0; i < 100; i++) {
        tspData.generateAsymetricData(N, 100);

        // 1. BF
        BruteForceAlgorithm bf;
        bf.run(tspData);
        long opt = bf.getLength();
        timeBF+=bf.getTime();

        // 2. NN
        NNAlgorithm nn;
        nn.run(tspData);
        sumErrNN += (double)(nn.getLength() - opt) / opt;
        timeNN+=nn.getTime();

        // 3. RNN
        RNNAlgorithm rnn;
        rnn.run(tspData);
        sumErrRNN += (double)(rnn.getLength() - opt) / opt;
        timeRNN+=rnn.getTime();

        // 4. Random (10*N permutacji)
        RandomAlgorithm ra;
        ra.setNumberOfTries(N*10);
        ra.run(tspData);
        sumErrRand += (double)(ra.getLength() - opt) / opt;
        timeRand+=ra.getTime();
    }

    cout << "Average relative mistake for N=" << N << ":" << endl;
    cout << "NN: " << (sumErrNN / 100.0) * 100 << "%" << endl;
    cout << "RNN: " << (sumErrRNN / 100.0) * 100 << "%" << endl;
    cout << "Random: " << (sumErrRand / 100.00) * 100 << "%" << endl;

    cout << endl << "Average time for N=" << N << ":" << endl;
    cout << "BF: " << (double)timeBF / 100.0 << " microseconds" << endl;
    cout << "NN: " << (double)timeNN / 100.0 << " microseconds" << endl;
    cout << "RNN: " << (double)timeRNN / 100.0 << " microseconds" << endl;
    cout << "Random: " << (double)timeRand / 100.00 << " microseconds" << endl;
}

int main() {
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
                            runBF(); break;
                        case '2':
                            runRandom(); break;
                        case '3':
                            runNN(); break;
                        case '4':
                            runRNN(); break;
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
