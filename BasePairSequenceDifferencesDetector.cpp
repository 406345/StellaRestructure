#include "BasePairSequenceDifferencesDetector.h"

BasePairSequenceDifferencesDetector::BasePairSequenceDifferencesDetector()
{
    int block_size = MAX_BP_LINE_LENGTH * MAX_BP_LINE_LENGTH;
    this->buf = (int*)malloc(block_size*sizeof(int) * 7);
    std::memset(buf, 0, block_size * sizeof(int) * 7);

    score = matrix<int>(this->buf);
    val   = matrix<int>(this->buf + block_size);
    idir  = matrix<int>(this->buf + block_size * 2);
    preV  = matrix<int>(this->buf + block_size * 3);
    preH  = matrix<int>(this->buf + block_size * 4);
    jpV   = matrix<int>(this->buf + block_size * 5);
    jpH   = matrix<int>(this->buf + block_size * 6);

    std::memset(seq1, 0, MAX_BP_LINE_LENGTH * sizeof(int));
    std::memset(seq2, 0, MAX_BP_LINE_LENGTH * sizeof(int));
    std::memset(j2i, 0, MAX_BP_LINE_LENGTH * sizeof(int));
}

BasePairSequenceDifferencesDetector::~BasePairSequenceDifferencesDetector()
{
    SAFE_DELETE(buf);
}

void BasePairSequenceDifferencesDetector::clear()
{
    std::memset(buf, 0, MAX_BP_LINE_LENGTH * MAX_BP_LINE_LENGTH * sizeof(int) * 7);
}

