#include "render.h"
#include "agent.h"
#include <stdbool.h>
#include "utils.h"

void start_render()
{
    // Start Page
    for (int i = 0; i < 6; i++)
        printf("\n");

    printf("\t         ___    __         ___ \n");
    printf("\t|\\  /|  |   |  |   \\   |  /   \\\n");
    printf("\t| \\/ |  |___|  |__ /   |  |   |\n");
    printf("\t|    |  |   |  |   \\   |  |   |\n");
    printf("\t|    |  |   |  |    \\  |  \\___/\n");
    printf("\n\n\n");
    printf("\t    Press any key to play\n\n");
    printf("\n\n\n");
    char input;
    scanf("%c", &input);

    // Select Level Page
    printf("Select the level you want to play :\n");
    printf("(1) Level 1\n");
    printf("(2) Level 2\n");
    printf("(3) Level 3\n");
    printf("(4) Level 4\n\n");
    scanf(" %c", &input);

    // Select Render Type
    printf("\n\nYou choose Level %c\n\n", input);
    printf("Please select the render type :\n");
    printf("(1) Display each turn of the player and the enemies\n");
    printf("(2) Display each turn of the player only\n");
    printf("(3) Display after epoch only\n\n");
    int type;
    do
    {
        scanf("%d", &type);
        render_type = type - 1;
    } while (render_type > 3 && render_type < 0);
    printf("\nYou choose render type %d\n\n", type);
    printf("Here is the level you have to beat, good lock !\n\n");
    level_render(0);

    char pause;
    scanf("%c", &pause);
    scanf("%c", &pause);
}

void level_render(int padding)
{
    if (!VERBOSE && padding)
        for (int i = 0; i < 17; i++)
            printf("\n");

    if VERBOSE
    {
        printf("\n");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                printf("%d ", visited[i][j]);
            }
            printf("\n");
        }
        printf("\n\n\n");
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == player_row && j == player_col)
                printf("ç ");
            else
                printf("%c ", level[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void add_crumbs()
{
    /*
    if VERBOSE
        printf("States :");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (visited[i][j] == crumb)
            {
                level[i][j] = '.';
                if VERBOSE
                    printf("%d ", pos_from_coord(i, j));
            }
        }
    }
    level[start_row][start_col] = 's';
    printf("\n");
    */
    // level[player_row][player_col] = '@';
    if VERBOSE
        printf("%d ", pos_from_coord(player_row, player_col));

    level[start_row][start_col] = 's';
    printf("\n");
}

void remove_crumbs()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (level[i][j] == '.')
            {
                level[i][j] = ' ';
            }
        }
    }
}

void print_action(action act)
{
    printf("%s", act == 0   ? "left    "
                 : act == 1 ? "right   "
                 : act == 2 ? "up      "
                 : act == 3 ? "up_left "
                 : act == 4 ? "up_right"
                            : "falling ");
}

void print_q_matrix()
{
    for (int i = 0; i < 2 * rows; i++)
    {
        if (i == rows)
            printf("____________________________\n");
        printf("%d\n", i % rows);
        for (int k = 0; k < nbr_actions; k++)
        {
            for (int j = 0; j < cols; j++)
            {

                double a = 10 * qfunction[state(i % rows, j % cols, (int)i / rows)][k];
                if (visited[i % rows][j % cols] == death)
                    printf("° ");
                else if (visited[i % rows][j % cols] == wall)
                    printf("^ ");
                else if (a <= 0 && a > -10)
                    printf("%.0f ", -a);
                else if (a < -10)
                    printf("- ");
                else if (a < 10)
                    printf(". ");
                else
                    printf("x ");
            }
            printf("  ");
            print_action(k);
            printf("\n");
        }
        // printf("\n");
    }
    printf("\n\n");
}