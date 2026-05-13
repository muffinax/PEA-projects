#include <iostream>
#include <fstream>
#include "TSPData.h"
#include "SimulatedAnnealingAlgorithm.h"

using namespace std;

struct Result{
    string filename;
    int path;
};

TSPData tspData = TSPData();
SimulatedAnnealingAlgorithm saAlg = SimulatedAnnealingAlgorithm();
bool def_L = true;  //is L default
string filename;    //data file
string resultfile="sol-ATSP.txt";
Result resultList[30];

char menu(){
    char x;
    cout << endl;
    cout << "MENU"<<endl;
    cout<< "Choose one option:"<<endl;
    cout<<" 1 - Open data from file"<<endl;
    cout<<" 2 - Show last saved data"<<endl;
    cout<<" 3 - Set max time"<<endl;
    cout<<" 4 - Calculate starting path"<<endl;
    cout<<" 5 - Modify parameters"<<endl;
    cout<<" 6 - Run algorithm"<<endl;
    cout<<" e - End program" << endl;
    cin>>x;
    return x;
}

void openResult(){
//    cout<<"Enter path to file with solutions: ";
//    cin>>resultfile;

    ifstream reader(resultfile);  //opening file

    if (!reader.is_open()) {
        cout << "Error - file " << resultfile << " doesn't exist" << endl;
        return;
    }

    string line;
    int index = 0;

    while(getline(reader, line)){
        char fil[50];
        int result;
        if(sscanf(line.c_str(), " %[^:]: %d", &fil, &result) == 2 ){
            resultList[index].filename = fil;
            resultList[index].path = result;
            index++;

            if (index >= 30) break;
        }
    }
    cout << "Successfully loaded " << index << " optimal results!" << endl;
    reader.close();
}

void openFile(){
    cout<<"Enter file name: ";
    cin>>filename;
    tspData.getDataFromFile(filename);
    if(tspData.getCities()>0){
        saAlg.clear();
        saAlg.set_L(saAlg.calculateTransformations(tspData.getCities()));
    }
}

void showPath(int* path , int length, int cities){
    for (int i = 0; i < cities; i++) {
        cout << path[i] << " -> ";
    }
    cout << path[0] << endl;
    cout<<"Length: "<<length<< endl;
}

void showResult(){
    cout<< endl;
    cout<< "Algorithm result:" << endl;

    if (saAlg.get_finalLength() == 0 || saAlg.get_finalPath() == nullptr) {
        cout<< endl << "No results. Try first running the algorithm" << endl;
        return;
    }

    cout<<"Optimal path: ";
    showPath(saAlg.get_finalPath(), saAlg.get_finalLength(), tspData.getCities());

    cout << "Time: " << saAlg.get_time() << " microseconds" << endl;
    cout<<endl;

    //Optimal result:
    if (filename != "") {
        string baseName = filename;

        //Preparing filename
        //cutting path/folders
        size_t slashPos = baseName.find_last_of("/\\");
        if (slashPos != string::npos) {
            baseName = baseName.substr(slashPos + 1);
        }

        // cutting .atsp
        size_t dotPos = baseName.find_last_of('.');
        if (dotPos != string::npos) {
            baseName = baseName.substr(0, dotPos);
        }

        //searching matching name
        int bestKnown = -1;
        for (int i = 0; i < 30; i++) {
            if (resultList[i].filename != "" && resultList[i].filename == baseName) {
                bestKnown = resultList[i].path;
                break;
            }
        }

        if (bestKnown != -1) {
            cout << "Best known solution: " << bestKnown << endl;

            int myResult = saAlg.get_finalLength();
            double error = ((double)(myResult - bestKnown) / bestKnown) * 100.0;

            cout << "Error (PRD): " << error << " %" << endl;
        }
    }
}

void change_maxTime(){
    char choice;
    cout << "Saved maximum algorithm runtime: " << saAlg.get_maxTime() << " s" << endl << endl;
    cout << "Do you want to change it?" << endl << " y - yes" << endl << " n - no" << endl << endl;

    cin>>choice;

    if(choice == 'y' || choice == 'Y'){
        int x;
        cout << "Set max time: ";
        cin>>x;
        saAlg.set_maxTime(x);
    }
    else if(choice == 'n' || choice == 'N') return;
    else    cout << "Chose YES or NO!" << endl;
}

void calculate_startingPath(){
    if (tspData.getCities() == 0) {
        cout << "Error: First read data from a file (Option 1)!" << endl;
        return;
    }

    char choice;
    cout << "How do you want starting path generated? " << endl << endl;
    cout << " 1 - random" << endl << " 2 - nearest neighbour" << endl << endl;

    cin>>choice;
    if(choice == '1')   saAlg.randStartingPath(tspData);
    else if(choice == '2') saAlg.nearestStartingPath(tspData);
    else{
        cout << "Chose YES or NO!" << endl;
        return;
    }

    cout << "Starting path:" << endl;
    showPath(saAlg.get_startingPath(), saAlg.get_startingLength(), tspData.getCities());
}

void runAlgorithm(){
    if (tspData.getCities() == 0) {
        cout << "Error: First read data from a file (Option 1)!" << endl;
        return;
    }
    saAlg.run(tspData);
    showResult();
}

void change_parameters(){
    cout << "ALGORITHM PARAMETERS" << endl;
    cout << "T: " << saAlg.get_T() << endl;
    cout << "alpha: " << saAlg.get_alpha() << endl;
    if(!def_L)  cout << "L: " << saAlg.get_L() << endl;
    else{
        if(saAlg.get_L() <= 0)    cout << "L: (n*(n-1))/2" << endl;
        else cout << "L: " << saAlg.get_L() << "  [ (n*(n-1))/2 ]" << endl;
    }

    char choice;
    cout<<endl<<"Do you want to change parameters?" << endl << " y - yes" << endl << " n - no" << endl << endl;
    cin>>choice;

    if(choice == 'y' || choice == 'Y'){

        cout<<endl<<"Do you want to set DEFAULT parameters?" << endl << " y - yes" << endl << " n - no" << endl << endl;
        cin>>choice;

        if(choice == 'y' || choice == 'Y'){
            saAlg.set_default();
            def_L=true;
        }
        else if(choice == 'n' || choice == 'N'){
            int temL;
            double temT, temA;
            cout << "Set T: ";
            cin>>temT;
            cout << "Set alpha: ";
            cin>>temA;
            cout << "Set L: ";
            cin>>temL;

            if(temT>0 && temL>0 && temA>0 && temA<1){
                saAlg.set_T(temT);
                saAlg.set_alpha(temA);
                saAlg.set_L(temL);
                def_L=false;
                cout << "Parameters saved!"<<endl;
            }
            else cout << "Wrong parameters!"<<endl;
        }
        else    cout << "Chose YES or NO!" << endl;

    }
    else if(choice == 'n' || choice == 'N') return;
    else    cout << "Chose YES or NO!" << endl;
}

int main() {
    srand(time(NULL));
    openResult();
    char choice;
    while(true){
        choice = menu();
        switch (choice) {
            case '1':
                openFile(); break;
            case '2':
                tspData.showData(); break;
            case '3':
                change_maxTime(); break;
            case '4':
                calculate_startingPath(); break;
            case '5':
                change_parameters();
                break;
            case '6':
                runAlgorithm();
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
