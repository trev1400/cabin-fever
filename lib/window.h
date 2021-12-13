#ifndef WINDOW_H
#define WINDOW_H

#define NUM_WINDOW_SIDE_PANELS_VERTICES 24

#define WINDOW_SIDE_PANELS_VERTEX_POSITIONS {\
    /* INSIDE LEFT */     \
    -5.f, 3.f, -9.f, \
    1.f, 4.f, \
    -5.f, -3.f, -9.f, \
    1.f, 0.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
    -5.f, 3.f, -9.f, \
    1.f, 4.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
    -8.f, 3.f, -9.f, \
    0.f, 4.f, \
    /* OUTSIDE LEFT */     \
    -5.f, 3.f, -9.f, \
    1.f, 4.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
    -5.f, -3.f, -9.f, \
    1.f, 0.f, \
    -5.f, 3.f, -9.f, \
    1.f, 4.f, \
    -8.f, 3.f, -9.f, \
    0.f, 4.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
    /* INSIDE RIGHT */     \
    8.f, 3.f, -9.f, \
    2.f, 4.f, \
    8.f, -3.f, -9.f, \
    1.f, 0.f, \
    5.f, -3.f, -9.f, \
    0.f, 0.f, \
    8.f, 3.f, -9.f, \
    1.f, 4.f, \
    5.f, -3.f, -9.f, \
    0.f, 0.f, \
    5.f, 3.f, -9.f, \
    0.f, 4.f, \
    /* OUTSIDE RIGHT*/     \
    8.f, 3.f, -9.f, \
    1.f, 4.f, \
    5.f, -3.f, -9.f, \
    0.f, 0.f, \
    8.f, -3.f, -9.f, \
    1.f, 0.f, \
    8.f, 3.f, -9.f, \
    1.f, 4.f, \
    5.f, 3.f, -9.f, \
    0.f, 4.f, \
    5.f, -3.f, -9.f, \
    0.f, 0.f, \
}

#define NUM_WINDOW_UPPER_PANEL_VERTICES 12

#define WINDOW_UPPER_PANEL_VERTEX_POSITIONS {\
    /* INSIDE TOP */     \
    5.f, 2.4f, -9.f, \
    4.f, 0.f, \
    -5.f, 3.f, -9.f, \
    0.f, 0.4f, \
    5.f, 3.f, -9.f, \
    4.f, 0.4f, \
    5.f, 2.4f, -9.f, \
    4.f, 0.f, \
    -5.f, 2.4f, -9.f, \
    0.f, 0.f, \
    -5.f, 3.f, -9.f, \
    0.f, 0.4f, \
    /* OUTSIDE TOP */     \
    5.f, 2.4f, -9.f, \
    4.f, 0.f, \
    5.f, 3.f, -9.f, \
    4.f, 0.4f, \
    -5.f, 3.f, -9.f, \
    0.f, 0.4f, \
    5.f, 2.4f, -9.f, \
    4.f, 0.f, \
    -5.f, 3.f, -9.f, \
    0.f, 0.4f, \
    -5.f, 2.4f, -9.f, \
    0.f, 0.f, \
}

#define NUM_WINDOW_LOWER_PANEL_VERTICES 12

#define WINDOW_LOWER_PANEL_VERTEX_POSITIONS {\
    /* INSIDE BOTTOM */     \
    5.f, -3.f, -9.f, \
    4.f, 0.f, \
    -5.f, -2.4f, -9.f, \
    0.f, 0.4f, \
    5.f, -2.4f, -9.f, \
    4.f, 0.4f, \
    5.f, -3.f, -9.f, \
    4.f, 0.f, \
    -5.f, -3.f, -9.f, \
    0.f, 0.f, \
    -5.f, -2.4f, -9.f, \
    0.f, 0.4f, \
    /* OUTSIDE BOTTOM */     \
    5.f, -3.f, -9.f, \
    4.f, 0.f, \
    5.f, -2.4f, -9.f, \
    4.f, 0.4f, \
    -5.f, -2.4f, -9.f, \
    0.f, 0.4f, \
    5.f, -3.f, -9.f, \
    4.f, 0.f, \
    -5.f, -2.4f, -9.f, \
    0.f, 0.4f, \
    -5.f, -3.f, -9.f, \
    0.f, 0.f, \
}

#define NUM_WINDOW_FRAME_VERTICES 12

#define WINDOW_FRAME_VERTEX_POSITIONS {\
    /* INSIDE */     \
     5.f, 2.4f, -9.f, \
     1.f, 1.f, \
     5.f, -2.4f, -9.f, \
     1.f, 0.f, \
     -5.f, -2.4f, -9.f, \
     0.f, 0.f, \
     5.f, 2.4f, -9.f, \
     1.f, 1.f, \
     -5.f, -2.4f, -9.f, \
     0.f, 0.f, \
     -5.f, 2.4f, -9.f, \
     0.f, 1.f, \
    /* OUTSIDE */     \
    5.f, 2.4f, -9.f, \
    1.f, 1.f, \
    -5.f, -2.4f, -9.f, \
    0.f, 0.f, \
    5.f, -2.4f, -9.f, \
    1.f, 0.f, \
    5.f, 2.4f, -9.f, \
    1.f, 1.f, \
    -5.f, 2.4f, -9.f, \
    0.f, 1.f, \
    -5.f, -2.4f, -9.f, \
    0.f, 0.f, \
}

#endif // WINDOW_H
