#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class correctSolution {
  public:
    double findMedianSortedArrays(
        const std::vector<int>& nums1,
        const std::vector<int>& nums2)
    {
        double median;
        if (nums1.size() == 0
            && nums2.size() == 0)
        {
            return 0.0;
        }
        else if (nums2.size() == 0)
        {
            return findMedianSorted(nums1);
        }
        else if (nums1.size() == 0)
        {
            return findMedianSorted(nums2);
        }
        else if (findMedianSorted(nums1) == findMedianSorted(nums2))
        {
            return findMedianSorted(nums1);
        }
        return findMedianSortedArraysNonEmpty2(nums1, nums2);
    }
    
    int debug{0};
  private:
    double findMedianSorted(const std::vector<int>& nums)
    {
        if (nums.size() != 0)
        {
            if ( nums.size() & 1)
            {
                return (double)nums[nums.size()>>1];
            }
            else
            {
                return ((double)(nums[nums.size()>>1] + nums[(nums.size()>>1)-1]))/2.0;
            }
        }
        return 0.0;
    }

    double findMedianSortedArraysNonEmpty2(
        const std::vector<int> &a1,
        const std::vector<int> &a2)
    {
        // The solution is to find the nth or nth and (n +1)th highest elements
        std::vector<int>::const_iterator it_a1 = a1.begin();
        std::vector<int>::const_iterator it_a2 = a2.begin();

        int m1 = 0;
        int m2 = 0;
        int n = (a1.size() + a2.size() + 1) / 2;
        if ((a1.size() + a2.size() & 1) == 0) ++n;
        int i = 0;
        while(it_a1 < a1.end() && it_a2 < a2.end() && i < n)
        {
            m2 = m1;
            if (*it_a1 < *it_a2)
            {
                m1 = *it_a1++;
            }
            else
            {
                m1 = *it_a2++;
            }
            i++;
        }
        while(it_a1 < a1.end() && i < n)
        {
            m2 = m1;
            m1 = *it_a1++;
            i++;
        }
        while(it_a2 < a2.end() && i < n)
        {
            m2 = m1;
            m1 = *it_a2++;
            i++;
        }
        if ((a1.size() + a2.size()) & 1)
        {
            return m1;
        }
        return static_cast<double>(m1 + m2)/2;
    }
};

#include <math.h>
class proposedSolution {
  public:
    double findMedianSortedArrays(
        const std::vector<int>& nums1,
        const std::vector<int>& nums2)
    {
        double median;
        if (nums1.size() == 0
            && nums2.size() == 0)
        {
            return 0.0;
        }
        else if (nums1.size() > 0 && nums2.size() == 0)
        {
            return findMedianSorted(nums1);
        }
        else if (nums2.size() > 0 && nums1.size() == 0)
        {
            return findMedianSorted(nums2);
        }
        double m1 = findMedianSorted(nums1);
        double m2 = findMedianSorted(nums2);
        if (m1 == m2) {
            return m1;
        }
        if (nums1[nums1.size() - 1] <= nums2[0])
        {
            // all a2 is larger
            return findMedianOrdered(nums1, nums2);
        }
        else if (nums2[nums2.size() - 1] <= nums1[0])
        {
            // all nums1 is larger than nums2
            return findMedianOrdered(nums2, nums1);
        }
        return findMedianSortedArraysNonEmpty3(nums1, nums2);
    }
    
    int debug{0};
  private:
    double findMedianOrdered(const std::vector<int> & low, const std::vector<int> & high)
    {
        int diff = low.size() - high.size();
        std::vector<int>::const_iterator it_m1;
        if (diff > 0)
        {
            it_m1 = low.begin() + (high.size() + low.size())/2;
        }
        else if (diff < 0)
        {
            it_m1 = high.begin() + (high.size() + low.size())/2 - low.size();
        }
        else {
            // equal length
            return (low[low.size() - 1] + high[0]) / 2.0;
        }
        int avg = ((low.size() + high.size()) & 1) == 0;
        if (avg) {
            return (*it_m1 + *(it_m1 -1)) / 2.0;
        }
        return (double)*it_m1;
    }

    double findMedianSorted(const std::vector<int>& nums)
    {
        if (nums.size() != 0)
        {
            if ( nums.size() & 1)
            {
                return (double)nums[nums.size()>>1];
            }
            else
            {
                return ((double)(nums[nums.size()>>1] + nums[(nums.size()>>1)-1]))/2.0;
            }
        }
        return 0.0;
    }
    
