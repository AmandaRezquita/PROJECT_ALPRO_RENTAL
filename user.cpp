#include "admin.cpp"

int hitungHari(int h, int b, int t)
{
    return h + (b * 30) + (t * 365);
}

void prosesPembayaran(Transaksi t)
{
    double uangDibayar, kembalian;
    bool pembayaranBerhasil = false;

    bersihkanLayar();
    printGoRent();
    cout << "\n   -----------------------------------------------\n";
    cout << "   |              P E M B A Y A R A N            |\n";
    cout << "   -----------------------------------------------\n";
    cout << "   Total Tagihan : Rp " << t.totalBayar << endl;
    cout << "   -----------------------------------------------\n";

    do
    {
        cout << "   Masukkan jumlah uang pembayaran : Rp ";
        cin >> uangDibayar;

        if (uangDibayar >= t.totalBayar)
        {
            kembalian = uangDibayar - t.totalBayar;
            pembayaranBerhasil = true;
        }
        else
        {
            cout << RED << "   [Error] Uang tidak cukup! Kekurangan: Rp "
                 << (t.totalBayar - uangDibayar) << RESET << endl;
            cout << "   Silakan masukkan jumlah yang benar.\n"
                 << endl;
        }
    } while (!pembayaranBerhasil);

    cout << "   -----------------------------------------------\n";
    cout << "   Status        : Pembayaran Berhasil!" << endl;
    cout << "   Kembalian     : Rp " << kembalian << endl;
    cout << "   -----------------------------------------------\n";
    riwayatTransaksi[jumlahRiwayat].kode = t.kode;
    riwayatTransaksi[jumlahRiwayat].pembeli = t.pembeli;
    riwayatTransaksi[jumlahRiwayat].barang = t.barang;
    riwayatTransaksi[jumlahRiwayat].totalBayar = t.totalBayar;
    riwayatTransaksi[jumlahRiwayat].dikembalikan = false;

    jumlahRiwayat++;
    cout << GREEN << "\n   [OK] Transaksi berhasil disimpan ke riwayat!" << RESET << endl;
    lanjutTampilan();
    dashboardUser();
}

void cetakNota(Transaksi t)
{
    bersihkanLayar();
    printGoRent();
    cout << "   -----------------------------------------------\n";
    cout << "   |             N O T A  P E S A N A N          |\n";
    cout << "   -----------------------------------------------\n";
    cout << "   ID Pesanan    : " << t.kode << endl;
    cout << "   User          : " << t.pembeli << endl;
    cout << "   Kendaraan     : " << t.barang << endl;
    cout << "   -----------------------------------------------\n";
    cout << "   Durasi        : " << t.totalDurasi << " Hari" << endl;
    cout << "   Total Tagihan : Rp " << t.totalBayar << endl;
    cout << "   ===============================================\n";
    cout << "   [ENTER] Lanjutkan Pembayaran | [ESC] Batalkan Pesanan\n";

    char key;
    do
    {
        key = _getch();
        if (key == 27)
        {
            cout << RED << "\n   [!] Pesanan dibatalkan." << RESET << endl;
            for (int i = 0; i < jumlahBarang; i++)
            {
                if (daftarBarang[i].nama == t.barang)
                {
                    daftarBarang[i].available = true;
                    break;
                }
            }

            jedaTampilan();
            dashboardUser();
            return;
        }
    } while (key != 13);
}

void prosesPesanan(string namaUser, Barang b)
{
    Transaksi t;
    t.pembeli = namaUser;
    t.barang = b.nama;
    t.kode = "TRX-" + namaUser.substr(0, 2);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    t.hariAwal = ltm->tm_mday;
    t.bulanAwal = 1 + ltm->tm_mon;
    t.tahunAwal = 1900 + ltm->tm_year;

    bersihkanLayar();
    printGoRent();
    cout << "\n   -----------------------------------------------\n";
    cout << "   |          S E W A  K E N D A R A A N         |\n";
    cout << "   -----------------------------------------------\n";
    cout << "      Nama       : " << b.nama << endl;
    cout << "\n      Harga      : Rp" << b.harga << endl;
    cout << "\n      Deskripsi  : " << b.deskripsi << endl;
    cout << "\n      " << BLUE << "\033]8;;" << b.url << "\033\\Foto Produk\033]8;;\033\\" << RESET << endl;
    cout << "   ===============================================\n";
    cout << "   Tanggal Mulai                      : "
         << t.hariAwal << "-" << t.bulanAwal << "-" << t.tahunAwal << endl;

    bool tanggalValid = false;
    do
    {
        cout << "   Input Tanggal Selesai (DD MM YYYY) : ";
        cin >> t.hariAkhir >> t.bulanAkhir >> t.tahunAkhir;

        int totalAwal = hitungHari(t.hariAwal, t.bulanAwal, t.tahunAwal);
        int totalAkhir = hitungHari(t.hariAkhir, t.bulanAkhir, t.tahunAkhir);

        int selisih = totalAkhir - totalAwal;

        if (selisih == 0)
        {
            t.totalDurasi = 1;
        }
        else
        {
            t.totalDurasi = selisih;
        }
        if (t.totalDurasi >= 1)
        {
            tanggalValid = true;
        }
        else
        {
            cout << RED << "   [Error] Tanggal tidak valid! Tanggal selesai tidak boleh sebelum tanggal mulai.\n"
                 << RESET
                 << endl;
        }
    } while (!tanggalValid);

    cout << "   -----------------------------------------------\n";
    t.totalBayar = t.totalDurasi * b.harga;
    tampilkanLoading();
    cetakNota(t);
    prosesPembayaran(t);
}

