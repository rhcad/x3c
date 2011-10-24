/*! \file AutoNew.h
 *  \brief Define helper classes to auto free memory: KAutoNew, KAutoNewArr, KAutoMalloc, KAutoNewArr2d
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.5.19
 */
#ifndef __AUTOFREE_NEW_H
#define __AUTOFREE_NEW_H

// KAutoNew:
// T* p = new T(); => KAutoNew<T> p (new T());
//
// KAutoNewArr:
// T* p = new T[5]; => KAutoNewArr<T> p (5);
//
// KAutoMalloc:
// T* p = (T*)malloc(5 * sizeof(T)); => KAutoMalloc<T> p (5);
//
// KAutoNewArr2d:
// T arr[100][200]; => KAutoNewArr2d<T> arr (100, 200);
//


//! Helper class to auto free memory (auto delete).
/*! Use this to convert from " T* p = new T; " to " KAutoNew<T> p (new T); ".
    \ingroup _GROUP_UTILFUNC
*/
template<typename T>
class KAutoNew
{
public:
    T*  ptr;

    KAutoNew() : ptr(NULL) {}
    KAutoNew(T* p) : ptr(p) {}
    ~KAutoNew() { delete ptr; }
    void Free() { if (ptr) { delete ptr; ptr = NULL; } }

    operator T* () { return ptr; }
    operator const T* () const { return ptr; }

    operator bool() const { return ptr != NULL; }
    bool operator!() const { return ptr == NULL; }

    T* operator->() const { return ptr; }

private:
    KAutoNew(const KAutoNew&);
    void operator=(const KAutoNew&);
};

//! Helper class to auto free memory (auto delete[]).
/*! Use this to convert from " T* p = new T[5]; " to " KAutoNewArr<T> p (5); ".
    \ingroup _GROUP_UTILFUNC
*/
template<typename T>
class KAutoNewArr
{
public:
    T*      ptr;
    size_t  count;

    KAutoNewArr() : ptr(NULL), count(0) {}
    KAutoNewArr(size_t _count) : ptr(new T[_count]), count(_count) {}
    ~KAutoNewArr() { delete[] ptr; }

    void Free()
    {
        if (ptr)
        {
            delete[] ptr;
            ptr = NULL;
        }
        count = 0;
    }

    bool Realloc(size_t _count)
    {
        T* newp = new T[_count];
        memcpy(newp, ptr, sizeof(T) * (count < _count ? count : _count));
        delete[] ptr;
        ptr = newp;
        count = _count;
        return true;
    }

    KAutoNewArr<T>& operator=(const KAutoNewArr<T>& src)
    {
        if (this != &src)
        {
            if (count == src.count || Realloc(src.count))
            {
                for (size_t i = 0; i < count; i++)
                {
                    ptr[i] = src.ptr[i];
                }
            }
        }
        return *this;
    }

    T& at(size_t index)
    {
        ASSERT(index >= 0 && index < count);
        return ptr[index];
    }

    T& operator[](size_t index)
    {
        ASSERT(index >= 0 && index < count);
        return ptr[index];
    }

    const T& operator[](size_t index) const
    {
        ASSERT(index >= 0 && index < count);
        return ptr[index];
    }

    operator bool() const { return ptr != NULL; }
    bool operator!() const { return ptr == NULL; }

private:
    KAutoNewArr(const KAutoNewArr&);
};

//! Helper class to auto free memory (malloc, realloc, free).
/*! Use this to convert from " T* p = (T*)malloc(5 * sizeof(T)); " to " KAutoMalloc<T> p (5); ".\n
    This class can be used to convert from static array to dynamic array, such as converting from
        " double a[10000] " to " KAutoMalloc< double> a(10000) ".
    \ingroup _GROUP_UTILFUNC
    \see KAutoNewArr2d
*/
template<typename T>
class KAutoMalloc
{
public:
    T*      ptr;
    size_t  count;

    KAutoMalloc() : ptr(NULL), count(0) {}
    ~KAutoMalloc() { if (ptr) free(ptr); }

    KAutoMalloc(size_t _count)
        : count(_count)
        , ptr((T*)malloc(sizeof(T)*_count))
    {
        memset(ptr, 0, sizeof(T)*_count);
    }

    void Free()
    {
        if (ptr)
        {
            free(ptr);
            ptr = NULL;
        }
        count = 0;
    }

    bool Realloc(size_t _count)
    {
        T* p = (T*)realloc(ptr, sizeof(T)*_count);
        if (p)
        {
            ptr = p;
            count = _count;
            memset(ptr, 0, sizeof(T)*_count);
        }
        return p != NULL;
    }

    KAutoMalloc<T>& operator=(const KAutoMalloc<T>& src)
    {
        if (this != &src)
        {
            if (count == src.count || Realloc(src.count))
            {
                memcpy(ptr, src.ptr, sizeof(T)*count);
            }
        }
        return *this;
    }

    T& at(size_t index)
    {
        ASSERT(index >= 0 && index < count);
        return ptr[index];
    }

    T& operator[](size_t index)
    {
        ASSERT(index >= 0 && index < count);
        return ptr[index];
    }

    const T& operator[](size_t index) const
    {
        ASSERT(index >= 0 && index < count);
        return ptr[index];
    }

    operator bool() const { return ptr != NULL; }
    bool operator!() const { return ptr == NULL; }

private:
    KAutoMalloc(const KAutoMalloc&);
};

//! Helper class to auto free 2d array (arr[m][n]).
/*! Use this to convert from " T arr[100][200]; " to " KAutoNewArr2d<T> arr (100, 200); ".\n
    This class can be used to convert from static array to dynamic array, such as converting from
        " double a[1000][1000] " to " KAutoNewArr2d< double> a(1000, 1000) ".
    \ingroup _GROUP_UTILFUNC
    \see KAutoMalloc
*/
template<typename T, typename T2 = KAutoMalloc<T> >
class KAutoNewArr2d : public KAutoNewArr<T2>
{
public:
    KAutoNewArr2d(size_t count1, size_t count2)
        : KAutoNewArr<T2>(count1)
    {
        for (size_t i = 0; i < count1; i++)
        {
            KAutoNewArr<T2>::at(i).Realloc(count2);
        }
    }

private:
    KAutoNewArr2d();
    KAutoNewArr2d(const KAutoNewArr2d&);
    void operator=(const KAutoNewArr2d&);
};

#endif // __AUTOFREE_NEW_H
