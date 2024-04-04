#include <stdio.h>
#include <stdbool.h>

void max_min(int arr[], int low, int high, int* max, int* min) {
    if (low == high) {
        *max = arr[low];
        *min = arr[low];
    } else if (high == low + 1) {
        if (arr[low] > arr[high]) {
            *max = arr[low];
            *min = arr[high];
        } else {
            *max = arr[high];
            *min = arr[low];
        }
    } else {
        int mid = (high + low) / 2;
        int max1, min1, max2, min2;
        max_min(arr, low, mid, &max1, &min1);
        max_min(arr, mid + 1, high, &max2, &min2);
        *max = (max1 > max2) ? max1 : max2;
        *min = (min1 < min2) ? min1 : min2;
    }
}

bool are_all_elements_same(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[0]) {
            return false;
        }
    }
    return true;
}
int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    if (are_all_elements_same(arr, n)) {
        printf("All elements are same lol!\n");
        return 0;
    }
    int max, min;
    max_min(arr, 0, n - 1, &max, &min);
    printf("Maximum element = %d\n", max);
    printf("Minimum element = %d\n", min);
    return 0;
}