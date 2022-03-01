#ifndef KMP_H_
#define KMP_H_

// Fills lps[] for given patttern pat[0..M-1]
void computePiArray(string pat, int M, int* pi) {
    //Finish this function
}
// Prints occurrences of txt[] in pat[]
void KMPSearch(string pat, string txt) {
    int M = pat.length();
    int N = txt.length();

    int pi[M];

    // Preprocess the pattern (calculate lps[] array)
    computePiArray(pat, M, pi);

    // Finish the function...
}


#endif