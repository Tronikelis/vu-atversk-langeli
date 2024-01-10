static const char GAME_STATE_FILENAME[] = "game_state.data";
static const char GAME_STATE_CHARS_FILENAME[] = "game_state_characters.data";

typedef struct OpenedGameFiles {
    FILE* gameFile;
    FILE* charsFile;
};

struct OpenedGameFiles openGameStateFiles(char* mode) {
    FILE* gameFile = fopen(GAME_STATE_FILENAME, mode);
    FILE* charsFile = fopen(GAME_STATE_CHARS_FILENAME, mode);

    if (gameFile == NULL || charsFile == NULL) {
        printf("can't open game saving files\n");

        fclose(gameFile);
        fclose(charsFile);
        exit(1);
    }

    struct OpenedGameFiles files;
    files.gameFile = gameFile;
    files.charsFile = charsFile;

    return files;
}

void saveGameState(struct Game game) {
    struct OpenedGameFiles files = openGameStateFiles("wb");

    int gameFileWrote = fwrite(&game, sizeof(struct Game), 1, files.gameFile);
    int charsFileWrote = fwrite(game.characters, sizeof(struct HiddenChar),
                                game.character_len, files.charsFile);

    int WRITE_COUNT = 1 + game.character_len;

    if (gameFileWrote + charsFileWrote != WRITE_COUNT) {
        printf("can't write to game saving files\n");

        fclose(files.gameFile);
        fclose(files.charsFile);
        exit(1);
    }

    fclose(files.gameFile);
    fclose(files.charsFile);
}

struct Game readGameState() {
    struct OpenedGameFiles files = openGameStateFiles("rb");
    struct Game game;

    int gameFileRead = fread(&game, sizeof(struct Game), 1, files.gameFile);

    struct HiddenChar* characters = HiddenChar_create_arr(game.character_len);

    int charsFileRead = fread(characters, sizeof(struct HiddenChar),
                              game.character_len, files.charsFile);

    int READ_COUNT = 1 + game.character_len;

    if (gameFileRead + charsFileRead != READ_COUNT) {
        printf("can't read game saving files\n");

        fclose(files.gameFile);
        fclose(files.charsFile);
        exit(1);
    }

    game.characters = characters;

    fclose(files.gameFile);
    fclose(files.charsFile);

    return game;
}
