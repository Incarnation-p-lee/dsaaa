#ifndef DIAGNOSIS_INFO_H
#define DIAGNOSIS_INFO_H


const char *error_digest[] = {                                       /* index */
  "Attempted to Access NULL Pointer",                                /*-  0  -*/
  "Not Positive Dimension",                                          /*-  1  -*/
  "Prime must more than 1",                                          /*-  2  -*/
  "Index out of Range",                                              /*-  3  -*/
  "Invalied Numeric Format",                                         /*-  4  -*/
  "Inconsistent Calculate Result",                                   /*-  5  -*/
  "Attempt to Open File Failed",                                     /*-  6  -*/
  "Malloc Failed to Get Memory",                                     /*-  7  -*/
  "Realloc Failed to Update Memory",                                 /*-  8  -*/
};


const char *warning_digest[] = {                                     /* index */
  "Attempted to Access NULL Pointer",                                /*-  0  -*/
  "Invalid Index of List",                                           /*-  1  -*/
  "Failed to Operation before Head",                                 /*-  2  -*/
  "Failed to Find Node in List",                                     /*-  3  -*/
  "Reached the Tail Node in List",                                   /*   4  -*/
  "Failed to Read from File Descriptor",                             /*   5  -*/
  "Unresolved Macro",                                                /*   6  -*/
  "Risk of Memory Leak",                                             /*   7  -*/
  "Specified Invalid Position",                                      /*   8  -*/
  "Invalid Valux of Specified Type",                                 /*-  9  -*/
};

#endif
