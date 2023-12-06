#define RLGL_IMPLEMENTATION
#include "rlgl.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "vertex.h"
#include "window.h"
#include <GLFW/glfw3.h>

const int WIDTH = 1280, HEIGHT = 720;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    rlViewport(0, 0, width, height);
}

/*
        Vector2 mouse = GetMousePosition();
        Vector2 virtualMouse = { 0 };
        virtualMouse.x = (mouse.x - (GetScreenWidth() - (gameScreenWidth*scale))*0.5f)/scale;
        virtualMouse.y = (mouse.y - (GetScreenHeight() - (gameScreenHeight*scale))*0.5f)/scale;
        virtualMouse = Vector2Clamp(virtualMouse, (Vector2){ 0, 0 }, (Vector2){ (float)gameScreenWidth, (float)gameScreenHeight });
*/

void CropViewport(int windowWidth, int windowHeight, int targetWidth, int targetHeight) {
    // Calculate the aspect ratio of the target size
    float targetAspectRatio = (float) targetWidth / targetHeight;

    // Calculate the aspect ratio of the window
    float windowAspectRatio = (float) windowWidth / windowHeight;

    // Calculate the scaled dimensions based on the aspect ratio
    int scaledWidth, scaledHeight;

    if (windowAspectRatio > targetAspectRatio) {
        // If window is wider, scale based on height
        scaledHeight = windowHeight;
        scaledWidth = (int) (targetAspectRatio * scaledHeight);
    } else {
        // If window is taller or has the same aspect ratio, scale based on width
        scaledWidth = windowWidth;
        scaledHeight = (int) (scaledWidth / targetAspectRatio);
    }

    // Calculate the position to center the scaled viewport
    int offsetX = (windowWidth - scaledWidth) / 2;
    int offsetY = (windowHeight - scaledHeight) / 2;

    // Set the scissor rectangle to crop the viewport
    rlScissor(offsetX, offsetY, scaledWidth, scaledHeight);

    // printf("%f, %f (%d, %d)\n", targetAspectRatio, windowAspectRatio, offsetX, offsetY);

    float scalingX = (float) windowWidth / (float) targetWidth;
    float scalingY = (float) windowHeight / (float) targetHeight;
    float scaling = std::min(scalingY, scalingX);

    rlOrtho(-windowWidth / scaling / 2.0f, windowWidth / scaling / 2.0f,
            -windowHeight / scaling / 2.0f, windowHeight / scaling / 2.0,
            0.1f, 100.0f);
}


void ClearBackground(Color color) {
    rlClearColor(color.r, color.g, color.b, color.a);// Set clear color
    rlClearScreenBuffers();                          // Clear current framebuffers
}

void BeginDrawing(void) {
    rlLoadIdentity();// Reset current matrix (modelview)
}

void EndDrawing(void) {
    rlDrawRenderBatchActive();// Update and draw internal render batch
}

unsigned char *load_image(const char *imagePath, int &width, int &height, int &channels) {
    return stbi_load(imagePath, &width, &height, &channels, 0);
}

class Texture {
public:
    Texture() : data(nullptr), width(0), height(0), format(0), id(0) {}

    void load_path(const char *path) {
        int channels;
        data = load_image(path, width, height, channels);

        if (channels == 1)
            format = RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
        else if (channels == 2)
            format = RL_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA;
        else if (channels == 3)
            format = RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8;
        else if (channels == 4)
            format = RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

        id = rlLoadTexture(data, width, height, format, 1);
    }

    void draw_at(Vec2 position) {
        rlSetTexture(id);
        rlBegin(RL_QUADS);

        rlColor4ub(255, 255, 255, 255);

        float half_width = 0.5f * (width / 2.0f);
        float half_height = 0.5f * (height / 2.0f);

        rlTexCoord2f(0.0f, 1.0f);
        rlVertex2f(position.x - half_width, position.y - half_height);

        rlTexCoord2f(1.0f, 1.0f);
        rlVertex2f(position.x + half_width, position.y - half_height);

        rlTexCoord2f(1.0f, 0.0f);
        rlVertex2f(position.x + half_width, position.y + half_height);

        rlTexCoord2f(0.0f, 0.0f);
        rlVertex2f(position.x - half_width, position.y + half_height);

        rlEnd();
        rlSetTexture(0);
    }


protected:
    unsigned char *data;
    int width, height, format;
    unsigned int id;
};


int main(void) {
    Window window(WIDTH, HEIGHT, "OpenGlTest");
    glfwSetFramebufferSizeCallback(window.window, framebuffer_size_callback);

    rlLoadExtensions(reinterpret_cast<void *>(glfwGetProcAddress));
    rlglInit(window.width(), window.height());

    Texture banana;
    banana.load_path("./Banana-Single.png");

    Vec2 position(0, 0);

    rlEnableScissorTest();

    while (!window.should_close()) {
        BeginDrawing();
        {
            ClearBackground({0, 0, 0, 255});

            // rlOrtho(-WIDTH / 2.0f, WIDTH / 2.0f, -HEIGHT / 2.0f, HEIGHT / 2.0f, 0.1f, 100.0f);

            CropViewport(window.width(), window.height(), WIDTH, HEIGHT);
            // rlOrtho(-window.width() / 2.0f, window.width() / 2.0f, -window.height() / 2.0f, window.height() / 2.0f, 0.1f, 100.0f);
            ClearBackground({48, 48, 48, 255});

            banana.draw_at(position);
        }
        EndDrawing();

        rlScissor(0, 0, window.width(), window.height());

        window.end_frame();
    }

    rlglClose();

    return 0;
}
