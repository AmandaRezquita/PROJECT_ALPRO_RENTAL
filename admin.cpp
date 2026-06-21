#include "umum.cpp"

using namespace std;

void bersihkanLayar();
void jedaTampilan();

void createBarang()
{
    bersihkanLayar();
    cout << "\n";
    cout << "   -----------------------------------------------\n";
    cout << "   |            I N P U T  B A R A N G           |\n";
    cout << "   -----------------------------------------------\n"
         << endl;
    cout << "   Nama Barang         : ";
    clearBuffer();
    getline(cin, daftarBarang[jumlahBarang].nama);
    cout << "\n   URL Gambar          : ";
    getline(cin, daftarBarang[jumlahBarang].url);
    cout << "\n   Jenis               : ";
    getline(cin, tempJenis);
    cout << "\n   Merk                : ";
    getline(cin, tempMerk);
    cout << "\n   Deskripsi           : ";
    getline(cin, tempDeskripsi);
    daftarBarang[jumlahBarang].deskripsi = "Jenis    : " + tempJenis + "\n                   Merk     : " + tempMerk + "\n                   Catatan  : " + tempDeskripsi;
    cout << "\n   Harga               : ";
    cin >> daftarBarang[jumlahBarang].harga;
    daftarBarang[jumlahBarang].available = true;
    jumlahBarang++;
    cout << BLUE << "\n   [Barang berhasil ditambahkan!]" << RESET;
    cout << endl;
    jedaTampilan();
}

void readBarang()
{
    int subPilih = 0;
    int key;
    do
    {
        bersihkanLayar();
        cout << "\n";
        cout << "   -----------------------------------------------\n";
        cout << "   |           D A F T A R  B A R A N G          |\n";
        cout << "   -----------------------------------------------\n";

        if (jumlahBarang == 0)
            cout << "\n   [Data kosong!]";
        for (int i = 0; i < jumlahBarang; i++)
        {
            cout << "\n   -----------------------------------------------" << endl;
            cout << "\n   " << i + 1 << ". Nama       : " << daftarBarang[i].nama << endl;
            cout << "\n      Harga      : Rp" << daftarBarang[i].harga << endl;
            cout << "\n      Status     : " << (daftarBarang[i].available ? "Tersedia" : "Sedang Disewa") << endl;
            cout << "\n      Deskripsi  : " << daftarBarang[i].deskripsi << endl;
            cout << "\n      " << BLUE << "\033]8;;" << daftarBarang[i].url << "\033\\Foto Produk\033]8;;\033\\" << RESET << endl;
        }

        cout << "\n   ================================================" << endl;
        string menu[] = {"Cari Barang", "Filter Barang", "Sortir Barang", "kembali"};
        for (int i = 0; i < 4; i++)
        {
            cout << endl
                 << "               " << (i == subPilih ? "\033[36m>> " : "   ") << menu[i] << "\033[0m" << endl;
        }
        cout << "\n   ================================================" << endl;

        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                subPilih = (subPilih == 0) ? 4 : subPilih - 1;
            else if (key == 80)
                subPilih = (subPilih == 4) ? 0 : subPilih + 1;
        }
    } while (key != 13);

    if (subPilih == 0)
    {
        // fungsi cari
    }
    else if (subPilih == 1)
    {
        menuFilterBarang();
    }
    else if (subPilih == 2)
    {
        menuSortirBarang();
    }
    else
    {
        _getch();
    }
}

void id_barang()
{
    for (int i = 0; i < jumlahBarang; i++)
    {
        cout << "\n   " << i + 1 << ". " << daftarBarang[i].nama << endl;
    }
    cout << "\n   -----------------------------------------------" << endl;
}

