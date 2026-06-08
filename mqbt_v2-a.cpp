// ========================================================================================
// AIEZR MQBT ARCHIVER v2.02-WIN_UI - DISCRETE PARAMETRIC ANS (ZERO-LOSS)-(OPEN SOURCE RELEASE)
// Description: Open Source packing with UTF-8 DNA Preservation and Manifest Audit Log.
// ----------------------------------------------------------------------------------------
// Principal Engineer   : R. Wahyu Wibisana
// Enterprise           : CV. Cahaya Bintang Engineering (CBEN) - cben.id | aiezr.com
// Headquarters         : Cimahi, Jawa Barat, Indonesia
// License              : MIT License (Open Source Educational Release)
// ========================================================================================
// Layer 0 Foundation   : Allaah Subhaanahu Wata'aala, Laaillaahailallaah Muhammadan 
//                        Abduhu Warasulullaah, Al-Qur'an & Hadis (Ethical Governor)
// ========================================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <set>

using namespace std;
namespace fs = std::filesystem;

const string MAGIC_HEADER = "MQBT_ANS_V2"; 
const size_t MAX_BLOCK_SIZE = 1024 * 1024 * 1024; // 1 GB Chunks

// --- FUNGSI UI ---
string draw_progress(int pct, int width = 30) {
    if (pct < 0) pct = 0; if (pct > 100) pct = 100;
    int pos = (width * pct) / 100; string bar = "[";
    for (int i = 0; i < width; ++i) {
        if (i < pos) bar += "="; else if (i == pos) bar += ">"; else bar += " ";
    }
    bar += "]"; return bar;
}

// ========================================================================================
// JANTUNG AIEZR v2.02: DISCRETE PARAMETRIC ANS + TURBO O(1) LOOKUP
// ========================================================================================
struct ANSModel {
    uint32_t freqs[256] = {0}; uint32_t cum_freqs[257] = {0}; uint32_t M = 0;
    void build_model(const string& data) {
        uint64_t counts[256] = {0}; for(uint8_t b : data) counts[b]++;
        M = 16384; uint64_t total = data.size(); uint32_t current_M = 0;
        for(int i = 0; i < 256; i++) {
            if (counts[i] > 0) freqs[i] = max((uint64_t)1, (counts[i] * M) / total); else freqs[i] = 1;
            current_M += freqs[i];
        }
        while (current_M < M) { freqs[0]++; current_M++; }
        while (current_M > M) { for(int i = 0; i < 256; i++) { if(freqs[i] > 1 && current_M > M) { freqs[i]--; current_M--; } } }
        M = 0; for(int i = 0; i < 256; i++) { cum_freqs[i] = M; M += freqs[i]; } cum_freqs[256] = M;
    }
    void reconstruct_model() {
        M = 0; for(int i = 0; i < 256; i++) { cum_freqs[i] = M; M += freqs[i]; } cum_freqs[256] = M;
    }
};

class DiscreteParametricANS {
private:
    const uint64_t LOWER_BOUND = 1ull << 24; 
public:
    vector<uint8_t> encode(const string& data, ANSModel& model) {
        vector<uint8_t> out; uint64_t x = LOWER_BOUND; 
        for (int i = data.size() - 1; i >= 0; i--) {
            uint8_t s = static_cast<uint8_t>(data[i]); uint32_t fs = model.freqs[s];
            uint64_t x_max = (LOWER_BOUND / model.M) * 256 * fs;
            while (x >= x_max) { out.push_back(static_cast<uint8_t>(x & 0xFF)); x >>= 8; }
            x = (x / fs) * model.M + (x % fs) + model.cum_freqs[s];
        }
        for (int i = 0; i < 8; i++) out.push_back(static_cast<uint8_t>((x >> (i * 8)) & 0xFF));
        std::reverse(out.begin(), out.end()); return out;
    }

