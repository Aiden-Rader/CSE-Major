#include <iostream>
#include <vector>
#include <chrono>
#include <random>





void insertionSort(std::vector<int>& numbers)
{
    int n = numbers.size();

    //Iterate through the elements, starting from the second element (index 1)
    for (int i = 1; i < n; ++i)
    {
        int key = numbers[i];
        int j = i - 1;


        //Move elements in the sorted part that are greater than the key to one position ahead of their current position
        while (j >= 0 && numbers[j] > key)
        {
            numbers[j + 1] = numbers[j];
            j = j - 1;
        }
        numbers[j + 1] = key;
    }
}


//====================================================================//


// Function to find the maximum value in a vector
//        // Find the maximum value
//        maxValue = numbers[0]
//        for (i = 1; i < numbersSize; i++) {
//            if (numbers[i] > maxValue)
//                maxValue = numbers[i]
int findMaxValue(const std::vector<int>& numbers)
{
    int maxValue = numbers[0];
    for (int i = 1; i < numbers.size(); i++) 
    {
        if (numbers[i] > maxValue) 
        {
            maxValue = numbers[i];
        }
    }
    return maxValue;
}


//BucketSort Function
//BucketSort(numbers, numbersSize, bucketCount) {
//    if (numbersSize < 1)
//        return
//        buckets = Create list of bucketCount buckets
//        // Find the maximum value with findMaxValue
//    // Put each number in a bucket
//    for each (number in numbers) {
//        index = floor(number * bucketCount / (maxValue + 1))
//            Append number to buckets[index]
//    }
//        // Sort each bucket
//        for each (bucket in buckets)
//            Sort(bucket)
//            // Combine all buckets back into numbers list
//            result = Concatenate all buckets together
//            Copy result to numbers
//}
void bucketSort(std::vector<int>& numbers, int numBuckets)
{

    if (numbers.size() < 1)
    {
        return;
    }

    // Uses findMaxValue to find the maximum value in a vector
    int maxValue = findMaxValue(numbers);

    // Create list of buckets
    std::vector<std::vector<int>> buckets(numBuckets);


    //for each number in numbers
    for (int number : numbers)
    {
        // number -> (double) * numBuckets(int) / Maximum Value + 1 
        int index = static_cast<int>(std::floor(static_cast<double>(number) * numBuckets / (maxValue + 1)));

        //Append number to buckets[index]
        buckets[index].push_back(number);
    }

    // Use insertionSort to sort the numbers in buckets vector
    for (std::vector<int>& bucket : buckets)
    {
        insertionSort(bucket);
    }
    // Combine buckets back into numbers
    
    //Clear the original vector
    numbers.clear();

    // iterate through each bucket in buckets
    for (const std::vector<int>& bucket : buckets) 
    {
        numbers.insert(numbers.end(), bucket.begin(), bucket.end());
    }
}

//====================================================================//


//RadixGetLength Function
//RadixGetLength(value) {
// // Returns the length, in number of digits, of value
//if (value == 0)
//return 1
//digits = 0
//while (value != 0) {
//    digits = digits + 1
//        value = value / 10
//}
//return digits
//}
int RadixGetLength(int value) 
{
    if (value == 0)
        return 1;

    int digits = 0;

    while (value != 0) 
    {
        digits = digits + 1;
        value = value / 10;
    }
    return digits;
}


//RadixGetMaxLength Function
//RadixGetMaxLength(array, arraySize) {
//    // Returns the maximum length, in number of digits, out of all elements in the array
//        maxDigits = 0
//        for (i = 0; i < arraySize; i++) {
//            digitCount = RadixGetLength(array[i])
//                if (digitCount > maxDigits)
//                    maxDigits = digitCount
//        }
//    return maxDigits
//}
int RadixGetMaxLength(const std::vector<int>& array) 
{
    int maxDigits = 0;
    for (int value : array) 
    {
        int digitCount = RadixGetLength(value);
        if (digitCount > maxDigits)
            maxDigits = digitCount;
    }
    return maxDigits;
}

