# 🚀 GoRent: Sistem Manajemen Rental Kendaraan

GoRent adalah aplikasi konsol (Command Line Interface) berbasis C++ yang dirancang untuk mengotomatisasi sistem penyewaan kendaraan. Aplikasi ini menyediakan alur kerja yang terstruktur bagi **Admin** untuk manajemen inventaris & operasional, serta **User** untuk melakukan transaksi penyewaan secara mandiri dan interaktif.

---

## 🛠️ Fitur Utama

### 👑 Modul Admin (Pengelola)
* **Manajemen Barang (CRUD):** Tambah, edit, hapus, dan lihat detail kendaraan secara mudah.
* **Konfirmasi Pengembalian:** Verifikasi status kendaraan yang dikembalikan oleh penyewa untuk pembaruan stok otomatis.
* **Laporan Transaksi:** Analisis pendapatan perusahaan dengan ringkasan transaksi yang transparan.
* **Monitoring Penyewa:** Melacak data penyewa aktif dan histori peminjaman.

### 👤 Modul User (Penyewa)
* **Sewa Kendaraan:** Sistem pencarian kendaraan, filter, dan kalkulasi durasi sewa yang otomatis.
* **Manajemen Profil:** Pengisian data diri (Nama, No. HP, Alamat) sebagai syarat sah penyewaan.
* **Riwayat Sewa:** Melacak status pesanan dan melihat histori penyewaan pribadi di masa lalu.
* **Pengajuan Pengembalian:** Fitur untuk menandai selesainya masa sewa kendaraan.

---

## 📂 Arsitektur & Struktur Proyek

Proyek ini menggunakan modularisasi kode untuk kemudahan pemeliharaan:

| File | Deskripsi |
| :--- | :--- |
| `umum.cpp` | **Core:** Berisi deklarasi `struct` (Barang, User, Transaksi), variabel global, dan fungsi utility (warna ANSI, format tanggal). |
| `admin.cpp` | **Admin Logic:** Menangani dashboard admin, pengelolaan stok, dan pelaporan. |
| `user.cpp` | **User Logic:** Menangani alur pemesanan, pembayaran, dan profil pengguna. |

---

## 💻 Cara Menjalankan

### 1. Prasyarat
* Compiler C++ (Direkomendasikan **G++** atau **MinGW**).
* Terminal yang mendukung *ANSI Escape Sequences* (seperti Windows Terminal, Git Bash, atau VS Code Integrated Terminal).

### 2. Kompilasi & Eksekusi
Buka terminal pada direktori proyek Anda, lalu jalankan perintah berikut:

**Windows (Menggunakan G++):**
```bash
g++ admin.cpp -o gorent.exe
./gorent.exe
