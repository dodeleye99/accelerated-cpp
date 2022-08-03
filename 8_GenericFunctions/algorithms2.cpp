#include <algorithm>


/**
 * Test whether two sequences bounded by iterators [b,  e) and [b2, ...) (same size as first)
 * are exactly the same. Outputs true if they match, and false otherwise.
 * 
 * Note theat we have two type-parameters, one for each iterator to its sequence.
 * This allows us to compare collections that are not the same type
 * (e.g, comparing a vector<T> with a list<T>)
 * 
 * Operators used: ==, ++, and *.
 * Iterator required: Input iterator.
 **/
template<class In1, class In2>
bool equal(In1 b, In1 e, In2 b2)
{
    // immediately return with true if the beginning iterator reaches the end, 
    // indicating every value in the sequences have been compared, and match.
    if(b == e)
        return true;

    // if values match, do recursive call with the iterators advanced.
    // otherwise, return false immediately. 
    return *b == *b2 ? equal(++b, e, ++b2) : false;

    // Non-recursive implementation:
    // while (b != e) {

    //     if(*b != *b2)
    //         return false;
    //     ++b; 
    //     ++b2;
    // }
    // return true;
}

/**
 * Searches a sequence bounded by iterators [b, e) and returns the iterator pointing to the 
 *  first occurance of t found. 
 * If not found, then e is returned.
 * 
 * Operators used: ==, ++, and *.
 * Iterator required: Input iterator.
 **/
template<class T, class In>
In find(In b, In e, T t)
{   
    // immediately return iterator b if it has reached the end 
    // or if t is found at where it currently points to.
    if(b == e || *b == t)
        return b;

    // continue the search - do recursive call with iterator b advanced.
    return find(++b, e, t);
}

/**
 * Writes a sequence of values pointed by the range of iterators [b, e) 
 * to another sequential collection or location, indicated by the iterator d which points to the start of the 
 * destination to output.
 * 
 * Operators used:
 * for b: ==, ++, *(dref.)
 * for d: ++, = (assgnment), *(dref. assignment only)
 * Iterator required: 
 * for b: input iterator 
 * for d: output iterator
 **/
template<class In, class Out>
Out copy(In b, In e, Out d)
{   
    // if b has reached the end, then immediately exit returning the output iterator d.
    if (b == e)
        return d;
    
    // write the value pointed to by b to the location pointed to by d, overwriting the original value at that location,
    // then increment both iterators.
    *d++ = *b++;
    
    // continue the copying process, using the advanced iterators.
    return copy(b, e, d);

    // Non-recursive implementation:
    // while(b != e)
    //     *d++ = *b++;
    
    // return d;
    
}

/**
 * Traverses over a sequence of values bounded by iterators [b, e) and, without deleting the values from the original sequence,
 * disregards all the values that pass a predicate p, and writes the remaining values (which fail the prediacte) to another 
 * sequential collection or location indicated by the iterator d, which points to the start of the destination to output.
 * 
 * Operators used:
 * for b: ==, ++, *(dref.)
 * for d: ++, = (assgnment), *(dref. assignment only)
 * 
 * Iterator required: 
 * for b (and e): input iterator 
 * for d:         output iterator
 **/
template<class In, class Out, class F_type>
Out remove_copy_if(In b, In e, Out d, F_type p)
{
    // if b has reached the end, then immediately exit returning the output iterator d.
    if (b == e)
        return d;
    
    // write values that fail the predicate p to the destination pointed to by d, incrementing it to point
    // to the next location to be written to.
    if(!p(*b))
        *d++ = *b;

    // continue traversing, advancing iterator b to point to the next value to read.
    return remove_copy_if(++b, e, d, p);

    // Non-recursive implementation:
    // while(b != e) {
    //     if (!p(*b))
    //         *d++ = *b;
    //     ++b;
    // }
    // return d;
}

/**
 * Applies a function f to a sequence of values bounded by the iterators [b, e), 
 * writting their outputs to another collection or location indicated by the iterator d, 
 * which points to the start of the destination to output. 
 * 
 * Operators used:
 * for b: ==, ++, *(dref.)
 * for d: ++, = (assgnment), *(dref. assignment only)
 * 
 * Iterator required: 
 * for b (and e): input iterator 
 * for d:         output iterator 
 **/
template<class In, class Out, class F_type>
Out transform(In b, In e, Out d, F_type f)
{
    // if b has reached the end, then immediately exit returning the output iterator d.
    if (b == e)
        return d;
    
    // write to the location pointed to by d the output of f applied to the value pointed to by b/
    // then increment both iterators. 
    *d++ = f(*b++)

    // continue the copying process, using the advanced iterators
    return transform(b, e, d, f);

    // while (b != e)
    // {
    //     *d++ = f(*b++)
    // }
    // return d;
    
}