void pilihBarangUntukDipesan()
{
    int key;
    int daftarTersedia[100];
    int countTersedia = 0;

    for (int i = 0; i < jumlahBarang; i++)
    {
        if (daftarBarang[i].available == true)
        {
            daftarTersedia[countTersedia] = i;
            countTersedia++;
        }
    }

    if (countTersedia == 0)
    {
        cout << RED << "\n   [!] Maaf, tidak ada barang yang tersedia saat ini." << RESET << endl;
        jedaTampilan();
        return;
    }

    int subPilih_t = 0;

    do
    {
        bersihkanLayar();
        printGoRent();
        cout << "\n   -----------------------------------------------" << endl;
        cout << "   |          S E W A  K E N D A R A A N         |" << endl;
        cout << "   -----------------------------------------------" << endl;
        cout << endl;
        for (int i = 0; i < countTersedia; i++)
        {
            int idxAsli = daftarTersedia[i];
            cout << (i == subPilih_t ? BLUE "           >> " : "              ")
                 << left << setw(15) << daftarBarang[idxAsli].nama
                 << "- Rp" << daftarBarang[idxAsli].harga << RESET << endl;
            cout << endl;
        }

        cout << "   ===============================================" << endl;
        cout << "   [ENTER] Pilih | [ESC] Kembali" << endl;

        key = _getch();
        if (key == 224 || key == -32)
        {
            key = _getch();
            if (key == 72)
                subPilih_t = (subPilih_t == 0) ? countTersedia - 1 : subPilih_t - 1;
            else if (key == 80)
                subPilih_t = (subPilih_t == countTersedia - 1) ? 0 : subPilih_t + 1;
        }
        else if (key == 27)
        {
            dashboardUser();
            return;
        }
    } while (key != 13);

    int pilihanAkhir = daftarTersedia[subPilih_t];
    daftarBarang[pilihanAkhir].available = false;
    prosesPesanan(userList[user_id].akun.username, daftarBarang[pilihanAkhir]);
}

void lihatHistory()
{
    bersihkanLayar();
    printGoRent();
    cout << "\n   -----------------------------------------------\n";
    cout << "   |            R I W A Y A T  S E W A           |\n";
    cout << "   -----------------------------------------------\n";

    bool ada = false;
    for (int i = 0; i < jumlahRiwayat; i++)
    {
        if (riwayatTransaksi[i].pembeli == userList[user_id].akun.username)
        {
            cout << "   ID         : " << riwayatTransaksi[i].kode << endl;
            cout << "   Kendaraan  : " << riwayatTransaksi[i].barang << endl;

            cout << "   Status     : ";
            if (!riwayatTransaksi[i].dikembalikan)
            {
                cout << RED << "[BELUM DIKEMBALIKAN]" << RESET << endl;
            }
            else
            {
                cout << GREEN << "[SUDAH DIKEMBALIKAN]" << RESET << endl;
            }

            cout << "   -----------------------------------------------\n";
            ada = true;
        }
    }

    if (!ada)
        cout << RED << "   [!] Belum ada riwayat transaksi." << RESET << endl;
    lanjutTampilan();
}

void menuProfil()
{
    int subPilih = 0;
    int key;

    do
    {
        bersihkanLayar();
        printGoRent();
        cout << "\n   -----------------------------------------------\n";
        cout << "   |             P R O F I L  U S E R            |\n";
        cout << "   -----------------------------------------------\n";
        cout << "   Username      : " << userList[user_id].akun.username << endl;
        cout << "   Nama Lengkap  : " << (userList[user_id].data.profilLengkap ? userList[user_id].data.namaLengkap : "-") << endl;
        cout << "   No. Telepon   : " << (userList[user_id].data.profilLengkap ? userList[user_id].data.noTelp : "-") << endl;
        cout << "   Alamat        : " << (userList[user_id].data.profilLengkap ? userList[user_id].data.alamat : "-") << endl;
        cout << "   -----------------------------------------------\n";

        string menu[] = {"Edit Profil", "Kembali"};
        for (int i = 0; i < 2; i++)
        {
            cout << endl
                 << "   " << (i == subPilih ? "\033[36m>> " : "   ") << menu[i] << "\033[0m" << endl;
        }
        cout << "\n   -----------------------------------------------\n";

        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72 || key == 80)
                subPilih = (subPilih == 0) ? 1 : 0;
        }
    } while (key != 13);

    if (subPilih == 0)
    {
        clearBuffer();
        cout << "   Nama Lengkap : ";
        getline(cin, userList[user_id].data.namaLengkap);
        cout << "   No. Telepon  : ";
        getline(cin, userList[user_id].data.noTelp);
        cout << "   Alamat       : ";
        getline(cin, userList[user_id].data.alamat);

        userList[user_id].data.profilLengkap = true;
        cout << GREEN << "\n   [OK] Profil berhasil disimpan!" << RESET << endl;
        jedaTampilan();
    }
    else
    {
        jedaTampilan();
    }
}

