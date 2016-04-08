

#include <iostream>
#include <iterator>
//using namespace std;

BASE64_INLINE
std::string
NVBase64::encode(const std::vector<unsigned char>& plainSeq)
{
    std::string retval;

    if(plainSeq.size() == 0) 
    {
        return retval;
    }
 
    // Reserve enough space for the returned base64 std::string
    unsigned long base64Bytes = (((plainSeq.size() * 4) / 3) + 1);
    unsigned long newlineBytes = (((base64Bytes * 2) / 76) + 1);
    unsigned long totalBytes = base64Bytes + newlineBytes;
 
    retval.reserve(totalBytes);

    unsigned char by1 = 0;
    unsigned char by2 = 0;
    unsigned char by3 = 0;
    unsigned char by4 = 0;
    unsigned char by5 = 0;
    unsigned char by6 = 0;
    unsigned char by7 = 0;

    for(unsigned long i = 0; i < plainSeq.size(); i += 3)
    {
        by1 = plainSeq[i];
        by2 = 0;
        by3 = 0;

        if((i + 1) < plainSeq.size())
        {
            by2 = plainSeq[i+1];
        }

        if((i + 2) < plainSeq.size())
        {
            by3 = plainSeq[i+2];
        }
 
        by4 = by1 >> 2;
        by5 = ((by1 & 0x3) << 4) | (by2 >> 4);
        by6 = ((by2 & 0xf) << 2) | (by3 >> 6);
        by7 = by3 & 0x3f;

        retval += encode(by4);
        retval += encode(by5);
 
        if((i + 1) < plainSeq.size())
        {
            retval += encode(by6);
        }
        else
        {
            retval += "=";
        }
 
        if((i + 2) < plainSeq.size())
        {
            retval += encode(by7);
        }
        else
        {
            retval += "=";
        }
    }

    std::string outString;
    outString.reserve(totalBytes);
    std::string::iterator iter = retval.begin();
	
	//-- do this for vc6 ,not in vc7,		add on 2005.11.18	scott
	std::vector<char> tmplist;    	
    while((retval.end() - iter) > 76)
    { 	
    	std::copy(iter, iter+76, std::back_inserter(tmplist));
        //std::copy(iter, iter+76, std::back_inserter(outString));
        outString.append(tmplist.begin(),tmplist.end());
        outString += "\r\n";
        iter += 76;
        tmplist.erase(tmplist.begin(),tmplist.end());
    }
    std::copy(iter, retval.end(), std::back_inserter(tmplist));
    outString.append(tmplist.begin(),tmplist.end());
    //std::copy(iter, retval.end(), std::back_inserter(outString));
    return outString;
}

BASE64_INLINE
std::vector<unsigned char>
NVBase64::decode(const std::string& str)
{
    std::string newStr;

    newStr.reserve(str.length());

    for(unsigned long j = 0; j < str.length(); j++)
    {
        if(isBase64(str[j]))
        {
            newStr += str[j];
        }
    }

    std::vector<unsigned char> retval;

    if(newStr.length() == 0)
    {
        return retval;
    }

    // Note: This is how we were previously computing the size of the return
    //       sequence.  The method below is more efficient (and correct).
    // unsigned long lines = str.size() / 78;
    // unsigned long totalBytes = (lines * 76) + (((str.size() - (lines * 78)) * 3) / 4);

    // Figure out how long the final sequence is going to be.
    unsigned long totalBytes = (newStr.size() * 3 / 4) + 1;

    retval.reserve(totalBytes);

    unsigned char by1 = 0;
    unsigned char by2 = 0;
    unsigned char by3 = 0;
    unsigned char by4 = 0;

    char c1, c2, c3, c4;

    for(unsigned long i = 0; i < newStr.length(); i += 4)
    {
        c1 = 'A';
        c2 = 'A';
        c3 = 'A';
        c4 = 'A';

        c1 = newStr[i];

        if((i + 1) < newStr.length())
        {
            c2 = newStr[i + 1];
        }

        if((i + 2) < newStr.length())
        {
            c3 = newStr[i + 2];
        }

        if((i + 3) < newStr.length())
        {
            c4 = newStr[i + 3];
        }

        by1 = decode(c1);
        by2 = decode(c2);
        by3 = decode(c3);
        by4 = decode(c4);

        retval.push_back((by1 << 2) | (by2 >> 4));

        if(c3 != '=')
        {
            retval.push_back(((by2 & 0xf) << 4) | (by3 >> 2));
        }

        if(c4 != '=')
        {
            retval.push_back(((by3 & 0x3) << 6) | by4);
        }
    }

    return retval;
}

BASE64_INLINE
char
NVBase64::encode(unsigned char uc)
{
    if(uc < 26)
    {
        return 'A' + uc;
    }
    
    if(uc < 52)
    {
        return 'a' + (uc - 26);
    }
    
    if(uc < 62)
    {
        return '0' + (uc - 52);
    }
    
    if(uc == 62)
    {
        return '+';
    }

    return '/';
}

BASE64_INLINE
unsigned char
NVBase64::decode(char c)
{
    if(c >= 'A' && c <= 'Z')
    {
        return c - 'A';
    }

    if(c >= 'a' && c <= 'z')
    {
        return c - 'a' + 26;
    }

    if(c >= '0' && c <= '9')
    {
        return c - '0' + 52;
    }

    if(c == '+')
    {
        return 62;
    }
 
    return 63;
}

BASE64_INLINE
bool
NVBase64::isBase64(char c)
{
    if(c >= 'A' && c <= 'Z')
    {
        return true;
    }

    if(c >= 'a' && c <= 'z')
    {
        return true;
    }

    if(c >= '0' && c <= '9')
    {
        return true;
    }

    if(c == '+')
    {
        return true;
    }

    if(c == '/')
    {
        return true;
    }

    if(c == '=')
    {
        return true;
    }

    return false;
}