void edit_Barang(int i)
{
    bersihkanLayar();
    cout << "\n";
    cout << "   -----------------------------------------------\n";
    cout << "   |             E D I T   B A R A N G           |\n";
    cout << "   -----------------------------------------------\n";

    cout << "\n   " << i + 1 << ". Nama       : " << daftarBarang[i].nama << endl;
    cout << "\n      Harga      : Rp" << daftarBarang[i].harga << endl;
    cout << "\n      Status     : " << (daftarBarang[i].available ? "Tersedia" : "Sedang Disewa") << endl;
    cout << "\n      Deskripsi  : " << daftarBarang[i].deskripsi << endl;
    cout << "\n      " << BLUE << "\033]8;;" << daftarBarang[i].url << "\033\\Foto Produk\033]8;;\033\\" << RESET << endl;
    cout << "\n   -----------------------------------------------" << endl;

    cout << "\n   Nama Baru      : ";
    clearBuffer();
    getline(cin, daftarBarang[i].nama);
    cout << "\n   URL Baru       : ";
    getline(cin, daftarBarang[i].url);
    cout << "\n   Jenis Baru     : ";
    getline(cin, tempJenis);
    cout << "\n   Merk Baru      : ";
    getline(cin, tempMerk);
    cout << "\n   Deskripsi Baru : ";
    getline(cin, tempDeskripsi);
    daftarBarang[jumlahBarang].deskripsi = "Jenis    : " + tempJenis + "\n                   Merk     : " + tempMerk + "\n                   Catatan  : " + tempDeskripsi;
    cout << "\n   Harga Baru     : ";
    cin >> daftarBarang[i].harga;
    cout << BLUE << "\n   [Data berhasil diupdate!]" << RESET;
}

void pilih_Barang_Edit()
{
    bersihkanLayar();
    int index;
    cout << "\n";
    cout << "   -----------------------------------------------\n";
    cout << "   |             E D I T   B A R A N G           |\n";
    cout << "   -----------------------------------------------\n";
    id_barang();
    cout << "\n   Masukkan nomor barang yang akan diupdate: ";
    clearBuffer();
    cin >> index;
    if (index > 0 && index <= jumlahBarang)
    {
        edit = index - 1;
        edit_Barang(edit);
    }
    else
    {
        cout << "\n   [Indeks tidak valid!]";
    }
    cout << '\n';
    jedaTampilan();
}

void deleteBarang()
{
    bersihkanLayar();
    int index;
    cout << "\n";
    cout << "   -----------------------------------------------\n";
    cout << "   |            H A P U S  B A R A N G           |\n";
    cout << "   -----------------------------------------------\n";
    id_barang();
    cout << "\n   Masukkan nomor barang yang akan dihapus: ";
    clearBuffer();
    cin >> index;
    if (index > 0 && index <= jumlahBarang)
    {
        for (int i = index - 1; i < jumlahBarang - 1; i++)
        {
            daftarBarang[i] = daftarBarang[i + 1];
        }
        jumlahBarang--;
        cout << BLUE << "\n   [Barang berhasil dihapus!]" << RESET << endl;
    }
    else
    {
        cout << "\n   [Indeks tidak valid!]" << endl;
        ;
    }
    jedaTampilan();
}

void kelolaBarang()
{
    int subPilih = 0;
    int key;
    do
    {
        bersihkanLayar();
        cout << "\n";
        cout << "   ===============================================\n";
        cout << "   |                                             |\n";
        cout << "   |             D A T A  B A R A N G            |\n";
        cout << "   |                                             |\n";
        cout << "   ===============================================\n";
        cout << "   \033[36m[Jumlah Barang Tersedia : " << jumlahBarang << "]\033[0m\n";
        cout << "   -----------------------------------------------\n";
        string menu[] = {"Input Barang", "Lihat Barang", "Edit Barang", "Hapus Barang", "Kembali"};
        for (int i = 0; i < 5; i++)
        {
            cout << endl
                 << "                 " << (i == subPilih ? "\033[36m>> " : "   ") << menu[i] << "\033[0m" << endl;
        }
        cout << "\n   ===============================================\n";
        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                subPilih = (subPilih == 0) ? 4 : subPilih - 1;
            else if (key == 80)
                subPilih = (subPilih == 4) ? 0 : subPilih + 1;
        }
    } while (key != 13);

    switch (subPilih)
    {
    case 0:
        createBarang();
        kelolaBarang();
        break;
    case 1:
        readBarang();
        kelolaBarang();
        break;
    case 2:
        pilih_Barang_Edit();
        kelolaBarang();
        break;
    case 3:
        deleteBarang();
        kelolaBarang();
        break;
    case 4:
        dashboardAdmin();
    }
}

