# AIEZR MQBT Archiver (Universal DNA Capsule) 🧬

![Version](https://img.shields.io/badge/version-2.0-blue)
![Standard](https://img.shields.io/badge/Standard-CNS_2.1-purple)
![C++](https://img.shields.io/badge/C++-17-green)
![License](https://img.shields.io/badge/License-MIT-orange)

> **Layer 0 Foundation (Ethical Governor):**
> *Allaah Subhaanahu Wata'aala, Laaillaahailallaah Muhammadan Abduhu Warasulullaah, Al-Qur'an & Hadis.*

**[ID]** **AIEZR MQBT Archiver** adalah rilis *Open Source* dari algoritma pengarsipan parametrik **CV. Cahaya Bintang Engineering (CBEN)**. Ini adalah mesin *Absolute Binary Byte-Pair / LZW* yang mendemonstrasikan pengemasan data menggunakan pendekatan Bio-Siber (Ekstraksi DNA Biner & Regenerasi Kapsul) tanpa kehilangan satu byte pun (*Zero Loss 100%*). Sistem ini dirilis dalam **Dua Varian Engine**:
1. **`mqbt-s` (Single Stream):** Spesialis *payload* ringan untuk file tunggal.
2. **`mqbt-a` (Archive Mode):** Spesialis *Cold Storage* multi-file untuk menelan folder raksasa lengkap dengan Daftar Isi (TOC) berkecepatan tinggi.

**[EN]** **AIEZR MQBT Archiver** is the *Open Source* release of the parametric archiving algorithm by **CV. Cahaya Bintang Engineering (CBEN)**. It is an *Absolute Binary Byte-Pair / LZW* engine demonstrating data packaging using a Bio-Cybernetic approach (Binary DNA Extraction & Capsule Regeneration) with absolute *Zero Loss 100%*. The system is released in **Two Engine Variants**:
1. **`mqbt-s` (Single Stream):** Lightweight payload specialist for single files.
2. **`mqbt-a` (Archive Mode):** Multi-file *Cold Storage* specialist to ingest giant folders complete with a high-speed Table of Contents (TOC).

---

## 🏛️ Identitas Enterprise / Enterprise Identity
* **Principal Engineer :** R. Wahyu Wibisana
* **Enterprise &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;:** CV. Cahaya Bintang Engineering (CBEN) - [cben.id](https://cben.id) | [aiezr.com](https://aiezr.com)
* **Headquarters &nbsp; &nbsp; &nbsp; :** Cimahi, West Java, Indonesia
* **License &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;:** MIT License (Open Source Educational Release)

---

## 🚀 Filosofi Arsitektur / Architecture Philosophy

**[ID]** Mesin ini dirancang dengan filosofi genetika: membaca file biner mentah, mengekstraksi polanya menjadi untaian urutan integer absolut (`vector<int>`), dan memicu rekonstruksi dinamis (Ledakan DNA) untuk mengembalikan materi fisik file persis seperti sedia kala (Solid State Vault).
**[EN]** This engine is designed around genetic philosophy: reading raw binary files, extracting patterns into a strand of absolute integer sequences (`vector<int>`), and triggering dynamic reconstruction (DNA Burst) to restore the physical material of the file exactly as it was (Solid State Vault).

---

## 🛠️ Cara Kompilasi / Compilation Guide (Build)

**[ID]** Pastikan Anda memiliki compiler GCC/MinGW (wajib mendukung **C++17**).
**[EN]** Ensure you have a GCC/MinGW compiler (**C++17** standard is required).

```bash
# Compile Varian Single (mqbt-s)
g++ -O3 mqbt-s.cpp -o mqbt-s.exe

# Compile Varian Multi-File Archive (mqbt-a)
g++ -O3 -std=c++17 mqbt-a.cpp -o mqbt-a.exe

💻 Cara Penggunaan / Usage Guide (CLI)
1️⃣ Varian mqbt-s (Single Stream Mode)
[ID] Mengemas dan membongkar file satuan. / [EN] Pack and unpack single files.

Pack: mqbt-s.exe pack "dokumen.pdf" "rahasia.mqbt"

Unpack: mqbt-s.exe unpack "rahasia.mqbt" "dokumen_pulih.pdf"

2️⃣ Varian mqbt-a (Multi-File Archive Mode)
[ID] Mengemas folder, melihat daftar isi, dan membongkar folder. / [EN] Pack directories, view TOC, and unpack directories.

Pack Folder: mqbt-a.exe pack_dir "Folder_Proyek" "Arsip_Proyek.mqbt"

List Archive: mqbt-a.exe list "Arsip_Proyek.mqbt"

Unpack Folder: mqbt-a.exe unpack_dir "Arsip_Proyek.mqbt" "Folder_Pulih"