int BasePairSequenceDifferencesDetector::NeedlemanWunsch(string & f1, string & f2, string & sequenceA, string & sequenceB, string & sequenceM, int gap_open, int gap_extn)
{
    if (f1.size()>MAX_BP_LINE_LENGTH || f2.size()>MAX_BP_LINE_LENGTH) 
    {
        //cerr << "long reads > 500bp could not be supported in current version. Trim read to " << MAX_READ_LENGTH << "bp." << endl;
        f1 = f1.substr(0, MAX_BP_LINE_LENGTH);
        f2 = f2.substr(0, MAX_BP_LINE_LENGTH);
    }
    
    // Seq1 and seq2 are arrays that store the amino acid order numbers of sequence1 and sequence2.
    // For example, 1 stand for A, 2 represent C, 3:G, 4:T, 5:N.
    int i, j;
    
    // Translate characters into bitcode
    for (i = 1; i<f1.length(); i++) { seq1[i] = BitCodes[f1[i] - 'A'] + 1; }
    for (i = 1; i<f2.length(); i++) { seq2[i] = BitCodes[f2[i] - 'A'] + 1; }

    /* Score[i][j] stard for the alignment score that
    align ith position of the seq1 to the jth position of seq2
    */
    for (i = 1; i<f1.length(); i++) {
        for (j = 1; j<f2.length(); j++) {
            score(i, j) = imut[seq1[i]][seq2[j]];
        }
    }

    // Link position in seq1 to seq2 
    for (j = 1; j<f2.length(); j++) {
        j2i[j] = -1; // !all are not aligned
    }

    int D, V, H;

    ////////////////////////////////////////////////////////////////////////////////
    //    This is a standard Needleman-Wunsch dynamic program (by Y. Zhang 2005).
    //      1. Count multiple-gap.
    //      2. The gap penality W(k)=Go+Ge*k1+Go+Ge*k2 if gap open on both sequences
    //      idir[i][j]=1,2,3, from diagonal, horizontal, vertical
    //      val[i][j] is the cumulative score of (i,j)
    ////////////////////////////////////////////////////////////////////////////////

    val(0, 0) = 0;

    // Open end penalty of read 1
    val(1, 0) = gap_open;

    for (i = 2; i<f1.length(); i++) {
        val(i, 0) = val(i - 1, 0) + gap_extn;
    }

    for (i = 1; i<f1.length(); i++) {
        preV(i, 0) = val(i, 0); // not use preV at the beginning
        idir(i, 0) = 0;         // useless
        jpV(i, 0) = 1;          // useless
        jpH(i, 0) = i;          // useless
    }

    /* do not count the open end penalty of reference seq.
    val[0][1]=gap_open; // open end penalty of read 2
    for(j=2;j<f2.length();j++){
    val[0][j]=val[0][j-1]+gap_extn;
    }*/

    // Open end penalty of read 2
    val(0, 1) = 0; 

    for (j = 2; j<f2.length(); j++) 
    {
        val(0, j) = val(0, j - 1) + 0;
    }

    for (j = 1; j<f2.length(); j++) {
        preH(0, j) = val(0, j);
        idir(0, j) = 0;
        jpV(0, j) = j;
        jpH(0, j) = 1;
    }

    // DP ------------------------------>
    /* complexity: 100x100, CPU heavy! */
    int val1, val2;
    
    for (j = 1; j < f2.length(); j++) 
    {
        for (i = 1; i < f1.length(); i++) 
        {
            // D=VAL(i-1,j-1)+SCORE(i,j)--------------->
            D = val(i - 1, j - 1) + score(i, j);    // from diagonal, val(i,j) is val(i-1,j-1)

            //    H=H+gap_open ------->
            jpH(i, j) = 1;
            val1 = val(i - 1, j) + gap_open;  // gap_open from both D and V
            val2 = preH(i - 1, j) + gap_extn; // gap_extn from horizontal
                                              // last step from D or V
            if (val1 > val2) 
            {
                H = val1;
                // last step from H
            }
            else 
            {
                H = val2;

                if (i > 1) 
                {
                    jpH(i, j) = jpH(i - 1, j) + 1;  // record long-gap
                }
            }

            //    V=V+gap_open --------->
            jpV(i, j) = 1;
            val1 = val(i, j - 1) + gap_open;
            val2 = preV(i, j - 1) + gap_extn;
            
            if (val1 > val2) 
            {
                V = val1;
            }
            else 
            {
                V = val2;

                if (j > 1)
                {
                    jpV(i, j) = jpV(i, j - 1) + 1;  
                    // Record long-gap
                }
            }

            preH(i, j) = H; // Unaccepted H
            preV(i, j) = V;    // Unaccepted V

            if ( ( D > H ) && ( D > V ) ) 
            {
                idir( i, j ) = 1;
                val( i, j ) = D;
            }
            else if ( H > V ) 
            {
                idir( i, j ) = 2;
                val( i, j ) = H;
            }
            else 
            {
                idir(i, j) = 3;
                val(i, j) = V;
            }
        }
    }

    // Tracing back the pathway
    i = static_cast<int>(f1.size()) - 1;
    j = static_cast<int>(f2.size()) - 1;

    while ((i>0) && (j>0))
    {
        if (idir(i, j) == 1)       // From diagonal
        {
            j2i[j] = i;
            i = i - 1;
            j = j - 1;
        }
        else if (idir(i, j) == 2)  // From horizonal
        {
            int temp1 = jpH(i, j);                  

            for (int me = 1; me <= temp1; me++)             //  In the point view of a programer,
            {                                                //  you should not use the  "for(int me=1;me<=jpH[i][j];me++)".
                if (i>0)                                    //  If you use up sentence,the value of jpH[i][j] is changed when variable i changes.
                {                                            //  So the value of jpH[i][j] was assigned to the value temp1 and use the setence "for(int me=1;me<=temp1;me++)" here.
                    i = i - 1;                              //
                }                                            //
            }
        }
        else
        {
            int temp2 = jpV(i, j);

            for (int me = 1; me <= temp2; me++)             //  In the point view of a programer,
            {                                                //  you should not use the  "for(int me=1;me<=jpV[i][j];me++)".
                if (j>0)                                    //  Because when variable i change, the jpV[i][j] employed here is also change.
                {                                            
                    // So the value of jpV[i][j] was assigned to 
                    // the value temp2 and use the setence "for(int me=1;me<=temp2;me++)" here.
                    j = j - 1;                             
                }
            }
        }
    }

    // output aligned sequences
    size_t buf_size = f1.size() + f2.size();
    sequenceA.resize(buf_size, 0);
    sequenceB.resize(buf_size, 0);
    sequenceM.resize(buf_size, 0);
    
    int k = 0;
    i = 1;
    j = 1;
    
    while (true)
    {
        if ((i>(f1.length() - 1)) && (j>(f2.length() - 1)))
            break;

        if ((i>(f1.length() - 1)) && (j<(f2.length() - 1)))     // unaligned C on 1
        {
            
            if (k<buf_size) 
            {
                sequenceA[k] = '-';
                sequenceB[k] = seqW[seq2[j]];
                sequenceM[k] = ' ';
            } 

            k = k + 1;
            j = j + 1;
        }
        else if ((i<(f1.length() - 1)) && (j>(f2.length() - 1))) //Unaligned C on 2
        {
            
            if (k<buf_size) {
                sequenceA[k] = seqW[seq1[i]];
                sequenceB[k] = '-';
                sequenceM[k] = ' ';
            } 

            k = k + 1;
            i = i + 1;
        }
        else if (i == j2i[j]) // If align
        {

            if (k<buf_size) {
                sequenceA[k] = seqW[seq1[i]];
                sequenceB[k] = seqW[seq2[j]];
                if (seq1[i] == seq2[j])  // Identical
                {
                    sequenceM[k] = 'M';
                }
                else
                {
                    sequenceM[k] = 'X';
                }
            }

            k = k + 1;
            i = i + 1;
            j = j + 1;
        }
        else if (j2i[j]<0)   // Gap on 1
        {

            if (k<buf_size) 
            {
                sequenceA[k] = '-';
                sequenceB[k] = seqW[seq2[j]];
                sequenceM[k] = 'D';
            }

            k = k + 1;
            j = j + 1;
        }
        else if (j2i[j] >= 0)  // gap on 2
        {
            if (k<buf_size) 
            {
                sequenceA[k] = seqW[seq1[i]];
                sequenceB[k] = '-';
                sequenceM[k] = 'I';
            }

            k = k + 1;
            i = i + 1;
        }
    }
    
    // Force set the read end to avoid the mem leaking bugs
    sequenceM[f1.size() + f2.size() - 1] = 0;
    
    return 0;
}
