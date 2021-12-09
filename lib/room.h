#ifndef ROOM_H
#define ROOM_H

#define NUM_QUAD_VERTICES 14

#define FRONT_WALL_VERTEX_POSITIONS {\
    /* FRONT INSIDE */     \
    8.f, 3.f, -9.f, \
    -8.f, 3.f, -9.f, \
    -8.f, -3.f, -9.f, \
    8.f, 3.f, -9.f, \
    -8.f, -3.f, -9.f, \
    8.f, -3.f, -9.f, \
    /* FRONT OUTSIDE */     \
    8.f, 3.f, -9.f, \
    -8.f, -3.f, -9.f, \
    -8.f, 3.f, -9.f, \
    8.f, 3.f, -9.f, \
    8.f, -3.f, -9.f, \
    -8.f, -3.f, -9.f, \
}

#define BACK_WALL_VERTEX_POSITIONS {\
    /* BACK INSIDE*/     \
    8.f, 3.f, 9.f, \
    -8.f, -3.f, 9.f, \
    -8.f, 3.f, 9.f, \
    8.f, 3.f, 9.f, \
    8.f, -3.f, 9.f, \
    -8.f, -3.f, 9.f, \
    /* BACK OUTSIDE*/     \
    8.f, 3.f, 9.f, \
    -8.f, 3.f, 9.f, \
    -8.f, -3.f, 9.f, \
    8.f, 3.f, 9.f, \
    -8.f, -3.f, 9.f, \
    8.f, -3.f, 9.f, \
}

#define CEILING_VERTEX_POSITIONS {\
    /* CEILING INSIDE */     \
    8.f, 3.f, 9.f, \
    -8.f, 3.f, 9.f, \
    -8.f, 3.f, -9.f, \
    8.f, 3.f, 9.f, \
    -8.f, 3.f, -9.f, \
    8.f, 3.f, -9.f, \
    /* CEILING OUTSIDE */     \
    8.f, 3.f, 9.f, \
    -8.f, 3.f, -9.f, \
    -8.f, 3.f, 9.f, \
    8.f, 3.f, 9.f, \
    8.f, 3.f, -9.f, \
    -8.f, 3.f, -9.f, \
}

#define FLOOR_VERTEX_POSITIONS {\
    /* FLOOR INSIDE */     \
    8.f, -3.f, 9.f, \
    -8.f, -3.f, -9.f, \
    -8.f, -3.f, 9.f, \
    8.f, -3.f, 9.f, \
    8.f, -3.f, -9.f, \
    -8.f, -3.f, -9.f, \
    /* FLOOR OUTSIDE */     \
    8.f, -3.f, 9.f, \
    -8.f, -3.f, 9.f, \
    -8.f, -3.f, -9.f, \
    8.f, -3.f, 9.f, \
    -8.f, -3.f, -9.f, \
    8.f, -3.f, -9.f, \
}

#define LEFT_WALL_VERTEX_POSITIONS {\
    /* LEFT INSIDE */     \
    -8.f, 3.f, 9.f, \
    -8.f, -3.f, -9.f, \
    -8.f, 3.f, -9.f, \
    -8.f, 3.f, 9.f, \
    -8.f, -3.f, 9.f, \
    -8.f, -3.f, -9.f, \
    /* LEFT OUTSIDE */     \
    -8.f, 3.f, 9.f, \
    -8.f, 3.f, -9.f, \
    -8.f, -3.f, -9.f, \
    -8.f, 3.f, 9.f, \
    -8.f, -3.f, -9.f, \
    -8.f, -3.f, 9.f, \
}

#define RIGHT_WALL_VERTEX_POSITIONS {\
    /* RIGHT INSIDE */     \
    8.f, 3.f, 9.f, \
    8.f, 3.f, -9.f, \
    8.f, -3.f, -9.f, \
    8.f, 3.f, 9.f, \
    8.f, -3.f, -9.f, \
    8.f, -3.f, 9.f, \
    /* RIGHT OUTSIDE */     \
    8.f, 3.f, 9.f, \
    8.f, -3.f, -9.f, \
    8.f, 3.f, -9.f, \
    8.f, 3.f, 9.f, \
    8.f, -3.f, 9.f, \
    8.f, -3.f, -9.f, \
}

#endif // ROOM_H
