#include <iostream>

template < class T >
struct BiList {
  T val;
  BiList<T> *next;
  BiList<T> *prev;
};

template<class T>
BiList<T>* init()
{
  BiList<T>* fake = new BiList<T>{0, nullptr, nullptr};
  fake->next = fake;
  fake->prev = fake;
  return fake;
}

template<class T>
BiList<T>* addAfter(BiList<T>* h, const T& v)
{
  BiList<T>* res = new BiList<T>{v, h->next, h}; // T::T(const T&)
  h->next->prev = res;
  h->next = res;
  return res;
}

template<class T>
BiList<T>* addBefore(BiList<T>* h, const T& value)
{
  return addAfter(h->prev, value);    // T::T(const T&)
}

template<class T>
BiList<T>* erase(BiList<T>* h) noexcept
{
  if (h->next == h) {
    delete h;  // T::~T()
    return nullptr;
  }
  h->prev->next = h->next;
  h->next->prev = h->prev;
  BiList<T>* res = h->next;
  delete h;  // T::~T()
  return res;
}

template<class T>
void clear(BiList<T>* fake) noexcept
{
  BiList<T>* cur = fake->next;
  while (cur != fake)
  {
    cur = erase(cur);   // T::~T()
  }
}
