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

int main() {

    cout << "Welcome to LabelBot AI!" << endl;   // the program pretends to be an AI app

    cout << "Before we start, what is your name? ";
    string name;
    getline(cin, name);   // getline instead of cin >> so names with spaces
    cout << "Thanks, " << name << ". Our AI is ready to label your data." << endl;

    cout << "You will earn $" << PAY_PER_TASK << " for each item you label." << endl;
    
    return 0;
}
