/*
John Sullivan
CSC 212
Assignment 2
10/3/2018
*/

#include <iostream>

//This function will add the last s numbers of n together.
unsigned long int rec_suffix_sum(unsigned int n, unsigned int s);

//This function takes all the even digits in num, and adds them together.
unsigned int rec_sum_even(unsigned int num);

//This function will tell you if an array A of n length is sorted or not.
bool rec_is_sorted(const int *A, unsigned int n);

//This function will tell you if a string S of n length is a palindrome or not.
bool rec_palindrome(const char *S, unsigned int n);

//This function will reverse a string in place.
void rec_reverse_str(char *str, unsigned int len);

//This function will tell you if all vowels in a word A are in order from a to u.
bool rec_sorted_vowels(const char *A);

//This function recursively binary searches for a key k in array A.
bool rec_bin_search(const int *A, unsigned int n, int k);

//This is a recursive version of selection sort.
void rec_selection_sort(int *A, unsigned int n);

//This will check if the numbers are increasing order, decreasing order, or neither.
int rec_check_order(const int *A, unsigned int n);

//This will print out all lowercase letters in reversed order of the input.
void rec_reversed_letters(const char *str);


unsigned long int rec_suffix_sum(unsigned int n, unsigned int s){
   //If s is equal to 0, return 0; Otherwise, recursively call the function with 1 less of each varible, and add n to it each call.
   return (s == 0)?  0 : n + rec_suffix_sum(n-1, s-1);
}

unsigned int rec_sum_even(unsigned int num){
    //Once we reach the base case, return recursively
    if (num == 0){
        return 0;
    }
    //If you mod any number by 10, you will get the last digit. So 9124891248 % 10 = 8. This is what this line does.
    int digit = num % 10;

    //If the digit we found is even, we must add it to our sum recursively, then divide the num by 10 to get rid of the last digit.
    if(digit % 2 == 0){
        return rec_sum_even(num / 10) + digit;
    }
    //If the digit we found is odd, we do not add it to the sum but still get rid of the last digit by dividing by 10.
    //So, 104391941 / 10 would equal 10439194 (the 1 falls off the end when dividing by 10)
    //This is how we traverse large numbers digit by digit.
    if(digit % 2 != 0){
        return rec_sum_even(num / 10);
    }
}

bool rec_is_sorted(const int *A, unsigned int n){
    //if the length is less than or equal to 1, or traversed the array with no problem, we can assume it's sorted
    if (n <= 1){
        return true;
    }
    //if the rightmost element is greater than the left, then it's not sorted correctly.
    else if(A[n-1] > A[n-2]){
        return false;
    }
    //recursively go to the next (left) element in the array.
    return rec_is_sorted(A, (n-1));
}

bool rec_palindrome(const char *S, unsigned int n){
    //If the length is less than or equal to 1, or we traversed the whole string with no problem, we assume it's a palindrome
    if(n <= 1){
        return true;
    }
    //If the leftmost element is not equal to the rightmost, then it's not a palindrome
    if(S[0] != S[n-1]){
        return false;
    }
    //Keep traversing the string by looking closer and closer to the middle of the string from the left and right, recursively.
    return rec_palindrome(S+1, n-2);
}

void rec_reverse_str(char *str, unsigned int len){
    char temp = str[0];
    //Basically, if the length is 1, stop reversing.
    if(len / 2 == 0){
        return;
    }
    //Reverse the letters in the string at this position.
    str[0] = str[len-1];
    str[len-1] = temp;

    //Traverse recursively through the string.
    rec_reverse_str(str+1, len-2);
}

bool rec_sorted_vowels(const char *A){
    //This counter 'i' will allow to me to check the index of my string against the later vowels.
    int i = 1;
    //If the element I'm looking at in the string (first element) is a vowel, enter this statement.
    if(A[0] == 'a' || A[0] == 'e' || A[0] == 'i' || A[0] == 'o' || A[0] == 'u'){
        //Check to see if the next vowel is a greater ASCII value.
        while(A[i] != '\0')
        {
            if(A[i] == 'a' || A[i] == 'e' || A[i] == 'i' || A[i] == 'o' || A[i] == 'u'){
                //If it is a greater ascii vowel, cool, keep traversing, else return not sorted!
                if (A[i] > A[0]){
                    return rec_sorted_vowels(A+1);
                }
                if (A[i] < A[0]){
                    return false;
                }
            }
            i++;
        }
    }
    //If it doesn't see an unsorted value, then we advance to the next element in the array!
    //If we reach the end of the array with no problems, it is sorted!
    return (A[0] == '\0')? true : rec_sorted_vowels(A+1);
}

bool rec_bin_search(const int *A, unsigned int n, int k){
   //If I can not break down the array anymore, check if the element I'm looking at is my key. If not, it's not in the array.
    if(n == 1){
        return (A[0] == k)? true : false;
    }
    //Takes half of the size of the array we are looking at.
    int half = n / 2;
    //If the key is in the center of half of the part of the array we are looking at, then we found our number!
    if(A[half] == k) return true;

    //If not, we keep checking, either to the left of the right of the halfway mark.
    //If my key is greater than the number at the half point, assuming my array is sorted in ***non-increasing order...
    //Then we check to the left of the half point.
    //Otherwise, we check to the right of the half point if our key is less than the halfway point.
    return (k > A[half])? rec_bin_search(A, n - (n/2), k) : rec_bin_search(A+half, n - (n/2), k);
}

void rec_selection_sort(int *A, unsigned int n){
    //Create an initial value for the minimum starting at the beginning of the array, so we can check this against..
    // all the other elements in the array.
    int min = A[0];
    if (n == 0){
        return;
    }
    //This counter is used to traverse through the array and find the index of the new minimum value.
    int ctr = 0;

    //This will be used to flag whether or not a new minimum value was found.
    bool newMin = false;

    //Try to find a new minimum value in the array. If one is found, swap it with the greater value at that index...
    // once the whole array has been traversed.
    for (int i = 0; i < n; i++){
        if(A[i] < min){
            min = A[i];
            ctr = i;
            newMin = true;
        }
    }
    if (newMin == true){
        int swap = A[0];
        A[0] = A[ctr];
        A[ctr] = swap;
    }
    //This recursive call looks at the next (first) element in the array.
    rec_selection_sort(A+1, n-1);
}

int rec_check_order(const int *A, unsigned int n){
    //If the length is less than or equal to 1, we can say that it's not in ascending or descending order.
    if(n <= 1){
        return 0;
    }
    //Check if the left most element is greater than the right most, if it is, either keep traversing or...
    // if we are only checking two more numbers, we can assume we are at the end of the array, and it's in decreasing order.
    if(A[0] > A[1]){

        if(n == 2) return -1;

        if (A[1] > A[2]) return rec_check_order(A+1, n-1);
    }
    //Same as previous statement, but checking for increasing order.
    if(A[0] < A[1]){

        if (n == 2) return 1;

        if (A[1] < A[2]) return rec_check_order(A+1, n-1);
    }
    //If at any point the elements are equal we can assume that it's neither non-increasing or non-decreasing
    if(A[0] == A[1]) return 0;

    //This is here to make the compiler stop complaining.
    return 0;
}

void rec_reversed_letters(const char *str){
    //If we are at the end of the string, start recursively printing out your results!
    if(str[0] == '\0') return;

    //Traverses the string to the end.
    rec_reversed_letters(str+1);

    //Prints from right to left in a string of all (only) lowercase letters.
    if(str[0] >= 'a' && str[0] <= 'z'){
        std::cout << str[0];
    }
}
