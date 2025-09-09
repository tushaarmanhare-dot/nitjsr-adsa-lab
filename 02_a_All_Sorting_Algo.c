#include <stdio.h>
#include <stdlib.h>

// Utility: swap two integers
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// ------------------ Sorting Algorithms ------------------

// 1. Insertion Sort
void insertion_sort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

// 2. Bubble Sort
void bubble_sort(int a[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (a[j] > a[j+1]) swap(&a[j], &a[j+1]);
        }
    }
}

// 3. Selection Sort
void selection_sort(int a[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++)
            if (a[j] < a[min]) min = j;
        swap(&a[i], &a[min]);
    }
}

// 4. Shell Sort
void shell_sort(int a[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i], j = i;
            while (j >= gap && a[j-gap] > temp) {
                a[j] = a[j-gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}

// 5. Quick Sort
int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low-1;
    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            swap(&a[i], &a[j]);                    
        }
    }
    swap(&a[i+1], &a[high]);
    return i+1;
}
void quick_sort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quick_sort(a, low, pi-1);
        quick_sort(a, pi+1, high);
    }
}

// 6. Merge Sort
// void merge(int a[], int l, int m, int r) {
//     int n1 = m-l+1, n2 = r-m;
//     int L[n1], R[n2];
//     for (int i=0; i<n1; i++) L[i]=a[l+i];
//     for (int j=0; j<n2; j++) R[j]=a[m+1+j];
//     int i=0, j=0, k=l;
//     while (i<n1 && j<n2) a[k++] = (L[i]<=R[j]) ? L[i++] : R[j++];
//     while (i<n1) a[k++] = L[i++];
//     while (j<n2) a[k++] = R[j++];
// }
// void merge_sort(int a[], int l, int r) {
//     if (l < r) {
//         int m = (l+r)/2;
//         merge_sort(a, l, m);
//         merge_sort(a, m+1, r);
//         merge(a, l, m, r);
//     }
// }
#include <stdio.h>

// Merge two sorted halves: a[l..m] and a[m+1..r]
void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1;  // size of left half
    int n2 = r - m;      // size of right half

    int L[n1], R[n2];    // temporary arrays

    // Copy left half into L[]
    for (int i = 0; i < n1; i++) {
        L[i] = a[l + i];
    }

    // Copy right half into R[]
    for (int j = 0; j < n2; j++) {
        R[j] = a[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    // Merge back into a[]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements of L[]
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    // Copy any remaining elements of R[]
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

// Recursive merge sort
void merge_sort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort(a, l, m); // sort left half
        //printf("1\n");       
        merge_sort(a, m + 1, r); // sort right half
        //printf("2\n");  
        merge(a, l, m, r);        // merge the two halves
    }
}

// // Utility to print array
// void print_array(int a[], int n) {
//     for (int i = 0; i < n; i++) {
//         printf("%d ", a[i]);
//     }
//     printf("\n");
// }

// int main() {
//     int arr[] = {12, 11, 13, 5, 6, 7};
//     int n = sizeof(arr) / sizeof(arr[0]);

//     printf("Original array: ");
//     print_array(arr, n);

//     merge_sort(arr, 0, n - 1);
//     //printf("3\n");


//     printf("Sorted array:   ");
//     print_array(arr, n);

//     return 0;
// }


