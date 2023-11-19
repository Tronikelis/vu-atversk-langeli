typedef struct HiddenChar {
    char character;
    bool picked;
};

void HiddenChar_print_box(struct HiddenChar character, int index) {
    printf(" -------\n");

    if (character.picked) {
        printf("|  *%c*  | <---- \n", character.character);
    } else {
        printf("|  %2d   |\n", index);
    }

    printf(" -------\n");
}

void HiddenChar_shuffle_arr(struct HiddenChar* arr, int length) {
    for (int i = 0; i < length; i++) {
        int left = create_random_int(0, length - 1);
        int right = create_random_int(0, length - 1);

        struct HiddenChar temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
    }
}

bool HiddenChar_all_picked(struct HiddenChar* arr, int length) {
    for (int i = 0; i < length; i++) {
        if (!arr[i].picked) {
            return false;
        }
    }

    return true;
}

struct HiddenChar* HiddenChar_create_arr(int length) {
    return (struct HiddenChar*)malloc(length * sizeof(struct HiddenChar));
}
