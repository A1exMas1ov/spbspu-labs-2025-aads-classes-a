#include <iostream>
#include <limits>

template< class T, class Cmp >
struct TriTree
{
  std::pair< T, T > data;
  TriTree< T, Cmp > * left, * middle, * right, * parent;
};

template< class T, class Cmp >
struct TriTreeIterator
{
  using this_t = TriTreeItretor< T, Cmp >;
  bool hasNext() const;
  bool hasPrev() const;

  this_t prev() const;
  this_t next() const;

  std::pair< T, T > & data();
 private:
  TriTree< T, Cmp > * current;
};

template< class T, class Cmp >
std::pair< T, T > & TriTreeIterator< T, Cmp >::data()
{
  return current->data;
}

template< class T, class Cmp >
bool TriTreeIterator< T, Cmp >::hasNext() const
{}

template< class T, class Cmp >
bool TriTreeIterator< T, Cmp >::hasPrev() const
{}

template< class T, class Cmp >
TriTreeIterator< T, Cmp >::this_t TriTreeIterator< T, Cmp >::next() const
{}

template< class T, class Cmp >
TriTreeIterator< T, Cmp >::this_t TriTreeIterator< T, Cmp >::prev() const
{}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > * root)
{}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root)
{}

template< class T, class Cmp >
void insertPair(TriTree< T, Cmp > * root, const std::pair< T, T > & pair, Cmp cmp)
{}

template< class T, class Cmp >
void clear(TriTree< T, Cmp > * root)
{}

template< class T, class Cmp >
size_t getIntersects(TriTree< T, Cmp > * root, int v1, int v2)
{
  size_t count = 0;
  for (auto it = begin(root); it.hasNext(); it = it.next())
  {
    auto pair = it.data();
    if (!(pair.first > v2 || pair.second < v1))
    {
      count++;
    }
  }
  return count;
}

template< class T, class Cmp >
size_t getCovers(TriTree< T, Cmp > * root, int v1, int v2)
{
  size_t count = 0;
  for (auto it = begin(root); it.hasNext(); it = it.next())
  {
    auto pair = it.data();
    if (v1 <= pair.first && pair.second <= v2)
    {
      count++;
    }
  }
  return count;
}

template< class T, class Cmp >
size_t getAvoids(TriTree< T, Cmp > * root, int v1, int v2)
{
  size_t count = 0;
  for (auto it = begin(root); it.hasNext(); it = it.next())
  {
    auto pair = it.data();
    if (pair.first > v2 || pair.second < v1)
    {
      count++;
    }
  }
  return count;
}

int main()
{
  size_t pairs = 0;
  if (!(std::cin >> pairs))
  {
    std::cerr << "ERROR: input\n";
    return 1;
  }
  int el1 = 0, el2 = 0;
  TriTree< int, std::less< int > > * root = nullptr;
  std::less< int > cmp;
  for (size_t i = 0; i < pairs; ++i)
  {
    if (!(std::cin >> el1 >> el2))
    {
      clear(root);
      std::cerr << "ERROR: input\n";
      return 1;
    }
    try
    {
      insertPair(root, {el1, el2}, cmp);
    }
    catch (const std::bad_alloc &)
    {
      clear(root);
      std::cerr << "ERROR: memory\n";
      return 1;
    }
  }

  std::string name;
  int v1 = 0, v2 = 0;
  while (!(std::cin >> name).eof())
  {
    std::cin >> v1 >> v2;
    if (!(std::cin) || (v1 > v2))
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
    try
    {
      if (name == "intersects")
      {
        std::cout << getIntersects(root, v1, v2) << "\n";
      }
      else if (name == "covers")
      {
        std::cout << getCovers(root, v1, v2) << "\n";
      }
      else if (name == "avoids")
      {
        std::cout << getAvoids(root, v1, v2) << "\n";
      }
      else
      {
        std::cerr << "<UNKNOWN COMMAND>\n";
        clear(root);
        return 1;
      }
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << "\n";
      clear(root);
      return 1;
    }
  }
  clear(root);
}
