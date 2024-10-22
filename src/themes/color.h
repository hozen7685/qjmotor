#ifndef COLOR_H
#define COLOR_H
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WHITE_C,
    BLACK_C,
    RED_C,
    GRAY_C,
    YELLOW_C,
    ORANGE_C,
    COLOR_MAX
} color_t;

extern const int s_palette[COLOR_MAX];
extern const int s_palette_r[COLOR_MAX];
extern const int s_palette_w[COLOR_MAX];

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* COLOR_H */
