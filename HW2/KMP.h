#ifndef KMP_H_
#define KMP_H_

// Fills lps[] for given patttern pat[0..M-1]
void computePiArray(string pat, int M, int* pi) {
    //Finish this function
    int len = 0;
    int i = 1;
    pi[0] = 0;

    while(i < M) {
        if(pat[i] == pat[len]) {
            len++;
            pi[i] = len;
            i++;
        }
        else {
            if(len != 0) len = pi[len-1];
            else if(len == 0) {
                pi[i] = 0;
                i++;
            }
        }
    }
}

// Prints occurrences of txt[] in pat[]
void KMPSearch(string pat, string txt) {
    int M = pat.length();
    int N = txt.length();
    int pi[M];
    // Preprocess the pattern (calculate lps[] array)
    computePiArray(pat, M, pi);

    int i = 0;
    int j = 0;

    while(i < N) {
        if(txt[i] == pat[j]) {
            i++;
            j++;
        }
        if(j == M) {
            std::cout << "Found pattern at index " << i - j << endl;
            j = pi[j-1];
        }
        else if(i < N && pat[j] != txt[i]) {
            if(j != 0) j = pi[j - 1];
            else i =i+1;
        }
    }
}


#endif