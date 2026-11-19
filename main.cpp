#include <iostream>
#include <string>
#include "raylib.h"
#include <vector>
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
    //Mahian....
    //Starting of the raylib window.
    const int screenWidth = 1000;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "LabelBot AI - Worker Portal");
    SetTargetFPS(60);

    //Loading the image after InitWIndow
    // Load all 5 Phase 1 images and alternating cats and non-cats
    vector <string> imageFiles = {
        "cats-img.jpg", "dog.jpg", "cat2.jpg", "car.jpg", "cat3.jpg"
    };
    vector <bool> isCat = { true, false, true, false, true };

    vector <Texture2D> photos;
    for (int i = 0; i < (int)imageFiles.size(); i++) {
        Texture2D tex = LoadTexture(imageFiles[i].c_str());
        if (tex.id == 0) {
            cout << "Error: Could not load " << imageFiles[i] << endl;
            CloseWindow();
            return 1;
        }
        photos.push_back(tex);
    }

    float timeLeft = 30.0f;
    int tasksCompleted = 0;
    int correctLabels = 0;

    //Defining two side by side clickable buttons
    Rectangle leftBtn = { 240, 560, 220, 80 };
    Rectangle rightBtn = { 540, 560, 220 , 80 };

    while (!WindowShouldClose() && timeLeft > 0 && tasksCompleted < (int)photos.size()) {
        timeLeft -= GetFrameTime();
        if (timeLeft < 0) timeLeft = 0;
        Vector2 mousePos = GetMousePosition();
        bool hoverLeft = CheckCollisionPointRec(mousePos, leftBtn);
        bool hoverRight = CheckCollisionPointRec(mousePos, rightBtn);

        if (hoverLeft && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (isCat[tasksCompleted]) correctLabels++;
            tasksCompleted++;
        }
        if (hoverRight && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!isCat[tasksCompleted]) correctLabels++;
            tasksCompleted++;
        }

        // Stoping immediately if finishing the last image
        if (tasksCompleted >= (int)photos.size()) break;

        //Beginning to draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        float progress = (float)tasksCompleted / (float)photos.size();
        DrawRectangle(40, 12, 920, 12, LIGHTGRAY);
        DrawRectangle(40, 12, (int)(920 * progress), 12, BLUE);

        //Top hud. Timer and task counter
        DrawText(TextFormat("Time: %.1fs", timeLeft), 780, 30, 32, MAROON);
        DrawText(TextFormat("Labeled: %d", tasksCompleted), 40, 30, 32, DARKGRAY);

        //prompt
        DrawText("Is this a cat?", 380, 100, 36, BLACK);

        //Drawing  image scaled into a 400x320 box in the center
        Texture2D currentPhoto = photos[tasksCompleted];
        Rectangle source = { 0, 0, (float)currentPhoto.width, (float)currentPhoto.height };
        Rectangle dest = { 300, 170, 400, 320 };
        DrawTexturePro(currentPhoto, source, dest, { 0, 0 }, 0.0f, WHITE);
        DrawRectangleLinesEx(dest, 3, LIGHTGRAY);

        //Drawing the left button which is "CAT"
        DrawRectangleRec(leftBtn, hoverLeft ? DARKGREEN : GREEN);
        DrawText("CAT", 315, 585, 32, WHITE);

        //Drawinf the right button which is "NOT CAT"
        DrawRectangleRec(rightBtn, hoverRight ? MAROON : RED);
        DrawText("NOT CAT", 575, 585, 32, WHITE);

        EndDrawing();
    }

    //Cleaning up memory
    for (int i = 0; i < (int)photos.size(); i++) {
        UnloadTexture(photos[i]);
    }
    CloseWindow();

    cout << "\nShift over! Tasks completed: " << tasksCompleted << endl;
    cout << "Correct labels: " << correctLabels << " / " << tasksCompleted << endl;
    //Ending of Raylib Window........

    printFacts();
    
    return 0;
}
