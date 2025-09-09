#include <stdio.h>

void merge(int arr[], int tmp[], int l, int m, int r) {
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
        }
    }

    while (i <= m) {
        tmp[k++] = arr[i++];
    }
    while (j <= r) {
        tmp[k++] = arr[j++];
    }

    // Copy back to original array
    for (i = l; i <= r; i++) {
        arr[i] = tmp[i];
    }
}

void merge_sort(int arr[], int n) {
    int tmp[n];
    int size, l, m, r;

    for (size = 1; size < n; size = 2 * size) {
        for (l = 0; l < n - 1; l += 2 * size) {
            m = l + size - 1;

            // Ensure mid is within range
            if (m >= n - 1) {
                m = n - 1;
            }

            // Compute right index
            if (l + 2 * size - 1 < n - 1) {
                r = l + 2 * size - 1;
            } else {
                r = n - 1;
            }

            merge(arr, tmp, l, m, r);
        }
    }
}

void print_arr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    print_arr(arr, n);

    merge_sort(arr, n);

    printf("Sorted array:\n");
    print_arr(arr, n);
}


