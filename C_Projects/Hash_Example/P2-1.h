/* P2-1.h - Header file for Data Structures Project */



// Function prototypes
extern void *CreateLL(int ElementSize,int (*Match)(void *key, void *MyElement), int (*LE)(void *MyElement1, void *MyElement2));
extern void *CreateElement(void *MyList);
extern void DeleteElement(void *MyElement);
extern void InsertElement(void *MyList, void *MyElement);
extern void InsertElementSorted(void *MyList, void *MyElement);
extern void *GetElement(void *MyList, void *key, int Remove);
