#ifndef WINDOW_H
#define WINDOW_H

#define NUM_WINDOW_VERTICES 48

#define WINDOW_VERTEX_POSITIONS {\
    /* INSIDE LEFT */     \
    -3.4f, 3.f, -9.f, \
    -3.4f, -3.f, -9.f, \
    -4.f, -3.f, -9.f, \
    -3.4f, 3.f, -9.f, \
    -4.f, -3.f, -9.f, \
    -4.f, 3.f, -9.f, \
    /* OUTSIDE LEFT */     \
    -3.4f, 3.f, -9.f, \
    -4.f, -3.f, -9.f, \
    -3.4f, -3.f, -9.f, \
    -3.4f, 3.f, -9.f, \
    -4.f, 3.f, -9.f, \
    -4.f, -3.f, -9.f, \
    /* INSIDE RIGHT */     \
     4.f, 3.f, -9.f, \
     4.f, -3.f, -9.f, \
     3.4f, -3.f, -9.f, \
     4.f, 3.f, -9.f, \
     3.4f, -3.f, -9.f, \
     3.4f, 3.f, -9.f, \
    /* OUTSIDE RIGHT*/     \
    4.f, 3.f, -9.f, \
    3.4f, -3.f, -9.f, \
    4.f, -3.f, -9.f, \
    4.f, 3.f, -9.f, \
    3.4f, 3.f, -9.f, \
    3.4f, -3.f, -9.f, \
    /* INSIDE TOP */     \
     3.4f, 2.4f, -9.f, \
     -3.4f, 3.f, -9.f, \
     3.4f, 3.f, -9.f, \
     3.4f, 2.4f, -9.f, \
     -3.4f, 2.4f, -9.f, \
     -3.4f, 3.f, -9.f, \
    /* OUTSIDE TOP */     \
    3.4f, 2.4f, -9.f, \
    3.4f, 3.f, -9.f, \
    -3.4f, 3.f, -9.f, \
    3.4f, 2.4f, -9.f, \
    -3.4f, 3.f, -9.f, \
    -3.4f, 2.4f, -9.f, \
    /* INSIDE BOTTOM */     \
     3.4f, -3.f, -9.f, \
     -3.4f, -2.4f, -9.f, \
     3.4f, -2.4f, -9.f, \
     3.4f, -3.f, -9.f, \
     -3.4f, -3.f, -9.f, \
     -3.4f, -2.4f, -9.f, \
    /* OUTSIDE BOTTOM */     \
    3.4f, -3.f, -9.f, \
    3.4f, -2.4f, -9.f, \
    -3.4f, -2.4f, -9.f, \
    3.4f, -3.f, -9.f, \
    -3.4f, -2.4f, -9.f, \
    -3.4f, -3.f, -9.f, \
}

#endif // WINDOW_H
