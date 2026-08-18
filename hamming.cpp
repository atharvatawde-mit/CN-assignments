#include <iostream>
#include <cmath>

using namespace std;


int main() {
    int data[20], hamming[30];
    int m, r = 0;

    cout << "Enter number of data bits: ";
    cin >> m;

    cout << "Enter data bits:\n";
    for (int i = 1; i <= m; i++) {
        cin >> data[i];
    }

    // Find the number of redundant bits (r) needed
    while ((pow(2, r)) < (m + r + 1)) {
        r++;
    }

    int total = m + r;
    int j = 1;

    // Place data and parity bits (initialized to 0) in correct positions
    for (int i = 1; i <= total; i++) {
        // Check if i is a power of 2
        if ((i & (i - 1)) == 0) {
            hamming[i] = 0;
        } else {
            hamming[i] = data[j++];
        }
    }

    // Calculate parity bits
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;
        for (int j = 1; j <= total; j++) {
            if (j & pos) {
                parity ^= hamming[j];
            }
        }
        hamming[pos] = parity;
    }

    cout << "\nTransmitted Hamming Code:\n";
    for (int i = total; i >= 1; i--) {
        cout << hamming[i] << " ";
    }
    cout << "\n";

    int received[30];
    cout << "\nEnter the received Hamming code (position 1 to " << total << "):\n";
    for (int i = 1; i <= total; i++) {
        cin >> received[i];
    }

    // Error detection
    int error = 0;
    for (int i = 0; i < r; i++) {
        int pos = (int)pow(2, i);
        int parity = 0;
        for (int j = 1; j <= total; j++) {
            if (j & pos) {
                parity ^= received[j];
            }
        }
        if (parity) {
            error += pos;
        }
    }

    // Error handling and correction
    if (error == 0) {
        cout << "\nNo error detected.\n";
    } else {
        cout << "\nError detected at position " << error << ".\n";
        
        // Correct the error in the received array
        received[error] ^= 1;
        
        cout << "Corrected Hamming Code:\n";
        for (int i = total; i >= 1; i--) {
            cout << received[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
