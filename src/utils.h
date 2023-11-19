void clear_terminal() { system("@cls||clear"); }

int create_random_int(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

int clamp_int(int target, int left, int right) {
    if (target < left) {
        return left;
    }
    if (target > right) {
        return right;
    }
    return target;
}
