#ifndef WINDOW_H
#define WINDOW_H

#define NUM_WINDOW_VERTICES 48

#define WINDOW_VERTEX_POSITIONS {\
    /* INSIDE LEFT */     \
    -1.7f, 1.5f, -2.f, \
    -1.7f, -1.5f, -2.f, \
    -2.f, -1.5f, -2.f, \
    -1.7f, 1.5f, -2.f, \
    -2.f, -1.5f, -2.f,\
    -2.f, 1.5f, -2.f, \
    /* OUTSIDE LEFT */     \
    -1.7f, 1.5f, -2.f, \
    -2.f, -1.5f, -2.f, \
    -1.7f, -1.5f, -2.f, \
    -1.7f, 1.5f, -2.f, \
    -2.f, 1.5f, -2.f, \
    -2.f, -1.5f, -2.f,\
    /* INSIDE RIGHT */     \
     2.f, 1.5f, -2.f, \
     2.f, -1.5f, -2.f, \
     1.7f, -1.5f, -2.f, \
     2.f, 1.5f, -2.f, \
     1.7f, -1.5f, -2.f,\
     1.7f, 1.5f, -2.f, \
    /* OUTSIDE RIGHT*/     \
    2.f, 1.5f, -2.f, \
    1.7f, -1.5f, -2.f, \
    2.f, -1.5f, -2.f, \
    2.f, 1.5f, -2.f, \
    1.7f, 1.5f, -2.f, \
    1.7f, -1.5f, -2.f,\
    /* INSIDE TOP */     \
     1.7f, 1.2f, -2.f, \
     -1.7f, 1.5f, -2.f, \
     1.7f, 1.5f, -2.f, \
     1.7f, 1.2f, -2.f, \
     -1.7f, 1.2f, -2.f,\
     -1.7f, 1.5f, -2.f, \
    /* OUTSIDE TOP */     \
    1.7f, 1.2f, -2.f, \
    1.7f, 1.5f, -2.f, \
    -1.7f, 1.5f, -2.f, \
    1.7f, 1.2f, -2.f, \
    -1.7f, 1.5f, -2.f, \
    -1.7f, 1.2f, -2.f,\
    /* INSIDE BOTTOM */     \
     1.7f, -1.5f, -2.f, \
     -1.7f, -1.2f, -2.f, \
     1.7f, -1.2f, -2.f, \
     1.7f, -1.5f, -2.f, \
     -1.7f, -1.5f, -2.f,\
     -1.7f, -1.2f, -2.f, \
    /* OUTSIDE BOTTOM */     \
    1.7f, -1.5f, -2.f, \
    1.7f, -1.2f, -2.f, \
    -1.7f, -1.2f, -2.f, \
    1.7f, -1.5f, -2.f, \
    -1.7f, -1.2f, -2.f, \
    -1.7f, -1.5f, -2.f,\
}

#endif // WINDOW_H
