#include "declaration/shell_sort.h"

//希尔排序，不稳定（各组内的直接插入排序，不同组间可能存在同值）
// 时间复杂度O(n^1.3)，相对于插入排序非常不错, 在len为100000时，我将希尔排序的后移操作次数与直接插入排序比较后发现，后者简直是前者的成百上千倍
void shell_sort(int *arr, int len) {
    /*
     * 首先有一个间隔序列 t1,t2,t3...tk, 其中 t1 = len/2, t2 = t1/2.....tk = 1 (增列序列不一定必须这样，有的地方从len-1开始,后面gap/3+1)
     * 希尔排序共根据上述序列进行k趟排序，每趟排序对应的ti称为间隙gap(从t1开始)
     * 在一趟排序中,数组根据gap分为几组，比如下标为0,gap,gap+gap..为一组，1,1+gap,1+gap+gap为一组，依次类推,
     * 然后分别在这些组内进行直接插入排序
     * 最后一趟 tk = 1, 即所有元素都是一个组，然后进行插入排序
     * 至此希尔排序结束
     *
     * 比如 1,3,4,7,5,2,9 在第一趟中,gap = 3, 那么 1,7 ; 3,2; 4,9; 5; 共4组， 然后组内进行直接插入排序，当然逻辑上的后移都是以gap间隔移动
     * 第一趟排序后---> 1,2,4,7,5,3,9
     * 第二趟排序gap = 1, 普通的直接插入排序
     *
     * 实际上分组进行插入排序是为了利用插入排序的特性（元素少时很好用）,每趟都是为了让元素分布更接近结果,最后一趟插入排序时就可以少做事
     */
    for (int gap = len / 2; gap > 0; gap = gap / 2) { //k趟排序
        //每组的直接插入排序都是从第二个元素开始的，向前比较，而gap之前的元素必然是每组中的第一个元素，不需要比较(也没得比较)
        for (int i = gap; i < len; i++) { //逻辑上是分组进行插入排序的，但其实这里是各组交替进行的，gap~len-1肯定存在不同组的
            // 如果我们真的严格为每组分别进行。其实没必要增加这个麻烦
            // 反正最终都会遍历到gap~len-1中的元素，何必呢
            int index = i - gap; //先开始比较组内前一个元素
            int current = arr[i]; //提出的值
            while (index >= 0 && current < arr[index]) { //理应先比较index>=0,否则越界
                arr[index + gap] = arr[index]; //逻辑后移
                index = index - gap;
            }
            //此时的[index]<=current,亦或者[index+gap]就是组中第一个元素
            arr[index + gap] = current; //插入
        }
    }
}