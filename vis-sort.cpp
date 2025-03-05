#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cmath>

using namespace std;

#define CLEAR_SCREEN "\033[2J\033[H"

struct complexitate {
    long long comparatii;
    long long swaps;
    clock_t startT;
    double execT;
};


void QuickSort(int v[], int st, int dr, complexitate& comp) {
    if (st < dr) {
        int pivot = v[dr];
        int i = st - 1;
        for (int j = st; j < dr; j++) {
            comp.comparatii++;
            if (v[j] < pivot) {
                i++;
                swap(v[i], v[j]);
                comp.swaps++;
            }
        }
        swap(v[i + 1], v[dr]);
        comp.swaps++;
        int p = i + 1;
        QuickSort(v, st, p - 1, comp);
        QuickSort(v, p + 1, dr, comp);
    }
}

const int MAX_SIZE = 1000;
int tmp[MAX_SIZE];

void MergeSort(int v[], int st, int dr, complexitate& comp) {
    if (st < dr) {
        int m = (st + dr) / 2;
        MergeSort(v, st, m, comp);
        MergeSort(v, m + 1, dr, comp);
        
        int i = st, j = m + 1, k = 0;
        while (i <= m && j <= dr) {
            comp.comparatii++;
            tmp[k++] = (v[i] < v[j]) ? v[i++] : v[j++];
        }
        while (i <= m)
            tmp[k++] = v[i++];
        while (j <= dr)
            tmp[k++] = v[j++];
        
        for (i = st, k = 0; i <= dr; i++, k++) {
            v[i] = tmp[k];
            comp.swaps++;
        }
    }
}

void meniu() {
    
 
cout << "        _                           _   \n"
"       (_)                         | |  \n"
" __   ___ ___ ______ ___  ___  _ __| |_ \n"
" \\ \\ / / / __|______/ __|/ _ \\| '__| __|\n"
"  \\ V /| \\__ \\      \\__ \\ (_) | |  | |_ \n"
"   \\_/ |_|___/      |___/\\___/|_|   \\__|\n"
"                                        \n"
"                                        \n"
<< endl;


    cout << "Lista actiuni: " << endl;
    cout << "S: Scrie o lista unidimensionala direct in terminal care sa fie sortata." << endl;
    cout << "F: Sorteaza o lista dintr-un fisier." << endl;
    cout << "Q: Iesire din program." << endl << endl;
    cout << "Alegere: ";
}

void displaycomplexitate(const complexitate& comp, const string& algoritm, int n) {
    cout << "\nAnaliza " << algoritm << ":" << endl;
    cout << "Complexitate teoretica: O("<<n<<" log "<<n<<")" << endl;
    cout << "Numar comparatii: " << comp.comparatii << endl;
    cout << "Numar swapuri: " << comp.swaps << endl;
    cout << "Timp de executie: " << comp.execT << " ms" << endl;
}

void salvare(int v[], int n) {
    char choice;
    cout << "\nSalvare lista sortata intr-un fisier? (y/n): ";
    cin >> choice;
    if (tolower(choice) == 'y') {
        string outputf;
        cout << "Introduceti numele fisierului (va fi salvat in folderul curent) ";
        cin >> outputf;
        ofstream fout(outputf);
        for (int i = 0; i < n; i++)
            fout << v[i] << " ";
        fout.close();
        cout << "salvat in: " << outputf << endl;
    }
}

void prompt_sortare(int v[], int n, char choice, complexitate& comp) {
    // comp = {0, 0, clock(), 0}; (nu merge pe macos)
    
    comp.comparatii = 0;
    comp.swaps = 0;
    comp.startT = clock();
    comp.execT = 0;

    if (tolower(choice) == 'q') {
        QuickSort(v, 0, n - 1, comp);
    } else if (tolower(choice) == 'm') {
        MergeSort(v, 0, n - 1, comp);
    }
    comp.execT = ((double)(clock() - comp.startT) / CLOCKS_PER_SEC) * 1000; // me when bash feature
}

