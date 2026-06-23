#include "umum.cpp"

void createBarang()
{
    clearBuffer();
    bersihkanLayar();
    printGoRent();
    cout << "\n -----------------------------------------------\n";
    cout << " |              I N P U T  B A R A N G         |\n";
    cout << " -----------------------------------------------\n\n";

    daftarBarang[jumlahBarang].nama = getValidatedInput("   Nama Barang         : ");
    daftarBarang[jumlahBarang].url  = getValidatedInput("\n   URL Gambar          : ");
    
    bool jenisValid = false;
    do
    {
        tempJenis = getValidatedInput("\n   Jenis (Mobil/Motor) : ");
        string cekJenis = tempJenis;
        for (int i = 0; i < cekJenis.length(); i++) cekJenis[i] = tolower(cekJenis[i]);

        if (cekJenis == "mobil" || cekJenis == "motor")
        {
            tempJenis = (cekJenis == "mobil" ? "Mobil" : "Motor");
            jenisValid = true;
        }
        else
        {
            cout << RED << "   [!] Input salah! Masukkan 'Mobil' atau 'Motor'." << RESET << endl;
        }
    } while (!jenisValid);

    tempMerk = getValidatedInput("\n   Merk                : ");
    tempDeskripsi = getValidatedInput("\n   Deskripsi           : ");

    daftarBarang[jumlahBarang].deskripsi = "Jenis     : " + tempJenis + "\n                   Merk      : " + tempMerk + "\n                   Catatan   : " + tempDeskripsi;

    bool inputValid = false;
    do
    {
        cout << "\n   Harga Sewa / Hari   : ";
        string hargaInput;
        getline(cin, hargaInput);
        
        if (hargaInput.empty()) {
            cout << RED << "   [!] Harga tidak boleh kosong!" << RESET << endl;
        } else {
            try {
                daftarBarang[jumlahBarang].harga = stoi(hargaInput);
                if (daftarBarang[jumlahBarang].harga > 0) inputValid = true;
                else cout << RED << "   [!] Harga harus lebih dari 0!" << RESET << endl;
            } catch (...) {
                cout << RED << "   [!] Input salah! Harap masukkan angka." << RESET << endl;
            }
        }
    } while (!inputValid);

    daftarBarang[jumlahBarang].available = true;
    jumlahBarang++;

    cout << GREEN << "\n   [Barang berhasil ditambahkan!]" << RESET << endl;
    jedaTampilan();
}