    double findMedianSortedArraysNonEmpty2(
        const std::vector<int> &a1,
        const std::vector<int> &a2)
    {
        // The solution is to find the nth or nth and (n +1)th highest elements
        std::vector<int>::const_iterator it_a1 = a1.begin();
        std::vector<int>::const_iterator it_a2 = a2.begin();

        int m1 = 0;
        int m2 = 0;
        int n = (a1.size() + a2.size() + 1) / 2;
        if ((a1.size() + a2.size() & 1) == 0) ++n;
        int i = 0;
        while(it_a1 < a1.end() && it_a2 < a2.end() && i < n)
        {
            m2 = m1;
            if (*it_a1 < *it_a2)
            {
                m1 = *it_a1++;
            }
            else
            {
                m1 = *it_a2++;
            }
            i++;
        }

        cerr << "steps: " << i << endl;

        while(it_a1 < a1.end() && i < n)
        {
            m2 = m1;
            m1 = *it_a1++;
            i++;
        }
        while(it_a2 < a2.end() && i < n)
        {
            m2 = m1;
            m1 = *it_a2++;
            i++;
        }
        if ((a1.size() + a2.size()) & 1)
        {
            return m1;
        }
        return static_cast<double>(m1 + m2)/2.0;
    }


    double findMedianSortedArraysNonEmpty4(
        const std::vector<int> &a1,
        const std::vector<int> &a2)
    {
        // The solution is to find the nth or nth and nth + 1 highest elements
        std::vector<int>::const_iterator it_a1 = a1.begin();
        std::vector<int>::const_iterator it_a2 = a2.begin();

        int m1 = 0;
        int m2 = 0;
        int n = (a1.size() + a2.size() + 1) / 2;
        if ((a1.size() + a2.size() & 1) == 0) ++n;
        int i = 0;
        int j = 0;
        int prev_i = 0;

        cerr << "in 4() a1.size(): " << a1.size() << " a2.size(): " << a2.size() << endl;
        
        double med_m1 = findMedianSorted(a1);
        double med_m2 = findMedianSorted(a2);

        int idx_m1_in_a2 = bs(a2, med_m1);
        int idx_m2_in_a1 = bs(a1, med_m2);
        cerr << "m1 @ in a2: " << idx_m1_in_a2 << " m2 @ in a1: " << idx_m2_in_a1 << endl;

        int a1_0_in_a2 = bs(a2, static_cast<double>(a1[0]));
        int a2_0_in_a1 = bs(a1, static_cast<double>(a2[0]));
        cerr << "a1[0] @ in a2: " << a1_0_in_a2 << " a2[0] @ in a1: " << a2_0_in_a1 << endl;
        int a1_n_in_a2 = bs(a2, static_cast<double>(*(a1.end() - 1)));
        int a2_n_in_a1 = bs(a1, static_cast<double>(*(a2.end() - 1)));
        cerr << "a1[n] @ in a2: " << a1_n_in_a2 << " a2[n] @ in a1: " << a2_n_in_a1 << endl;

        // One of the arrays (or both) has an index of zero,
        // the other is the location of the first element
        // in the other array.
        // Furthermore, if the first element of one vector is beyond the
        // mid-point of the combined vectors, then the median is in the
        // vector with the lower range numbers.
        int underhang = a1_0_in_a2;
        if (underhang == 0) {
            underhang = a2_0_in_a1;
        }
        int overhang = a2.size() - (a1_n_in_a2 + 1);
        if (overhang == 0) {
            overhang = a1.size() - (a2_n_in_a1 + 1);
        }
        double med_by_uh = 0.0;
        auto uhv = & a1;
        if (underhang >= (a1.size() + a2.size())/2) {
            // median is within low range vector
            if (a1_0_in_a2 == 0)
            {
                uhv = & a2;
            }
            if ((a1.size() + a2.size() & 1) == 1)
            {
                // odd
                int m_idx = (a1.size() + a2.size())/2;
                med_by_uh = static_cast<double>((*uhv)[m_idx]);
            }
            else
            {
                int m_idx = (a1.size() + a2.size())/2;
                med_by_uh = static_cast<double>((*uhv)[m_idx] + (*uhv)[m_idx - 1]) / 2.0;
            }
            return med_by_uh;
        }

        // FIX ME: overhang vs. underhang, small vector versus larger vector
        const std::vector<int> new_a2(a2.begin() + underhang, a2.end());
        const std::vector<int> new_a1(a1.begin(), a1.end() - underhang);

        cout << "[" << new_a1[0];
        for(auto x : std::vector<int>(new_a1.begin()+1, new_a1.end())) {
            cout << "," << x;
        }
        cout << "]" << endl;
        cout << "[" << new_a2[0];
        for(auto x : std::vector<int>(new_a2.begin()+1, new_a2.end())) {l
            cout << "," << x;
        }
        cout << "]" << endl;

        int new_a1_0_in_new_a2 = bs(new_a2, static_cast<double>(new_a1[0]));
        int new_a2_0_in_new_a1 = bs(new_a1, static_cast<double>(new_a2[0]));

        cerr << "in 4() new_a1.size(): " << new_a1.size() << " new_a2.size(): " << new_a2.size() << endl;
        
        cerr << "new_a1[0] @ in new_a2: " << new_a1_0_in_new_a2 << " new_a2[0] @ in new_a1: " << new_a2_0_in_new_a1 << endl;
        int new_a1_n_in_new_a2 = bs(new_a2, static_cast<double>(*(new_a1.end() - 1)));
        int new_a2_n_in_new_a1 = bs(new_a1, static_cast<double>(*(new_a2.end() - 1)));
        cerr << "new_a1[n] @ in new_a2: " << new_a1_n_in_new_a2 << " a2[n] @ in a1: " << new_a2_n_in_new_a1 << endl;

        double med_x = findMedianSortedArraysNonEmpty2(new_a2, new_a1);
        cout << "use 2 in 4 result: " << med_x << endl;
        double med_x3 = findMedianSortedArraysNonEmpty2(new_a2, new_a1);
        cout << "use 3 in 4 result: " << med_x3 << endl;
        return med_x;

#if 0
        while(it_a1 < a1.end() && it_a2 < a2.end() && i < n)
        {
            int idx_m1_in_a2 = bs(a2, med_m1);
            int idx_m2_in_a1 = bs(a1, med_m1);
            cerr << " " << *it_a1 << "@" << it_a1 - a1.begin() << " *it_a2@:  " << *it_a2 << "@" << it_a2 - a2.begin() << endl;
            j++;
        }

        cerr << "steps: " << j << endl;
        cerr << "i: " << i << " n: " << n << " prev_i: " << prev_i << endl;

        while(it_a1 < a1.end() && i < n)
        {
            m2 = m1;
            m1 = *it_a1++;
            i++;
        }
        while(it_a2 < a2.end() && i < n)
        {
            m2 = m1;
            m1 = *it_a2++;
            i++;
        }
        if ((a1.size() + a2.size()) & 1)
        {
            return m1;
        }
#endif
        return static_cast<double>(0);
    }