void vizualizare(int v[], int n, const string& algoritm, bool bool_comparatii = false) {
    const int inaltimemax = 20; 
    int val_max = 0;
    
    for (int i = 0; i < n; i++) {
        if (v[i] > val_max) val_max = v[i];
    }
    
    if (!bool_comparatii) {
        cout << "\nVizualizare a sortarii (" << algoritm << "):\n";
    }
    
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++) temp[i] = v[i];
    
    int contor_it = 0;
    bool is_sortat = false;

    if (algoritm == "QuickSort") {
        struct stagiu_quick {
            int st, dr, pivot_pislaru;
            bool partitionat;
        };
        stagiu_quick stiva_osi[MAX_SIZE];
        int top = -1;
        top++;
        stiva_osi[top].st = 0;
        stiva_osi[top].dr = n - 1;
        stiva_osi[top].pivot_pislaru = -1;
        stiva_osi[top].partitionat = false;

        while (top >= 0 && !is_sortat) {
            stagiu_quick& curent = stiva_osi[top];
            int st = curent.st, dr = curent.dr;

            if (!curent.partitionat && st < dr) {
                if (!bool_comparatii && contor_it > 0) cout << CLEAR_SCREEN;
                if (!bool_comparatii) cout << "Pas " << contor_it + 1 << ":\n";

                int pivot = temp[dr];
                int i = st - 1;
                for (int j = st; j < dr; j++) {
                    if (temp[j] < pivot) {
                        i++;
                        swap(temp[i], temp[j]);
                    }
                }
                swap(temp[i + 1], temp[dr]);
                curent.pivot_pislaru = i + 1;
                curent.partitionat = true;

                for (int inaltime = inaltimemax; inaltime >= 1; inaltime--) {
                    for (int i = 0; i < n; i++) {
                        int scalat = (temp[i] * inaltimemax) / (val_max ? val_max : 1);
                        if (scalat >= inaltime) {
                            if (i == curent.pivot_pislaru) cout << "P";
                            else if (i >= st && i <= dr) cout << "|";
                            else cout << "S";
                        } else {
                            cout << " ";
                        }
                    }
                    cout << endl;
                }
                for (int i = 0; i < n; i++) cout << "_";
                cout << endl;
                for (int i = 0; i < n; i++) cout << (temp[i] % 10);
                cout << endl << endl;

                if (!bool_comparatii) {
                    cout << "algoritm: QuickSort, interval: [" << st << ", " << dr << "]\n";
                    clock_t start = clock();
                    while ((clock() - start) < (0.3 * CLOCKS_PER_SEC));
                }
                contor_it++; // incrementare dupa partitionare ca sa nu isi dea ecranul clear
            } else {
                int p = curent.pivot_pislaru;
                top--;
                if (p - 1 > st) {
                    top++;
                    stiva_osi[top].st = st;
                    stiva_osi[top].dr = p - 1;
                    stiva_osi[top].pivot_pislaru = -1;
                    stiva_osi[top].partitionat = false;
                }
                if (p + 1 < dr) {
                    top++;
                    stiva_osi[top].st = p + 1;
                    stiva_osi[top].dr = dr;
                    stiva_osi[top].pivot_pislaru = -1;
                    stiva_osi[top].partitionat = false;
                }
            }

            is_sortat = true;
            for (int i = 1; i < n; i++) {
                if (temp[i-1] > temp[i]) {
                    is_sortat = false;
                    break;
                }
            }
        }
    } else if (algoritm == "MergeSort") {
        struct stagiu_merge {
            int st, dr, m;
            bool merged;
        };
        stagiu_merge stiva_osi[MAX_SIZE];
        int top = -1;
        top++;
        stiva_osi[top].st = 0;
        stiva_osi[top].dr = n - 1;
        stiva_osi[top].m = -1;
        stiva_osi[top].merged = false;

        while (top >= 0 && !is_sortat) {
            if (contor_it > 0 && !bool_comparatii) cout << CLEAR_SCREEN;
            if (!bool_comparatii) cout << "Pas " << contor_it + 1 << ":\n";

            stagiu_merge& curent = stiva_osi[top];
            int st = curent.st, dr = curent.dr;

            if (!curent.merged && st < dr) {
                curent.m = (st + dr) / 2;
                if (curent.m > st) {
                    top++;
                    stiva_osi[top].st = st;
                    stiva_osi[top].dr = curent.m;
                    stiva_osi[top].m = -1;
                    stiva_osi[top].merged = false;
                }
                if (curent.m + 1 < dr) {
                    top++;
                    stiva_osi[top].st = curent.m + 1;
                    stiva_osi[top].dr = dr;
                    stiva_osi[top].m = -1;
                    stiva_osi[top].merged = false;
                }
                curent.merged = true;
            } else {
                top--;
                int m = curent.m;
                int i = st, j = m + 1, k = 0;
                int tmp_local[MAX_SIZE];
                while (i <= m && j <= dr) {
                    tmp_local[k++] = (temp[i] < temp[j]) ? temp[i++] : temp[j++];
                }
                while (i <= m) tmp_local[k++] = temp[i++];
                while (j <= dr) tmp_local[k++] = temp[j++];
                for (i = st, k = 0; i <= dr; i++) temp[i] = tmp_local[k++];
            }

            for (int inaltime = inaltimemax; inaltime >= 1; inaltime--) {
                for (int i = 0; i < n; i++) {
                    int scalat = (temp[i] * inaltimemax) / (val_max ? val_max : 1);
                    if (scalat >= inaltime) {
                        if (i >= st && i <= dr) cout << "M";
                        else cout << "S";
                    } else {
                        cout << " ";
                    }
                }
                cout << endl;
            }
            for (int i = 0; i < n; i++) cout << "_";
            cout << endl;
            for (int i = 0; i < n; i++) cout << (temp[i] % 10);
            cout << endl << endl;

            is_sortat = true;
            for (int i = 1; i < n; i++) {
                if (temp[i-1] > temp[i]) {
                    is_sortat = false;
                    break;
                }
            }
            contor_it++;
            if (!bool_comparatii) {
                cout << "algoritm: MergeSort, interval: [" << st << ", " << dr << "]\n";
                clock_t start = clock();
                while ((clock() - start) < (0.3 * CLOCKS_PER_SEC));
            }
        }
    }

    if (!bool_comparatii) {
        cout << "Sortare finalizata in " << contor_it << " iteratii. Enter pentru intoarcere la meniu.";
        cin.get();
    }
}

