#ifndef WINDOW_H
#define WINDOW_H

#define NUM_WINDOW_VERTICES 48

#define WINDOW_VERTEX_POSITIONS {\
    /* INSIDE LEFT */     \
    -5.f, 3.f, -9.f, \
    -5.f, -3.f, -9.f, \
    -8.f, -3.f, -9.f, \
    -5.f, 3.f, -9.f, \
    -8.f, -3.f, -9.f, \
    -8.f, 3.f, -9.f, \
    /* OUTSIDE LEFT */     \
    -5.f, 3.f, -9.f, \
    -8.f, -3.f, -9.f, \
    -5.f, -3.f, -9.f, \
    -5.f, 3.f, -9.f, \
    -8.f, 3.f, -9.f, \
    -8.f, -3.f, -9.f, \
    /* INSIDE RIGHT */     \
     8.f, 3.f, -9.f, \
     8.f, -3.f, -9.f, \
     5.f, -3.f, -9.f, \
     8.f, 3.f, -9.f, \
     5.f, -3.f, -9.f, \
     5.f, 3.f, -9.f, \
    /* OUTSIDE RIGHT*/     \
    8.f, 3.f, -9.f, \
    5.f, -3.f, -9.f, \
    8.f, -3.f, -9.f, \
    8.f, 3.f, -9.f, \
    5.f, 3.f, -9.f, \
    5.f, -3.f, -9.f, \
    /* INSIDE TOP */     \
     5.f, 2.4f, -9.f, \
     -5.f, 3.f, -9.f, \
     5.f, 3.f, -9.f, \
     5.f, 2.4f, -9.f, \
     -5.f, 2.4f, -9.f, \
     -5.f, 3.f, -9.f, \
    /* OUTSIDE TOP */     \
    5.f, 2.4f, -9.f, \
    5.f, 3.f, -9.f, \
    -5.f, 3.f, -9.f, \
    5.f, 2.4f, -9.f, \
    -5.f, 3.f, -9.f, \
    -5.f, 2.4f, -9.f, \
    /* INSIDE BOTTOM */     \
     5.f, -3.f, -9.f, \
     -5.f, -2.4f, -9.f, \
     5.f, -2.4f, -9.f, \
     5.f, -3.f, -9.f, \
     -5.f, -3.f, -9.f, \
     -5.f, -2.4f, -9.f, \
    /* OUTSIDE BOTTOM */     \
    5.f, -3.f, -9.f, \
    5.f, -2.4f, -9.f, \
    -5.f, -2.4f, -9.f, \
    5.f, -3.f, -9.f, \
    -5.f, -2.4f, -9.f, \
    -5.f, -3.f, -9.f, \
}

#endif // WINDOW_H
