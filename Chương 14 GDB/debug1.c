typedef struct {
    char *data;
    int key;
} item;

item array[] = {{"bill", 3},{"neil", 4},{"John", 2}, {"Risk", 5}, {"alex", 1}};


sort(a, n)
item *a;
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

    return 0;
}