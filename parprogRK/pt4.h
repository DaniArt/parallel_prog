#ifndef PT4H
#define PT4H
#include <windows.h>
#include <string>
#include <iterator>

void _DeleteNode(void* p);

struct TNode
{
  int Data;
  TNode* Next;
  TNode* Prev;
  TNode* Left;
  TNode* Right;
  TNode* Parent;
  static void operator delete(void* p)
  {
    _DeleteNode(p);
  }
};

typedef TNode* PNode;

void Task(const char* Name);
void DeleteNode(TNode* p);
DWORD Filter(struct _EXCEPTION_POINTERS *e);
class PTIO
{};

PTIO& operator << (PTIO& p, bool a);
PTIO& operator << (PTIO& p, int a);
PTIO& operator << (PTIO& p, long a);
PTIO& operator << (PTIO& p, double a);
PTIO& operator << (PTIO& p, char a);
PTIO& operator << (PTIO& p, const char* a);
PTIO& operator << (PTIO& p, std::string a);
PTIO& operator << (PTIO& p, TNode* a);
PTIO& operator >> (PTIO& p, bool& a);
PTIO& operator >> (PTIO& p, short& a);
PTIO& operator >> (PTIO& p, unsigned int& a);
PTIO& operator >> (PTIO& p, int& a);
PTIO& operator >> (PTIO& p, long& a);
PTIO& operator >> (PTIO& p, double& a);
PTIO& operator >> (PTIO& p, float& a);
PTIO& operator >> (PTIO& p, char& a);
PTIO& operator >> (PTIO& p, char* a);
PTIO& operator >> (PTIO& p, std::string& a);
PTIO& operator >> (PTIO& p, TNode*& a);

void PutB(bool a);
void PutN(int a);
void PutD(double a);
void PutC(char a);
void PutS(const char* a);
void PutS(std::string a);
void PutP(TNode* a);
void GetB(bool& a);
void GetN(int& a);
void GetN(unsigned int& a);
void GetD(double& a);
void GetC(char& a);
void GetS(char* a);
void GetS(std::string& a);
void GetP(TNode*& a);

extern PTIO pt;

void raisePT(const char*, const char*);

void Show(const char* s);
void Show(const char* s, int a, int w);
void Show(const char* s, double a, int w);
void Show(const char* s, int a);
void Show(const char* s, double a);
void Show(char c);
void Show(std::string s);
void Show(std::string s, int a, int w);
void Show(std::string s, double a, int w);
void Show(std::string s, int a);
void Show(std::string s, double a);
void Show(int a, int w);
void Show(double a, int w);
void Show(int a);
void Show(double a);
void ShowLine();
void ShowLine(const char* s);
void ShowLine(const char* s, int a, int w);
void ShowLine(const char* s, double a, int w);
void ShowLine(const char* s, int a);
void ShowLine(const char* s, double a);
void ShowLine(char c);
void ShowLine(std::string s);
void ShowLine(std::string s, int a, int w);
void ShowLine(std::string s, double a, int w);
void ShowLine(std::string s, int a);
void ShowLine(std::string s, double a);
void ShowLine(int a, int w);
void ShowLine(double a, int w);
void ShowLine(int a);
void ShowLine(double a);
void SetPrecision(int n);
void HideTask();

template<typename T>
class ptin_iterator : public std::iterator<std::input_iterator_tag, T>
{
private:
        unsigned int state_;
        bool end_;
        T   value_;

        void getNext()
        {
                if (end_ = state_ == 0)
                        return;
                --state_;
                pt >> value_;
        }

public:
        bool operator==(const ptin_iterator& it) const
        {
                return end_ && end_ == it.end_;
        }

        bool operator!=(const ptin_iterator& it) const
        {
                return ! (*this == it);
        }


        ptin_iterator(unsigned int count) : value_(T())
        {
                state_ = count;
                if (state_ == 0)
                        pt >> state_;
        if (state_ < 0)
                    state_ = 0;
        getNext();
        }

        ptin_iterator(): state_(0), value_(T()), end_(true)
        {
        }

        const T& operator*()
        {
            return value_;
        }

        const T* operator->() 
        {
        return &value_;
        }

        ptin_iterator& operator++()
        {
        getNext();
                return *this;
        }

        ptin_iterator operator++(int)
        {
                ptin_iterator<T> prev = *this;
        getNext();
                return prev;
        }

};

template<typename T>
class ptout_iterator : public std::iterator<std::output_iterator_tag, T>
{
public:

        ptout_iterator& operator*()
        {
        return *this;
        }

        ptout_iterator& operator=(const T& value) 
        {
                pt << value;
        return *this;
        }

        ptout_iterator& operator++()
        {
                return *this;
        }

        ptout_iterator& operator++(int)
        {
                return *this;
        }

};


template<typename T1, typename T2>
void Show(std::pair<T1, T2> a)
{
    Show("(");
    Show(a.first);
    Show(",");
    Show(a.second);
    Show(")");
}

template<typename T1, typename T2>
void ShowLine(std::pair<T1, T2> a)
{
    Show("(");
    Show(a.first);
    Show(",");
    Show(a.second);
    ShowLine(")");
}

