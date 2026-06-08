# AIEZR MQBT Archiver - v2.02 Enterprise 🧬

![Version](https://img.shields.io/badge/version-2.02--Enterprise-blue)
![Algorithm](https://img.shields.io/badge/Algorithm-Discrete_Parametric_ANS-purple)
![C++](https://img.shields.io/badge/C++-17-green)
![License](https://img.shields.io/badge/License-MIT-orange)

> **Layer 0 Foundation (Ethical Governor):**
> *Allaah Subhaanahu Wata'aala, Laaillaahailallaah Muhammadan Abduhu Warasulullaah, Al-Qur'an & Hadis.*

**[ID]** **AIEZR MQBT Archiver v2.02** adalah arsitektur pengarsipan data tingkat *Enterprise* yang dirancang oleh **CV. Cahaya Bintang Engineering (CBEN)**. Versi ini meninggalkan algoritma klasik LZW dan beralih menggunakan mesin **Discrete Parametric ANS (Asymmetric Numeral Systems)**. Sistem ini dirancang khusus untuk ekosistem *Engineering* guna menelan folder raksasa (Multi-Block 1 GB) dengan kecepatan tinggi, memproteksi DNA karakter *Unicode* (UTF-8), dan secara otomatis menyelamatkan file dari batasan nama ilegal OS Windows (*Virtual Auto-Fix*).

**[EN]** **AIEZR MQBT Archiver v2.02** is an *Enterprise-grade* data archiving architecture designed by **CV. Cahaya Bintang Engineering (CBEN)**. This version transcends classic LZW algorithms by utilizing a **Discrete Parametric ANS (Asymmetric Numeral Systems)** engine. It is specifically built for the engineering ecosystem to ingest giant folders (1 GB Multi-Block) at high speed, protect Unicode character DNA (UTF-8), and automatically rescue files from Windows OS illegal naming constraints (*Virtual Auto-Fix*).

---

## 🏛️ Identitas Enterprise / Enterprise Identity
* **Principal Engineer :** R. Wahyu Wibisana
* **Enterprise &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;:** CV. Cahaya Bintang Engineering (CBEN) - [cben.id](https://cben.id) | [aiezr.com](https://aiezr.com)
* **Headquarters &nbsp; &nbsp; &nbsp; :** Cimahi, West Java, Indonesia
* **Hotline &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;:** +62 821-2005-5558
* **Email &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;:** hotline@cben.id; rwahyuwibisana@cben.id
* **License &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;:** MIT License (Open Source Educational Release)

---

## 🌟 Fitur Utama / Key Features

1. **Discrete Parametric ANS Engine:** Pemerasan entropi data secara fraksional yang menekan *byte* mendekati Batas Shannon tanpa kehilangan satu *bit* pun (*100% Zero-Loss*).
2. **Turbo O(1) Lookup Decoder:** Proses dekompresi menggunakan peta memori instan (menghapus triliunan kalkulasi *looping* linear) sehingga kecepatan *Unpack* mengimbangi kecepatan tulis SSD.
3. **Bulletproof Pre-Pack Radar & Virtual Auto-Fix:** Radar heuristik yang memindai dan memotong nama file/folder yang melanggar batas 260 karakter Windows atau mengandung simbol ilegal, secara *virtual* saat di- *pack*, tanpa merusak file asli di dalam *storage*.
4. **Manifest Audit Log:** Sistem tata kelola data otomatis yang menerbitkan `MQBT_Rename_Manifest.txt` setelah proses ekstraksi, memberikan pemetaan transparan antara nama asli (*Illegal*) dan nama hasil pemulihan (*Safe*).

---

## 🛠️ Cara Kompilasi / Compilation Guide (Build)

**[ID]** Pastikan Anda memiliki compiler GCC/MinGW (wajib mendukung **C++17**). Engine ini 100% *native* tanpa ketergantungan *library* pihak ketiga.
**[EN]** Ensure you have a GCC/MinGW compiler (**C++17** standard is required). This engine is 100% native with zero third-party dependencies.

```bash
# Compile Varian Multi-File Archive (mqbt-a)
g++ -O3 -std=c++17 mqbt_v2-a.cpp -o mqbt-a.exe

💻 Cara Penggunaan / Usage Guide (CLI)

1. Mengemas Folder (Pack Directory)
[ID] Mengompresi seluruh isi folder menjadi satu kapsul .mqbt Solid State. Mesin akan menanyakan aktivasi Virtual Auto-Fix jika menemukan nama file yang berpotensi merusak OS.
[EN] Compresses an entire folder into a single .mqbt Solid State capsule. The engine will prompt for Virtual Auto-Fix activation if OS-breaking filenames are detected.

Pack Folder: mqbt-a.exe pack_dir "C:\Path\Ke\Folder_Proyek" "Arsip_Proyek.mqbt"

2. Melihat Daftar Isi (List Archive)
[ID] Membaca struktur Kapsul, jumlah blok, ukuran asli vs kompresi, dan daftar file tanpa melakukan ekstraksi.
[EN] Reads the Capsule structure, block count, original vs compressed size, and file list without extracting.

List Archive: mqbt-a.exe list "Arsip_Proyek.mqbt"


3. Membongkar Kapsul (Unpack Directory)
[ID] Mengekstraksi kapsul ke folder tujuan. Jika ada penyesuaian nama file selama packing, mesin akan menerbitkan Manifest Audit Log di dalam folder ini.
[EN] Extracts the capsule to the target folder. If filenames were adjusted during packing, the engine will publish a Manifest Audit Log inside this folder.

Unpack Folder: mqbt-a.exe unpack_dir "Arsip_Proyek.mqbt" "C:\Path\Ke\Folder_Proyek"