void comparatie(int v[], int n) {
    int v1[MAX_SIZE], v2[MAX_SIZE];
    for (int i = 0; i < n; i++) {
        v1[i] = v[i];
        v2[i] = v[i];
    }
    
    complexitate compQ, compM;
    prompt_sortare(v1, n, 'q', compQ);
    prompt_sortare(v2, n, 'm', compM);
    
    cout << "\nLista sortata: ";
    for (int i = 0; i < n; i++) cout << v1[i] << " ";
    cout << endl;
    
    displaycomplexitate(compQ, "QuickSort", n);
    displaycomplexitate(compM, "MergeSort", n);
    
    if (compQ.comparatii < compM.comparatii)
        cout << "Comparatii: QuickSort este mai eficient cu " << (compM.comparatii - compQ.comparatii) << endl;
    else if (compM.comparatii < compQ.comparatii)
        cout << "Comparatii: MergeSort este mai eficient cu " << (compQ.comparatii - compM.comparatii) << endl;
    else
        cout << "Comparatii: Amandoi algoritmii sunt la fel de eficienti." << endl;

    if (compQ.swaps < compM.swaps)
        cout << "Swapuri: QuickSort este mai eficient cu " << (compM.swaps - compQ.swaps) << endl;
    else if (compM.swaps < compQ.swaps)
        cout << "Swapuri: MergeSort este mai eficient cu " << (compQ.swaps - compM.swaps) << endl;
    else
        cout << "Swapuri: Amandoi algoritmii sunt la fel de eficienti" << endl;

    if (compQ.execT < compM.execT)
        cout << "Timp: QuickSort este mai rapid cu " << (compM.execT - compQ.execT) << " ms." << endl;
    else if (compM.execT < compQ.execT)
        cout << "Timp: MergeSort este mai rapid cu " << (compQ.execT - compM.execT) << " ms." << endl;
    else
        cout << "Timp: Amandoi algoritmii sunt aproximativ la fel de eficienti." << endl;

    int quickPuncte = 0, mergePuncte = 0;
    if (compQ.comparatii < compM.comparatii) quickPuncte++;
    else if (compM.comparatii < compQ.comparatii) mergePuncte++;
    
    if (compQ.swaps < compM.swaps) quickPuncte++;
    else if (compM.swaps < compQ.swaps) mergePuncte++;
    
    if (compQ.execT < compM.execT) quickPuncte++;
    else if (compM.execT < compQ.execT) mergePuncte++;

    cout << "\nEficienta generala: ";
    if (quickPuncte > mergePuncte)
        cout << "QuickSort este, in mare, mai eficient (avantaj: " << quickPuncte - mergePuncte << " punct(e))." << endl;
    else if (mergePuncte > quickPuncte)
        cout << "MergeSort este, in mare, mai eficient (avantaj: " << mergePuncte - quickPuncte << " punct(e))." << endl;
    else
        cout << "Amandoi algoritmii sunt, in mare, la fel de eficienti (diferenta de 0 puncte)." << endl;
    
    salvare(v1, n);

    char visualize;
    cout << "\nDoriti sa accesati vizualizarea ambelor metode de sortare? (y/n): ";
    cin >> visualize;
    if (tolower(visualize) == 'y') {
        if (n > 10) {
            cout << "\nVizualizarea este limitata la maxim 10 elemente.\n";
            cout << "Enter pentru a merge inapoi la meniu";
            cin.ignore();
            cin.get();
            return;
        }

        cout << CLEAR_SCREEN;
        
        const int inaltimemax = 20;
        int val_max = 0;
        for (int i = 0; i < n; i++) if (v[i] > val_max) val_max = v[i];
        
        int temp1[MAX_SIZE], temp2[MAX_SIZE];
        for (int i = 0; i < n; i++) {
            temp1[i] = v[i];
            temp2[i] = v[i];
        }
        
        int quicksort_iteratii = 0, mergesort_iteratii = 0;
        bool quicksort_sortat = false, mergesort_sortat = false;
        struct stagiu_quick { int st, dr, pivot_pislaru; bool partitionat; };
        struct stagiu_merge { int st, dr, m; bool merged; };
        stagiu_quick qstiva_osi[MAX_SIZE];
        stagiu_merge mstiva_osi[MAX_SIZE];
        int qtop = -1, mtop = -1;
        qtop++;
        qstiva_osi[qtop].st = 0;
        qstiva_osi[qtop].dr = n - 1;
        qstiva_osi[qtop].pivot_pislaru = -1;
        qstiva_osi[qtop].partitionat = false;
        mtop++;
        mstiva_osi[mtop].st = 0;
        mstiva_osi[mtop].dr = n - 1;
        mstiva_osi[mtop].m = -1;
        mstiva_osi[mtop].merged = false;

        int overall_step = 0;
        while (!quicksort_sortat || !mergesort_sortat) {
            if (overall_step > 0) cout << CLEAR_SCREEN;
            cout << "Pas " << overall_step + 1 << ":\n";

            if (!quicksort_sortat && qtop >= 0) {
                stagiu_quick& curent = qstiva_osi[qtop];
                int st = curent.st, dr = curent.dr;
                if (!curent.partitionat && st < dr) {
                    int pivot = temp1[dr];
                    int i = st - 1;
                    for (int j = st; j < dr; j++) {
                        if (temp1[j] < pivot) {
                            i++;
                            swap(temp1[i], temp1[j]);
                        }
                    }
                    swap(temp1[i + 1], temp1[dr]);
                    curent.pivot_pislaru = i + 1;
                    curent.partitionat = true;
                    quicksort_iteratii++;
                } else {
                    int p = curent.pivot_pislaru;
                    qtop--;
                    if (p - 1 > st) {
                        qtop++;
                        qstiva_osi[qtop].st = st;
                        qstiva_osi[qtop].dr = p - 1;
                        qstiva_osi[qtop].pivot_pislaru = -1;
                        qstiva_osi[qtop].partitionat = false;
                    }
                    if (p + 1 < dr) {
                        qtop++;
                        qstiva_osi[qtop].st = p + 1;
                        qstiva_osi[qtop].dr = dr;
                        qstiva_osi[qtop].pivot_pislaru = -1;
                        qstiva_osi[qtop].partitionat = false;
                    }
                }
                quicksort_sortat = true;
                for (int i = 1; i < n; i++) if (temp1[i-1] > temp1[i]) quicksort_sortat = false;
            }

            if (!mergesort_sortat && mtop >= 0) {
                stagiu_merge& curent = mstiva_osi[mtop];
                int st = curent.st, dr = curent.dr;
                if (!curent.merged && st < dr) {
                    curent.m = (st + dr) / 2;
                    if (curent.m > st) {
                        mtop++;
                        mstiva_osi[mtop].st = st;
                        mstiva_osi[mtop].dr = curent.m;
                        mstiva_osi[mtop].m = -1;
                        mstiva_osi[mtop].merged = false;
                    }
                    if (curent.m + 1 < dr) {
                        mtop++;
                        mstiva_osi[mtop].st = curent.m + 1;
                        mstiva_osi[mtop].dr = dr;
                        mstiva_osi[mtop].m = -1;
                        mstiva_osi[mtop].merged = false;
                    }
                    curent.merged = true;
                } else {
                    mtop--;
                    int m = curent.m;
                    int i = st, j = m + 1, k = 0;
                    int tmp_local[MAX_SIZE];
                    while (i <= m && j <= dr) tmp_local[k++] = (temp2[i] < temp2[j]) ? temp2[i++] : temp2[j++];
                    while (i <= m) tmp_local[k++] = temp2[i++];
                    while (j <= dr) tmp_local[k++] = temp2[j++];
                    for (i = st, k = 0; i <= dr; i++) temp2[i] = tmp_local[k++];
                    mergesort_iteratii++;
                }
                mergesort_sortat = true;
                for (int i = 1; i < n; i++) if (temp2[i-1] > temp2[i]) mergesort_sortat = false;
            }

            for (int inaltime = inaltimemax; inaltime >= 1; inaltime--) {
                for (int i = 0; i < n; i++) {
                    int scalat1 = (temp1[i] * inaltimemax) / (val_max ? val_max : 1);
                    if (scalat1 >= inaltime) {
                        if (qtop >= 0 && i == qstiva_osi[qtop].pivot_pislaru) cout << "P";
                        else if (qtop >= 0 && i >= qstiva_osi[qtop].st && i <= qstiva_osi[qtop].dr) cout << "|";
                        else cout << "S";
                    } else cout << " ";
                }
                cout << "                          ";
                for (int i = 0; i < n; i++) {
                    int scalat2 = (temp2[i] * inaltimemax) / (val_max ? val_max : 1);
                    if (scalat2 >= inaltime) {
                        if (mtop >= 0 && i >= mstiva_osi[mtop].st && i <= mstiva_osi[mtop].dr) cout << "M";
                        else cout << "S";
                    } else cout << " ";
                }
                cout << endl;
            }
            for (int i = 0; i < n; i++) cout << "_";
            cout << "                          ";
            for (int i = 0; i < n; i++) cout << "_";
            cout << endl;
            for (int i = 0; i < n; i++) cout << (temp1[i] % 10);
            cout << "                          ";
            for (int i = 0; i < n; i++) cout << (temp2[i] % 10);
            cout << endl << endl;

            cout << "iteratii QuickSort: " << quicksort_iteratii << (quicksort_sortat ? " (rezolvat)" : "") << "   ";
            cout << "iteratii MergeSort: " << mergesort_iteratii << (mergesort_sortat ? " (rezolvat)" : "") << endl << endl;

            overall_step++;
            clock_t start = clock();
            while ((clock() - start) < (0.3 * CLOCKS_PER_SEC));
        }

        cout << "Sortare finalizata. QuickSort: " << quicksort_iteratii 
             << " iteratii, MergeSort: " << mergesort_iteratii 
             << " iteratii. Enter pentru a merge inapoi la meniu.";
        cin.get();
    }
}