    string decode(const vector<uint8_t>& enc, ANSModel& model, size_t orig_len) {
        string out(orig_len, '\0'); if (enc.size() < 8) return out;
        vector<uint8_t> slot_to_symbol(model.M);
        for (int c = 0; c < 256; c++) {
            for (uint32_t i = model.cum_freqs[c]; i < model.cum_freqs[c+1]; i++) { slot_to_symbol[i] = static_cast<uint8_t>(c); }
        }
        uint64_t x = 0; for(int i = 0; i < 8; i++) x = (x << 8) | enc[i];
        size_t enc_ptr = 8;
        for (size_t i = 0; i < orig_len; i++) {
            uint32_t slot = x % model.M; uint8_t s = slot_to_symbol[slot]; out[i] = static_cast<char>(s);
            uint32_t fs = model.freqs[s]; uint32_t Cs = model.cum_freqs[s];
            x = fs * (x / model.M) + slot - Cs;
            while (x < LOWER_BOUND && enc_ptr < enc.size()) x = (x << 8) | enc[enc_ptr++];
        }
        return out;
    }
};

// ========================================================================================
// FUNGSI PENCUCI NAMA STRING-BASED (FOLDER AMAN 100%)
// ========================================================================================
string sanitize_and_truncate(const string& rel_path) {
    string clean_path = rel_path;
    string ilegal = "<>:\"|?*"; 
    
    // 1. Bersihkan Karakter Ilegal Tanpa Merusak Unicode/Simbol Engine
    for (char& c : clean_path) {
        if (ilegal.find(c) != string::npos) c = '_';
        if (c == '\\') c = '/';
    }
    
    // 2. Pisahkan Folder dan File
    size_t last_slash = clean_path.find_last_of('/');
    string folder_part = (last_slash != string::npos) ? clean_path.substr(0, last_slash + 1) : "";
    string file_part = (last_slash != string::npos) ? clean_path.substr(last_slash + 1) : clean_path;
    
    // 3. Pisahkan Nama File dan Ekstensi
    size_t last_dot = file_part.find_last_of('.');
    string stem = (last_dot != string::npos) ? file_part.substr(0, last_dot) : file_part;
    string ext = (last_dot != string::npos) ? file_part.substr(last_dot) : "";
    
    // 4. POTONG NAMA FILE SAJA (Folder Tetap Utuh 100%)
    if (stem.length() > 120) {
        stem = stem.substr(0, 120) + "~";
    }
    
    return folder_part + stem + ext;
}

struct PackFile { string nama_asli; string nama_aman; fs::path path_lengkap; size_t ukuran_asli; };
struct BlockData { vector<PackFile> files; size_t total_asli = 0; };

