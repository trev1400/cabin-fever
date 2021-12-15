#ifndef ROOM_H
#define ROOM_H

#define NUM_ONE_SIDED_QUAD_VERTICES 6
#define NUM_TWO_SIDED_QUAD_VERTICES 12

#define FRONT_WALL_VERTEX_POSITIONS {\
    /* FRONT INSIDE */     \
    8.f, 3.f, -9.f, \
    4.f, 4.f, \
    -8.f, 3.f, -9.f, \
    0.f, 4.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
    8.f, 3.f, -9.f, \
    4.f, 4.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
    8.f, -3.f, -9.f, \
    4.f, 0.f, \
    /* FRONT OUTSIDE */     \
    8.f, 3.f, -9.f, \
    4.f, 4.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
    -8.f, 3.f, -9.f, \
    0.f, 4.f, \
    8.f, 3.f, -9.f, \
    4.f, 4.f, \
    8.f, -3.f, -9.f, \
    4.f, 0.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
}

#define BACK_WALL_VERTEX_POSITIONS {\
    /* BACK INSIDE*/     \
    8.f, 3.f, 9.f, \
    4.f, 4.f, \
    -8.f, -3.f, 9.f, \
     0.f, 0.f, \
    -8.f, 3.f, 9.f, \
    0.f, 4.f, \
    8.f, 3.f, 9.f, \
    4.f, 4.f, \
    8.f, -3.f, 9.f, \
    4.f, 0.f, \
    -8.f, -3.f, 9.f, \
    0.f, 0.f, \
    /* BACK OUTSIDE*/     \
    8.f, 3.f, 9.f, \
    4.f, 4.f, \
    -8.f, 3.f, 9.f, \
    0.f, 4.f, \
    -8.f, -3.f, 9.f, \
    0.f, 0.f, \
    8.f, 3.f, 9.f, \
    4.f, 4.f, \
    -8.f, -3.f, 9.f, \
    0.f, 0.f, \
    8.f, -3.f, 9.f, \
    4.f, 0.f, \
}

#define CEILING_VERTEX_POSITIONS {\
    /* CEILING INSIDE */     \
    8.f, 3.f, 9.f, \
    7.f, 0.f, \
    -8.f, 3.f, -9.f, \
    0.f, 7.f, \
    -8.f, 3.f, 9.f, \
    7.f, 7.f, \
    8.f, 3.f, 9.f, \
    7.f, 0.f, \
    8.f, 3.f, -9.f, \
    0.f, 0.f, \
    -8.f, 3.f, -9.f, \
    0.f, 7.f, \
    /* CEILING OUTSIDE */     \
    8.f, 3.f, 9.f, \
    7.f, 0.f, \
    -8.f, 3.f, 9.f, \
    7.f, 7.f, \
    -8.f, 3.f, -9.f, \
    0.f, 7.f, \
    8.f, 3.f, 9.f, \
    7.f, 0.f, \
    -8.f, 3.f, -9.f, \
    0.f, 7.f, \
    8.f, 3.f, -9.f, \
    0.f, 0.f, \
}

#define FLOOR_VERTEX_POSITIONS {\
    /* FLOOR INSIDE */     \
    8.f, -3.f, 9.f, \
    0.f, 7.f, \
    -8.f, -3.f, -9.f, \
    7.f, 0.f, \
    -8.f, -3.f, 9.f, \
    0.f, 0.f, \
    8.f, -3.f, 9.f, \
    0.f, 7.f, \
    8.f, -3.f, -9.f, \
    7.f, 7.f, \
    -8.f, -3.f, -9.f, \
    7.f, 0.f, \
    /* FLOOR OUTSIDE */     \
    8.f, -3.f, 9.f, \
    0.f, 7.f, \
    -8.f, -3.f, 9.f, \
    0.f, 0.f, \
    -8.f, -3.f, -9.f, \
    7.f, 0.f, \
    8.f, -3.f, 9.f, \
    0.f, 7.f, \
    -8.f, -3.f, -9.f, \
    7.f, 0.f, \
    8.f, -3.f, -9.f, \
    7.f, 7.f, \
}

#define LEFT_WALL_VERTEX_POSITIONS {\
    /* LEFT INSIDE */     \
    -8.f, 3.f, 9.f, \
    4.f, 4.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
    -8.f, 3.f, -9.f, \
    0.f, 4.f, \
    -8.f, 3.f, 9.f, \
    4.f, 4.f, \
    -8.f, -3.f, 9.f, \
    4.f, 0.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
    /* LEFT OUTSIDE */     \
    -8.f, 3.f, 9.f, \
    4.f, 4.f, \
    -8.f, 3.f, -9.f, \
    0.f, 4.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
    -8.f, 3.f, 9.f, \
    4.f, 4.f, \
    -8.f, -3.f, -9.f, \
    0.f, 0.f, \
    -8.f, -3.f, 9.f, \
    4.f, 0.f, \
}

#define RIGHT_WALL_VERTEX_POSITIONS {\
    /* RIGHT INSIDE */     \
    8.f, 3.f, 9.f, \
    0.f, 4.f, \
    8.f, 3.f, -9.f, \
    4.f, 4.f, \
    8.f, -3.f, -9.f, \
    4.f, 0.f, \
    8.f, 3.f, 9.f, \
    0.f, 4.f, \
    8.f, -3.f, -9.f, \
    4.f, 0.f, \
    8.f, -3.f, 9.f, \
    0.f, 0.f, \
    /* RIGHT OUTSIDE */     \
    8.f, 3.f, 9.f, \
    0.f, 4.f, \
    8.f, -3.f, -9.f, \
    4.f, 0.f, \
    8.f, 3.f, -9.f, \
    4.f, 4.f, \
    8.f, 3.f, 9.f, \
    0.f, 4.f, \
    8.f, -3.f, 9.f, \
    0.f, 0.f, \
    8.f, -3.f, -9.f, \
    4.f, 0.f, \
}

#define DOOR_VERTEX_POSITIONS {\
    /* DOOR INSIDE*/     \
    2.f, 1.f, 8.95f, \
    1.f, 1.f, \
    -2.f, -2.99f, 8.95f, \
     0.f, 2.f, \
    -2.f, 1.f, 8.95f, \
    0.f, 1.f, \
    2.f, 1.f, 8.95f, \
    1.f, 1.f, \
    2.f, -2.99f, 8.95f, \
    1.f, 0.f, \
    -2.f, -2.99f, 8.95f, \
    0.f, 0.f, \
}

#endif // ROOM_H
