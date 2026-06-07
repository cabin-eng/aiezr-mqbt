// ========================================================================================
// AIEZR MQBT ARCHIVER v2.0 - UNIVERSAL DNA CAPSULE (OPEN SOURCE RELEASE)
// Standard: CNS 2.0 (Absolute Binary Byte-Pair / LZW Compression Engine)
// Description: Deterministic zero-loss binary extraction and regeneration.
// Mendukung ekstraksi polimorfik untuk SEMUA tipe file.
// ----------------------------------------------------------------------------------------
// Principal Engineer   : R. Wahyu Wibisana
// Enterprise           : CV. Cahaya Bintang Engineering (CBEN) - cben.id | aiezr.com
// Headquarters         : Cimahi, Jawa Barat, Indonesia
// License              : MIT License (Open Source Educational Release)
// ----------------------------------------------------------------------------------------
// Layer 0 Foundation   : Allaah Subhaanahu Wata'aala, Laaillaahailallaah Muhammadan 
//                        Abduhu Warasulullaah, Al-Qur'an & Hadist (Ethical Governor)
// ========================================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// --- FASE 1: PENYERAPAN BINER & EKSTRAKSI DNA UNIVERSAL ---
vector<int> extract_universal_dna(const string& raw_binary) {
    unordered_map<string, int> dictionary;
    // 1. Inisialisasi Kamus Genetik Dasar (256 Byte murni)
    for (int i = 0; i < 256; i++) {
        dictionary[string(1, char(i))] = i;
    }
    
    string w;
    vector<int> dna_sequence;
    int dictSize = 256;
    
    // 2. Pencarian Pola Polimorfik
    for (char c : raw_binary) {
        string wc = w + c;
        if (dictionary.count(wc)) {
            w = wc;
        } else {
            dna_sequence.push_back(dictionary[w]);
            dictionary[wc] = dictSize++; // Tambah Gen baru ke kamus
            w = string(1, c);
        }
    }
    if (!w.empty()) dna_sequence.push_back(dictionary[w]);
    
    return dna_sequence;
}

// --- FASE 2: MESIN PEMICU REKONSTRUKSI (REGENERASI BINER) ---
string trigger_regeneration(const vector<int>& dna_sequence) {
    if (dna_sequence.empty()) return "";
    
    unordered_map<int, string> dictionary;
    // 1. Bangun ulang Kamus Genetik Dasar
    for (int i = 0; i < 256; i++) {
        dictionary[i] = string(1, char(i));
    }
    
    int dictSize = 256;
    string w(1, char(dna_sequence[0]));
    string result = w;
    string entry;
    
    // 2. Ledakan DNA menjadi Materi Utuh
    for (size_t i = 1; i < dna_sequence.size(); i++) {
        int k = dna_sequence[i];
        if (dictionary.count(k)) {
            entry = dictionary[k];
        } else if (k == dictSize) {
            entry = w + w[0];
        } else {
            cerr << "[!] DNA Cacat (Decoherence terdeteksi)\n"; return "";
        }
        
        result += entry;
        dictionary[dictSize++] = w + entry[0];
        w = entry;
    }
    return result;
}

// --- OPERASI BACA/TULIS FILE KAPSUL (.mqbt) ---
void pack_file(const string& input_file, const string& output_file) {
    ifstream in(input_file, ios::binary);
    if(!in) { cerr << "[!] File asal tidak ditemukan!\n"; return; }
    string raw_binary((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    vector<int> dna = extract_universal_dna(raw_binary);

    ofstream out(output_file, ios::binary);
    size_t dna_len = dna.size();
    out.write(reinterpret_cast<const char*>(&dna_len), sizeof(dna_len));
    out.write(reinterpret_cast<const char*>(dna.data()), dna.size() * sizeof(int));
    out.close();

    cout << "\n[*] KAPSUL UNIVERSAL .mqbt BERHASIL DICETAK!\n";
    cout << "    Ukuran Asli Mentah : " << raw_binary.size() << " bytes\n";
    cout << "    Ukuran Rantai DNA  : " << (dna.size() * sizeof(int)) << " bytes\n";
}

void unpack_file(const string& input_file, const string& output_file) {
    ifstream in(input_file, ios::binary);
    if(!in) { cerr << "[!] Kapsul .mqbt tidak ditemukan!\n"; return; }
    
    size_t dna_len;
    in.read(reinterpret_cast<char*>(&dna_len), sizeof(dna_len));
    vector<int> dna(dna_len);
    in.read(reinterpret_cast<char*>(dna.data()), dna_len * sizeof(int));
    in.close();

    string pulih = trigger_regeneration(dna);

    ofstream out(output_file, ios::binary);
    out.write(pulih.data(), pulih.size());
    out.close();

    cout << "\n[*] KAPSUL .mqbt MELEDAK & REKONSTRUKSI SEMPURNA!\n";
    cout << "    Materi Pulih : " << pulih.size() << " bytes (Zero Loss)\n";
}

int main(int argc, char* argv[]) {
    cout << "=================================================\n";
    cout << " AIEZR MQBT UNIVERSAL ARCHIVER v2.0\n";
    cout << " Kemampuan: Binary DNA Extraction (Zero Loss)\n";
    cout << "=================================================\n";
    
    if(argc < 4) {
        cout << "Gunakan: mqbt_archiver.exe <pack/unpack> <input> <output>\n";
        return 1;
    }

    string mode = argv[1];
    string f_in = argv[2];
    string f_out = argv[3];

    if(mode == "pack") pack_file(f_in, f_out);
    else if(mode == "unpack") unpack_file(f_in, f_out);
    else cout << "[!] Perintah tidak valid.\n";

    return 0;
}