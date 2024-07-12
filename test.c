#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 256
#define MAX_MAP_WIDTH  50
#define MAX_MAP_HEIGHT 50

typedef struct {
    char north_texture[MAX_PATH_LENGTH];
    char south_texture[MAX_PATH_LENGTH];
    char west_texture[MAX_PATH_LENGTH];
    char east_texture[MAX_PATH_LENGTH];
    int floor_color[3];
    int ceiling_color[3];
    char map[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
    int map_height;
} CubData;

void parseColor(const char* line, int color[3]) {
    sscanf(line, "%*c %d,%d,%d", &color[0], &color[1], &color[2]);
}

void readCubFile(const char* filename, CubData* data) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    data->map_height = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "NO ", 3) == 0) {
            sscanf(line, "NO %s", data->north_texture);
        } else if (strncmp(line, "SO ", 3) == 0) {
            sscanf(line, "SO %s", data->south_texture);
        } else if (strncmp(line, "WE ", 3) == 0) {
            sscanf(line, "WE %s", data->west_texture);
        } else if (strncmp(line, "EA ", 3) == 0) {
            sscanf(line, "EA %s", data->east_texture);
        } else if (line[0] == 'F') {
            parseColor(line, data->floor_color);
        } else if (line[0] == 'C') {
            parseColor(line, data->ceiling_color);
        } else if (line[0] == '1' || line[0] == ' ') {
            strcpy(data->map[data->map_height], line);
            data->map_height++;
        }
    }

    fclose(file);
}

int main() {
    CubData data = {0};

    readCubFile("map.cub", &data);

    // Print texture paths
    printf("North Texture: %s\n", data.north_texture);
    printf("South Texture: %s\n", data.south_texture);
    printf("West Texture: %s\n", data.west_texture);
    printf("East Texture: %s\n", data.east_texture);

    // Print floor and ceiling colors
    printf("Floor Color: %d,%d,%d\n", data.floor_color[0], data.floor_color[1], data.floor_color[2]);
    printf("Ceiling Color: %d,%d,%d\n", data.ceiling_color[0], data.ceiling_color[1], data.ceiling_color[2]);

    // Print map
    printf("Map:\n");
    for (int i = 0; i < data.map_height; i++) {
        printf("%s", data.map[i]);
    }

    return 0;
}