    void calcTrimAmount(
        const std::vector<int> &a1,
        const std::vector<int> &a2,
        int * trim_amount_p,
        bool * a1_is_lower_p
        )
    {
        int m1 = 0;
        int m2 = 0;
        int n = (a1.size() + a2.size() + 1) / 2;
        if ((a1.size() + a2.size() & 1) == 0) ++n;
        int i = 0;
        int j = 0;
        int prev_i = 0;

        cerr << "in calcTrimAmount() a1.size(): " << a1.size() << " a2.size(): " << a2.size() << endl;
        
        // one of a1_0_in_a2 or a2_0_in_a1 will be zero
        int a1_0_in_a2 = bs(a2, static_cast<double>(a1[0]));
        int a2_0_in_a1 = bs(a1, static_cast<double>(a2[0]));
        *a1_is_lower_p = a1_0_in_a2 == 0;

        cerr << "a1[0] @ in a2: " << a1_0_in_a2 << " a2[0] @ in a1: " << a2_0_in_a1 << endl;
        int a1_n_in_a2 = bs(a2, static_cast<double>(*(a1.end() - 1)));
        int a2_n_in_a1 = bs(a1, static_cast<double>(*(a2.end() - 1)));
        cerr << "a1[n] @ in a2: " << a1_n_in_a2 << " a2[n] @ in a1: " << a2_n_in_a1 << endl;

        int trim = min((unsigned long)m2_in_a1, a1.size()-m2_in_a1);
        const std::vector<int> new_l_vec(a1.begin() + trim / 2, a1.end() - trim / 2);
        trim = min((unsigned long)m1_in_a2, a2.size()-m1_in_a2);
        const std::vector<int> new_h_vec(a2.begin() + trim / 2, a2.end() - trim / 2);
        return trim;

#if 0 // skip overhand processing for now
        
        // One of the arrays (or both) has an index of zero,
        // the other is the location of the first element
        // in the other array.
        // Furthermore, if the first element of one vector is beyond the
        // mid-point of the combined vectors, then the median is in the
        // vector with the lower range numbers.
        int underhang = a1_0_in_a2;
        if (underhang == 0) {
            underhang = a2_0_in_a1;
        }
        int overhang = a2.size() - (a1_n_in_a2 + 1);
        if (overhang == 0) {
            overhang = a1.size() - (a2_n_in_a1 + 1);
        }
        double med_by_uh = 0.0;
        auto uhv = & a1;
        if (underhang >= (a1.size() + a2.size())/2) {
            // median is within low range vector
            if (a1_0_in_a2 == 0)
            {
                uhv = & a2;
            }
            if ((a1.size() + a2.size() & 1) == 1)
            {
                // odd
                int m_idx = (a1.size() + a2.size())/2;
                med_by_uh = static_cast<double>((*uhv)[m_idx]);
            }
            else
            {
                int m_idx = (a1.size() + a2.size())/2;
                med_by_uh = static_cast<double>((*uhv)[m_idx] + (*uhv)[m_idx - 1]) / 2.0;
            }
            return med_by_uh;
        }
#endif        
#if 0
        cout << "[" << new_a1[0];
        for(auto x : std::vector<int>(new_a1.begin()+1, new_a1.end())) {
            cout << "," << x;
        }
        cout << "]" << endl;
        cout << "[" << new_a2[0];
        for(auto x : std::vector<int>(new_a2.begin()+1, new_a2.end())) {
            cout << "," << x;
        }
        cout << "]" << endl;

        int new_a1_0_in_new_a2 = bs(new_a2, static_cast<double>(new_a1[0]));
        int new_a2_0_in_new_a1 = bs(new_a1, static_cast<double>(new_a2[0]));

        cerr << "in 4() new_a1.size(): " << new_a1.size() << " new_a2.size(): " << new_a2.size() << endl;
        
        cerr << "new_a1[0] @ in new_a2: " << new_a1_0_in_new_a2 << " new_a2[0] @ in new_a1: " << new_a2_0_in_new_a1 << endl;
        int new_a1_n_in_new_a2 = bs(new_a2, static_cast<double>(*(new_a1.end() - 1)));
        int new_a2_n_in_new_a1 = bs(new_a1, static_cast<double>(*(new_a2.end() - 1)));
        cerr << "new_a1[n] @ in new_a2: " << new_a1_n_in_new_a2 << " a2[n] @ in a1: " << new_a2_n_in_new_a1 << endl;

        double med_x = findMedianSortedArraysNonEmpty2(new_a2, new_a1);
        cout << "use 2 in 4 result: " << med_x << endl;
        return med_x;
#endif
    }