void readBarang(bool isAdmin)
{
    int subPilih = 0;
    int key;

    do
    {
        bersihkanLayar();
        printGoRent();
        cout << "\n";
        cout << "   -----------------------------------------------\n";
        cout << "   |             D A F T A R  B A R A N G        |\n";
        cout << "   -----------------------------------------------\n";

        bool adaBarang = false;
        int nomor = 1;

        for (int i = 0; i < jumlahBarang; i++)
        {
            if (!isAdmin && !daftarBarang[i].available)
            {
                continue;
            }

            adaBarang = true;
            cout << "   " << nomor++ << ". Nama       : " << daftarBarang[i].nama << endl;
            cout << "\n      Harga      : Rp " << daftarBarang[i].harga << endl;
            cout << "\n      Status     : " << (daftarBarang[i].available ? GREEN "Tersedia" RESET : RED "Sedang Disewa" RESET) << endl;
            cout << "\n      Deskripsi  : " << daftarBarang[i].deskripsi << endl;
            cout << "\n      " << BLUE << "\033]8;;" << daftarBarang[i].url << "\033\\Foto Produk\033]8;;\033\\" << RESET << endl;
            cout << "   -----------------------------------------------" << endl;
        }

        if (!adaBarang)
        {
            cout << RED << "\n   [!] Tidak ada barang tersedia untuk ditampilkan." << RESET << endl;
        }

        string menu[] = {"Cari Barang", "Filter Barang", "Sortir Barang", "Kembali"};
        for (int i = 0; i < 4; i++)
        {
            cout << endl
                 << "               " << (i == subPilih ? BLUE ">> " : "   ")
                 << menu[i] << RESET << endl;
        }
        cout << "\n   ================================================" << endl;
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
        cariBarang();
        break;
    case 1:
        menuFilterBarang();
        break;
    case 2:
        menuSortirBarang();
        break;
    case 3:
        return;
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
    printGoRent();
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
    cin.clear();
    cout << "\n   Nama Barang Baru    : ";
    getline(cin, daftarBarang[i].nama);

    cout << "\n   URL Gambar Baru     : ";
    getline(cin, daftarBarang[i].url);

    bool jenisValid = false;
    do
    {
        cout << "\n   Jenis (Mobil/Motor) : ";
        getline(cin, tempJenis);
        string cekJenis = tempJenis;
        for (int i = 0; i < cekJenis.length(); i++)
            cekJenis[i] = tolower(cekJenis[i]);

        if (cekJenis == "mobil")
        {
            tempJenis = "Mobil";
            jenisValid = true;
        }
        else if (cekJenis == "motor")
        {
            tempJenis = "Motor";
            jenisValid = true;
        }
        else
        {
            cout << RED << "   [!] Input salah! Masukkan 'Mobil' atau 'Motor'." << RESET << endl;
        }
    } while (!jenisValid);

    cout << "\n   Merk Baru           : ";
    getline(cin, tempMerk);

    cout << "\n   Deskripsi Baru      : ";
    getline(cin, tempDeskripsi);

    daftarBarang[i].deskripsi = "Jenis    : " + tempJenis + "\n                   Merk     : " + tempMerk + "\n                   Catatan  : " + tempDeskripsi;

    bool inputValid = false;
    do
    {
        cout << "\n   Harga Sewa / Hari   : ";
        if (!(cin >> daftarBarang[i].harga))
        {
            cout << "   " << RED << "[!] Input salah! Harap masukkan angka saja." << RESET << endl;
            clearBuffer();
        }
        else
        {
            inputValid = true;
            clearBuffer();
        }
    } while (!inputValid);
    cout << GREEN << "\n   [Data berhasil diupdate!]" << RESET << endl;
    jedaTampilan();
}

void pilih_Barang_Edit()
{
    int pilihIndex = 0;
    char key;

    do
    {
        bersihkanLayar();
        printGoRent();
        cout << "\n -----------------------------------------------" << endl;
        cout << " |            PILIH BARANG UNTUK DIEDIT        |" << endl;
        cout << " -----------------------------------------------" << endl;
        cout << endl;

        if (jumlahBarang == 0)
        {
            cout << RED << "   [!] Tidak ada barang yang bisa diedit." << RESET << endl;
            jedaTampilan();
            return;
        }

        for (int i = 0; i < jumlahBarang; i++)
        {
            cout << (i == pilihIndex ? BLUE "           >> " : "              ")
                 << i + 1 << ". " << daftarBarang[i].nama << RESET << endl;
            cout << endl;
        }
        cout << " ===============================================" << endl;
        cout << "\n [ENTER] Pilih | [ESC] Kembali" << endl;

        key = _getch();
        if (key == 224 || key == -32)
        {
            key = _getch();
            if (key == 72)
                pilihIndex = (pilihIndex == 0) ? jumlahBarang - 1 : pilihIndex - 1;
            else if (key == 80)
                pilihIndex = (pilihIndex == jumlahBarang - 1) ? 0 : pilihIndex + 1;
        }
        else if (key == 27)
            return;

    } while (key != 13);
    clearBuffer();

    edit = pilihIndex;
    edit_Barang(edit);
}

void deleteBarang()
{
    int pilihIndex = 0;
    char key;

    do
    {
        bersihkanLayar();
        printGoRent();
        cout << "\n   -----------------------------------------------" << endl;
        cout << "   |             H A P U S  B A R A N G          |" << endl;
        cout << "   -----------------------------------------------" << endl;
        cout << endl;

        if (jumlahBarang == 0)
        {
            cout << RED << "   [!] Tidak ada barang yang bisa dihapus." << RESET << endl;
            jedaTampilan();
            return;
        }

        for (int i = 0; i < jumlahBarang; i++)
        {
            cout << (i == pilihIndex ? RED "                 >> " : "                    ")
                 << i + 1 << ". " << daftarBarang[i].nama << RESET << endl;
            cout << endl;
        }
        cout << "   ================================================" << endl;
        cout << "\n   [ENTER] Hapus Barang | [ESC] Kembali" << endl;

        key = _getch();
        if (key == 224 || key == -32)
        {
            key = _getch();
            if (key == 72)
                pilihIndex = (pilihIndex == 0) ? jumlahBarang - 1 : pilihIndex - 1;
            else if (key == 80)
                pilihIndex = (pilihIndex == jumlahBarang - 1) ? 0 : pilihIndex + 1;
        }
        else if (key == 27)
            return;

    } while (key != 13);

    for (int i = pilihIndex; i < jumlahBarang - 1; i++)
    {
        daftarBarang[i] = daftarBarang[i + 1];
    }
    jumlahBarang--;

    cout << GREEN << "\n   [OK] Barang berhasil dihapus!" << RESET << endl;
    jedaTampilan();
}

void kelolaBarang()
{
    int subPilih = 0;
    int key;
    do
    {
        int totalTersedia = 0;
        int totalDisewa = 0;
        for (int i = 0; i < jumlahBarang; i++)
        {
            if (daftarBarang[i].available)
                totalTersedia++;
            else
                totalDisewa++;
        }
        bersihkanLayar();
        printGoRent();
        cout << "   ===============================================\n";
        cout << "   |                                             |\n";
        cout << "   |             D A T A  B A R A N G            |\n";
        cout << "   |                                             |\n";
        cout << "   ===============================================\n";
        cout << GREEN << "             [Jumlah Barang Tersedia : " << totalTersedia << "]" << RESET << endl;
        cout << RED << "          [Jumlah Barang Sedang DiSewa : " << totalDisewa << "]" << RESET << endl;
        cout << "   -----------------------------------------------\n";
        string menu[] = {"Input Barang", "Lihat Barang", "Edit Barang", "Hapus Barang", "Kembali"};
        for (int i = 0; i < 5; i++)
        {
            cout << endl
                 << "                 " << (i == subPilih ? BLUE ">> " : "   ") << menu[i] << RESET << endl;
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
        readBarang(true);
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
        return;
    }
}

void menuKonfirmasiPengembalian()
{
    Transaksi *daftarPengembalian[100];
    int count = 0;

    for (int i = 0; i < jumlahRiwayat; i++)
    {
        if (riwayatTransaksi[i].diajukan && !riwayatTransaksi[i].dikembalikan)
        {
            daftarPengembalian[count] = &riwayatTransaksi[i];
            count++;
        }
    }

    if (count == 0)
    {
        bersihkanLayar();
        printGoRent();
        cout << "\n   ====================================================" << endl;
        cout << "   |  K O N F I R M A S I  P E N G E M B A L I A N    |" << endl;
        cout << "   ====================================================" << endl;
        cout << RED << "\n   [!] Tidak ada pengajuan pengembalian saat ini." << RESET << endl;
        jedaTampilan();
        return;
    }

    int subPilih = 0;
    char key;

    do
    {
        bersihkanLayar();
        printGoRent();
        cout << "\n   ====================================================" << endl;
        cout << "   |  K O N F I R M A S I  P E N G E M B A L I A N    |" << endl;
        cout << "   ====================================================" << endl;
        cout << endl;
        for (int i = 0; i < count; i++)
        {
            cout << (i == subPilih ? BLUE "   >> " : "      ")
                 << "User: " << daftarPengembalian[i]->pembeli
                 << " | Kendaraan: " << daftarPengembalian[i]->barang << RESET << endl;
            cout << endl;
        }

        cout << "   ====================================================" << endl;
        cout << "   [ENTER] Konfirmasi (ACC) | [ESC] Kembali" << endl;

        key = _getch();
        if (key == 224 || key == -32)
        {
            key = _getch();
            if (key == 72)
                subPilih = (subPilih == 0) ? count - 1 : subPilih - 1;
            else if (key == 80)
                subPilih = (subPilih == count - 1) ? 0 : subPilih + 1;
        }
        else if (key == 27)
            return;

    } while (key != 13);

    Transaksi *pTarget = daftarPengembalian[subPilih];
    pTarget->dikembalikan = true;

    for (int j = 0; j < jumlahBarang; j++)
    {
        if (daftarBarang[j].nama == pTarget->barang)
        {
            daftarBarang[j].available = true;
            break;
        }
    }

    cout << GREEN << "\n   [OK] Pengembalian berhasil dikonfirmasi!" << RESET << endl;
    jedaTampilan();
}

void menuLaporanTransaksi()
{
    bersihkanLayar();
    printGoRent();
    double totalPendapatan = 0;
    cout << "\n   ===============================================\n";
    cout << "   |       L A P O R A N  T R A N S A K S I      |\n";
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

void daftarPenyewa()
{
    bersihkanLayar();
    printGoRent();
    cout << "\n   ==========================================================" << endl;
    cout << "   |              D A F T A R  P E N Y E W A                |" << endl;
    cout << "   ==========================================================" << endl;

    bool ditemukan = false;
    int nomor = 1;

    for (int i = 0; i < jumlahRiwayat; i++)
    {
        if (!riwayatTransaksi[i].dikembalikan)
        {
            ditemukan = true;
            int id_p = -1;
            for (int j = 0; j < jumlahUser; j++)
            {
                if (userList[j].akun.username == riwayatTransaksi[i].pembeli)
                {
                    id_p = j;
                    break;
                }
            }

            cout << "\n   " << nomor++ << ". Nama Barang : " << riwayatTransaksi[i].barang << endl;
            cout << "      Penyewa     : " << riwayatTransaksi[i].pembeli << endl;

            if (id_p != -1 && userList[id_p].data.profilLengkap)
            {
                cout << "      Nama Lengkap: " << userList[id_p].data.namaLengkap << endl;
                cout << "      No. HP      : " << userList[id_p].data.noTelp << endl;
            }
            else
            {
                cout << "      Profil      : [Profil belum dilengkapi]" << endl;
            }
            cout << "\n   ----------------------------------------------------------" << endl;
        }
    }

    if (!ditemukan)
        cout << RED << "\n   [!] Tidak ada data penyewa saat ini." << RESET << endl;

    jedaTampilan();
}

void dashboardAdmin()
{
    int subPilih = 0;
    int key;
    do
    {
        int countPending = 0;
        for (int i = 0; i < jumlahRiwayat; i++)
        {
            if (riwayatTransaksi[i].diajukan && !riwayatTransaksi[i].dikembalikan)
            {
                countPending++;
            }
        }

        bersihkanLayar();
        cout << "\n";
        printGoRent();
        cout << "   -----------------------------------------------------\n";
        cout << RED << "   [!] Pengembalian yang harus anda konfirmasi : " << countPending << RESET;
        cout << "\n   =====================================================\n";
        cout << "                                            " << CYAN << "[" << tanggal_sekarang << "]" << RESET;
        string menu[] = {"Data Barang", "Data Penyewa", "Konfirmasi Pengembalian", "Laporan Transaksi", "Logout"};
        for (int i = 0; i < 5; i++)
        {
            cout << endl
                 << "            " << (i == subPilih ? BLUE ">> " : "   ") << menu[i] << RESET << endl;
        }
        cout << "\n   ====================================================\n";
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
        kelolaBarang();
        dashboardAdmin();
        break;
    case 1:
        daftarPenyewa();
        dashboardAdmin();
        break;
    case 2:
        menuKonfirmasiPengembalian();
        dashboardAdmin();
        break;
    case 3:
        menuLaporanTransaksi();
        dashboardAdmin();
        break;
    case 4:
        cout << "   Apakah anda yakin ingin logout ? (y/n) ";
        cin >> yesorno;

        if (yesorno == 'y' || yesorno == 'Y')
        {
            cout << GREEN << "\n   [Logout berhasil!]" << RESET << endl;
            lanjutTampilan();
            menuUtama();
        }
        else
            dashboardAdmin();
    }
}