#include <raylib.h>
#include <stdio.h>

#define WINDOW_WIDTH 250
#define WINDOW_HEIGHT 250
#define WINDOW_NAME "Lidget"
#define FPS 5

#define DOWNSCALE_TARGET 32

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Image file path is required as first argument");
        return 1;
    }

    char *IMAGE_PATH = argv[1];

    Image originalImage = LoadImage(IMAGE_PATH);

    if (!IsImageValid(originalImage)) {
        fprintf(stderr, "Image is invalid");
        return 1;
    }
    Image pixelated = ImageCopy(originalImage);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);

    SetTargetFPS(FPS);

    ImageResize(&originalImage, WINDOW_WIDTH, WINDOW_HEIGHT);
    ImageResize(&pixelated, DOWNSCALE_TARGET, DOWNSCALE_TARGET);

    Texture2D originalTexture = LoadTextureFromImage(originalImage);
    Texture2D pixelatedTexture = LoadTextureFromImage(pixelated);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            if (IsWindowFocused()) {
                DrawTexture(originalTexture, 0, 0, WHITE);
            } else {
                float scale = (float)WINDOW_WIDTH / DOWNSCALE_TARGET;
                ClearBackground(BLACK);
                DrawTextureEx(pixelatedTexture, (Vector2){0, 0}, 0, scale, WHITE);
            }
        EndDrawing();
    }

    UnloadImage(originalImage);
    UnloadImage(pixelated);

    UnloadTexture(originalTexture);
    UnloadTexture(pixelatedTexture);

    CloseWindow();

    return 0;
}