    double findMedianSortedArraysNonEmpty5(
        const std::vector<int> &a1,
        const std::vector<int> &a2
        )
    {
        std::vector<int> next_a1 = *n1;
        std::vector<int> next_a2 = *n2;
        double median = 0.0;
        do {
            if (new_a1.size() + new_a2_size() <= 10)
            {
                median = findMedianSortedArraysaNonEmpty5(next_a1, next_a2);
                break;
            }
            bool a1_is_lower = true;
            int trim_amount = 0;
            trim(new_a1, new_a2, &trim_amount, &a1_is_lower);
            if (trim_amount == 0) {
                // cannot trim
                median = findMedianSortedArraysNonEmpty5(next_a1, next_a2);
                break;
            }
            if (a1_is_lower)
            {
                next_a1 = std::vector(next_a1.begin() + trim_amount, next_a1.end());
                next_a2 = std::vector(next_a2.begin(), next_a2.end() - (trim_amount + 1));
            }
            else {
                next_a1 = std::vector(next_a1.begin(), next_a1.end() - (trim_amount + 1));
                next_a2 = std::vector(next_a2.begin() + trim_amount, next_a2.end());
            }
        } while(true);
        return median;
    }

    int bs(const vector<int> v, const double dVal)
    {
        int val = rint(floor(dVal));

#if 0
        int mid = v.size() / 2;
        if (mid == 0) {
            return 0;
        }
#endif
        if (v.size() == 0
            || dVal < v[0]) {
            return 0;
        }
        int h = v.size() - 1;
        int l = 0;
        int mid = h / 2;
        while(h - l > 1) {
            if (val < v[mid]) {
                h = mid;
            }
            else if (val > v[mid]) {
                l = mid;
            }
            else {
                break;
            }
            // cerr << h << " " << l << endl;
            mid = l + (h - l) / 2;
        }
        // return mid;
        return h;
    }