template<typename T1, typename T2>
void Show(std::string s, std::pair<T1, T2> a)
{
    Show(s + "(");
    Show(a.first);
    Show(",");
    Show(a.second);
    Show(")");
}

template<typename T1, typename T2>
void ShowLine(std::string s, std::pair<T1, T2> a)
{
    Show(s + "(");
    Show(a.first);
    Show(",");
    Show(a.second);
    ShowLine(")");
}

void Show(std::string s, std::string a)
{
    Show(s + a);
}

void ShowLine(std::string s, std::string a)
{
    ShowLine(s + a);
}

void Show(std::string s, char a)
{
    Show(s + a);
}

void ShowLine(std::string s, char a)
{
    ShowLine(s + a);
}

template<typename InIter>
void Show(InIter first, InIter last, std::string s = "")
{
    if (first != last)
        Show(s, *first++);
    else if (s.length() != 0)
        Show(s);
    for (; first != last;)
        Show(*first++);
    ShowLine();
}

template<typename InIter>
void ShowLine(InIter first, InIter last, std::string s = "")
{
    if (first != last)
    {
        Show(s, *first++);
        ShowLine();
    }
    else if (s.length() != 0)
        ShowLine(s);
    for (; first != last;)
    {
        Show(*first++);
        ShowLine();
    }
}

#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>

template<typename T>
void Show(std::string s, std::vector<T> cont)
{
    typename std::vector<T>::iterator p = cont.begin();
    if (p != cont.end())
    {
        Show(s, *p++);
        for (; p != cont.end(); ++p)
            Show(*p);
    }
    else if (s.length() != 0)
        Show(s);
}

template<typename T>
void Show(std::vector<T> cont)
{
    for (typename std::vector<T>::iterator p = cont.begin(); p != cont.end(); ++p)
        Show(*p);
}

template<typename T>
void Show(std::string s, std::deque<T> cont)
{
    typename std::deque<T>::iterator p = cont.begin();
    if (p != cont.end())
    {
        Show(s, *p++);
        for (; p != cont.end(); ++p)
            Show(*p);
    }
    else if (s.length() != 0)
        Show(s);
}

template<typename T>
void Show(std::deque<T> cont)
{
    for (typename std::deque<T>::iterator p = cont.begin(); p != cont.end(); ++p)
        Show(*p);
}

template<typename T>
void Show(std::string s, std::list<T> cont)
{
    typename std::list<T>::iterator p = cont.begin();
    if (p != cont.end())
    {
        Show(s, *p++);
        for (; p != cont.end(); ++p)
            Show(*p);
    }
    else if (s.length() != 0)
        Show(s);
}

template<typename T>
void Show(std::list<T> cont)
{
    for (typename std::list<T>::iterator p = cont.begin(); p != cont.end(); ++p)
        Show(*p);
}

template<typename T>
void Show(std::string s, std::set<T> cont)
{
    typename std::set<T>::iterator p = cont.begin();
    if (p != cont.end())
    {
        Show(s, *p++);
        for (; p != cont.end(); ++p)
            Show(*p);
    }
    else if (s.length() != 0)
        Show(s);
}

template<typename T>
void Show(std::set<T> cont)
{
    for (typename std::set<T>::iterator p = cont.begin(); p != cont.end(); ++p)
        Show(*p);
}

template<typename T>
void Show(std::string s, std::multiset<T> cont)
{
    typename std::multiset<T>::iterator p = cont.begin();
    if (p != cont.end())
    {
        Show(s, *p++);
        for (; p != cont.end(); ++p)
            Show(*p);
    }
    else if (s.length() != 0)
        Show(s);
}

template<typename T>
void Show(std::multiset<T> cont)
{
    for (typename std::multiset<T>::iterator p = cont.begin(); p != cont.end(); ++p)
        Show(*p);
}

template<typename T1, typename T2>
void Show(std::string s, std::map<T1, T2> cont)
{
    typename std::map<T1, T2>::iterator p = cont.begin();
    if (p != cont.end())
    {
        Show(s, *p++);
        for (; p != cont.end(); ++p)
            Show(*p);
    }
    else if (s.length() != 0)
        Show(s);
}

template<typename T1, typename T2>
void Show(std::map<T1, T2> cont)
{
    for (typename std::map<T1, T2>::iterator p = cont.begin(); p != cont.end(); ++p)
        Show(*p);
}

template<typename T1, typename T2>
void Show(std::string s, std::multimap<T1, T2> cont)
{
    typename std::multimap<T1, T2>::iterator p = cont.begin();
    if (p != cont.end())
    {
        Show(s, *p++);
        for (; p != cont.end(); ++p)
            Show(*p);
    }
    else if (s.length() != 0)
        Show(s);
}

template<typename T1, typename T2>
void Show(std::multimap<T1, T2> cont)
{
    for (typename std::multimap<T1, T2>::iterator p = cont.begin(); p != cont.end(); ++p)
        Show(*p);
}

void Solve();

#pragma warning (disable:4430)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    _try
    {
         Solve();
    }
    _except(Filter(GetExceptionInformation()))
    {}
    return 0;
}
#pragma warning (default:4430)

#define MPICH_SKIP_MPICXX 1

char* GetExename();

#endif
