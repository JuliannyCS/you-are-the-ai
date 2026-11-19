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

    // Phase 2 portion. Moderating text comments. So true = SAFE and false = HARMFUL
    vector <string> comments = {
        "Great recipe! I added a little\nextra garlic and my family loved it.",
        "You are completely worthless.\nDelete your account and disappear.",
        "Does anyone know what time\nthe library closes on Fridays?",
        "People like you don't belong here.\nGo back to where you came from.",
        "URGENT: Send your bank details now\nor your account will be locked."
    };
    vector<bool> isSafe = { true, false, true, false, false };

    int numPhotos = photos.size();
    int totalTasks = numPhotos + comments.size();

    //Defining two side by side clickable buttons
    Rectangle leftBtn = { 240, 560, 220, 80 };
    Rectangle rightBtn = { 540, 560, 220 , 80 };

    while (!WindowShouldClose() && timeLeft > 0 && tasksCompleted < totalTasks) {
        timeLeft -= GetFrameTime();
        if (timeLeft < 0) timeLeft = 0;
        Vector2 mousePos = GetMousePosition();
        bool hoverLeft = CheckCollisionPointRec(mousePos, leftBtn);
        bool hoverRight = CheckCollisionPointRec(mousePos, rightBtn);
        
        //phase 2
        bool isPhase2 = (tasksCompleted >= numPhotos);

        if (hoverLeft && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!isPhase2 && isCat[tasksCompleted]) correctLabels++;
            else if (isPhase2 && isSafe[tasksCompleted - numPhotos]) correctLabels++;
            tasksCompleted++;
        }
        if (hoverRight && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!isPhase2 && !isCat[tasksCompleted]) correctLabels++;
            else if (isPhase2 && !isSafe[tasksCompleted - numPhotos]) correctLabels++;
            tasksCompleted++;
        }

        //After the final task is given, do a stop
        if (tasksCompleted >= totalTasks) break;

        //Rechecking the whole phase so that no click is moved to phase 2
        isPhase2 = (tasksCompleted >= numPhotos);

        //Beginning to draw
        BeginDrawing();
        Color bgColor = isPhase2 ? Color{ 28, 28, 36, 255 } : RAYWHITE;
        Color textColor = isPhase2 ? RAYWHITE : DARKGRAY;
        ClearBackground(bgColor);

        // Progress bar across all 10 tasks
        float progress = (float)tasksCompleted / (float)totalTasks;
        DrawRectangle(40, 12, 920, 12, LIGHTGRAY);
        DrawRectangle(40, 12, (int)(920 * progress), 12, isPhase2 ? RED : BLUE);

        // Top HUD: Timer and task counter
        DrawText(TextFormat("Time: %.1fs", timeLeft), 780, 30, 32, isPhase2 ? RED : MAROON);
        DrawText(TextFormat("Labeled: %d / %d", tasksCompleted, totalTasks), 40, 30, 32, textColor);

        //prompt
        // Middle Zone: Image (Phase 1) vs. Comment Card (Phase 2)
        if (!isPhase2) {
            DrawText("Is this a cat?", 380, 100, 36, BLACK);

            Texture2D currentPhoto = photos[tasksCompleted];
            Rectangle source = { 0, 0, (float)currentPhoto.width, (float)currentPhoto.height };
            Rectangle dest = { 300, 170, 400, 320 };
            DrawTexturePro(currentPhoto, source, dest, { 0, 0 }, 0.0f, WHITE);
            DrawRectangleLinesEx(dest, 3, LIGHTGRAY);
        } else {
            DrawText("Is this comment harmful?", 290, 100, 36, RED);

            Rectangle card = { 150, 180, 700, 290 };
            DrawRectangleRec(card, Color{ 45, 45, 58, 255 });
            DrawRectangleLinesEx(card, 3, GRAY);

            DrawText(comments[tasksCompleted - numPhotos].c_str(), 190, 270, 28, RAYWHITE);
        }

        // Drawing the left button ("CAT" -> "SAFE")
        DrawRectangleRec(leftBtn, hoverLeft ? DARKGREEN : GREEN);
        DrawText(isPhase2 ? "SAFE" : "CAT", isPhase2 ? 305 : 315, 585, 32, WHITE);

        // Drawing the right button ("NOT CAT" -> "HARMFUL")
        DrawRectangleRec(rightBtn, hoverRight ? MAROON : RED);
        DrawText(isPhase2 ? "HARMFUL" : "NOT CAT", 575, 585, 32, WHITE);

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