// --- FUNGSI 1: PACK ---
void pack_folder(const string& input_dir, const string& output_file) {
    if (!fs::exists(input_dir)) { cerr << "[!] Target tidak ditemukan!\n"; return; }
    
    cout << "\n=======================================================\n";
    cout << " [i] INISIASI SISTEM AIEZR MQBT v2.02 (PACKING RADAR)\n";
    cout << "=======================================================\n";
    
    vector<PackFile> temp_files; int file_bermasalah = 0;
    cout << " [*] Menjalankan Radar Pemindai Hulu...\n";
    
    fs::recursive_directory_iterator it;
    try { it = fs::recursive_directory_iterator(input_dir, fs::directory_options::skip_permission_denied); } 
    catch (...) { cerr << "[!] Gagal membuka direktori utama.\n"; return; }
    fs::recursive_directory_iterator end;

    while (it != end) {
        try {
            if (it->is_regular_file()) {
                fs::path p = it->path();
                string rel_str;
                
                // MANTRA UTF-8 (MEMPERTAHANKAN SIMBOL DERAJAT/UNICODE TANPA CRASH)
                try { rel_str = fs::relative(p, input_dir).u8string(); } 
                catch (...) { rel_str = fs::relative(p, input_dir).string(); }
                
                for(char& c : rel_str) { if(c == '\\') c = '/'; }
                
                string safe_rel = sanitize_and_truncate(rel_str);
                if (rel_str != safe_rel) file_bermasalah++;
                
                temp_files.push_back({rel_str, rel_str, p, fs::file_size(p)});
            }
            ++it;
        } catch (...) { try { ++it; } catch (...) { break; } } // Melompati file OS terkunci (thumbs.db dll)
    }

    bool use_autofix = false;
    if (file_bermasalah > 0) {
        cout << "\n [!] PERINGATAN: Ditemukan " << file_bermasalah << " file/folder melanggar batas Windows.\n";
        cout << " [1] OTOMATIS : Lakukan Virtual Auto-Fix dan Kompresi\n";
        cout << " [2] MANUAL   : Batalkan operasi\n";
        cout << " Pilihan (1/2): ";
        int pil; cin >> pil;
        if (pil != 1) { cout << " [i] Operasi Dibatalkan.\n"; return; }
        use_autofix = true;
    }

    auto start_time = chrono::high_resolution_clock::now();
    vector<BlockData> blocks; BlockData current_block; set<string> kapsul_names;

    for (auto& f : temp_files) {
        if (use_autofix) {
            string safe_name = sanitize_and_truncate(f.nama_asli);
            string final_name = safe_name;
            int counter = 1;
            while (kapsul_names.count(final_name)) {
                // Ekstrak folder part secara aman tanpa fs::path
                size_t ls = safe_name.find_last_of('/');
                string f_part = (ls != string::npos) ? safe_name.substr(0, ls + 1) : "";
                string n_part = (ls != string::npos) ? safe_name.substr(ls + 1) : safe_name;
                size_t ld = n_part.find_last_of('.');
                string stem = (ld != string::npos) ? n_part.substr(0, ld) : n_part;
                string ext = (ld != string::npos) ? n_part.substr(ld) : "";
                
                final_name = f_part + stem + "_salin" + to_string(counter) + ext;
                counter++;
            }
            f.nama_aman = final_name;
            kapsul_names.insert(final_name);
        }

        if (current_block.total_asli + f.ukuran_asli > MAX_BLOCK_SIZE && !current_block.files.empty()) {
            blocks.push_back(current_block); current_block = BlockData(); 
        }
        current_block.files.push_back(f); current_block.total_asli += f.ukuran_asli;
    }
    if (!current_block.files.empty()) blocks.push_back(current_block);

    ofstream out(output_file, ios::binary);
    size_t h_len = MAGIC_HEADER.size(), j_block = blocks.size();
    out.write(reinterpret_cast<const char*>(&h_len), sizeof(h_len));
    out.write(MAGIC_HEADER.data(), h_len);
    out.write(reinterpret_cast<const char*>(&j_block), sizeof(j_block));

    cout << "\n Berkas Terdeteksi: " << temp_files.size() << " File (File OS Terkunci Diabaikan)\n";
    cout << " Alokasi Memori   : " << j_block << " Blok Solid\n\n";

    size_t global_asli = 0, global_comp = 0;

    for (size_t b = 0; b < j_block; b++) {
        const auto& block = blocks[b];
        cout << " MEMPROSES [BLOK " << b + 1 << " / " << j_block << "]\n";
        string kolam_raksasa; kolam_raksasa.reserve(block.total_asli); 
        size_t f_count = block.files.size(); out.write(reinterpret_cast<const char*>(&f_count), sizeof(f_count));
        size_t bytes_read = 0; int last_io_pct = -1;

        for (const auto& f : block.files) {
            size_t n_len = f.nama_aman.size(); out.write(reinterpret_cast<const char*>(&n_len), sizeof(n_len));
            out.write(f.nama_aman.data(), n_len);
            size_t o_len = f.nama_asli.size(); out.write(reinterpret_cast<const char*>(&o_len), sizeof(o_len));
            out.write(f.nama_asli.data(), o_len);
            out.write(reinterpret_cast<const char*>(&f.ukuran_asli), sizeof(f.ukuran_asli));
            
            ifstream in(f.path_lengkap, ios::binary);
            kolam_raksasa.append((istreambuf_iterator<char>(in)), istreambuf_iterator<char>()); in.close();

            bytes_read += f.ukuran_asli; int pct = (bytes_read * 100) / block.total_asli;
            if (pct != last_io_pct && pct % 2 == 0) { cout << "\r    " << draw_progress(pct) << " " << setw(3) << pct << "% | I/O Disk -> RAM" << flush; last_io_pct = pct; }
        }
        cout << "\n";
        ANSModel model; model.build_model(kolam_raksasa);
        DiscreteParametricANS ans; vector<uint8_t> comp_data = ans.encode(kolam_raksasa, model);
        size_t comp_size = comp_data.size(); kolam_raksasa.clear(); 
        
        out.write(reinterpret_cast<const char*>(&block.total_asli), sizeof(block.total_asli));
        out.write(reinterpret_cast<const char*>(model.freqs), sizeof(model.freqs)); 
        out.write(reinterpret_cast<const char*>(&comp_size), sizeof(comp_size));
        out.write(reinterpret_cast<const char*>(comp_data.data()), comp_size);
        
        cout << "    [V] State X: " << comp_size / 1024 << " KB\n\n";
        global_asli += block.total_asli; global_comp += comp_size;
    }
    out.close();
    auto end_time = chrono::high_resolution_clock::now(); double t_sec = chrono::duration<double>(end_time - start_time).count();
    cout << "=======================================================\n";
    cout << " 🏆 AIEZR MQBT v2.02 REPORT\n";
    cout << " Waktu Eksekusi   : " << t_sec << " detik\n";
    cout << "=======================================================\n";
}

