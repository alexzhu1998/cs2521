typedef struct Node *List;
struct Node { int value; List next; };

List mergeSort(List l1, List l2) {
    
    if (l1 == NULL || l2 == NULL) {
        if (l1 == NULL && l2 == NULL) return NULL;
        else if (l1 == NULL) return l2;
        else if (l2 == NULL) return l1;
    } 

    List newList = calloc(sizeof(List)); 
    List newIndex = newList;
    List index1 = l1;
    List index2 = l2;

    if (l1->value > l2->value) {
        newIndex->value = l2->value;
        index2 = index2->next;
    } else {
        newIndex->value = l1->value;
        index1 = index1->next;
    }
    
    while ((index1 != NULL) && (index2 != NULL)) {
        if (index1->value < index2->value) {
            List newNode = calloc(sizeof(List));
            newIndex->next = newNode;
            newNode->value = index1->value;
            newIndex = newIndex->next; 
            index1 = index1->next;
        } else {
            List newNode = calloc(sizeof(List));
            newIndex->next = newNode;
            newNode->value = index2->value;
            newIndex = newIndex->next; 
            index2 = index2->next;
        }
    }

    if (index1 == NULL || index2 == NULL) {
        if (index1 == NULL) {
            while (index2 != NULL) {
                List newNode = calloc(sizeof(List));
                newIndex->next = newNode;
                newNode->value = index2->value;
                newIndex = newIndex->next; 
                index2 = index2->next;
            }
        } else {
           while (index1 != NULL) {
                List newNode = calloc(sizeof(List));
                newIndex->next = newNode;
                newNode->value = index1->value;
                newIndex = newIndex->next; 
                index1 = index1->next;
            } 
        }
    }



    return newList;
}