void ajukanPengembalian()
{
    int indexDitemukan[100];
    int count = 0;
    for (int i = 0; i < jumlahRiwayat; i++)
    {
        if (riwayatTransaksi[i].pembeli == userList[user_id].akun.username &&
            !riwayatTransaksi[i].dikembalikan && !riwayatTransaksi[i].diajukan)
        {
            indexDitemukan[count] = i;
            count++;
        }
    }
    if (count == 0)
    {
        bersihkanLayar();
        printGoRent();
        cout << "\n   -----------------------------------------------" << endl;
        cout << "   |     A J U K A N  P E N G E M B A L I A N    |" << endl;
        cout << "   -----------------------------------------------" << endl;
        cout << RED <<"\n   [!] Tidak ada kendaraan yang perlu dikembalikan." << RESET << endl;
        jedaTampilan();
        return;
    }
    int subPilih = 0;
    char key;
    do
    {
        bersihkanLayar();
        printGoRent();
        cout << "\n   -----------------------------------------------" << endl;
        cout << "   |     A J U K A N  P E N G E M B A L I A N    |" << endl;
        cout << "   -----------------------------------------------" << endl;
        cout << endl;
        for (int i = 0; i < count; i++)
        {
            int idx = indexDitemukan[i];
            cout << (i == subPilih ? BLUE "   >> " : "      ")
                 << riwayatTransaksi[idx].barang << " (ID: "
                 << riwayatTransaksi[idx].kode << ")" << RESET << endl;
        }
        cout << "\n   ===============================================" << endl;
        cout << "   [ENTER] Ajukan | [ESC] Kembali" << endl;
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

    int targetIdx = indexDitemukan[subPilih];
    riwayatTransaksi[targetIdx].diajukan = true;

    cout << GREEN << "\n   [OK] Pengajuan berhasil dikirim!" << RESET << endl;
    cout << "\n   [!] Mohon tunggu admin memproses verifikasi Anda.\n";
    jedaTampilan();
}

void dashboardUser()
{
    int subPilih = 0;
    int key;
    do
    {
        bersihkanLayar();
        cout << "\n";
        printGoRent();
        cout << "   -----------------------------------------------\n";
        cout << CYAN << "   [Selamat datang : " << userList[user_id].akun.username << "]" << RESET << endl;
        cout << "   -----------------------------------------------\n";
        cout << "                                      " << GREEN << "[" << tanggal_sekarang << "]" << RESET << endl;

        string menu[] = {"Lihat Barang", "Profil Saya", "Sewa Kendaraan", "Riwayat Sewa", "Ajukan Pengembalian", "Logout"};
        for (int i = 0; i < 6; i++)
        {
            cout << endl
                 << "              " << (i == subPilih ? BLUE ">> " : "   ") << menu[i] << RESET << endl;
        }
        cout << "\n   ===============================================\n";
        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                subPilih = (subPilih == 0) ? 5 : subPilih - 1;
            else if (key == 80)
                subPilih = (subPilih == 5) ? 0 : subPilih + 1;
        }
    } while (key != 13);

    switch (subPilih)
    {
    case 0:
        readBarang(false);
        dashboardUser();
        break;
    case 1:
        menuProfil();
        dashboardUser();
        break;
    case 2:
        if (!userList[user_id].data.profilLengkap)
        {
            cout << RED << "   [!] PERINGATAN: Profil belum lengkap!" << RESET << endl;
            cout << "   Harap isi profil melalui menu 'Profil Saya' sebelum menyewa.\n";
            lanjutTampilan();
            dashboardUser();
        }
        else
        {
            pilihBarangUntukDipesan();
        }
        break;
    case 3:
        lihatHistory();
        dashboardUser();
        break;
    case 4:
        ajukanPengembalian();
        dashboardUser();
        break;
    case 5:
        cout << "   Apakah anda yakin ingin logout ? (y/n) ";
        cin >> yesorno;

        if (yesorno == 'y' || yesorno == 'Y')
        {
            cout << GREEN << "\n   [Logout berhasil!]" << RESET << endl;
            lanjutTampilan();
            menuUtama();
        }
        else
            dashboardUser();
    }
}