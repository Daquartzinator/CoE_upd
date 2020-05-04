#include<iostream>
using namespace std;

class Location {
public:
    string txName;
    int x;
    int y;

    Location(string stxName, int sX, int sY){
        txName = stxName;
        x = sX;
        y = sY;
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

int main(){
    string in1, in2;
    string temp[4] = {};
    Location L_VOID("a cavern wall.", 0, 0);
    Location L_center("the center of the large cavern.", 1, 2);
    Location L_crackedWall("the cracked wall.", 2, 1);
    Location L_houseDoor("the door to the house.", 1, 1);
    Location L_pitMouth("the mouth of the large pit.", 2, 2);

    Location cavernMap[4][4] = {
        {L_VOID, L_VOID,        L_VOID,         L_VOID},
        {L_VOID, L_houseDoor,   L_crackedWall,  L_VOID},
        {L_VOID, L_center   ,   L_pitMouth,     L_VOID},
        {L_VOID, L_VOID,        L_VOID,         L_VOID}};

    int playerCol = 1;
    int playerRow = 2;
    int playerFacingNS = -1; /** -1 north, 1 south **/
    int playerFacingEW = 0; /** -1 west, 1 east **/

	while (true){
        cout << "\n\nYou are at " << cavernMap[playerRow][playerCol].txName;
        cout << "\nAhead of you is " << cavernMap[playerRow + playerFacingNS][playerCol + playerFacingEW].txName;
        cout << "\nTo your left is " << cavernMap[playerRow + playerFacingEW][playerCol + playerFacingNS].txName;
        cout << "\nTo your right is " << cavernMap[playerRow - playerFacingEW][playerCol - playerFacingNS].txName;
        cout << "\nBehind you is " << cavernMap[playerRow - playerFacingNS][playerCol - playerFacingEW].txName;
        cout << "\n > ";
        cin >> in1 >> in2;
        if (in1 == "go" || in1 == "walk"){
            if (in2 == "forward" || "f"){
                if (cavernMap[playerRow + playerFacingNS][playerCol + playerFacingEW].txName == "a cavern wall.") {
                    cout << "\nYou can't walk into a wall.";
                } else {
                    playerRow += playerFacingNS;
                    playerCol += playerFacingEW;
                }
            }
        } else if (in1 == "turn"){
            if (in2 == "left" || in2 == "l"){
//                if (playerFacingNS == 1){
//                    playerFacingNS--;
//                    playerFacingEW++;
//                } else if (playerFacingNS == -1){
//                    playerFacingNS++;
//                    playerFacingEW--;
//                } else if (playerFacingEW == 1){
//                    playerFacingNS--;
//                    playerFacingEW--;
//                } else {
//                    playerFacingNS++;
//                    playerFacingEW++;
//                }
                turnLeft(&playerFacingNS, &playerFacingEW);
                cout << playerFacingNS << playerFacingEW << endl;
            } else if (in2 == "right" || in2 == "r"){
                if (playerFacingNS == 1){
                    playerFacingNS--;
                    playerFacingEW--;
                } else if (playerFacingNS == -1){
                    playerFacingNS++;
                    playerFacingEW++;
                } else if (playerFacingEW == 1){
                    playerFacingNS++;
                    playerFacingEW--;
                } else {
                    playerFacingNS--;
                    playerFacingEW++;
                }
            } else if (in2 == "around") {
                playerFacingNS *= -1;
                playerFacingEW *= -1;
            } else {
                cout << "\nI don't recognize that direction.";
            }
        }
	}
}