//Radix Sort
//RadixSort(array, arraySize) {
//    buckets = create array of 10 buckets
//        // Find the max length, in number of digits
//        maxDigits = RadixGetMaxLength(array, arraySize)
//       
//      // Start with the least significant digit
//        pow10 = 1
//        for (digitIndex = 0; digitIndex < maxDigits; digitIndex++) {
//            for (i = 0; i < arraySize; i++) {
//                bucketIndex = abs(array[i] / pow10) % 10
//                    Append array[i] to buckets[bucketIndex]
//            }
//            arrayIndex = 0
//                for (i = 0; i < 10; i++) {
//                    for (j = 0; j < buckets[i]⇢size(); j++)
//                        array[arrayIndex++] = buckets[i][j]
//                }
//            pow10 = 10 * pow10
//                Clear all buckets
//        }
//}
void radixSort(std::vector<int>& numbers)
{
    int arraySize = numbers.size();

    if (arraySize <= 0)
    {
        return;
    }

    int maxDigits = RadixGetMaxLength(numbers);

    //Least significant digit 
    int pow10 = 1;


    for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++)
    {
        std::vector<std::vector<int>> buckets(10);

        for(int i = 0; i < arraySize; i++)
        {
            int bucketIndex = abs(numbers[i] / pow10) % 10;

            //Append array[i] to buckets[bucketIndex]
            buckets[bucketIndex].push_back(numbers[i]);
        }

        int arrayIndex = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < buckets[i].size(); j++)
            {
                numbers[arrayIndex++] = buckets[i][j];
            }
        }
        pow10 = 10 * pow10;

        //Clear the buckets
        for (int i = 0; i < 10; i++)
        {
            buckets[i].clear();
        }
    }
}

//====================================================================//


int main()
{
    std::vector<int> nValues = { 10, 100, 1000, 10000 };
    int numBuckets = 10;

    // Seed for random number generator
    std::random_device rd;
    std::mt19937 rnd(rd());

    for (int n : nValues)
    {
        std::cout << "Vector size: " << n << std::endl;

        // Repeat the process 10 times
        for (int iter = 0; iter < 10; ++iter)
        {
            // Generate a random vector of length N
            std::vector<int> numbers(n);
            for (int i = 0; i < n; ++i)
            {
                numbers[i] = rnd() % 1000; // Random numbers between 0 and 999
            }

            //Random number for Radix and Bucket Sorts


        //====================================================================//

            // Start the timer for Insertion Sort
            auto start_INSERT = std::chrono::high_resolution_clock::now();
            
            insertionSort(numbers);

            // Stop the timer for Insertion Sort
            auto stop_INSERT = std::chrono::high_resolution_clock::now();

            // Calculate and print the elapsed time in milliseconds for Insertion Sort
            auto duration_INSERT = (double)std::chrono::duration_cast<std::chrono::microseconds>(stop_INSERT - start_INSERT).count() / 1000;

        //====================================================================//

            // Start the timer for Bucket Sort
            auto start_BUCKET = std::chrono::high_resolution_clock::now();

            bucketSort(numbers, numBuckets);

            // Stop the timer for Bucket Sort
            auto stop_BUCKET = std::chrono::high_resolution_clock::now();

            // Calculate and print the elapsed time in milliseconds for Bucket Sort
            auto duration_BUCKET = (double)std::chrono::duration_cast<std::chrono::microseconds>(stop_BUCKET - start_BUCKET).count() / 1000;

        //====================================================================//

            // Start the timer for Radix Sort
            auto start_RADIX = std::chrono::high_resolution_clock::now();

            radixSort(numbers);

            // Stop the timer for Radix Sort
            auto stop_RADIX = std::chrono::high_resolution_clock::now();

            // Calculate and print the elapsed time in milliseconds for Radix Sort
            auto duration_RADIX = (double)std::chrono::duration_cast<std::chrono::microseconds>(stop_RADIX - start_RADIX).count() / 1000;


        //====================================================================//


            std::cout << "Insertion Sort: " << duration_INSERT << " milliseconds " << std::endl;

            std::cout << "Bucket Sort: " << duration_BUCKET << " milliseconds " << std::endl;

            std::cout << "Radix sort: " << duration_RADIX << " milliseconds " << std::endl << std::endl << "==============================" << std::endl;;
        }
        std::cout << std::endl; // Add a newline between different N values
    }
    return 0;
}