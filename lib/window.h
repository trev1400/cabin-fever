#ifndef WINDOW_H
#define WINDOW_H

#define NUM_QUAD_VERTICES 12

#define LEFT_PANEL_VERTEX_POSITIONS {\
    /* INSIDE */     \
    -1.7f, 1.5f, -2.f, \
    -1.7f, -1.5f, -2.f, \
    -2.f, -1.5f, -2.f, \
    -1.7f, 1.5f, -2.f, \
    -2.f, -1.5f, -2.f,\
    -2.f, 1.5f, -2.f, \
    /* OUTSIDE */     \
    -1.7f, 1.5f, -2.f, \
    -2.f, -1.5f, -2.f, \
    -1.7f, -1.5f, -2.f, \
    -1.7f, 1.5f, -2.f, \
    -2.f, 1.5f, -2.f, \
    -2.f, -1.5f, -2.f,\
}

#define RIGHT_PANEL_VERTEX_POSITIONS {\
    /* INSIDE */     \
     2.f, 1.5f, -2.f, \
     2.f, -1.5f, -2.f, \
     1.7f, -1.5f, -2.f, \
     2.f, 1.5f, -2.f, \
     1.7f, -1.5f, -2.f,\
     1.7f, 1.5f, -2.f, \
    /* OUTSIDE */     \
    2.f, 1.5f, -2.f, \
    1.7f, -1.5f, -2.f, \
    2.f, -1.5f, -2.f, \
    2.f, 1.5f, -2.f, \
    1.7f, 1.5f, -2.f, \
    1.7f, -1.5f, -2.f,\
}

#define TOP_PANEL_VERTEX_POSITIONS {\
    /* INSIDE */     \
     1.7f, 1.2f, -2.f, \
     -1.7f, 1.5f, -2.f, \
     1.7f, 1.5f, -2.f, \
     1.7f, 1.2f, -2.f, \
     -1.7f, 1.2f, -2.f,\
     -1.7f, 1.5f, -2.f, \
    /* OUTSIDE */     \
    1.7f, 1.2f, -2.f, \
    1.7f, 1.5f, -2.f, \
    -1.7f, 1.5f, -2.f, \
    1.7f, 1.2f, -2.f, \
    -1.7f, 1.5f, -2.f, \
    -1.7f, 1.2f, -2.f,\
}

#define BOTTOM_PANEL_VERTEX_POSITIONS {\
    /* INSIDE */     \
     1.7f, -1.5f, -2.f, \
     -1.7f, -1.2f, -2.f, \
     1.7f, -1.2f, -2.f, \
     1.7f, -1.5f, -2.f, \
     -1.7f, -1.5f, -2.f,\
     -1.7f, -1.2f, -2.f, \
    /* OUTSIDE */     \
    1.7f, -1.5f, -2.f, \
    1.7f, -1.2f, -2.f, \
    -1.7f, -1.2f, -2.f, \
    1.7f, -1.5f, -2.f, \
    -1.7f, -1.2f, -2.f, \
    -1.7f, -1.5f, -2.f,\
}

#endif // WINDOW_H
