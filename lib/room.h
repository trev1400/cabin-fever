#ifndef ROOM_H
#define ROOM_H

#define NUM_QUAD_VERTICES 14

#define FRONT_WALL_VERTEX_POSITIONS {\
    /* FRONT INSIDE */     \
    4.f, 3.f, -9.f, \
    -4.f, 3.f, -9.f, \
    -4.f, -3.f, -9.f, \
    4.f, 3.f, -9.f, \
    -4.f, -3.f, -9.f, \
    4.f, -3.f, -9.f, \
    /* FRONT OUTSIDE */     \
    4.f, 3.f, -9.f, \
    -4.f, -3.f, -9.f, \
    -4.f, 3.f, -9.f, \
    4.f, 3.f, -9.f, \
    4.f, -3.f, -9.f, \
    -4.f, -3.f, -9.f, \
}

#define BACK_WALL_VERTEX_POSITIONS {\
    /* BACK INSIDE*/     \
    4.f, 3.f, 9.f, \
    -4.f, -3.f, 9.f, \
    -4.f, 3.f, 9.f, \
    4.f, 3.f, 9.f, \
    4.f, -3.f, 9.f, \
    -4.f, -3.f, 9.f, \
    /* BACK OUTSIDE*/     \
    4.f, 3.f, 9.f, \
    -4.f, 3.f, 9.f, \
    -4.f, -3.f, 9.f, \
    4.f, 3.f, 9.f, \
    -4.f, -3.f, 9.f, \
    4.f, -3.f, 9.f, \
}

#define CEILING_VERTEX_POSITIONS {\
    /* CEILING INSIDE */     \
    4.f, 3.f, 9.f, \
    -4.f, 3.f, 9.f, \
    -4.f, 3.f, -9.f, \
    4.f, 3.f, 9.f, \
    -4.f, 3.f, -9.f, \
    4.f, 3.f, -9.f, \
    /* CEILING OUTSIDE */     \
    4.f, 3.f, 9.f, \
    -4.f, 3.f, -9.f, \
    -4.f, 3.f, 9.f, \
    4.f, 3.f, 9.f, \
    4.f, 3.f, -9.f, \
    -4.f, 3.f, -9.f, \
}

#define FLOOR_VERTEX_POSITIONS {\
    /* FLOOR INSIDE */     \
    4.f, -3.f, 9.f, \
    -4.f, -3.f, -9.f, \
    -4.f, -3.f, 9.f, \
    4.f, -3.f, 9.f, \
    4.f, -3.f, -9.f, \
    -4.f, -3.f, -9.f, \
    /* FLOOR OUTSIDE */     \
    4.f, -3.f, 9.f, \
    -4.f, -3.f, 9.f, \
    -4.f, -3.f, -9.f, \
    4.f, -3.f, 9.f, \
    -4.f, -3.f, -9.f, \
    4.f, -3.f, -9.f, \
}

#define LEFT_WALL_VERTEX_POSITIONS {\
    /* LEFT INSIDE */     \
    -4.f, 3.f, 9.f, \
    -4.f, -3.f, -9.f, \
    -4.f, 3.f, -9.f, \
    -4.f, 3.f, 9.f, \
    -4.f, -3.f, 9.f, \
    -4.f, -3.f, -9.f, \
    /* LEFT OUTSIDE */     \
    -4.f, 3.f, 9.f, \
    -4.f, 3.f, -9.f, \
    -4.f, -3.f, -9.f, \
    -4.f, 3.f, 9.f, \
    -4.f, -3.f, -9.f, \
    -4.f, -3.f, 9.f, \
}

#define RIGHT_WALL_VERTEX_POSITIONS {\
    /* RIGHT INSIDE */     \
    4.f, 3.f, 9.f, \
    4.f, 3.f, -9.f, \
    4.f, -3.f, -9.f, \
    4.f, 3.f, 9.f, \
    4.f, -3.f, -9.f, \
    4.f, -3.f, 9.f, \
    /* RIGHT OUTSIDE */     \
    4.f, 3.f, 9.f, \
    4.f, -3.f, -9.f, \
    4.f, 3.f, -9.f, \
    4.f, 3.f, 9.f, \
    4.f, -3.f, 9.f, \
    4.f, -3.f, -9.f, \
}

#endif // ROOM_H