/**
 * Starting with initial value t, sums the values of a sequence bounded by the iterators [b, e) and returns
 * the resulting value.
 * 
 * Operators used: ==, ++, *(dref.)
 * Iterator required: input iterator 
 **/
template<class In, class T>
T accumulate(In b, In e, T t) {

    // if b has reached the end, then immediately exit returning the output t.
    if (b == e)
        return t;
    
    // add to t the value pointed pointed by b, then increment b.
    t = t + *b++;

    // continue the sum by doing a recursive call using the advanced iterator b 
    // and the increased value of t.
    return accumulate(b, e, t);

    // Non-recursive implementation:
    // while (b != e) {
    //     t = t + *b++;
    // }
    // return t;
}

/**
 * Searches a sequence bounded by the range of iterators [b, e) 
 * for the first occurence of a sequence of values specified by the range of iterators [b2, e2),
 * returning the iterator to the first element. If none found, then e is returned.
 * 
 * Operators used:
 * for b : == (and !=), ++,  *(dref.),
 * for b2: ==, ++, *(dref.),
 * 
 * Another VERY important point in the algorithm:
 * - b_temp and b2_temp are both copies of the iterators b and b2 respectively. 
 * - They both go beyond the original iterator, and thus it may cause dereferenceing at the same location more than once.
 * - This is not possible for input iterators, but it is for forward iterators (of higher).
 * 
 * Iterator required:
 * for b (and e): Forward iterator 
 * for d:         Forward iterator
 * (treat them separetely, to allow differently typed collections to be searched against each other)
 *
 **/
template<class Fw1, class Fw2>
Fw1 search(Fw1 b, Fw1 e, Fw2 b2, Fw2 e2)
{
    // immediately exit if the iterator bounds of the target sequence are equal (i.e. nothing to search for)
    if (b2 != e2) {
        // continue searching if we have yet to reach the end.
        while (b != e)
        {
            // to remember where iterator b is, use a copy, temporarily advancing through the sequence with it.
            Fw1 b_temp = b;
            // b2 should not be moved, otherwise we forget the start position of the target sequence.
            // therefore use a copy of it instead.
            Fw2 b2_temp = b2;

            // continuously advance them if the values they point to match, which implies part of the target sequence
            // exists in the checked sequence.
            while(*b_temp++ == *b2_temp++) {
                // if we reach the end of the target sequence, then we have found to be in the first sequence.
                // thus return b, pointing to the start of where the sequence occurs.
                if (b2_temp == e2)
                    return b;
                // but if the first sequence reaches its end first, then the complete sequence is not found,
                // thus return the end iterator.
                if (b_temp == e)
                    return e;
            }
            // at this point, the target sequence staring from where b points to was not found.
            // so advance b one step further to point to the next point of the sequence.
            ++b;
        }
        // (output e in the ca)
        return e;
    }
    // b is outputted if it reaches the end iterator e
    // (but also in the case of an empty target sequence, due to vacuous truth)
    return b;
}

/**
 * Searches a sequence bounded by iterators [b, e) and returns the iterator pointing to the first value that
 * passess the predicate p. If not found, then e is returned.
 * 
 * Operators used: ==, ++, *(dref.)
 * Iterator required: Input iterator
 **/
template<class In, class F_type>
In find_if(In b, In e, F_type p)
{
    /**
     * Immediately exit returning iterator b if it has reached the end (unsuccessful search)
     * or if the value it currently points to passes the predicate (successful search)
     **/
    if(b == e || p(*b))
        return b;
    
    // otherwise continue the search - do recursive call with iterator b advanced.
    return find_if(++b, e, p);
}

/**
 * Traverses over a sequence of values bounded by iterators [b, e) and, without deleting the values from the original sequence,
 * disregards all the values equal to t, and writes the remaining values to another sequential collection or location indicated
 * by the iterator d, which points to the start of the destination to output.
 * 
 * Operators used:
 * for b: ==, ++, *(dref.)
 * for d: ++, = (assgnment), *(dref. assignment only)
 * Iterator required: 
 * for b (and e): input iterator 
 * for d:         output iterator
 **/
template<class In, class Out, class T>
Out remove_copy(In b, In e, Out d, T t)
{

    // if b has reached the end, then immediately exit returning the output iterator d.
    if (b == e)
        return d;
    
    // write values that do not match t to the destination pointed to by d, incrementing it to point
    // to the next location to be written to.
    if(*b != t)
        *d++ = *b;
    
    // continue traversing, using advancing iterator b to point to the next value to read.
    return remove_copy(++b, e, d, t);

}

/**
 * Traverses over a sequence of values bounded by iterators [b, e) and disregards all the values equal to t.
 * It writes the remaining values to the front of the sequence (overwritting the original values) and returns
 * an iterator poining to one past the last of these written values to keep.
 * 
 * Operators used: !=, ++, = (assignment), *(dref.)
 * (read + write)
 * Iterator required: Forward iterator
 **/
