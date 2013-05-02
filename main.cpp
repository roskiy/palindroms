#include <sys/timeb.h>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

struct Range
    {
        int min, max;
    };
void invertBuffer(int buffer[10],int len)
{
    int a;
    for (int i=0;i<len/2;i++)
    {

        a=buffer[i];buffer[i]=buffer[len-i-1];buffer[len-i-1]=a;
    }
}

void intactify(int i, int buffer[10],int &len)
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

int unintactify(int buffer[10],int len)
{
    invertBuffer(buffer,len);
    int result=0;
    for (int i=0;i<len;i++)
    {
        result+=buffer[i]*(int)pow10(i);
    }
    return result;
}

int justnine (int buffer[], int n );

void generateNextPalindromeUtil (int buffer[], int n )
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
    int buffer[10],n=0;
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

int justnine( int* buffer, int n )
{
    for( int i = 0; i < n; ++i )
        if( buffer[i] != 9 )
            return 0;
    return 1;
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

int getMilliCount(){
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}

int getMilliSpan(int nTimeStart){
    int nSpan = getMilliCount() - nTimeStart;
    if(nSpan < 0)
        nSpan += 0x100000 * 1000;
    return nSpan;
}


int main()
{
    int a[100],b[100];
    int n,m,count=0,i=0;
    ifstream read("seed.txt");
    while(read>>n>>m){
        a[i]=n;b[i]=m;
        i++;
    }
int start = getMilliCount();

    for (int h=0;h<i;h++)    count+=countPalindromes((Range) {a[h],b[h]});

int milliSecondsElapsed = getMilliSpan(start);

cout<<"\r\n result:"<< count<<" in "<<milliSecondsElapsed<<" milli seconds \r\n";
    return 0;
}
