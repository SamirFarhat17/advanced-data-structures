#ifndef KMP_H_
#define KMP_H_

// Fills lps[] for given patttern pat[0..M-1]
void computePiArray(string pat, int M, int* pi) {
    //Finish this function
    int k = 0;
    int i = 1;
    pi[0] = 0;

    while(i < M) {
        if(pat[i] == pat[k]) {
            k++;
            pi[i] = k;
            i++;
        }
        else if(k == 0) {
                pi[i] = 0;
                i++;
            }
        else k = pi[k-1];
    }
}

// Prints occurrences of txt[] in pat[]
void KMPSearch(string pat, string txt) {
    int M = pat.length();
    int N = txt.length();
    int pi[M];
    // Preprocess the pattern (calculate lps[] array)
    computePiArray(pat, M, pi);

    int j = 0;
    int k = 0;

    while(j < N) {
        if(txt[j] == pat[k]) {
            j++;
            k++;
        }
        if(k == M) {
            std::cout << "Found pattern at index " << j - k << endl;
            k = pi[k-1];
        }
        else if(j < N && pat[k] != txt[j]) {
            if(k != 0) k = pi[k - 1];
            else j++;
        }
    }
}


#endif