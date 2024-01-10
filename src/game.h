enum State { FIRST_PICK, SECOND_PICK };

typedef struct Game {
    struct HiddenChar* characters;
    int character_len;

    enum State state;
    int tries_left;

    int first_pick;
    int second_pick;
};
