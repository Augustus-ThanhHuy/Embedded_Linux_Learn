#include <stdio.h>

typedef struct {
    char *data;
    int key;
} item;

item array[] = {{"bill", 3},{"neil", 4},{"John", 2}, {"Risk", 5}, {"alex", 1}};


void sort(item *a, int n)
{
    int i = 0, j = 0;
    int s = 1;
    for (; i < n && s !=0; i++)
    {
        s = 0;
        for (j = 0; j < n; j++)
        {
            if (a[j].key > a[j+1].key)
            {
                item swap = a[j];
                a[j] = a[j+1];
                a[j+1] = swap;
                s++;
            }
            
        }
        n--;
        
    }
    
}


int main(){
    sort(array, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("array[%d] = {%d, %s}\n", i, array[i].key, array[i].data);
    }
    
    return 0;
}