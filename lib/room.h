#ifndef ROOM_H
#define ROOM_H

#define NUM_QUAD_VERTICES 12

#define FRONT_WALL_VERTEX_POSITIONS {\
    /* FRONT INSIDE */     \
    2.f, 1.5f, -2.f, \
    -2.f, 1.5f, -2.f, \
    -2.f, -1.5f, -2.f, \
    2.f, 1.5f, -2.f, \
    -2.f, -1.5f, -2.f,\
    2.f, -1.5f, -2.f, \
    /* FRONT OUTSIDE */     \
    2.f, 1.5f, -2.f, \
    -2.f, -1.5f, -2.f, \
    -2.f, 1.5f, -2.f, \
    2.f, 1.5f, -2.f, \
    2.f, -1.5f, -2.f, \
    -2.f, -1.5f, -2.f,\
}

#define BACK_WALL_VERTEX_POSITIONS {\
    /* BACK INSIDE*/     \
    2.f, 1.5f, 2.f, \
    -2.f, -1.5f, 2.f, \
    -2.f, 1.5f, 2.f, \
    2.f, 1.5f, 2.f, \
    2.f, -1.5f, 2.f,\
    -2.f, -1.5f, 2.f, \
    /* BACK OUTSIDE*/     \
    2.f, 1.5f, 2.f, \
    -2.f, 1.5f, 2.f, \
    -2.f, -1.5f, 2.f, \
    2.f, 1.5f, 2.f, \
    -2.f, -1.5f, 2.f, \
    2.f, -1.5f, 2.f,\
}

#define CEILING_VERTEX_POSITIONS {\
    /* CEILING INSIDE */     \
    2.f, 1.5f, 2.f, \
    -2.f, 1.5f, 2.f, \
    -2.f, 1.5f, -2.f, \
    2.f, 1.5f, 2.f, \
    -2.f, 1.5f, -2.f, \
    2.f, 1.5f, -2.f,\
    /* CEILING OUTSIDE */     \
    2.f, 1.5f, 2.f, \
    -2.f, 1.5f, -2.f, \
    -2.f, 1.5f, 2.f, \
    2.f, 1.5f, 2.f, \
    2.f, 1.5f, -2.f,\
    -2.f, 1.5f, -2.f, \
}

#define FLOOR_VERTEX_POSITIONS {\
    /* FLOOR INSIDE */     \
    2.f, -1.5f, 2.f, \
    -2.f, -1.5f, -2.f, \
    -2.f, -1.5f, 2.f, \
    2.f, -1.5f, 2.f, \
    2.f, -1.5f, -2.f,\
    -2.f, -1.5f, -2.f, \
    /* FLOOR OUTSIDE */     \
    2.f, -1.5f, 2.f, \
    -2.f, -1.5f, 2.f, \
    -2.f, -1.5f, -2.f, \
    2.f, -1.5f, 2.f, \
    -2.f, -1.5f, -2.f, \
    2.f, -1.5f, -2.f,\
}

#define LEFT_WALL_VERTEX_POSITIONS {\
    /* LEFT INSIDE */     \
    -2.f, 1.5f, 2.f, \
    -2.f, -1.5f, -2.f, \
    -2.f, 1.5f, -2.f, \
    -2.f, 1.5f, 2.f, \
    -2.f, -1.5f, 2.f,\
    -2.f, -1.5f, -2.f, \
    /* LEFT OUTSIDE */     \
    -2.f, 1.5f, 2.f, \
    -2.f, 1.5f, -2.f, \
    -2.f, -1.5f, -2.f, \
    -2.f, 1.5f, 2.f, \
    -2.f, -1.5f, -2.f, \
    -2.f, -1.5f, 2.f,\
}

#define RIGHT_WALL_VERTEX_POSITIONS {\
    /* RIGHT INSIDE */     \
    2.f, 1.5f, 2.f, \
    2.f, 1.5f, -2.f, \
    2.f, -1.5f, -2.f, \
    2.f, 1.5f, 2.f, \
    2.f, -1.5f, -2.f,\
    2.f, -1.5f, 2.f, \
    /* RIGHT OUTSIDE */     \
    2.f, 1.5f, 2.f, \
    2.f, -1.5f, -2.f, \
    2.f, 1.5f, -2.f, \
    2.f, 1.5f, 2.f, \
    2.f, -1.5f, 2.f, \
    2.f, -1.5f, -2.f,\
}

#endif // ROOM_H