    double findMedianSortedArraysNonEmpty3(
        const std::vector<int> &a1,
        const std::vector<int> &a2)
    {
        cerr << "a1.size(): " << a1.size() << " a2.size(): " << a2.size() << endl;

        // skip optimizations for small cases.
        if (a1.size() + a2.size() < 10) {
            return findMedianSortedArraysNonEmpty2(a1, a2);
        }

        double m1 = findMedianSorted(a1);
        double m2 = findMedianSorted(a2);
        if (m2 == m1) {
            // if medians are equal then...
            return m1;
        }

        int m2_in_a1 =  bs(a1, m2);
        // cerr << "m1 in a2 " << m2_in_a1 << endl;
        int m1_in_a2 = bs(a2, m1);
        // cerr << "m2 in a1 " << m1_in_a2 << endl;

        // will it converge too slowly?
        if (m2_in_a1 < 5 || m1_in_a2 < 5) {
            // diminishing returns...
            cout << "[" << a1[0];
            for(auto x : std::vector<int>(a1.begin()+1,a1.end())) {
                cout << "," << x;
            }
            cout << "]" << endl;
            cout << "[" << a2[0];
            for(auto x : std::vector<int>(a2.begin()+1,a2.end())) {
                cout << "," << x;
            }
            cout << "]" << endl;
            
            double med1 = findMedianSortedArraysNonEmpty2(a1, a2);
            double med2 = findMedianSortedArraysNonEmpty4(a1, a2);
            cerr << "median via 4: " << med2 << endl;
            return med1;
        }

        int trim = min((unsigned long)m2_in_a1, a1.size()-m2_in_a1);
        const std::vector<int> new_l_vec(a1.begin() + trim / 2, a1.end() - trim / 2);
        trim = min((unsigned long)m1_in_a2, a2.size()-m1_in_a2);
        const std::vector<int> new_h_vec(a2.begin() + trim / 2, a2.end() - trim / 2);
        return findMedianSortedArraysNonEmpty3(new_l_vec, new_h_vec);
    }
};

std::vector<int>
readNumArray(ifstream & inFile) 
{
    std::vector<int> rv;
    char lBracket;
    inFile >> lBracket;
    if (lBracket != '[') {
        cerr << "input file error, left bracket" << endl;
        return rv;
    }
    int num;
    char comma = ',';
    while(comma == ',') {
        inFile >> num;
        rv.push_back(num);
        inFile >> comma;
    }
    if (comma != ']') {
        cerr << "input file error, right bracket" << endl;
        rv.clear();
    }
    return rv;
}

int
main(int argc, char **argv)
{
    if (argc < 2) {
        cerr << "supply input file" << endl;
        return 1;
    }

    ifstream inFile;
    inFile.open(argv[1], ios_base::in);

    // cout << "First array:" << endl;
    vector<int> firstArray;
    firstArray = readNumArray(inFile);
    for(int d : firstArray) {
        // cout << "num is " << d << endl;
    }
    
    // cout << "Second array:" << endl;
    vector<int> secondArray;
    secondArray = readNumArray(inFile);
    for(int d : secondArray) {
        // cout << "num is " << d << endl;
    }

    correctSolution csol;
    proposedSolution psol;
    double med = csol.findMedianSortedArrays(firstArray, secondArray);
    cout << "correct Median is " << med << endl;
    med = psol.findMedianSortedArrays(firstArray, secondArray);
    cout << "propsed Median is " << med << endl;
    return 0;
}