// --- FUNGSI 2: LIST ARCHIVE ---
void list_archive(const string& input_file) {
    ifstream in(input_file, ios::binary);
    if (!in) { cerr << "[!] Kapsul tidak ditemukan!\n"; return; }
    size_t h_len; in.read(reinterpret_cast<char*>(&h_len), sizeof(h_len));
    string header(h_len, '\0'); in.read(&header[0], h_len);
    if (header != MAGIC_HEADER) { cerr << "[!] FORMAT INVALID!\n"; return; }
    size_t j_block; in.read(reinterpret_cast<char*>(&j_block), sizeof(j_block));
    cout << "\n[*] BUKU TAMU KAPSUL: " << input_file << " (" << j_block << " Blok)\n-------------------------------------------------------\n";
    for (size_t b = 0; b < j_block; b++) {
        size_t j_file; in.read(reinterpret_cast<char*>(&j_file), sizeof(j_file));
        for (size_t i = 0; i < j_file; i++) {
            size_t l1, l2, u;
            in.read(reinterpret_cast<char*>(&l1), sizeof(l1)); in.seekg(l1, ios::cur);
            in.read(reinterpret_cast<char*>(&l2), sizeof(l2)); in.seekg(l2, ios::cur);
            in.read(reinterpret_cast<char*>(&u), sizeof(u));
        }
        size_t t, c; uint32_t df[256];
        in.read(reinterpret_cast<char*>(&t), sizeof(t)); in.read(reinterpret_cast<char*>(df), sizeof(df));
        in.read(reinterpret_cast<char*>(&c), sizeof(c)); in.seekg(c, ios::cur); 
    }
    cout << "Selesai membaca TOC.\n";
}

