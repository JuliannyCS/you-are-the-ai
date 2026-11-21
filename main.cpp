#include <iostream>
#include <string>
#include "raylib.h"
#include <vector>
#include <iomanip>
#include "Content.h"
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
    cout << "In 1918, 'computers' were people." << endl;
    cout << "In 2023, 'AI' was people too." << endl;
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

    SetTraceLogLevel(LOG_WARNING);   // hide raylib's INFO messages, only show warnings/errors
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

    float timeLeft = 45.0f;
    int tasksCompleted = 0;
    int correctLabels = 0;

        // Phase 2: comments from Content.h. There is no "right" answer on purpose.
    vector<string> comments(COMMENTS, COMMENTS + NUM_COMMENTS);

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
            
            tasksCompleted++;
        }
        if (hoverRight && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!isPhase2 && !isCat[tasksCompleted]) correctLabels++;
           
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

        // ----- Ending screen: "The AI was you." (Julianny) -----
    // Earnings use the pay rates from our research (top of file)
    double playerEarnings = tasksCompleted * PAY_PER_TASK;
    double companyEarnings = tasksCompleted * COMPANY_PER_TASK;

    string finalMessage = "The AI was you, " + name + ".";
    float endTimer = 0.0f;            // seconds since the ending screen started
    const float GLITCH_START = 1.5f;  // when the logo starts glitching
    const float TYPE_START = 3.0f;    // when the message starts typing
    const float TYPE_SPEED = 0.08f;   // seconds per letter
    float typeEnd = TYPE_START + finalMessage.length() * TYPE_SPEED;
    float barStart = typeEnd + 0.5f;  // bars start after the message is typed

    // make the font smaller if a long name makes the message too wide
    int msgSize = 52;
    while (MeasureText(finalMessage.c_str(), msgSize) > screenWidth - 80 && msgSize > 24) {
        msgSize -= 2;
    }

    while (!WindowShouldClose() && !IsKeyPressed(KEY_ENTER)) {
        endTimer += GetFrameTime();

        BeginDrawing();
        ClearBackground(Color{ 15, 15, 20, 255 });   // dark screen: the "AI app" is gone

        // 1) the "LabelBot AI" logo, then it glitches and breaks
        if (endTimer < TYPE_START) {
            const char* logo = "LabelBot AI";
            int logoX = (screenWidth - MeasureText(logo, 72)) / 2;
            int logoY = 300;

            if (endTimer < GLITCH_START) {
                DrawText(logo, logoX, logoY, 72, Color{ 120, 140, 255, 255 });
            } else {
                // glitch: random shake, red/blue copies, flicker and broken lines
                int dx = GetRandomValue(-12, 12);
                int dy = GetRandomValue(-6, 6);
                DrawText(logo, logoX + dx - 4, logoY + dy, 72, Fade(RED, 0.7f));
                DrawText(logo, logoX + dx + 4, logoY - dy, 72, Fade(SKYBLUE, 0.7f));
                if (GetRandomValue(0, 3) > 0) {
                    DrawText(logo, logoX + dx, logoY, 72, WHITE);
                }
                for (int i = 0; i < 5; i++) {
                    int y = GetRandomValue(0, screenHeight);
                    DrawRectangle(0, y, screenWidth, GetRandomValue(2, 8), Fade(WHITE, 0.15f));
                }
            }
        }
        // 2) typewriter effect with the player's name
        else {
            int letters = (int)((endTimer - TYPE_START) / TYPE_SPEED);
            if (letters > (int)finalMessage.length()) letters = finalMessage.length();
            string shown = finalMessage.substr(0, letters);

            // measure the FULL message so the text doesn't move while typing
            int msgX = (screenWidth - MeasureText(finalMessage.c_str(), msgSize)) / 2;
            DrawText(shown.c_str(), msgX, 200, msgSize, WHITE);

            // blinking cursor while it types
            if (letters < (int)finalMessage.length() && (int)(endTimer * 4) % 2 == 0) {
                DrawText("_", msgX + MeasureText(shown.c_str(), msgSize), 200, msgSize, WHITE);
            }
        }

        // 3) money bars grow after the message is done
        if (endTimer > barStart && companyEarnings > 0) {
            float grow = (endTimer - barStart) / 1.5f;   // goes from 0 to 1 in 1.5 seconds
            if (grow > 1.0f) grow = 1.0f;

            int barX = 150;
            int maxWidth = 700;
            int playerWidth = (int)(maxWidth * (playerEarnings / companyEarnings) * grow);
            int companyWidth = (int)(maxWidth * grow);

            DrawText(TextFormat("You: $%.2f", playerEarnings * grow), barX, 340, 26, LIGHTGRAY);
            DrawRectangle(barX, 375, playerWidth, 40, LIGHTGRAY);

            DrawText(TextFormat("The company: $%.2f", companyEarnings * grow), barX, 450, 26, RED);
            DrawRectangle(barX, 485, companyWidth, 40, RED);
        }

                // 4) hint at the end (blinks so the player notices it)
        if (endTimer > barStart + 1.5f && (int)(endTimer * 2) % 2 == 0) {
            const char* hint = "Press ENTER to see the truth in the terminal";
            DrawText(hint, (screenWidth - MeasureText(hint, 26)) / 2, 600, 26, WHITE);
        
        }

        EndDrawing();
    }
    //Cleaning up memory
    for (int i = 0; i < (int)photos.size(); i++) {
        UnloadTexture(photos[i]);
    }
    CloseWindow();

    cout << fixed << setprecision(2);   // always show money with 2 decimals
    cout << "\nShift over! Tasks completed: " << tasksCompleted << endl;
    cout << "You earned $" << playerEarnings << ". The company made $" << companyEarnings << "." << endl;
    //Ending of Raylib Window........

    printFacts();

    return 0;
}