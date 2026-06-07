// ========================================================================================
// AIEZR MQBT ARCHIVER v2.0-MULTI - UNIVERSAL DNA CAPSULE (OPEN SOURCE RELEASE)
// Standard: CNS 2.1 (Multi-File / Folder Archive Structure)
// Description: Multi-file parametric packaging with rapid TOC (Table of Contents) scanning.
// ----------------------------------------------------------------------------------------
// Principal Engineer   : R. Wahyu Wibisana
// Enterprise           : CV. Cahaya Bintang Engineering (CBEN) - cben.id | aiezr.com
// Headquarters         : Cimahi, Jawa Barat, Indonesia
// License              : MIT License (Open Source Educational Release)
// ----------------------------------------------------------------------------------------
// Layer 0 Foundation   : Allaah Subhaanahu Wata'aala, Laaillaahailallaah Muhammadan 
//                        Abduhu Warasulullaah, Al-Qur'an & Hadis (Ethical Governor)
// ========================================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

const string MAGIC_HEADER = "MQBT_ARC_V2";

// --- FASE 1: PENYERAPAN BINER & EKSTRAKSI DNA UNIVERSAL (LZW CORE) ---
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

// --- FASE 2: MESIN PEMICU REKONSTRUKSI (REGENERASI BINER LZW) ---
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

