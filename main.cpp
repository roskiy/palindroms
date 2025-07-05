#include <sys/timeb.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

struct Range
    {
        int min, max;
    };
void invertBuffer(array<int,10>& buffer,int len)
{
    reverse(buffer.begin(), buffer.begin() + len);
}

void intactify(int i, array<int,10>& buffer,int &len)
{
    len=0;
    for (int n=0;n<10&&i>0;n++)
    {
        buffer[n]=i%10;
        i/=10;
        len++;
    }
    invertBuffer(buffer,len);
}

int unintactify(const array<int,10>& buffer,int len)
{
    int result=0;
    for (int i=0;i<len;i++)
    {
        result = result*10 + buffer[i];
    }
    return result;
}

bool justnine (const array<int,10>& buffer, int n );

void generateNextPalindromeUtil (array<int,10>& buffer, int n )
{
    int mid = n/2,i = mid - 1,j = (n % 2)? mid + 1 : mid;
    bool l2r = false;
    while (i >= 0 && buffer[i] == buffer[j])
        i--,j++;
        l2r = (i < 0 || buffer[i] < buffer[j]);
    while (i >= 0)
    {
        buffer[j] = buffer[i];
        j++;
        i--;
    }
    if (l2r)
    {
        int pass = 1;
        i = mid - 1;
        if (n%2 == 1)
        {
            buffer[mid] += pass;
            pass = buffer[mid] / 10;
            buffer[mid] %= 10;
            j = mid + 1;
        }
        else
            j = mid;
        while (i >= 0)
        {
            buffer[i] += pass;
            pass = buffer[i] / 10;
            buffer[i] %= 10;
            buffer[j++] = buffer[i--];
        }
    }
}

int generateNextPalindrome(int bufferber)
{
    array<int,10> buffer{};
    int n=0;
    if (bufferber<10) return bufferber+1;
    intactify(bufferber,buffer,n);
    if( justnine( buffer, n ) )
    {
        return bufferber+2;
    }

    else
    {
        generateNextPalindromeUtil ( buffer, n );
    }
    return unintactify(buffer,n);
}

bool justnine( const array<int,10>& buffer, int n )
{
    for( int i = 0; i < n; ++i )
        if( buffer[i] != 9 )
            return false;
    return true;
}


int countPalindromes(Range range)
{
    int count=0;
    for(int i=range.min;i<=range.max;i=generateNextPalindrome(i))
    {
        count++;
    }
    return count-1;
}


int main()
{
    vector<Range> ranges;
    int n, m, count = 0;
    ifstream read("seed.txt");
    while(read >> n >> m){
        ranges.push_back({n, m});
    }
    auto start = chrono::steady_clock::now();

    for (const auto& r : ranges)
        count += countPalindromes(r);

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count();

    cout << "\n result:" << count << " in " << elapsed << " milli seconds \n";
    return 0;
}
