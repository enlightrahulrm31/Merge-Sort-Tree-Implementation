#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int a[N];
// Implementation of merge sort tree using the given question
// Time complexity to build the merge sort tree is O(n*log(n))
// Question is to find the number of elements greater than val in range l to r 
class MergeSortTree{
    vector<int>seg[4*N]; // this is the segment which will store sorted integers in from l to r of a given index
    public:
    vector<int> MergeThem(vector<int>a,vector<int>b){  // here I will applying merge sort to sort two vectors 
        int n = a.size();
        int m = b.size();
        int i=0 , j=0;
        vector<int>ans;
        while(i<n && j<m){
            if(a[i]<=b[j]){
                ans.push_back(a[i]);
                i++;
            }
            else{
                ans.push_back(b[j]);
                j++;
            }
        }
        while(i<n){
            ans.push_back(a[i]);
            i++;
        }
        while(j<m){
            ans.push_back(b[j]);
            j++;
        }
        return ans;
    }
    void Build(int i,int l,int r){
        if(l == r){  
            seg[i].push_back(a[l]);
            return ;
        }
        int mid = (l+r)/2;
        Build(2*i,l,mid);
        Build(2*i+1,mid+1,r);
        seg[i] = MergeThem(seg[2*i],seg[2*i+1]); // After sorting I will place this in seg so that I can use this seg array in my query funtion
        return ;
    }
    int query(int i,int l,int r,int GivenL,int GivenR,int val){
        if(l>GivenR || r<GivenL){  // it means the (l,r) is not intersecting with our given ranges
            return 0;
        }
        if(l>=GivenL && r<=GivenR){ // it means it is totally coinciding wiht the give ranges 
            int lo = 0;
            int hi = seg[i].size();
            int ind = seg[i].size(); // initially assuming that no element in seg[i] is greater than val that is why keep the ind as seg[i].size()
            while(lo<hi){
                int mid = (lo+hi)/2;
                if(seg[i][mid]>val){
                    hi = mid;
                    ind = mid;
                }
                else{
                    lo = mid+1;
                }
            }
            return seg[i].size()-ind; // it will give me the number of elemets greater than val in vector seg[i]
        }
        int mid = (l+r)/2;
        int left = query(2*i,l,mid,GivenL,GivenR,val);
        int right = query(2*i+1,mid+1,r,GivenL,GivenR,val);
        return left+right;
    }
};
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    MergeSortTree mg; // making object of a class 
    mg.Build(1,0,n-1);     // building the Merge Sort Tree 
    int q;
    cin>>q;
    while(q--){
        int l,r,val;
        cin>>l>>r>>val;
        l--,r--; // as i am taking zero based indexing              
        cout<<mg.query(1,0,n-1,l,r,val)<<"\n";
    }

}