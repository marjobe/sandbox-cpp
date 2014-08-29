#include <iostream>
#include <forward_list>
#include <cassert>

/** @brief Stack class with max and min methods.
 *  @details All methods are in O(1).
 *  @param T Type with order. The operator< must be defined.
 */
template<typename T>
class Stack
{
public:

    /**
     * @brief Constructor.
     */
    Stack() :
        _fwdList(),
        _min(nullptr),
        _max(nullptr)
    {}

    /**
     * @brief Indicates if the stack is empty.
     * @return True if the stack is empty.
     */
    inline bool isEmpty() const
    {
        return _fwdList.empty();
    }

    /**
     * @brief Pushes an element into the stack. Increases the number of elements by one.
     * @details Time: O(1).
     * @param[in] t Element to push.
     */
    void push(T t)
    {
        const bool wasEmpty(isEmpty());
        
        // Inserts the element and gets the iterator.
        _fwdList.emplace_front(t);
        const Iterator itNew(_fwdList.begin());

        if(wasEmpty)
        {
            // The only case that the max and min is the same element.
            _min = _max = itNew;
        }
        else
        {
            // If the new value is the new minimum (maximum), it has to track the previous
            // min (max), that is the min (max) value without it, and then actualizes the
            // new min or max.
            // NOTE THAT IF THE NEW VALUE IS THE MIN, IT WILL NOT BE THE MAX, AND VICEVERSA.
            // FOR THIS REASON, THERE IS ONLY ONE "next" COMPONENT IN "Elem".
            if(itNew->value < _min->value)
            {
                itNew->next = _min;
                _min = itNew;
            }
            else if(_max->value < itNew->value)
            {
                itNew->next = _max;
                _max = itNew;
            }
        }
        
    }

    /**
     * @brief Popes the last element pushed. Decreases the number of elements by one.
     * @details Time: O(1).
     * @param[out] t Element poped.
     */
    void pop(T& t)
    {
        assert(!isEmpty());

        // Gets the iterator of the first element.
        const Iterator front(_fwdList.begin());

        // If the element that it is going to be poped is the min(max), the new minimum (maximum)
        // is the min (max) without it, that is pointed by the "next" iterator.
        if(front == _min)
        {
            _min = front->next;
        }
        if(front == _max)
        {
            _max = front->next;
        }

        // Gets the value and pop the element.
        t = front->value;
        _fwdList.pop_front();
    }

    /**
     * @brief Gets the minimum value of the stack.
     * @details Time: O(1).
     * @param[out] t The minimum value.
     */
    inline void getMin(T& t) const
    {
        assert(!isEmpty());
        t = _min->value;
    }

    /**
     * @brief Gets the maximum value of the stack.
     * @details Time: O(1).
     * @param[out] t The maximum value.
     */
    inline void getMax(T& t) const
    {
        assert(!isEmpty());
        t = _max->value;
    }
    
private:

    /* Forward declaration */
    struct Elem;
    /* Typedefs */
    typedef std::forward_list<Elem> FwdList;
    typedef typename FwdList::iterator Iterator;
    /* Members */
    std::forward_list<Elem> _fwdList;
    Iterator                _min;
    Iterator                _max;

    /**
     * @brief Elem class that contains value and the next min or max iterator.
     * @details There is only one next because a element is candidate for the minimum or
     *          the maximum value, not both.
     */
    struct Elem
    {
        /**
         * @brief Constructor.
         */
        Elem(T t) :
            value(t),
            next(nullptr)
        {}

        /* Value */
        T           value;
        /** @brief This iterator points to the next (min or max) value, it is used when this
         *         element is poped.
         */
        Iterator    next;
    };

};

int main()
{
    Stack<int> stack;
/*
    stack.push(5);
    stack.push(7);
    stack.push(1);
    stack.push(0);
    stack.push(9);
    stack.push(2);
    stack.push(14);
*/

    stack.push(3);
    stack.push(2);
    stack.push(1);
    stack.push(5);
    stack.push(2);

    while(!stack.isEmpty())
    {
        int min, max, elem;
        stack.getMin(min);
        stack.getMax(max);
        std::cout << "min, max = " << min << ", " << max;
        stack.pop(elem);
        std::cout << " - Poped: " << elem << std::endl;
    }

    return 0;
}
