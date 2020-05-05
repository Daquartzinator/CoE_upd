#include<iostream>
#include<vector>
using namespace std;

class Location {
public:
    string txName;
    vector<string> items;

    Location(string stxName){
        txName = stxName;
    }
};

void turnLeft(int *NS, int *EW){
    if (*NS == 1){
        (*NS)--;
        (*EW)++;
    } else if (*NS == -1){
        (*NS)++;
        (*EW)--;
    } else if (*EW == 1){
        (*NS)--;
        (*EW)--;
    } else {
        (*NS)++;
        (*EW)++;
    }
}

void turnRight(int *NS, int *EW){
    if (*NS == 1){
        (*NS)--;
        (*EW)--;
    } else if (*NS == -1){
        (*NS)++;
        (*EW)++;
    } else if (*EW == 1){
        (*NS)++;
        (*EW)--;
    } else {
        (*NS)--;
        (*EW)++;
    }
}

void turnAround(int *NS, int *EW){
    (*NS) *= -1;
    (*EW) *= -1;
}

int main(){
    string in1, in2;
    string temp[4] = {};
    Location L_VOID("a cavern wall.");
    Location L_center("the center of the large cavern.");
    L_center.items.push_back("torch");
    Location L_crackedWall("the cracked wall.");
    Location L_houseDoor("the door to the house.");
    Location L_pitMouth("the mouth of the large pit.");

    Location cavernMap[4][4] = {
        {L_VOID, L_VOID,        L_VOID,         L_VOID},
        {L_VOID, L_houseDoor,   L_crackedWall,  L_VOID},
        {L_VOID, L_center   ,   L_pitMouth,     L_VOID},
        {L_VOID, L_VOID,        L_VOID,         L_VOID}};

    int playerCol = 1;
    int playerRow = 2;
    int playerFacingNS = -1; /** -1 north, 1 south **/
    int playerFacingEW = 0; /** -1 west, 1 east **/

    vector<string> inventory;
    string lightS = "none";
    string weapon = "none";

    string strTemp;
    bool breaker = false;

	while (true){
        /* Status : where you are */
        cout << "\n\nYou are at " << cavernMap[playerRow][playerCol].txName;
        cout << "\nAhead of you is " << cavernMap[playerRow + playerFacingNS][playerCol + playerFacingEW].txName;
        cout << "\nTo your left is " << cavernMap[playerRow - playerFacingEW][playerCol + playerFacingNS].txName;
        cout << "\nTo your right is " << cavernMap[playerRow + playerFacingEW][playerCol - playerFacingNS].txName;
        cout << "\nBehind you is " << cavernMap[playerRow - playerFacingNS][playerCol - playerFacingEW].txName;
        for (int i = 0; i < cavernMap[playerRow][playerCol].items.size(); i++){
            cout << "\nThere is a " << cavernMap[playerRow][playerCol].items[i] << ".";
        }
        cout << "\n > ";

        cin >> in1 >> in2;

        /* Decipher user input */
        if (in1 == "go" || in1 == "walk"){
            if (in2 == "forward" || in2 == "f" || in2 == "left" || in2 == "l" || in2 == "right" || in2 == "r" || in2 == "backwards" || in2 == "back" || in2 == "b"){
                if (in2 == "left" || in2 == "l"){
                    turnLeft(&playerFacingNS, &playerFacingEW);
                } else if (in2 == "right" || in2 == "r"){
                    turnRight(&playerFacingNS, &playerFacingEW);
                } else if (in2 == "backwards" || in2 == "back" || in2 == "b"){
                    turnAround(&playerFacingNS, &playerFacingEW);
                }
                if (cavernMap[playerRow + playerFacingNS][playerCol + playerFacingEW].txName == "a cavern wall.") {
                    cout << "\nYou can't walk into a wall.";
                } else {
                    playerRow += playerFacingNS;
                    playerCol += playerFacingEW;
                }
            }
        } else if (in1 == "turn"){
            if (in2 == "left" || in2 == "l"){
                turnLeft(&playerFacingNS, &playerFacingEW);
            } else if (in2 == "right" || in2 == "r"){
                turnRight(&playerFacingNS, &playerFacingEW);
            } else if (in2 == "around") {
                turnAround(&playerFacingNS, &playerFacingEW);
            } else {
                cout << "\nI don't recognize that direction.";
            }
        } else if (in1 == "take"){
            breaker = false;
            for(int i = 0; i < cavernMap[playerRow][playerCol].items.size(); i++){
                if (in2 == cavernMap[playerRow][playerCol].items[i]){
                    cout << "\nYou take the " << cavernMap[playerRow][playerCol].items[i] << ".";
                    inventory.push_back(cavernMap[playerRow][playerCol].items[i]);
                    cavernMap[playerRow][playerCol].items.erase(cavernMap[playerRow][playerCol].items.begin() + i);
                    breaker = true;
                    break;
                }
            }
            if (!breaker){
                cout << "\nI don't recognize that item.";
            }
        } else if (in1 == "check"){
            if (in2 == "inventory" || in2 == "i"){
                cout << "\nInventory\n---------\n";
                if (inventory.size() == 0){
                    cout << "Your inventory is empty.";
                }
                for (int i = 0; i < inventory.size(); i++){
                    cout << inventory[i] << endl;
                }
                cout << "\nLight Source: " << lightS;
                cout << "\nWeapon: " << weapon;
            }
        } else if (in1 == "equip"){
            breaker = false;
            for (int i = 0; i < inventory.size(); i++){
                if (in2 == inventory[i]){
                    if (in2 == "torch"){
                        strTemp = lightS;
                        lightS = in2;
                        inventory.erase(inventory.begin() + i);
                        if (strTemp != "none"){
                            inventory.push_back(strTemp);
                        }
                    } else if (in2 == "dagger"){
                        strTemp = weapon;
                        weapon = in2;
                        inventory.erase(inventory.begin() + i);
                        if (strTemp != "none"){
                            inventory.push_back(strTemp);
                        }
                    } else {
                        cout << "\nYou can't equip that item.";
                    }
                    breaker = true;
                    break;
                }
            }
            if (!breaker){
                "\nI don't recognize that item.";
            }
        } else if (in1 == "quit" && in2 == "game"){
            cout << "\n\nAre you sure you want to quit?\n > ";
            cin >> in1;
            if (in1 == "y" || in1 == "yes"){
                return 0;
            }
        } else {
            cout << "\nI don't recognize that command.";
        }
    }
}
