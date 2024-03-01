#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below

  std::vector<T> data;
  int m_ary;
  PComparator comp;


};

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) 
: data(), m_ary(m), comp(c) 
{  }

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  data.push_back(item);
  std::size_t index = data.size()-1;
   while (index != 0) {
        std::size_t parent_index = (index - 1) / m_ary;
        T& current = data[index];
        T& parent = data[parent_index];
        if (comp(parent, current)) {
            break;
        }
        std::swap(current, parent);
        index = parent_index;
    }
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
  if (size() < 1) {
    return true;
  }
  return false;
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return data.size();
}



// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap Empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap Empty");
  }
  if (size() == 1) {
    data.pop_back();
    return;
  }
  std::swap(data[0], data[size() - 1]);
  data.pop_back();

  size_t parent_index = 0;
  size_t maxIndex = size() - 1;

  while (m_ary * parent_index + 1 <= maxIndex) { //while current parent has at least one child
    size_t mostChildIndex = m_ary * parent_index + 1;
    
    for (int i = 2; i <= m_ary; i++) { //find most m_ary child
      if ((m_ary * parent_index + i) <= maxIndex) { //should check if in range
        if (comp(data[m_ary * parent_index + i], data[mostChildIndex])) {
          mostChildIndex = m_ary * parent_index + i;
        }
      } else {
        break;
      }
    }

    if (comp(data[mostChildIndex], data[parent_index])) { //swap is necessary
      std::swap(data[mostChildIndex], data[parent_index]);
      parent_index = mostChildIndex;
    } else {
      return;
    }
    
  }

  
  
}



#endif

