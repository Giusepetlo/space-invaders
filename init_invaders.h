

enum direction_t {left, right, stationary};
enum colour_t {red, green, purple};

struct enemy_t {

    SDL_Rect hitbox;
    enum colour_t colour;
    unsigned int alive;
    unsigned int points;
};

struct invaders_t {

    struct enemy_t enemy[5][10];
    enum direction_t direction;
    unsigned int killed;
    int speed;
    int state;
    int state_speed;
    Uint32 state_time;
};
struct invaders_t invaders;

void init_invaders();
