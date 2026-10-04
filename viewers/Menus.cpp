#include "Menus.h"

/**
 * @file Menus.cpp
 * @brief Dá print aos menus.
 */

void mainMenu(){
    cout<<"-------------------------Main Menu-------------------------"<<endl;
    cout<<"Select the option you wish to go:                          "<<endl;
    cout<<"(1) Basic Service Metrics                               [2]"<<endl;
    cout<<"(2) Reliability and Sensitivity to Failures             [3]"<<endl;
    cout<<"(0) Quit                                                   "<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    string option;
    while (true){
        cout<<"Choose: ";
        cin>>option;
        if (option=="1"){
            secondMenu();
        }
        else if (option=="2"){
            thirdMenu();
        }
        else if (option=="0"){
            return;
        }
        else{
            cout << "You typed something that is not one of the options." << endl
                 <<"Try again? (YES: Any character | NO: 0): ";
            cin>>option;
            if (option == "0") break;
            continue;
        }
        return;
    }
}

void secondMenu(){
    cout<<"-------------------Basic Service Metrics-------------------"<<endl;
    cout<<"Select the option you wish to go:                          "<<endl;
    cout<<"(1) Maximum amount of water                           [2.1]"<<endl;
    cout<<"(2) Check if the water from the reservoirs is enough  [2.2]"<<endl;
    cout<<"(0) Go back                                                "<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    string option;
    while (true){
        cout<<"Choose: ";
        cin>>option;
        if (option=="1"){
            wsn2_1Menu();
        }
        else if (option=="2"){
            printCheckIfWSNIsEnough();
            pressAnyCharacterToContinue();
            secondMenu();
        }
        else if (option=="3"){

        }
        else if (option=="0"){
            mainMenu();
        }
        else{
            cout << "You typed something that is not one of the options." << endl
                 <<"Try again? (YES: Any character | NO: 0): ";
            cin>>option;
            if (option == "0") break;
            continue;
        }
        return;
    }
}

void thirdMenu(){
    cout<<"----------Reliability and Sensitivity to Failures----------"<<endl;
    cout<<"Select the option you wish to go:                          "<<endl;
    cout<<"(1) Removing a reservoir                              [3.1]"<<endl;
    cout<<"(2) Removing pumping station                          [3.2]"<<endl;
    cout<<"(3) Removing pipe                                     [3.3]"<<endl;
    cout<<"(0) Go back                                                "<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    string option;
    while (true){
        cout<<"Choose: ";
        cin>>option;
        if (option=="1"){
            string rCode = inputReservoir();
            printWSNWithoutAReservoir(rCode);
            pressAnyCharacterToContinue();
            thirdMenu();
        }
        else if (option=="2"){
            vector<string> psCodes = inputPumpStations();
            printWSNWithoutStation(psCodes);
            pressAnyCharacterToContinue();
            thirdMenu();
        }
        else if (option=="3"){
            vector<pair<string, string>> pipeList = inputPipes();
            printWSNWithoutPipes(pipeList);
            pressAnyCharacterToContinue();
            thirdMenu();
        }
        else if (option=="0"){
            mainMenu();
        }
        else{
            cout << "You typed something that is not one of the options." << endl
                 <<"Try again? (YES: Any character | NO: 0): ";
            cin>>option;
            if (option == "0") break;
            continue;
        }
        return;
    }
}

void wsn2_1Menu() {
    cout<<"------------------Maximum amount of water------------------"<<endl;
    cout<<"Select the option you wish to go:                          "<<endl;
    cout<<"(1) Maximum amount of water of a specific city        [2.1]"<<endl;
    cout<<"(2) Maximum amount of water of each city              [2.1]"<<endl;
    cout<<"(0) Go back                                                "<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    string option;
    while (true){
        cout<<"Choose: ";
        cin>>option;
        if (option=="1"){
            string cityCode = inputCity();
            printMaxFlowCity(cityCode);
            pressAnyCharacterToContinue();
            wsn2_1Menu();
        }
        else if (option=="2"){
            printMaxFlowCities();
            pressAnyCharacterToContinue();
            wsn2_1Menu();
        }
        else if (option=="0"){
            secondMenu();
        }
        else{
            cout << "You typed something that is not one of the options." << endl
                 <<"Try again? (YES: Any character | NO: 0): ";
            cin>>option;
            if (option == "0") break;
            continue;
        }
        return;
    }
}

string inputCity() {
    string ans;
    while (true) {
        cout<<"Type a city code that you wish to see: ";
        cin>>ans;
        if (cityExists(ans)) {
            return ans;
        } else {
            cout<<"You typed a wrong city code."<<endl;
            continue;
        }
    }
}
string inputReservoir() {
    string ans;
    while (true) {
        cout<<"Type a reservoir code that you wish to remove: ";
        cin>>ans;
        if (reservoirExists(ans)) {
            return ans;
        } else {
            cout<<"You typed a wrong reservoir code."<<endl;
            continue;
        }
    }
}
vector<string> inputPumpStations() {
    vector<string> ans;
    string input;
    while (true) {
        cout<<"Type a pumping station code that you wish to remove. You can type more, if you want."<<endl;
        cout<<"If you want to stop, type (0)."<<endl;
        cout<<"Pumping station code: ";
        cin>>input;
        if (pumpStationExsists(input)) {
            ans.push_back(input);
        } else if (input == "0") {
            return ans;
        } else {
            cout<<"You typed a wrong pumping station code."<<endl;
            continue;
        }
    }
}
vector<pair<string,string>> inputPipes() {
    vector<pair<string,string>> ans;
    string sourceCode, targetCode;
    while(true) {
        cout<<"Type the source and target codes. You can type more, if you want."<<endl;
        cout<<"If you want to stop, type (0)."<<endl;
        cout<<"Source code: ";
        cin>>sourceCode;
        if (sourceCode == "0") return ans;
        cout<<"Target code: ";
        cin>>targetCode;
        if (pipeExists(sourceCode, targetCode)) {
            ans.push_back({sourceCode, targetCode});
        } else if (targetCode == "0") {
            return ans;
        } else {
            cout<<"You typed a wrong source or target code or it doesn't exist a pipe connecting those points."<<endl;
            continue;
        }
    }
}
void pressAnyCharacterToContinue() {
    cout <<"Press any character to continue... ";
    string userInput;
    cin>>userInput;
}

