#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

/*int str_to_dec(string line){
 int number = 0;
 for(int i = 0; i < line.size(); i++){
 if line[i] == " ":
 
 }
 }*/

void quick_sort(int tab[], int left, int right){
    if(left >= right) return;
    int pivot = tab[(left+right)/2];
    int i = left, j = right;
    while(i <= j){
        while(tab[i] < pivot){
            i++;
        }
        while(tab[j] > pivot){
            j--;
        }
        if(i <= j){
            swap(tab[i], tab[j]);
            i++;
            j--;
        }
    }
    if (left < j) quick_sort(tab, left, j);
    if (i < right) quick_sort(tab, i, right);
}
void merge(int tab[], int left, int right){
    int piv = (left+right)/2;
    int i = left, j = piv+1, k = 0;
    int *tab_pom = new int[(right-left+1)];
    while(i <= piv && j <= right){
        if (tab[i] < tab[j]){
            tab_pom[k] = tab[i];
            i++;
        }else{
            tab_pom[k] = tab[j];
            j++;
        }
        k++;
    }
    while(i <= piv){
        tab_pom[k] = tab[i];
        k++;
        i++;
    }
    while(j <= right){
        tab_pom[k] = tab[j];
        k++;
        j++;
    }
    for(int l = 0; l < k; l++){
        tab[left+l] = tab_pom[l];
    }
    delete [] tab_pom;
}
void merge_sort(int tab[], int left, int right){
    if(left >= right) return;
    int piv = (left+right)/2;
    merge_sort(tab, left, piv);
    merge_sort(tab, piv+1, right);
    merge(tab, left, right);
}
int find_max(int tab[], int n){
    int x = tab[0];
    for(int i = 0; i < n; i++){
        if(  tab[i] > x) x =  tab[i];
    }
    return x;
}
int find_min(int tab[], int n){
    int x = tab[0];
    for(int i = 0; i < n; i++){
        if(  tab[i] < x) x =  tab[i];
    }
    return x;
}
void counting_sort(int tab[], int n){
    int min = find_min(tab, n), maks = find_max(tab, n);
    int N = maks-min+2;
    int * tab_pom = new int[N];
    for(int i = 0; i < N; i++) tab_pom[i] = 0;
    for(int i = 0; i < n; i++) tab_pom[tab[i]]++;
    int k = 0;
    for(int i = 0; i < N; i++){
        while(tab_pom[i] > 0){
            tab[k] = i;
            tab_pom[i]--;
            k++;
        }
    }
    delete [] tab_pom;
}
void selection_sort(int tab[], int n){
    int min;
    for(int i = 0; i < n; i++){
        min = i;
        for(int j = i; j < n; j++){
            if( tab[j] < tab[min]){
                min = j;
            }
        }
        swap(tab[min], tab[i]);
    }
}
void bubble_sort(int tab[], int n){
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(tab[j] < tab[i]) swap(tab[i], tab[j]);
        }
    }
}
int main(int argc, const char * argv[]) {
    fstream czasy;
    czasy.open("czasy.txt", ios::app);
    int N;
    cin >> N;
    int *table = new int[N];
    int x;
    for(int i = 0; i < N; i++){
        cin >> x;
        table[i] = x;
    }
    double start = clock();
    bubble_sort(table, N);
    double end = clock();
    for(int i = 0; i < N; i++){
        cout << table[i] << " ";
    }
    czasy << "\nCzas dla " << N << " argumentow\n" << (double)(end - start)/CLOCKS_PER_SEC;
    czasy.close();
    delete[] table;
    return 0;
}
