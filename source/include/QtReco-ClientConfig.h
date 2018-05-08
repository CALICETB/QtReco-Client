#ifndef QtReco-ClientConfig_H
#define QtReco-ClientConfig_H

// version macros
#define QtReco-Client_MAJOR_VERSION 
#define QtReco-Client_MINOR_VERSION 
#define QtReco-Client_PATCH_LEVEL 
#define QtReco-Client_VERSION_STR ".."
#define QtReco-Client_VERSION_GE( MAJV , MINV , PLEV )  \
     ( (QtReco-Client_MAJOR_VERSION > MAJV) || ( (QtReco-Client_MAJOR_VERSION == MAJV) && (QtReco-Client_MINOR_VERSION > MINV) ) \
  || ( (QtReco-Client_MAJOR_VERSION == MAJV) && (QtReco-Client_MINOR_VERSION == MINV) && (QtReco-Client_PATCH_LEVEL >= PLEV) ) )

// project source dir
// useful for icons
#define QtReco-Client_DIR "/afs/desy.de/group/flc/pool/saivahu/QtReco-Client"

#endif // QtReco-ClientConfig_H
