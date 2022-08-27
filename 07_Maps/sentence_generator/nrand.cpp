#include <cstdlib>          // defines rand, srand, RAND_MAX, NULL
#include <ctime>            // defines time
#include <stdexcept>        // defines domain_error

#include "nrand.h"

using std::domain_error;
using std::rand;
using std::srand;
using std::time;


/**
 * HOW WE WILL GENERATE RANDOM INTEGER FROM THE INTERVAL [1, n]
 * Partition the available random numbers into n equal-sized buckets, perhaps with some numbers left over.
 * Then we can compute a random number, figure out into which bucket it falls, and return that bucket's number.
 * If the random number isn't in any bucket, we will ignore it, and keep asking for random numbes until 
 *  we get one that lands in a bucket.
 **/
int nrand(int n)
{
    // set a flag for initialising the seed.
    static bool init_seed = false;

    // n must to be a positive integer, but also no bigger than RAND_MAX 
    // (RAND_MAX = 2147483647, the cap for int types as well as the rand() function).
    if (n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nrand is out of range");
    
    // if not done so yet, set the random seed, using the current time.
    if(!init_seed) {
        srand(time(NULL));
        // change the flag, as the seed only needs to be set once.
        init_seed = true;
    }

    // 1) Partition
    const int bucket_size = RAND_MAX / n;

    // 2) Begin computing random numbers
    int r;
    do
    {
        // rand() generates a random integer in the range [0, RAND_MAX]
        r = rand() / bucket_size;
    } while (r >= n); // 3) ignore generated value if outside buckets

    return r;
    
}
// =========================================================================================================
// EXAMPLE of nrand() process:
// =========================================================================================================
// Suppose for simplicity RAND_MAX = 1000 (thus rand() gives values in interval [0, 1000])
// Let n = 9 (want to generate random integer in interval [1, 9])
// Then bucket_size = 111 (111.11... rounded down)
// This gives the following partitions/buckets each of equal size (111):
// [0, 111), [111, 222), [222, 333), [333, 444), [444, 555), [555, 666), [666, 777), [777, 888), [888, 999),
//  (1)         (2)         (3)         (4)         (5)         (6)         (7)         (8)         (9)
// Remainders: 999 and 1000.
// ---------------------------------------------------------------------------------------------------------
// Now suppose rand() gives 999 (or 1000)
// then r = 9, which is outside the range of buckets (r >= n). So try again.
// ---------------------------------------------------------------------------------------------------------
// Now if rand() gives, say, 756, 
// then r = 6 (6.810810... rounded down)
// this is wihin the the range of buckets (r < n), particularly bucket #6.
// Thus, the integer 6 out of [1, 9] is outputted by nrand().
// =========================================================================================================
