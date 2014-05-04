#ifndef __DOM_CONSTANTS_H__
#define __DOM_CONSTANTS_H__

//! Debug mode flag
#define DEBUG false

//! The maximum number of quadtree levels. Root is 0, Deepest is QT_N_LEVELS - 1.
#define QT_N_LEVELS  16
#define QT_MAX_LEVEL 15

//! The ratio of a QTNode that must be filled to mark it as occupied
#define SUBDIV_THRESHOLD 0.975f

//! Default window width in pixels
#define DEFAULT_W 900
//! Default window height in pixels
#define DEFAULT_H 900

#endif