void menuKonfirmasiPengembalian()
{
    bersihkanLayar();
    cout << "\n   ===============================================\n";
    cout << "   |      K O N F I R M A S I  P E M B A L I A N |\n";
    cout << "   ===============================================\n";

    int indexDitemukan[100], count = 0;
    for (int i = 0; i < jumlahRiwayat; i++)
    {
        if (riwayatTransaksi[i].diajukan && !riwayatTransaksi[i].dikembalikan)
        {
            cout << "   " << count + 1 << ". User: " << riwayatTransaksi[i].pembeli
                 << " | Alat: " << riwayatTransaksi[i].barang << endl;
            indexDitemukan[count] = i;
            count++;
        }
    }

    if (count == 0)
    {
        cout << "\n   Tidak ada pengajuan pengembalian saat ini.\n";
    }
    else
    {
        int pilih;
        cout << "\n   Pilih transaksi untuk di-ACC (0 untuk batal): ";
        cin >> pilih;

        if (pilih > 0 && pilih <= count)
        {
            int targetIdx = indexDitemukan[pilih - 1];
            riwayatTransaksi[targetIdx].dikembalikan = true;

            for (int j = 0; j < jumlahBarang; j++)
            {
                if (daftarBarang[j].nama == riwayatTransaksi[targetIdx].barang)
                {
                    daftarBarang[j].available = true;
                    break;
                }
            }
            cout << "\n   [OK] Pengembalian berhasil dikonfirmasi!\n";
        }
    }
    lanjutTampilan();
}

void menuLaporanTransaksi()
{
    bersihkanLayar();
    double totalPendapatan = 0;
    cout << "\n   ===============================================\n";
    cout << "   |        L A P O R A N  T R A N S A K S I     |\n";
    cout << "   ===============================================\n";

    for (int i = 0; i < jumlahRiwayat; i++)
    {
        cout << "   " << i + 1 << ". [" << riwayatTransaksi[i].kode << "] "
             << riwayatTransaksi[i].pembeli << " - "
             << riwayatTransaksi[i].barang << " | Rp "
             << riwayatTransaksi[i].totalBayar << endl;
        totalPendapatan += riwayatTransaksi[i].totalBayar;
    }

    cout << "   -----------------------------------------------\n";
    cout << "   TOTAL PENDAPATAN : Rp " << totalPendapatan << endl;
    cout << "   ===============================================\n";
    lanjutTampilan();
}

void dashboardAdmin()
{
    int subPilih = 0;
    int key;
    do
    {
        bersihkanLayar();
        cout << "\n";
        cout << "   ===============================================\n";
        cout << "   |                                             |\n";
        cout << "   |        D A S H B O A R D  A D M I N         |\n";
        cout << "   |                                             |\n";
        cout << "   ===============================================\n";
        cout << setw(44) << "\033[36m[" << tanggal_sekarang << "]\033[0m\n";
        cout << "   -----------------------------------------------\n";

        string menu[] = {"Data Barang", "Konfirmasi Pengembalian", "Laporan Transaksi", "Logout"};
        for (int i = 0; i < 4; i++)
        {
            cout << endl
                 << "            " << (i == subPilih ? "\033[36m>> " : "   ") << menu[i] << "\033[0m" << endl;
        }
        cout << "\n   ===============================================\n";
        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                subPilih = (subPilih == 0) ? 3 : subPilih - 1;
            else if (key == 80)
                subPilih = (subPilih == 3) ? 0 : subPilih + 1;
        }
    } while (key != 13);

    switch (subPilih)
    {
    case 0:
        kelolaBarang();
        dashboardAdmin();
        break;
    case 1:
        menuKonfirmasiPengembalian();
        dashboardAdmin();
        break;
    case 2:
        menuLaporanTransaksi();
        dashboardAdmin();
        break;
    case 4:
        cout << "   Apakah anda yakin ingin logout ? (y/n) ";
        cin >> yesorno;

        if (yesorno == 'y' || yesorno == 'Y')
        {
            cout << "\n   [Logout berhasil!]" << endl;
            lanjutTampilan();
            menuUtama();
        }
        else
            dashboardAdmin();
    }
}