void procesare(int v[], int n) {
    char choice;
    cout << "Alegeti algoritmul de sortare (q - QuickSort, m - MergeSort, c - Compara ambele): ";
    cin >> choice;
    
    int v_original[MAX_SIZE];
    for (int i = 0; i < n; i++) {
        v_original[i] = v[i];
    }

    int v_uz[MAX_SIZE];
    for (int i = 0; i < n; i++) {
        v_uz[i] = v[i];
    }

    if (tolower(choice) == 'c') {
        comparatie(v_original, n);
    } else {
        complexitate comp;
        prompt_sortare(v_uz, n, choice, comp);
        cout << "\nLista sortata: ";
        for (int i = 0; i < n; i++)
            cout << v_uz[i] << " ";
        cout << endl;
        displaycomplexitate(comp, (tolower(choice) == 'q' ? "QuickSort" : "MergeSort"), n);
        salvare(v_uz, n);
        
        char visualize;
        cout << "\nDoriti sa accesati vizualizarea sortarii? (y/n): ";
        cin >> visualize;
        if (tolower(visualize) == 'y') {
            cout << CLEAR_SCREEN;
            vizualizare(v_original, n, (tolower(choice) == 'q' ? "QuickSort" : "MergeSort"));
        }
    }
}

void terminal() {
    int v[MAX_SIZE], n;
    cout << "Introduceti numarul de elemente (n): ";
    cin >> n;
    cout << "Introduceti elementele: ";
    for (int i = 0; i < n; i++)
        cin >> v[i];
    
    procesare(v, n);
}

void fisier() {
    string inputFile;
    cout << "Introduceti pathul fisierului: ";
    cin >> inputFile;
    ifstream fin(inputFile);
    if (!fin) {
        cout << "eroare: path incorect (enter pentru meniu)" << endl;
        cin.get();
        return;
    }
    int v[MAX_SIZE], n = 0;
    while (fin >> v[n] && n < MAX_SIZE)
        n++;
    fin.close();
    
    procesare(v, n);
}

int main() {
    while (true) {
        cout << CLEAR_SCREEN;
        meniu();

        char intrare;
        cin >> intrare;
        cin.ignore();
        intrare = tolower(intrare);

        cout << CLEAR_SCREEN;

        switch (intrare) {
        case 's':
            terminal();
            break;
        case 'f':
            fisier();
            break;
        case 'q':
            cout << CLEAR_SCREEN;
            cout << "exiting." << endl;
            return 0;
        default:
            cout << "optiune invalida (enter)" << endl;
        }
        cin.get();
    }
}


