#include <iostream>
#include <string>
using namespace std;

// Pay numbers based on: Billy Perrigo, "Exclusive: OpenAI Used Kenyan Workers on 
// Less Than $2 Per Hour to Make ChatGPT Less Toxic," TIME, Jan 18, 2023.
// https://time.com/6247678/openai-chatgpt-kenya-workers/
// Workers made $1.32-$2/hr and labeled 150-250 passages per 9-hour shift.
// OpenAI paid Sama $12.50/hr per worker.
const double PAY_PER_TASK = 0.07;
const double COMPANY_PER_TASK = 0.56;

// Shows the real facts behind the game at the end
void printFacts() {
    cout << endl;
    cout << "----- The truth behind LabelBot AI -----" << endl;
    cout << "In 1918, 'computers were people." << endl;
    cout << "In 2023,'AI' was people too." << endl;
    cout << "Workers in Kenya labeled text for ChatGPT for $1.32-$2 an hour." << endl;
    cout << "OpenAI paid the company $12.50 an hour per worker." << endl;
    cout << "The AI was you." << endl;
}

int main() {

    cout << "Welcome to LabelBot AI!" << endl;   // the program pretends to be an AI app

    cout << "Before we start, what is your name? ";
    string name;
    getline(cin, name);   // getline instead of cin >> so names with spaces
    cout << "Thanks, " << name << ". Our AI is ready to label your data." << endl;

    cout << "You will earn $" << PAY_PER_TASK << " for each item you label." << endl;

    // TODO: the raylib game window goes here (Mahian's part)

    printFacts();
    
    return 0;
}
