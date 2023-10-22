/**
 * Author: Lee Zongyu
 * Description: suffix array
 */

typedef vector<ll> vl;

class SuffixArray{
    private:
        ll max_range = 2e5+2; // TODO the maximum value (Ensure it won,t exceed the requirement)
        ll n;
        
        void countingSort(int k){      
            vl freq(max_range);   
            for (int i = 0; i < n; ++i)                     // count the frequency
                freq[ i + k < n ? rk[i+k] : 0]++;           // of each integer rank
            for (int i = 0, sum = 0; i < max_range; ++i) {
                int t = freq[i]; 
                freq[i] = sum;
                sum += t;
            }
            vl tempsa(n);
            for (int i = 0; i < n; ++i)                      // sort SA
            tempsa[ freq[ sa[i]+k < n ? rk[sa[i]+k] : 0] ++ ] = sa[i];
            swap(sa, tempsa);                                   
        }

        void constructLCP(){
            vl phi(n);
            vl plcp(n);
            phi[sa[0]] = -1;
            for(int i = 1; i < n; i++)
                phi[sa[i]] = sa[i-1];
            
            for(int i = 0, l = 0; i < n; i ++ ){
                if(phi[i] == -1){
                    plcp[i] = 0;
                    continue;
                }
                while((i+l < n ) && (phi[i] + l < n) && s[i+l] == s[phi[i] + l] ) l++;
                plcp[i] = l;
                l = max(l-1,0);
            }
            lcp.resize(n);
            for(int i = 0; i < n; i++)
                lcp[i] = plcp[sa[i]];
        }

        void constructSA() {                           
            // init
            rk.assign(n,0);
            sa.assign(n,0);
            iota(sa.begin(), sa.end(), 0);               
            for (int i = 0; i < n; ++i) rk[i] = s[i];    

            // repeat log_2 n times
            for (int k = 1; k < n; k <<= 1) {          
                countingSort(k);                           // radix sort
                countingSort(0);                           // stable-sort
                vl temprk(n);
                int r = 0;
                temprk[sa[0]] = r;                         // re-ranking process
                for (int i = 1; i < n; ++i)                // compare adj suffixes, same pair => same rank r; otherwise, increase r
                    temprk[sa[i]] = 
                    ((rk[sa[i]] == rk[sa[i-1]]) && (rk[sa[i]+k] == rk[sa[i-1]+k])) ?
                        r : ++r;
                swap(rk, temprk);                          // update RA

                // constant optimization
                max_range = r + 1;
                if (rk[sa[n-1]] == n-1) break;             
            }
        }
    // vl for s,a,q are changable to string
    public:
        vl rk, sa, lcp, owner; // 0 - index lcp in sa form between me and previous
        vector<ll> s; 
        void discrete(vector<ll> a){
            set<ll> st;
            for(int c:a) st.insert(c);
            ll idx = 0;
            unordered_map<ll,ll> mp;
            for(int c:st) mp[c] = idx++;
            s.assign(a.size(),0);
            for(int i = 0; i < n; i++) s[i] = mp[a[i]];
        }
        SuffixArray(vector<ll> a){
            n = a.size();
            discrete(a); // Comment if discretization is unnecesary;
            constructSA();
            constructLCP();
        }

        int lower_bound(vl q){
            int l = 1, r = n;
            while(l<r){
                int m = (l+r)/2;
                if(compare(sa[m],q)>=0) r = m;
                else l = m + 1;
            }
            return (l!=n)? sa[l]: -1;
        }

        int upper_bound(vl q){
            int l = 1, r= n;
            while(l < r){
                int m = (l + r)/2;
                if(compare(sa[m], q) > 0) r = m;
                else l = m + 1;
            }
            return (l!=n)? sa[l] : -1;
        }

        int compare(int idx, vl q){
            for(int i = 0; i < q.size(); i++){ 
                if(s[idx+i] < q[i]) return -1;
                else if(s[idx+i] > q[i]) return 1;
            }
            return 0;
        }

};
