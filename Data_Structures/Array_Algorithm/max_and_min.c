#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#ifdef __cplusplus
extern "C" {

void max_and_min(int* a, int left, int right, int* pmax, int* pmin) {
    if(a==NULL || left > right) {
        return;
    }

    if(left == right) {//只有一个元素
        *pmax = a[left];
        *pmin = a[right];
        return;
    }

    if(left + 1 == right) {// 有两个元素
        *pmin = a[left] >= a[right] ? a[right] : a[left];
        *pmax = a[left] >= a[right] ? a[left] : a[right];
        return;
    }
    
    //printf("*pmax=%d,*pmin=%d\n", *pmax, *pmin);

    int left_tmp_min = 0x00;
    int left_tmp_max = 0x00;
    int right_tmp_min = 0x00;
    int right_tmp_max = 0x00;
    max_and_min(a, left, (left+right)/2, &left_tmp_max, &left_tmp_min);
    max_and_min(a, (left+right)/2+1, right, &right_tmp_max, &right_tmp_min);

    *pmax = left_tmp_max > right_tmp_max ? left_tmp_max : right_tmp_max;
    *pmin = left_tmp_min > right_tmp_min ? right_tmp_min : left_tmp_min;
return;
}

int main() {
    int a[10] = {11,12,23,34,45,46,37,28,19,3};

    int max = 0, min = 0;

    max_and_min(a,0,(sizeof(a)/sizeof(int))-1,&max,&min);

    printf("最大值:%d,最小值:%d\n", max, min);
return 0;
}

}
#endif

#if 0
void MaxandMin(int *a, int l, int r, int& maxValue, int& minValue)
{
    if(l == r) // l与r之间只有一个元素
    {
        maxValue = a[l];
        minValue = a[l];
        return ;
    }

    if(l + 1 == r) // l与r之间只有两个元素
    {
        if(a[l] >= a[r])
        {
            maxValue = a[l] ;
            minValue = a[r] ;
        }
        else
        {
            maxValue = a[r] ;
            minValue = a[l] ;
        }
        //return ;
    } 

    int m = (l + r) / 2 ; // 求中点

    int lmax ; // 左半部份最大值
    int lmin ; // 左半部份最小值
    MaxandMin(a, l, m, lmax, lmin) ; // 递归计算左半部份

    int rmax ; // 右半部份最大值
    int rmin ; // 右半部份最小值
    MaxandMin(a, m + 1, r, rmax, rmin) ; // 递归计算右半部份

    //maxValue = max(lmax, rmax) ; // 总的最大值
    //minValue = min(lmin, rmin) ; // 总的最小值

    maxValue = lmax > rmax ? lmax : rmax; // 总的最大值
    minValue = lmin > rmin ? rmin : lmin ; // 总的最小值
return;
}

int main() {
    int a[10] = {1,2,3,4,5,6,7,8,9};

    int max = 0, min = 0;

    //max_and_min(a,0,sizeof(a)-1,&max,&min);
    MaxandMin(a,0,sizeof(a)/sizeof(int)-1,max,min);
    //MaxandMin(a,0,9,max,min);

    printf("最大值:%d,最小值:%d\n", max, min);
return 0;
}

#endif

#if 0
//#include "stdafx.h"
#define n 10
int A[n];
int Max(int a, int b)
{
    return ((a >= b) ? a : b);
}
int Min(int a, int b)
{
    return ((a <= b) ? a : b);
}
void MaxMin(int i, int j, int &fmax, int &fmin)
{
    int mid;
    if (i == j)
    {
        fmax = A[i];
        fmin = A[i];
    }
    else if(i==j-1)
    {
        if (A[i] < A[j])
        {
            fmin = A[i];
            fmax = A[j];
        }
        else
        {
            fmin = A[j];
            fmax = A[i];
        }
    }
    else
    {
        int lmax, lmin, rmax, rmin;
        //mid = floor((i + j) / 2);
        mid = (i + j) / 2;
        MaxMin(i, mid, lmax, lmin);
        MaxMin(mid + 1, j, rmax, rmin);
        fmax = Max(lmax, rmax);
        fmin = Min(lmin, rmin);
    }
}
int main()
{
    for (int i = 0; i < n; i++)
    {
        A[i] = i;;
    }   
    int fmax, fmin;
    MaxMin(0, n-1, fmax, fmin);
    printf("\n\n最大值为:%d\n最小值为:%d\n\n", fmax, fmin);

    return 0;
}
#endif
