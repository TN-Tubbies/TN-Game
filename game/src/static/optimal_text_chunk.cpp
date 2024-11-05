#include "optimal_text_chunk.hpp"

static int OptimalTextChunk = 0;

// We'll use a Lorem Ipsum (with black Font) to calculate the optimal text chunk
std::string LoremIpsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue. Ut in risus volutpat libero pharetra tempor. Cras vestibulum bibendum augue. Praesent egestas leo in pede. Praesent blandit odio eu enim. Pellentesque sed dui ut augue blandit sodales. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aliquam nibh. Mauris ac mauris sed pede pellentesque fermentum. Maecenas adipiscing ante non diam sodales hendrerit.";
SDL_Color black_color = {0, 0, 0, 0};

/*TODO:
    déterminer la taille optimale de nb de lettres de sorte que l'affichage se fasse en temps optimal
*/

void SplitText(int ChunkSize, int TextMaxWidth, int TextMaxHeight, TTF_Font *Font)
{
    std::vector<std::string> CutText;

    int chunkRef = 0;
    std::string currentString;
    std::string previousString;
    for (int i = 0; i < LoremIpsum.size(); i++)
    {
        currentString += LoremIpsum[i];
        chunkRef++;

        if (chunkRef >= ChunkSize)
        {
            chunkRef = 0;
            SDL_Surface *textSurface = TTF_RenderText_Solid_Wrapped(Font, currentString.c_str(), black_color, TextMaxWidth);
            if (textSurface->h > TextMaxHeight)
            {
                CutText.push_back(previousString);
                currentString = "";
                previousString = "";
            }
            else
            {
                previousString = currentString;
            }
            SDL_FreeSurface(textSurface);
        }
    }
}

int SetOptimalTextChunk(int TextMaxWidth, int TextMaxHeight, TTF_Font *Font)
{
    int CurrentBestDuration = (int)INFINITY;

    for (int i = 1; i <= MAX_CHUNK_SIZE; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        SplitText(i, TextMaxWidth, TextMaxHeight, Font);

        auto stop = std::chrono::high_resolution_clock::now();
        int duration = (duration_cast<std::chrono::microseconds>(stop - start)).count(); // In microseconds

        if (duration < CurrentBestDuration)
        {
            CurrentBestDuration = duration;
            OptimalTextChunk = i;
        }
    }
}

int GetOptimalTextChunk() { return OptimalTextChunk; }
