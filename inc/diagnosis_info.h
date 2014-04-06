#ifndef DIAGNOSIS_INFO_H
#define DIAGNOSIS_INFO_H


const char *error_digest[] = {                                       /* index */
  "Attempted to Access NULL Pointer",                                /*-  0  -*/
  "Not Positive Dimension",                                          /*-  1  -*/
};


const char *warning_digest[] = {                                     /* index */
  "Attempted to Access NULL Pointer",                                /*-  0  -*/
  "Invalid Index of List",                                           /*-  1  -*/
  "Failed to Exchange before Head",                                  /*-  2  -*/
  "Failed to Find Node in List",                                     /*-  3  -*/
  "Reached the Tail Node in List",                                   /*   4  -*/
};

#endif
