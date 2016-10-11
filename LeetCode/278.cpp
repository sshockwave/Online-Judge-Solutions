// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        long long l=0,r=n,mid;
        while(l<r){
        	mid=(l+r>>1)+1;
        	if(isBadVersion(mid)){
        		r=mid-1;
			}else{
				l=mid;
			}
		}
		return l+1;
    }
};