// --- FUNGSI 3: UNPACK ---
void unpack_folder(const string& input_file, const string& output_dir) {
    ifstream in(input_file, ios::binary);
    if (!in) { cerr << "[!] Kapsul tidak ditemukan!\n"; return; }
    size_t h_len; in.read(reinterpret_cast<char*>(&h_len), sizeof(h_len));
    string header(h_len, '\0'); in.read(&header[0], h_len);
    if (header != MAGIC_HEADER) { cerr << "[!] FORMAT INVALID!\n"; return; }

    size_t j_block; in.read(reinterpret_cast<char*>(&j_block), sizeof(j_block));
    cout << "\n=======================================================\n";
    cout << " [i] INISIASI SISTEM AIEZR MQBT v2.02 (UNPACKING)\n";
    cout << "=======================================================\n";

    fs::create_directories(output_dir); fs::path abs_out = fs::absolute(output_dir);
    struct AuditEntry { string asli; string ekstrak; }; vector<AuditEntry> audit_log;

    for (size_t b = 0; b < j_block; b++) {
        cout << " MEMBONGKAR [BLOK " << b + 1 << " / " << j_block << "]\n";
        size_t j_file; in.read(reinterpret_cast<char*>(&j_file), sizeof(j_file));
        struct TempTOC { string aman; string asli; size_t ukuran; }; vector<TempTOC> toc;
        
        for (size_t i = 0; i < j_file; i++) {
            size_t l1, l2, u; 
            in.read(reinterpret_cast<char*>(&l1), sizeof(l1)); string n1(l1, '\0'); in.read(&n1[0], l1);
            in.read(reinterpret_cast<char*>(&l2), sizeof(l2)); string n2(l2, '\0'); in.read(&n2[0], l2);
            in.read(reinterpret_cast<char*>(&u), sizeof(u)); toc.push_back({n1, n2, u});
        }
        
        size_t t_asli, c_size; ANSModel model;
        in.read(reinterpret_cast<char*>(&t_asli), sizeof(t_asli)); in.read(reinterpret_cast<char*>(model.freqs), sizeof(model.freqs)); 
        in.read(reinterpret_cast<char*>(&c_size), sizeof(c_size));
        
        vector<uint8_t> comp_data(c_size); in.read(reinterpret_cast<char*>(comp_data.data()), c_size);
        model.reconstruct_model(); DiscreteParametricANS ans; string kolam_pulih = ans.decode(comp_data, model, t_asli);
        
        size_t kursor = 0; int last_w_pct = -1; int b_sukses = 0, b_gagal = 0;

        for (size_t i = 0; i < toc.size(); i++) {
            const auto& f = toc[i]; string data_file = kolam_pulih.substr(kursor, f.ukuran); kursor += f.ukuran;
            fs::path tp = abs_out / f.aman;
            try { fs::create_directories(tp.parent_path()); } catch (...) {}
            
            if (fs::exists(tp)) {
                string stem = tp.stem().string(); string ext = tp.extension().string();   
                fs::path parent = tp.parent_path(); fs::path new_tp = parent / (stem + " (salin)" + ext);
                int counter = 1;
                while (fs::exists(new_tp)) { new_tp = parent / (stem + " (salin " + to_string(counter) + ")" + ext); counter++; }
                tp = new_tp; 
            }

            if (f.asli != f.aman) { audit_log.push_back({f.asli, f.aman}); }

            ofstream out(tp, ios::binary);
            if (!out) { b_gagal++; } else { out.write(data_file.data(), data_file.size()); out.close(); b_sukses++; }

            int pct = ((i + 1) * 100) / toc.size();
            if (pct != last_w_pct && pct % 2 == 0) { cout << "\r    " << draw_progress(pct) << " " << setw(3) << pct << "% | SSD Write" << flush; last_w_pct = pct; }
        }
        cout << "\n    [i] Ekstrak: " << b_sukses << " Berhasil | " << b_gagal << " Gagal\n\n";
    }

    if (!audit_log.empty()) {
        ofstream log_out(abs_out / "MQBT_Rename_Manifest.txt");
        log_out << "AIEZR MQBT v2.02 - MANIFEST AUDIT LOG\n=================================================\n";
        for (const auto& e : audit_log) { log_out << "ASLI: " << e.asli << "\nBARU: " << e.ekstrak << "\n-------------------------------------------------\n"; }
        log_out.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) { cout << "AIEZR MQBT ARCHIVER (v2.02 Enterprise)\n"; return 1; }
    string m = argv[1];
    if (m == "pack_dir") { pack_folder(argv[2], argv[3]); } else if (m == "unpack_dir") { unpack_folder(argv[2], argv[3]); } 
    return 0;
}