// 7. Heap Sort
void heapify(int a[], int n, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}
void heap_sort(int a[], int n) {
    for (int i=n/2-1; i>=0; i--) heapify(a, n, i);
    for (int i=n-1; i>0; i--) {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
}

// 8. Counting Sort
void counting_sort(int a[], int n) {
    int max = a[0];
    for (int i=1; i<n; i++) if (a[i] > max) max = a[i];
    int count[max+1];
    for (int i=0; i<=max; i++) count[i]=0;
    for (int i=0; i<n; i++) count[a[i]]++;
    int k=0;
    for (int i=0; i<=max; i++)
        while (count[i]--) a[k++] = i;
}

// 9. Radix Sort (LSD, base 10)
void counting_sort_exp(int a[], int n, int exp) {
    int output[n], count[10] = {0};
    for (int i=0; i<n; i++) count[(a[i]/exp)%10]++;
    for (int i=1; i<10; i++) count[i] += count[i-1];
    for (int i=n-1; i>=0; i--) {
        int digit = (a[i]/exp)%10;
        output[--count[digit]] = a[i];
    }
    for (int i=0; i<n; i++) a[i] = output[i];
}
void radix_sort(int a[], int n) {
    int max = a[0];
    for (int i=1; i<n; i++) if (a[i] > max) max = a[i];
    for (int exp=1; max/exp > 0; exp*=10)
        counting_sort_exp(a, n, exp);
}

// 10. Bucket Sort (for [0,1) floats)
void bucket_sort(float a[], int n) {
    float b[n][n];
    int count[n];
    for (int i=0; i<n; i++) count[i]=0;
    for (int i=0; i<n; i++) {
        int bi = (int)(a[i]*n);
        b[bi][count[bi]++] = a[i];
    }
    for (int i=0; i<n; i++) {
        for (int j=1; j<count[i]; j++) {
            float key = b[i][j]; int k=j-1;
            while (k>=0 && b[i][k]>key) { b[i][k+1]=b[i][k]; k--; }
            b[i][k+1]=key;
        }
    }
    int idx=0;
    for (int i=0; i<n; i++)
        for (int j=0; j<count[i]; j++)
            a[idx++] = b[i][j];
}

// 11. Radix Exchange Sort (MSD quicksort style, non-negative)
void radix_exchange_sort(int a[], int n, int bit) {
    if (n<=1 || bit<0) return;
    int i=0, j=n-1;
    while (i<=j) {
        while (i<=j && ((a[i]>>bit)&1)==0) i++;
        while (i<=j && ((a[j]>>bit)&1)==1) j--;
        if (i<j) swap(&a[i], &a[j]);
    }
    radix_exchange_sort(a, i, bit-1);
    radix_exchange_sort(a+i, n-i, bit-1);
}

// 12. Address Calculation Sort (simple direct addressing)
void address_calculation_sort(int a[], int n) {
    int min=a[0], max=a[0];
    for (int i=1; i<n; i++) {
        if (a[i]<min) min=a[i];
        if (a[i]>max) max=a[i];
    }
    int m = max-min+1;
    int table[m];
    for (int i=0; i<m; i++) table[i]=0;
    for (int i=0; i<n; i++) table[a[i]-min]=1;
    int k=0;
    for (int i=0; i<m; i++) if (table[i]) a[k++]=i+min;
}

// ------------------ Utility ------------------
void print_arr_int(int a[], int n) {
    for (int i=0; i<n; i++) printf("%d ", a[i]);
    printf("\n");
}
void print_arr_float(float a[], int n) {
    for (int i=0; i<n; i++) printf("%.2f ", a[i]);
    printf("\n");
}

// ------------------ Main ------------------
int main() {
    int arr1[] = {5,2,9,1,5,6};
    int n1 = 6;
    insertion_sort(arr1, n1); printf("Insertion Sort: "); print_arr_int(arr1,n1);

    int arr2[] = {5,2,9,1,5,6};
    bubble_sort(arr2, 6); printf("Bubble Sort: "); print_arr_int(arr2,6);

    int arr3[] = {5,2,9,1,5,6};
    selection_sort(arr3, 6); printf("Selection Sort: "); print_arr_int(arr3,6);

    int arr4[] = {12,34,54,2,3};
    shell_sort(arr4, 5); printf("Shell Sort: "); print_arr_int(arr4,5);

    int arr5[] = {10,7,8,9,1,5};
    quick_sort(arr5, 0, 5); printf("Quick Sort: "); print_arr_int(arr5,6);

    int arr6[] = {12,11,13,5,6,7};
    merge_sort(arr6, 0, 5); printf("Merge Sort: "); print_arr_int(arr6,6);

    int arr7[] = {12,11,13,5,6,7};
    heap_sort(arr7, 6); printf("Heap Sort: "); print_arr_int(arr7,6);

    int arr8[] = {170,45,75,90,802,24,2,66};
    radix_sort(arr8, 8); printf("Radix Sort: "); print_arr_int(arr8,8);

    int arr9[] = {4,2,2,8,3,3,1};
    counting_sort(arr9, 7); printf("Counting Sort: "); print_arr_int(arr9,7);

    float arr10[] = {0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68};
    bucket_sort(arr10, 10); printf("Bucket Sort: "); print_arr_float(arr10,10);

    int arr11[] = {5,2,9,1,7,3};
    radix_exchange_sort(arr11, 6, 31); printf("Radix Exchange Sort: "); print_arr_int(arr11,6);

    int arr12[] = {12,10,11,13};
    address_calculation_sort(arr12, 4); printf("Address Calculation Sort: "); print_arr_int(arr12,4);

    return 0;
}