// --- FUNGSI 1: MENGEMAS SELURUH FOLDER (SEPERTI ZIP) ---
void pack_folder(const string& input_dir, const string& output_file) {
    if (!fs::exists(input_dir) || !fs::is_directory(input_dir)) {
        cerr << "[!] Direktori target tidak ditemukan!\n"; return;
    }

    struct FileKapsul {
        string nama_relatif;
        size_t ukuran_asli;
        vector<int> dna;
    };
    vector<FileKapsul> daftar_file;

    cout << "[*] Merayapi Wilayah: " << input_dir << "...\n";
    
    // 1. Serap semua file ke RAM
    for (const auto& entry : fs::recursive_directory_iterator(input_dir)) {
        if (entry.is_regular_file()) {
            string path_lengkap = entry.path().string();
            // Ambil path relatif agar struktur folder di dalam kapsul tetap terjaga
            string path_relatif = fs::relative(entry.path(), input_dir).string();
            
            // Konversi backslash Windows ke forward slash standar agar bisa cross-platform
            for(char& c : path_relatif) { if(c == '\\') c = '/'; }
            
            ifstream in(path_lengkap, ios::binary);
            string raw_binary((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
            in.close();

            FileKapsul fk;
            fk.nama_relatif = path_relatif;
            fk.ukuran_asli = raw_binary.size();
            fk.dna = extract_universal_dna(raw_binary); // Kompresi LZW
            
            daftar_file.push_back(fk);
            cout << "  -> " << path_relatif << " diserap.\n";
        }
    }

    // 2. Cetak Kapsul Multi-File (Penulisan Biner Berurutan)
    ofstream out(output_file, ios::binary);
    
    // Tulis Header & Jumlah File
    size_t header_len = MAGIC_HEADER.size();
    out.write(reinterpret_cast<const char*>(&header_len), sizeof(header_len));
    out.write(MAGIC_HEADER.data(), header_len);
    
    size_t jumlah_file = daftar_file.size();
    out.write(reinterpret_cast<const char*>(&jumlah_file), sizeof(jumlah_file));

    // Tulis DAFTAR ISI (TOC) di depan
    for (const auto& fk : daftar_file) {
        size_t nama_len = fk.nama_relatif.size();
        size_t dna_len = fk.dna.size();
        
        out.write(reinterpret_cast<const char*>(&nama_len), sizeof(nama_len));
        out.write(fk.nama_relatif.data(), nama_len);
        out.write(reinterpret_cast<const char*>(&fk.ukuran_asli), sizeof(fk.ukuran_asli));
        out.write(reinterpret_cast<const char*>(&dna_len), sizeof(dna_len));
    }

    // Tulis BLOK MATERI DNA
    for (const auto& fk : daftar_file) {
        out.write(reinterpret_cast<const char*>(fk.dna.data()), fk.dna.size() * sizeof(int));
    }
    out.close();

    cout << "\n[OK] KAPSUL " << output_file << " BERHASIL DICETAK! (Total: " << jumlah_file << " File)\n";
}

// --- FUNGSI 2: MEMBACA DAFTAR ISI TANPA EKSTRAKSI (SEPERTI UNZIP -L) ---
void list_archive(const string& input_file) {
    ifstream in(input_file, ios::binary);
    if (!in) { cerr << "[!] Kapsul tidak ditemukan!\n"; return; }

    size_t header_len;
    in.read(reinterpret_cast<char*>(&header_len), sizeof(header_len));
    string header(header_len, '\0');
    in.read(&header[0], header_len);

    if (header != MAGIC_HEADER) {
        cerr << "[!] BUKAN KAPSUL MQBT MULTI-FILE YANG VALID!\n"; return;
    }

    size_t jumlah_file;
    in.read(reinterpret_cast<char*>(&jumlah_file), sizeof(jumlah_file));

    cout << "\n[*] BUKU TAMU KAPSUL: " << input_file << " (Total: " << jumlah_file << " File)\n";
    cout << "--------------------------------------------------------\n";
    
    for (size_t i = 0; i < jumlah_file; i++) {
        size_t nama_len, ukuran_asli, dna_len;
        in.read(reinterpret_cast<char*>(&nama_len), sizeof(nama_len));
        string nama_relatif(nama_len, '\0');
        in.read(&nama_relatif[0], nama_len);
        
        in.read(reinterpret_cast<char*>(&ukuran_asli), sizeof(ukuran_asli));
        in.read(reinterpret_cast<char*>(&dna_len), sizeof(dna_len));
        
        cout << i + 1 << ". " << nama_relatif 
             << " | Asli: " << ukuran_asli << " B -> DNA: " << (dna_len * sizeof(int)) << " B\n";
    }
    cout << "--------------------------------------------------------\n";
    in.close();
}

// --- FUNGSI 3: MEMBONGKAR KAPSUL KE FOLDER (UNPACK DIR) ---
void unpack_folder(const string& input_file, const string& output_dir) {
    ifstream in(input_file, ios::binary);
    if (!in) { cerr << "[!] Kapsul tidak ditemukan!\n"; return; }

    size_t header_len;
    in.read(reinterpret_cast<char*>(&header_len), sizeof(header_len));
    string header(header_len, '\0');
    in.read(&header[0], header_len);

    if (header != MAGIC_HEADER) {
        cerr << "[!] BUKAN KAPSUL MQBT MULTI-FILE YANG VALID!\n"; return;
    }

    size_t jumlah_file;
    in.read(reinterpret_cast<char*>(&jumlah_file), sizeof(jumlah_file));

    cout << "\n[*] MEMBONGKAR KAPSUL: " << input_file << "...\n";

    // Struct untuk menyimpan data Daftar Isi sementara
    struct TOCEntry {
        string nama_relatif;
        size_t ukuran_asli;
        size_t dna_len;
    };
    vector<TOCEntry> toc;

    // 1. Baca Daftar Isi (TOC)
    for (size_t i = 0; i < jumlah_file; i++) {
        TOCEntry entry;
        size_t nama_len;
        in.read(reinterpret_cast<char*>(&nama_len), sizeof(nama_len));
        entry.nama_relatif.resize(nama_len);
        in.read(&entry.nama_relatif[0], nama_len);
        
        in.read(reinterpret_cast<char*>(&entry.ukuran_asli), sizeof(entry.ukuran_asli));
        in.read(reinterpret_cast<char*>(&entry.dna_len), sizeof(entry.dna_len));
        
        toc.push_back(entry);
    }

    // Pastikan folder tujuan tersedia
    fs::create_directories(output_dir);

    // 2. Baca Blok DNA dan Lakukan Rekonstruksi
    for (const auto& entry : toc) {
        vector<int> dna(entry.dna_len);
        in.read(reinterpret_cast<char*>(dna.data()), entry.dna_len * sizeof(int));
        
        // Rekonstruksi DNA kembali menjadi biner utuh
        string pulih = trigger_regeneration(dna);
        
        // Buat struktur sub-folder sesuai path relatifnya
        fs::path target_path = fs::path(output_dir) / entry.nama_relatif;
        fs::create_directories(target_path.parent_path());
        
        // Tulis file ke harddisk
        ofstream out(target_path.string(), ios::binary);
        out.write(pulih.data(), pulih.size());
        out.close();
        
        cout << "  -> [OK] " << entry.nama_relatif << " direkonstruksi.\n";
    }
    
    in.close();
    cout << "\n[*] REKONSTRUKSI SELESAI! (" << jumlah_file << " file dikembalikan ke folder '" << output_dir << "')\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "AIEZR MQBT MULTI-FILE ARCHIVER\n";
        cout << "----------------------------------\n";
        cout << "Pack Folder : mqbt-a.exe pack_dir <nama_folder_sumber> <output.mqbt>\n";
        cout << "Lihat Isi   : mqbt-a.exe list <file.mqbt>\n";
        cout << "Unpack Dir  : mqbt-a.exe unpack_dir <file.mqbt> <nama_folder_tujuan>\n";
        return 1;
    }

    string mode = argv[1];
    
    if (mode == "pack_dir" && argc >= 4) {
        pack_folder(argv[2], argv[3]);
    } 
    else if (mode == "list") {
        list_archive(argv[2]);
    }
    else if (mode == "unpack_dir" && argc >= 4) {
        unpack_folder(argv[2], argv[3]);
    }
    else {
        cout << "[!] Perintah tidak valid. Cek parameter argumen Anda.\n";
    }

    return 0;
}