template<class Fw, class T>
Fw remove(Fw b, Fw e, T t)
{
    /**
     * Make a copy of the b iterator, using it as an input (read) iterator to traverse through the sequence,
     * while using b as an output (write) iterator to keep track of the front of the sequence where 
     * values will be overwritten.
     **/
    Fw b_in = b;

    // keep traversing until the end is reached
    while(b_in != e)
    {
        // write values that do not match t to the position pointed to by b,
        // ncrementing it to point to the next location to be written to.
        if(*b_in != t)
            *b++ = *b_in;
         // continue traversing by advancing the input-iterator.
        ++b_in;
    }
    // output b, which points to the end position of the sequence of written values. 
    // (i.e. one-past the last value written).
    return b;
}

/**
 * Rearranges a sequence bounded by iterators [b, e) into two halves using a predicate p.
 * The first half will consist of values that pass the predicate, 
 * while the second half which follows will consist of values that fail it.
 * 
 * It returns an iterator pointing to the end of the first half (i.e the beginning of the second half),
 * giving the dividing line in the partition.
 * 
 * Operators used: !=, ++
 * by iter_swap(): = (assignment), *(dref.)
 * (read + write)
 * 
 * Iterator required: Forward iterator
 **/
template<class Fw, class F_type>
Fw partition(Fw b, Fw e, F_type p)
{
    /**
     * Make a copy of the b iterator, using it as an output (write) iterator to keep track of the front of the
     * sequence where the first half of the partition will be written, traverse through the sequence,
     * while using b as an input (read) iterator to traverse through the entire sequence.
     **/
    Fw b_out = b;

    // keep traversing until the end is reached
    while(b != e) {
        if (p(b)) {
            /**
             * We want to exchange the values at the positions pointed to by the two iterators.
             * The normal way to do this would invlolve creating a temporary variable holding one of the values.
             * 
             * But we want to do it without explicitly knowing the types of the values.
             * Therefore we use the iter_swap() algorithm, which only needs to take the two iterators
             * to perform the exchange of their values.
             * 
             * (After the swap, advance b_out (output iterator) to point to the next position 
             *  for adding to the first half)
             **/
            std::iter_swap(b, b_out++);
        }
        // continue traversing by advancing b (input iterator).
        ++b;
    }
    // return the output-iterator, currently pointing to the end of the first half, indicating the dividing point. 
    return b_out;

    /**
     * =================================
     * Example of the partition process:
     * =================================
     * (r = read iterator, w = write iterator)
     * (P{n} = values passing predicate, F{n} = values failing predicate)
     * --------------------------------------------------------------------
     * START (point to beginning of the sequence)
     *   r
     * [|P1 P2 F1 P3 F2 F3 P4]      (1) Write P1 to first half
     *   w
     *     r
     * [P1|P2 F1 P3 F2 F3 P4]       (2) Write P2 to first half
     *     w
     *        r
     * [P1 P2|F1 P3 F2 F3 P4]       (3) Pass over F1
     *        w
     *           r
     * [P1 P2|F1 P3 F2 F3 P4]       (4) Write P3 to first half, swapping with F1
     *        w
     *              r
     * [P1 P2 P3|F1 F2 F3 P4]       (5) Pass over F2
     *           w
     *                 r
     * [P1 P2 P3|F1 F2 F3 P4]       (6) Pass over F3
     *           w
     *                    r
     * [P1 P2 P3|F1 F2 F3 P4]       (7) Write P4 to first half, swapping with F1
     *           w
     *                    r
     * [P1 P2 P3|P4 F2 F3 F1]       (End of sequence reached)
     *              w
     * STOP (Output w)
     **/
}

/**
 * ================================================================
 * General overview of what the functions do, in iterator notation:
 * ================================================================
 * 
 * accumulate():        t + sum(*[b, e))
 * 
 * copy():              *[b, e) -> *[d, ...)
 * 
 * equal():             *[b, e) == *[d, ...)
 * 
 * find():              i in [b, e) : *i == t
 * find_if():           i in [b, e) : p(*i) is true
 * 
 * partition():         c in [b, e) : p(*[b, e)) -> [b, c) (true) + (c, e) (false)
 * 
 * remove_copy():       (*[b, e) != t) -> *[d, ...)
 * remove_copy_if():    !p(*[b, e)) -> *[d, ...)
 * remove():            c in [b, e) : (*[b, e) != t) -> *[b, c) (overwrite) + (c, e) (garbage)
 * 
 * search():            i in [b, e): *[b2, e2) ==  *[i, ...)
 * 
 * transform():         f(*[b, e)) -> *[d, ...)
 **/